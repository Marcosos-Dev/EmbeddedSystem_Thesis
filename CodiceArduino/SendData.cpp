#include "SendData.h"
#include "Credential.h"
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

String sendRequest(String msg) {
  const char* msgToSend = msg.c_str();

  WiFi.disconnect(true);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(10000);
    Serial.println("Connessione alla rete WiFi...");
  }
  Serial.println("Connessione effettuata con successo alla rete WiFi");

  udp.begin(WiFi.localIP(),udpPort);
  if (WiFi.status() == WL_CONNECTED){
    udp.beginPacket(udpAddress, udpPort);
    udp.printf(msgToSend);
    udp.endPacket();
  } else { 
    return "Messaggio non inviato";
  }

  return "Messaggio inviato";
}