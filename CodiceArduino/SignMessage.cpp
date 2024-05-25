#include "SignMessage.h"
#include <keccak.h>
#include <secp256k1_recovery.h>

byte* createSignature(String data, String private_key){
  String hash = generateKeccacHash(data);
  uint8_t _hash[32];
  stringToUint(hash, _hash);
  uint8_t _privateKey[32];
  stringToUint(private_key, _privateKey);

  secp256k1_context *ctx = NULL;
  int res;

  ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY | SECP256K1_CONTEXT_SIGN);
  
  secp256k1_ecdsa_recoverable_signature Signature;
  secp256k1_ecdsa_sign_recoverable(ctx, &Signature, _hash, _privateKey, NULL, NULL);

  int recid;
  unsigned char *serialized_signature = new unsigned char[65];

  secp256k1_ecdsa_recoverable_signature_serialize_compact(ctx, serialized_signature, &recid, &Signature);
  
  serialized_signature[64] = recid + 27;

  secp256k1_context_destroy(ctx);

  return serialized_signature;
}

String generateKeccacHash(String msg) {
  Keccak keccak;
  std::string _hash = keccak(std::string(msg.c_str()));
  return _hash.c_str();
}

void stringToUint(String input, uint8_t* output) {
  int index = 0;

  if (input.charAt(0) == '0' && input.charAt(1) == 'x') {
    input = input.substring(2);
  }
  for (int i = 0; i < input.length(); i += 2) {
    unsigned char second = char2byte(input[i]);
    unsigned char first = char2byte(input[i+1]);
    output[index] = second*16 + first;
    index++;
  }
}


char char2byte(char input) {
  if (input >= 'a' && input <= 'f') {
    return input - 87;
  } else {
    return input - 48;
  }
}