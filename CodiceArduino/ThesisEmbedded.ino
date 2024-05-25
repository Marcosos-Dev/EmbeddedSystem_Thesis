#include "ContractAbi.h"
#include "SignMessage.h"
#include "SensorType.h"
#include "SendData.h"
#include "JsonMessage.h"

void setup() {
  Serial.begin(9600);
  //Encode ABI
  byte tempData[] = {0xAB,0xFF,0x01,0x00,0x12,0x67};
  sensorData myData;
  myData.data = tempData;
  myData.timestamp = 5678;
  myData.sequence_number = sizeof(tempData) / sizeof(tempData[0]);
  myData.tp = "Sono numeri casuali senza senso evvai";

  //Create abi encoded string
  String encodedData = createDataField(myData);

  //Generate the signature
  sensorMessage msg;
  msg.data = myData;
  msg.signature = createSignature(encodedData,""); //Inserire PrivateKey
  
  //Create the json
  String json = createJson(msg);
  Serial.println(json);

  //Send the request to UDP Server
  sendRequest(json);
}

void loop() {

}