#ifndef Credential_h
#define Credential_h

#include <Arduino.h>

//SSID della rete wifi
const char* ssid = "";

//Password della rete wifi
const char* password = "";

/*
* Indirizzo IP del server a cui mandare i dati
* è possibile usare sia quello specifico che
* uno di broadcast
*/
const char *udpAddress = "";

//Porta da utilizzare per l'invio dei dati
const int udpPort = 0;

#endif