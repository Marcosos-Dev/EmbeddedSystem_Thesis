#include "ContractAbi.h"
#include <Arduino.h>

String createDataField(SensorData data) {
  //Offset dell'inizio della tupla (Struct = Tuple in Remix)
  String abiEncodedString = "0000000000000000000000000000000000000000000000000000000000000020";
  
  //Offset dell'inizio dei dati
  abiEncodedString += "0000000000000000000000000000000000000000000000000000000000000080";
  
  //Inserisco i dati
  //abiEncodedString += addOffset(String(data.timestamp,HEX));
  //abiEncodedString += addOffset(String(data.sequence_number,HEX));
  abiEncodedString += stringNumToHex(data.timestamp);
  abiEncodedString += stringNumToHex(data.sequence_number);
  
  //Inserimento dell'offset dell'inizio della stringa
  //0x80 (offset dati dei byte) + (numero di record occupati dai byte * 32)
  //Ottengo quanti blocchi di 32 byte necessito per inserire il campo data,
  //tenendo conto dei campi lunghezza dell'array e lunghezza dei dati
  uint8_t numOfData = (data.sequence_number/32)+2;
  //Prevedo il caso in cui sia un multiplo di 32, perciò devo
  //restare nell'ultimo blocco e non aggiungerne uno di soli zeri
  if(data.sequence_number%32==0) { numOfData-=1; }
  abiEncodedString += addOffset(String((128 + (numOfData * 32)),HEX));

  //Inserisco la lunghezza dell'array
  abiEncodedString += stringNumToHex(data.sequence_number);

  //Con il seguente ciclo:
  // 1- Inserisco il campo data del mio sensorData
  // 2- Inserisco la lunghezza della stringa
  // 3- Inserisco la stringa
  // X = 0, inserimento del campo data
  // X = 1, inserimento della stringa
  for(int x=0;x<2;x++){
    String toEncode = "";
    //Variabile per decidere quanti dati sono da ciclare
    int numOfCycles = (x==0) ? data.sequence_number : data.tp.length();
    for(int i=0;i<numOfCycles;i++){
      String lastRead = (x==0) ? String(data.data[i],HEX) : String(data.tp.charAt(i),HEX);
      if(lastRead.length()==1)
        toEncode += '0';
      
      toEncode += lastRead;
      if((i+1)%32==0 && i!=0){
        abiEncodedString += toEncode;
        toEncode = "";
      }
    }

    //Se sono rimasti dei dati nel buffer li scrivo, altrimenti andrebbero persi
    if(toEncode != ""){ abiEncodedString += addOffsetByte(toEncode); }
    //Una volta scritti i valori del campo data, inserisco la lunghezza della stringa
    //Li scrivo prima di passare ad X = 1
    if(x==0) { abiEncodedString += stringNumToHex(data.tp.length()); }
  }

  return abiEncodedString;
}

String stringNumToHex(uint64_t num) {
  String lengthInHex = String(num, HEX);
  uint32_t outputLength = lengthInHex.length();
  if (outputLength < 64) {
    String offsetString;
    uint32_t offset = 64 - outputLength;
    for (int i = 0; i < offset; i++) {
      offsetString += '0';
    }
    lengthInHex = offsetString + lengthInHex;
  }
  return lengthInHex;
}

String addOffset(String input) {
  String output;
  int outputLength = input.length();
  if (outputLength < 64) {
    int offset = 64 - outputLength;
    for (int i = 0; i < offset; i++) {
      output += '0';
    }
    output += input;
  }
  return output;
}

String addOffsetByte(String input) {
  String output = input;
  int outputLength = input.length();
  if (outputLength < 64) {
    int offset = 64 - outputLength;
    for (int i = 0; i < offset; i++) {
      output += '0';
    }
  }
  return output;
}