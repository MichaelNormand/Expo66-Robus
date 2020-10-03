#include <Arduino.h>
#include <LibRobus.h>
 
float PID(int32_t encoder, float speed, float steps);
 
void setup() {
  BoardInit();
  Serial.begin(115200);
}
 
void loop() {
  int32_t now;
  int32_t before = 0;
  int32_t steps = 10;

  float speed0 = 0.5;
  float speed1 = 0.5;

  while (1)
  {
    MOTOR_SetSpeed(0, speed0);
    MOTOR_SetSpeed(1, speed1);

    now = millis();
    if(now - before >= steps)
    {
      before = now;
      speed0 = PID(ENCODER_Read(0), speed0, steps);
      speed1 = PID(ENCODER_Read(1), speed1, steps);
      ENCODER_Reset(0);
      ENCODER_Reset(1);
    }
  }
}
 
float PID(int32_t encoder, float speed, float steps)
{
  float Kp = 0.0005;
  float Ki = 0.0003;
  float Kd = 0.0004;

  int32_t goal = 50;                              //steps per 10ms.

  float error = (float)(goal - encoder);          //error each 10ms.

  static float cumError = 0;  

  static float lastError = 0;
  float rateError;
  
  cumError += error * steps / 1000;               //cumulated error over time.

  rateError = (error - lastError) / steps / 1000; //rate of error every 10ms.

  lastError = error;                              //keep track of error for delta error.

  speed = speed + (Kp * error) + (Ki * cumError) + (Kd * rateError); //adjust speed in function of error.

  if(speed > 1)
    speed = 1;

  return speed;            
}