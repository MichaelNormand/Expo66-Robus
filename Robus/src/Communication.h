
#ifndef COMUNICATIONS
#define COMUNICATIONS
#define BOMB_ZONE_X 0
#define BOMB_ZONE_Y -50
#define EXTRACT_ZONE_X 200
#define EXTRACT_ZONE_Y -50
#define IAROMYR_POSITION_X 100
#define IAROMYR_POSITION_Y -50
#define HC_05_RX_PIN A11
#define HC_05_TX_PIN A10
#endif

#include <Wire.h>
#include <Arduino.h>
#include <GetSet.h>
#include <SoftwareSerial.h>
#include <LibRobus.h>

void DataRequest(void);

void SendDetectedObject(float angle, float distance);

void SendStartOfSweepInstruction();

void SendEndOfSweepInstruction();

void SendFeedback();

void SendQuadranChangeInstruction();

void SendObjectTypeFeedback(bool isTheBomb);

void SendGrabFeedback();

void SendReleaseFeedback();

void SendOriginChangeFeedback();

void SendZonesInformations();

void SendConnectivityFeedback();

void SendActualPosition();

void HandleBluetooth();

void Communication_Init(void (*distanceCallback)(float), void (*rotateRightCallback)(float), void (*rotateLeftCallback)(float), void (*sweepCallback)(void), void (*grabCallback)(void), void (*releaseCallback)(void), void (*requestObjectTypeCallback)(void));