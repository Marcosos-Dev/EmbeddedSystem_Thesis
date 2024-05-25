#ifndef JsonMessage_h
#define JsonMessage_h

#include "SensorType.h"
#include <Arduino.h>

/**
 * Metodo per la creazione di una stringa contenente
 * i dati in codifica JSON
 * 
 * Input:
 *  - SensorMessage msg, il messaggio contente i dati da inviare
 * 
 * Output:
 *  - String, la stringa JSON
*/
String createJson(SensorMessage msg);

/**
 * Metocdo per realizzare la formattazione di un campo
 * dati del JSON
 * 
 * Input:
 *  - String field_name, stringa con il nome del campo per il formato JSON
 *  - String value, stringa con il valore da inserire
 *  - Uint8_t terminate, carattere che identifica 
 *    se inserire una virgola al termine del campo
 * 
 * Output:
 *  - String, una singola coppia chiave/valore JSON
*/
String addJsonFormatter(String field_name,String value,uint8_t terminate);

/**
 * Metodo usato da createJson per correggere la formattazione
 * dei dati di tipo byte* inseriti nel messaggio, inserisci il carattere '0'
 * nel caso il byte sia a singola cifra
 * 
 * Input:
 *  - Byte *msgData, array di byte contenente i dati
 *  - Int lenght, lunghezza dell'array
 * 
 * Output:
 *  - String, la stringa contente i dati con lunghezza corretta
*/
String correctData(byte *msgData, int lenght);

#endif