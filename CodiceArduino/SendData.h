#ifndef SendData_h
#define SendData_h

#include "SensorType.h"
#include <Arduino.h>

/**
* Metodo per l'invio di dati ad un server UDP a cui
* è possibile fornire una qualsiasi stringa già
* formattata (esempio: Json). 
* Effettua inizialmente la connessione alla rete Wi-Fi
* e poi invia i dati tramite UDP.
*
* Prima dell'invio assicurarsi di aver compilato i
* tutti i campi di Credential.h.
*
* Input:
*  - String input, stringa iniziale da mettere in testa
*
* Output:
* - String, Messaggio inviato con successo o Messaggio non inviato
*/
String sendRequest(String msg);

#endif