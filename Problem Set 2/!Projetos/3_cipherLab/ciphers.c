#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ciphers.h"
#include "auxiliary.h"

int vigenere_encrypt(const char *plaintext, const char *key) {
    // Tamanhos
    int plainLen = strlen(plaintext);
    int keyLen = strlen(key);

    // Verifica emptyness
    if (plainLen == 0) {
        printf("Plaintext não pode ser vazio\n");
        return 1;
    }
    if (keyLen == 0) {
        printf("Key não pode ser vazia\n");
        return 1;
    }

    // Verifica caracteres não alfabéticos na chave
    for (int i = 0; i < keyLen; i++) {
        if (!isalpha(key[i])) {
            printf("Key não pode possuir caracteres não alfabéticos\n");
            return 1;
        }
    }

    char encrypted;
    for (int i = 0; i < plainLen; i++) {
        if (isalpha(plaintext[i])) {
            // Realiza o alinhamento do caractere na tabela
            // Fórmula: (Caractere + Caractere atual da chave) % 26
            // i % keyLen garante que o valor não avance além do tamanho da chave
            // +65 para que o número se alinhe com a tabela ASCII após ser modulado por 26
            encrypted = (toupper(plaintext[i]) + toupper(key[i % keyLen])) % 26 + 65;
            if (islower(plaintext[i])) encrypted = tolower(encrypted);
        }
        else encrypted = plaintext[i];
        printf("%c", encrypted);
    }

    printf("\n");
    return 0;
}

int vigenere_decrypt(const char *ciphertext, const char *key) {
    int cipherLen = strlen(ciphertext);
    int keyLen = strlen(key);

    // Verifica emptyness
    if (!cipherLen) {
        printf("Ciphertext não pode ser vazio\n");
        return 1;
    }
    if (!keyLen) {
        printf("Key não pode ser vazio\n");
        return 1;
    }
    
    // Verifica caracteres não alfabéticos na chave  
    for (int i = 0; i < keyLen; i++) {
        if (!isalpha(key[i])) {
            printf("Key não pode possuir caracteres não alfabéticos\n");
            return 1;
        }
    }

    char decrypted;
    for (int i = 0; i < cipherLen; i++) {
        if (isalpha(ciphertext[i])) {
            // Desalinhamento do caractere na tabela:
            // Fórmula: (Caractere - Caractere atual da chave) % 26
            // +26 garante que o número sempre será positivo (mesmo se ele já for positivo, o resultado não será afetado por causa do % 26)
            // i % keyLen garante que o valor não avance além do tamanho da chave
            // +65 para que o número se alinhe com a tabela ASCII após ser modulado por 26
            decrypted = ((toupper(ciphertext[i]) - toupper(key[i % keyLen])) + 26) % 26 + 65;
            if (islower(ciphertext[i])) decrypted = tolower(decrypted);
        }
        else decrypted = ciphertext[i];
        printf("%c", decrypted);
    }

    printf("\n");
    return 0;
}

int atbash_cipher(const char *plaintext) {
    int plainLen = strlen(plaintext);
    
    // Verifica emptyness
    if (!plainLen) {
        printf("Plaintext não pode ser vazio\n");
        return 1;
    }

    char opposite;
    for (int i = 0; i < plainLen; i++) {
        if (isalpha(plaintext[i])) {
            // Encontra o caractere oposto no alfabeto:
            opposite = 65 + 90 - toupper(plaintext[i]);
            if (islower(plaintext[i])) opposite = tolower(opposite);
        }
        else opposite = plaintext[i];
        printf("%c", opposite);
    }
    
    printf("\n");
    return 0;
}

int xor_encrypt(const char *plaintext, const char *key) {
    int plainLen = strlen(plaintext);
    int keyLen = strlen(key);

    // Verifica emptyness
    if (!plainLen) {
        printf("Plaintext não pode ser vazio\n");
        return 1;
    }
    if (!keyLen) {
        printf("Chave não pode ser vazia\n");
        return 1;
    }

    unsigned char encrypted;
    for (int i = 0; i < plainLen; i++) {
        // Realiza operação xor no caractere e mostra como hexadecimal
        encrypted = plaintext[i] ^ key[i % keyLen];
        printf("%02X ", encrypted);
    }
    
    printf("\n");
    return 0;
}

int xor_decrypt(const char *ciphertext, const char *key) { 
    int keyLen = strlen(key);
    int cipherLen = strlen(ciphertext);

    // Verifica emptyness
    if (!cipherLen) {
        printf("Ciphertext não pode ser vazio\n");
        return 1;
    }
    if (!keyLen) {
        printf("Chave não pode ser vazia\n");
        return 1;
    }

    // Para ler os caracteres hexadecimais:
    int decrypted = 0; // Guarda o valor que o hexadecimal representa
    int valor; // Guarda o valor numérico do caractere hexadecimal lido
    int j = 0; // Guarda qual caractere da string hexadecimal está sendo lido
    int k = 0; // Quantidade de bytes (caracteres ASCII) lidos em forma de hexadecimal

    for (int i = 0; i < cipherLen; i++) {
        if (ciphertext[i] == ' ') {
            continue;
        }
        
        valor = charToHex(ciphertext[i]); // Valor do caractere sendo lido
        if (valor < 0) {
            printf("Caractere %i do input é inválido\n", i+1);
            return 1;
        }

        decrypted = decrypted * 16 + valor; // Soma o valor do caractere lido ao valor que o hexadecimal representa
        j++; // Avança caractere da string hexadecimal

        if (j == 2) {
            // Se j == 2 então lemos um byte, podemos realizar a operação xor
            decrypted = decrypted ^ key[k % keyLen];
            printf("%c", decrypted);
            // Resetamos esses valores para nos prepararmos para um novo byte hexadecimal
            j = decrypted = 0;
            // Lemos uma letra, então devemos avançar a posição da chave
            k++;
        }
    }
    
    printf("\n");
    return 0;
}