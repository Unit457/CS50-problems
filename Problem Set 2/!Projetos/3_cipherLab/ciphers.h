#ifndef CIPHERS_H
#define CIPHERS_H

// Funções de cifra
int vigenere_encrypt(const char *plaintext, const char *key);
int vigenere_decrypt(const char *plaintext, const char *key);
int atbash_cipher(const char *plaintext);
int xor_encrypt(const char *plaintext, const char *key);
int xor_decrypt(const char *ciphertext, const char *key);

#endif