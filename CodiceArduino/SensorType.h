#ifndef SensorType_h
#define SensorType_h

#include <Arduino.h>

typedef struct SensorData {
  byte *data;
  uint64_t timestamp;
  uint64_t sequence_number;
  String tp; //Type
} sensorData;

typedef struct SensorMessage {
  SensorData data;
  byte *signature;
} sensorMessage;

#endif