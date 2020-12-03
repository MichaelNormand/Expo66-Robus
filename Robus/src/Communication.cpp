#include "Communication.h"


SoftwareSerial SerialBT(HC_05_RX_PIN, HC_05_TX_PIN);
String incomingMessage = "";
String sendingMessage = "";
float positionX = IAROMYR_POSITION_X;
float positionY = IAROMYR_POSITION_Y;
float tempPositionY = 0;
float distanceToOrigin = 0;
void (*TriggerDistance)(float);
void (*TriggerAngleLeft)(float);
void (*TriggerAngleRight)(float);
void (*TriggerGrab)(void);
void (*TriggerRelease)(void);
void (*TriggerSweep)(void);
void (*TriggerRequestObjectType)(void);
String targetObject = "";

void SendMessage()
{
  SerialBT.print(sendingMessage);
  sendingMessage = "";
}

void SendDetectedObject(float angle, float distance)
{
  Serial.println("Sending detection instruction...");
  sendingMessage = "{\"IAROMYR_OBJECT_DETECTED\":{\"ANGLE\":\"" + String(angle) + "\",\"DISTANCE\":\"" + String(distance) + "\"}}";
  SendMessage();
}

void SendStartOfSweepInstruction()
{
  Serial.println("Sending begining of scanning object sequence.");
  sendingMessage = "{\"IAROMYR_START_SWEEP_SEQUENCE\":\"Starting sweep sequence.\"}";
  SendMessage();
}

void SendEndOfSweepInstruction()
{
  Serial.println("Sending end of scanning object sequence.");
  sendingMessage = "{\"IAROMYR_END_SWEEP_SEQUENCE\":\"End of sweep sequence.\"}";
  SendMessage();
}

void SendFeedback()
{
  Serial.println("Sending feeding response...");
  sendingMessage = "{\"IAROMYR_COMMAND\":\"DONE\"}";
  SendMessage();
}

void SendObjectTypeFeedback(bool isTheBomb)
{
  Serial.println("Sending feeding response...");
  sendingMessage = "{\"IAROMYR_COMMAND\":{\"IS_THE_BOMB\":";
  if (isTheBomb)
  {
    sendingMessage += "true";
  }
  else
  {
    sendingMessage += "false";
  }
  sendingMessage += ",\"ID\":\"" + targetObject + "\"}}";
  SendMessage();
}

void SendGrabFeedback()
{
  Serial.println("Sending feeding response...");
  sendingMessage = "{\"IAROMYR_COMMAND\":{\"OBJECT_GRABBED\":true,\"ID\":\"" + targetObject + "\"}}";
  SendMessage();
}

void SendReleaseFeedback()
{
  Serial.println("Sending feeding response...");
  sendingMessage = "{\"IAROMYR_COMMAND\":{\"OBJECT_RELEASED\":true,\"ID\":\"" + targetObject + "\"}}";
  SendMessage();
}

void SendOriginChangeFeedback()
{
  Serial.println("Sending feeding response...");
  sendingMessage = "{\"IAROMYR_COMMAND\":{\"ORIGIN_CHANGED\":{\"X\":\"" + String(positionX) + "\",\"Y\":\"" + String(positionY) + "\"}}}";
  SendMessage();
}

void SendZonesInformations()
{
  Serial.println("Sending zones informations...");
  sendingMessage = "{\"IAROMYR_ZONES\":[{\"X\":\"" + String(IAROMYR_POSITION_X) + "\",\"Y\":\"" + String(IAROMYR_POSITION_Y) + "\"},{\"X\":\"" + String(EXTRACT_ZONE_X) + "\",\"Y\":\"" + String(EXTRACT_ZONE_Y) + "\"}]}";
  SendMessage();
}

void SendConnectivityFeedback()
{
  Serial.println("Sending response to device...");
  sendingMessage = "{\"RESPONSE\":\"IAROMYR_OPERATIONAL\"}";
  SendMessage();
}

void SendActualPosition()
{
  Serial.println("Sending actual position relative to the map...");
  sendingMessage = "{\"IAROMYR_POSITION\":{\"X\":\"" + String(positionX) + "\",\"Y\":\"" + String(positionY) + "\"}}";
  SendMessage();
}

