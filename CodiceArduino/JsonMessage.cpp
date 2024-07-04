#include "JsonMessage.h"

String createJson(SensorMessage msg){
  String jsonStr = "{\n";
  jsonStr += addJsonFormatter("data","0x"+correctData(msg.data.data,msg.data.sequence_number),0,0);
  jsonStr += addJsonFormatter("timestamp",String(msg.data.timestamp),1,0);
  jsonStr += addJsonFormatter("sequence_number",String(msg.data.sequence_number),1,0);
  jsonStr += addJsonFormatter("type",msg.data.tp,0,0);
  jsonStr += addJsonFormatter("signature","0x"+correctData(msg.signature,65),0,1);
  jsonStr += "\n}";
  return jsonStr;
}

String addJsonFormatter(String field_name,String value,uint8_t isNumeric, uint8_t terminate){
  String jsonStr = "    ";
  jsonStr += '"' + field_name + '"' + ": ";
  if(!isNumeric) jsonStr += '"' + value + '"';
  else jsonStr += value;
  if(!terminate) { jsonStr += ",\n"; }
  return jsonStr;
}

String correctData(byte *msgData, int lenght){
  String temp = "";
  for(int i=0;i<lenght;i++) {
    if(String(msgData[i],HEX).length()==1)
        temp += '0';
    temp += String(msgData[i],HEX);
  }
  return temp;
}
