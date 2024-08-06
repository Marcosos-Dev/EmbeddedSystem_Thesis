# ESP32 Firmware per la realizzazione di una transazione sulla blockchain Ethereum

Il seguente repository fornisce un'implementazione per ipotetici dispositivi IoT a seguito 
di quanto discusso nel il progetto Diversity. 
Il dispositov IoT ha l'obiettivo di svolgere i seguenti compiti
 - Effettuare la codifica ABI di dati in un formato ben definito
 - Firmare in ECDSA dei dati in codifica ABI
 - Assemblare una stringa JSON definita a priori
 - Spedire dei dati in formato JSON ad un server UDP

Il repository presenta due cartelle, con lo scopo di presentare un esempio il più completo possibile.
Dentro [Codice Arduino](https://github.com/Marcosos-Dev/EmbeddedSystem_Thesis/tree/main/CodiceArduino/) è presente l'effettiva implementazione per il dispositivo IoT, 
in [Server Java](https://github.com/Marcosos-Dev/EmbeddedSystem_Thesis/tree/main/ServerJava) è fornito, **con solo scopo dimostrativo**, un generico codice per la 
ricezione dei pacchetti UDP generati dal dispositivo IoT.

Il programma è stato testato su un ESP32-Wroom-32 di AzDelivery utilizzando Arduino IDE.

## Configurazione preliminare

Per la realizzazione di alcune funzionalità sono state impiegate delle librerie esterne, reperibili ai seguenti link:
 - [Portable C++ Hashing Library](https://github.com/stbrumme/hash-library/tree/master) per la funzione di hashing _Keccak256_
 - [libsecp256k1](https://github.com/bitcoin-core/secp256k1/tree/be8d9c262f46309d9b4165b0498b71d704aba8fe) per firmare con la curva _secp256k1_ dell'algoritmo _ECDSA_.

Nel caso venga utilizzato il medesimo dispositivo citato nella precedente sezione occore seguire la guida [ESP32 Arduino core](https://github.com/espressif/arduino-esp32).
Necessaria per ottenere la corretta board (ESP32 Dev Module) e funzionamente del modulo atto a realizzare l'invio dei dati tramite UDP.

Per motivi di sicurezza, le informazioni per l'invio dei dati tramite _UDP_ non sono stati inserite. Esse vanno aggiunte nel file [Credential.h](https://github.com/Marcosos-Dev/EmbeddedSystem_Thesis/blob/main/CodiceArduino/Credential.h)
```
Informazioni relative alla propria rete Wi-Fi
const char* ssid = "";
const char* password = "";

Informazioni relative al server UDP
const char *udpAddress = "";
const int udpPort = 0;
```

## Utilizzare l'applicazione

I moduli sono stati separati e nominati in modo da rispecchiare le relative funzioni, predisponendo un esempio di esecuzione in [ThesisEmbedded.ino](https://github.com/Marcosos-Dev/EmbeddedSystem_Thesis/blob/main/CodiceArduino/ThesisEmbedded.ino).
Una generica esecuzione è composta da: 

***creazione di una stringa ABI -> firma della stringa precedentemente generata -> formattazione JSON dei dati originali includendo la loro firma -> invio del JSON ad un server UDP***

Per effettuare la codifica ABI dei dati con il formato definito in [SensorType.h](https://github.com/Marcosos-Dev/EmbeddedSystem_Thesis/blob/main/CodiceArduino/SensorType.h) è necessario utilizzare il metodo:
```
createDataField(sensorData);

* sensorData è un generico oggetto SensorData, restituendo in output una stringa
```
Per ottenere la firma dei dati, che si presuppone siano già stati codificati in ABI, è necessario utilizzare il seguente metodo:
```
createSignature(encodedData,"privateKey");

* privateKey va sostituita con la propria chiave privata per realizzare le transazione in blockchain
  encodedData è una stringa contente i dati da firmare, restituendo in output un array di byte
```
Per formattare in una stringa json i campi di un SensorData unendo la loro firma è necessario utilizzare il seguente metodo:
``` 
createJson(msg);

* msg è un generico oggetto SensorData, restituendo in output una stringa
```
Per inviare dei dati ad un server UDP è necessario utilizzare il seguente metodo:
```
sendRequest(msg);

* msg è una stringa contenente i dati da inviare al server UDP, restituendo in output un intero per la gestione di possibili errori durante l'invio
```

### Obiettivi futuri

In futuro si prevede un miglioramento per quanto riguarda i seguenti aspetti:

 - Modifica del modulo atto a effettuare l'invio dei dati al server UDP, con lo scopo di migliorarne le performance ed evitare il blocco in caso di mancata connessione alla rete Wi-Fi
 - Dismissione della classe _String_
 - Implementazione di un modulo atto a ottenere dei dati effettivi da sensori
 - Implementazione di un modulo atto a realizzare la funzione di hash _Keccka256_
 - Implementazione di un modulo atto a realizzare l'invio dei dati tramite _UDP_
