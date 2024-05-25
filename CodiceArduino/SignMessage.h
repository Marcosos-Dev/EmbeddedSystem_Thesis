#ifndef SignMessage_h
#define SignMessage_h

#include "SensorType.h"
#include <Arduino.h>

/**
 * Metodo per firmare in ECDSA con una chiave privata
 * dei dati in codifica ABI
 *
 * Input:
 *  - String data, stringa con i dati da codificare
 *  - String private_key, chiave privata da usare per la firma
 * 
 * Output:
 *  - Byte*, firma ECDSA
*/
byte* createSignature(String data, String private_key);

/**
 * Method usato da createSignature per effettuare l'hashing
 * della stringa contentente i dati da firmare.
 * 
 * Input:
 *  - String msg, stringa con i dati
 * 
 * Output:
 * - String, Kekkac256 della stringa in input
*/
String generateKeccacHash(String msg);

/**
 * Method usato da createSignature per convertire una stringa
 * con dati in formato esadecimale in un array di byte
 * 
 * Input:
 *  - String input, stringa in formato esadecimale
 * 
 * Output:
 *  - uint8_t* output, output in bytes
*/
void stringToUint(String input, uint8_t* output);

/**
 * Method usato da stringToUint per convertire un
 * singolo carattere in byte
 * 
 * Input:
 *  - char input, carattere da convertire
 * 
 * Output:
 * - char, byte corrispondente al carattere
*/
char char2byte(char input);

#endif