void CheckMessage(String message)
{
  if (message.indexOf("CONNECTIVITY_TEST") != -1)
  {
    positionX = IAROMYR_POSITION_X;
    positionY = IAROMYR_POSITION_Y;
    SendConnectivityFeedback();
  }
  if (message.indexOf("GET_DROP_ZONES") != -1)
  {
    SendZonesInformations();
  }
  if (message.indexOf("GET_RELATIVE_POSITION") != -1)
  {
    SendActualPosition();
  }
  if (message.indexOf("SWEEP_AROUND") != -1)
  {
    TriggerSweep();
  }
  if (message.indexOf("IAROMYR_INSTRUCTION") != -1)
  {
    Serial.println("Recieved an instruction...");
    if (message.indexOf("SET_TARGET_OBJECT") != -1)
    {
      Serial.println("Setting target object");
      targetObject = message.substring(message.indexOf("SET_TARGET_OBJECT") + 20, message.length() - 3);
      Serial.println("Target object: " + targetObject);
      SendFeedback();
    }
    if (message.indexOf("ANGLE_LEFT") != -1)
    {
      float angle = message.substring(message.indexOf("ANGLE_LEFT") + 12, message.length() - 2).toFloat();
      Serial.println("Making a left turn of " + String(angle) + " degrees.");
      TriggerAngleLeft(angle);
    }
    if (message.indexOf("ANGLE_RIGHT") != -1)
    {
      float angle = message.substring(message.indexOf("ANGLE_RIGHT") + 13, message.length() - 2).toFloat();
      Serial.println("Making a left turn of " + String(angle) + " degrees.");
      TriggerAngleRight(angle);
    }
    if (message.indexOf("DISTANCE") != -1)
    {
      float distance = message.substring(message.indexOf("DISTANCE") + 10, message.length() - 2).toFloat();
      Serial.println("Going forward by " + String(distance) + " cm.");
      TriggerDistance(distance);
    }
    if (message.indexOf("REQUEST_OBJECT_TYPE") != -1)
    {
      Serial.println("Sending object type.");
      TriggerRequestObjectType();
    }
    if (message.indexOf("GRAB_OBJECT") != -1)
    {
      Serial.println("Sending grab feedback.");
      TriggerGrab();
    }
    if (message.indexOf("RELEASE_OBJECT") != -1)
    {
      Serial.println("Sending release feedback.");
      TriggerRelease();
    }
    if (message.indexOf("SET_ORIGIN") != -1)
    {
      tempPositionY = positionY;
      positionX = message.substring(message.indexOf("X") + 3, message.indexOf("Y") - 2).toFloat();
      positionY = message.substring(message.indexOf("Y") + 3, message.length() - 3).toFloat();
      distanceToOrigin = positionY - tempPositionY;
      Serial.println("New origin: (" + String(positionX) + " ; " + String(positionY) + ")");
      Serial.println("Distance: " + String(distanceToOrigin));
      TriggerDistance(distanceToOrigin);
      SendOriginChangeFeedback();
    }
  }
}

void HandleBluetooth()
{
  if (SerialBT.available())
  {
    SERVO_Disable(WRIST);
    SERVO_Disable(GRIPPER);
    incomingMessage += SerialBT.readString();
    Serial.println(incomingMessage);
    SERVO_Enable(WRIST);
    SERVO_Enable(GRIPPER);
  }
  else if (incomingMessage != "")
  {
    CheckMessage(incomingMessage);
    incomingMessage = "";
  }
}

void Communication_Init(void (*distanceCallback)(float), void (*rotateRightCallback)(float), void (*rotateLeftCallback)(float), void (*sweepCallback)(void), void (*grabCallback)(void), void (*releaseCallback)(void), void (*requestObjectTypeCallback)(void))
{
  Wire.begin();
  SerialBT.begin(9600);
  Serial.println("The device started, now you can pair it with bluetooth!");
  TriggerDistance = distanceCallback;
  TriggerAngleRight = rotateRightCallback;
  TriggerAngleLeft = rotateLeftCallback;
  TriggerSweep = sweepCallback;
  TriggerGrab = grabCallback;
  TriggerRelease = releaseCallback;
  TriggerRequestObjectType = requestObjectTypeCallback;
}

void DataRequest()
{
  static uint8_t data[16];
  int i = 0;

  Wire.requestFrom(8, 16);
  while(Wire.available())
  {
    data[i] = Wire.read();
    i++;
  }
  GetSetData(data, SET);
}