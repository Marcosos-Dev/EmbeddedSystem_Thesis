#ifndef ContractAbi_h
#define ContractAbi_h

#include "SensorType.h"
#include <Arduino.h>

/**
 * Metodo per l'encoding ABI di un SensorData
 * 
 * Input:
 *  - SensorData struct, contenenti i dati da codificare
 * 
 * Output:
 *  - String, la stringa contenente la codifica abi della struct
 *            fornita in ingresso
*/
String createDataField(SensorData data);

/**
 * Metodo per l'aggiunta dell'offset come da specifica abi
 * Inserisci 0 fino a 64 - Len(input) ed infine input in coda
 * 
 * Input:
 *  - String input
 *
 * Output:
 * - String, l'input con offset (0...input HEX)
*/
String addOffset(String input);

/**
 * Metodo per l'aggiunta dell'offset come da specifica abi
 * Inserisci l'input in testa e poi 0 fino a 64 - Len(input)
 * 
 * Input:
 *  - String input, stringa iniziale da mettere in testa
 *
 * Output:
 * - String, l'input con offset (input HEX .. 0)
*/
String addOffsetByte(String input);

/**
* Metodo per l'aggiunta dell'offset ad un numer intero come
* da specifica abi
*
* Input:
*  - int num, il numero da convertire
*
* Output:
* - String, stringa composto dall'offset e il numero in input
*           in formato esadecimale
*/
String stringNumToHex(uint64_t num);

#endif