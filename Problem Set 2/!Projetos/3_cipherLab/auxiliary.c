#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "auxiliary.h"
#include "ciphers.h"

// Funções auxiliares (para código mais limpo)

// Menu help
void help() {
    printf("Argumentos: --mode (mode) --type (type) --key (key) (ordem não importa)\n");
    printf("\n");
    printf("--mode encrypt, decrypt, analyze\n");
    printf("-> analyze não requer type ou key\n");
    printf("\n");
    printf("--type vigenere, atbash, xor\n");
    printf("-> atbash não requer key ou mode\n");
    printf("-> type xor com mode decrypt precisa que o input seja em hexadecimal (Formato: \"A1 B2 C3\")\n");
}

// Valida o modo inserido, 1 = inválido
int validate_mode(char *argv[], int argc, int i) {
    // Mode é o último argumento?
    if (i+1 >= argc) {
        printf("--mode inválido (vazio) (utilize cipherlab.exe --help para ver as opções de mode)\n");
        return 1;
    }

    char *mode = argv[i+1];
    // Mode não é encrypt, decrypt nem analyze?
    if (strcasecmp(mode, "encrypt") && strcasecmp(mode, "decrypt") && strcasecmp(mode, "analyze")) {
        printf("--mode inválido (%s não é um mode) (utilize cipherlab.exe --help para ver as opções de mode)\n", argv[i+1]);
        return 1;
    }

    // Mode é válido
    return 0;
}

// Valida o type inserido, 1 = inválido
int validate_type(char *argv[], int argc, int i) {
    // Type é o último argumento?
    if (i+1 >= argc) {
        printf("--type inválido (vazio) (utilize cipherlab.exe --help para ver as opções de type)\n");
        return 1;
    }

    // Type não é vigenere, atbash nem analyze?
    if (strcasecmp(argv[i+1], "vigenere") && strcasecmp(argv[i+1], "atbash") && strcasecmp(argv[i+1], "xor")) {
        printf("--type inválido (%s não é um type) (utilize cipherlab.exe --help para ver as opções de type)\n", argv[i+1]);
        return 1;
    }

    // Type é válido
    return 0;
}

// Encontra mode, type e key
int findArgs(char *argv[], const int argc,
    int *modeNotFound, char **mode,
    int *typeNotFound, char **type,
    int *keyNotFound, char **key) {
    for (int i = 1; i < argc; i++) {
        if (!strcasecmp(argv[i], "--help")) {
            help();
            *modeNotFound = *typeNotFound = *keyNotFound = 0;
            return 1;
        }

        // --- MODE ---
        if (!strcasecmp(argv[i], "--mode")) {
            if (validate_mode(argv, argc, i)) return 1;

            // Mode encontrado
            i++;
            *mode = argv[i];
            *modeNotFound = 0;    
        }

        // --- TYPE ---  
        else if (!strcasecmp(argv[i], "--type")) {
            if (validate_type(argv, argc, i)) return 1;

            // Type foi encontrado
            i++;
            *type = argv[i];
            *typeNotFound = 0;
        }

        // --- KEY ---
        else if (!strcasecmp(argv[i], "--key")) {
            // Key é o último argumento?
            if (i+1 >= argc) {
                printf("--key inválida\n");
                return 1;
            }

            // Key foi encontrada
            i++;
            *key = argv[i];
            *keyNotFound = 0;
        }
    }
    
    return 0;
}

// Encontra a função associada ao mode e type
int findFunction(const char *type, const int typeNotFound,
    const char *key, const int keyNotFound,
    const char *input, const char *mode) {
    // --- ANALYZE ---
    if (!strcasecmp(mode, "analyze")) {
        return 0;
    }

    // --- ATBASH ---
    if (!strcasecmp(type, "atbash")) {
        atbash_cipher(input);
        return 0;
    }

    // --- ENCRYPT ---
    if (!strcasecmp(mode, "encrypt")) {
        // Type existe?
        if (typeNotFound) {
            printf("--mode encrypt precisa de um type\n");
            return 0;
        }

        // Encrypt em qual type?
        // --- VIGENERE ---
        if (!strcasecmp(type, "vigenere")) {
            // Key existe?
            if (keyNotFound) {
                printf("--type vigenere precisa de uma key\n");
                return 1;
            }

            vigenere_encrypt(input, key);
            return 0;
        }

        // --- XOR ---
        if (!strcasecmp(type, "xor")) {
            // Key existe?
            if (keyNotFound) {
                printf("--type xor precisa de uma key\n");
                return 1;
            }

            xor_encrypt(input, key);
            return 0;
        }
    }

    // --- DECRYPT ---
    else if (!strcasecmp(mode, "decrypt")) {
        // Type existe?
        if (typeNotFound) {
            printf("--mode decrypt precisa de um type\n");
            return 1;
        }

        // Decrypt em qual type?
        // --- VIGENERE ---
        if (!strcasecmp(type, "vigenere")) {
            // Key existe?
            if (keyNotFound) {
                printf("--type vigenere precisa de uma key\n");
                return 1;
            }

            vigenere_decrypt(input, key);
            return 0;
        }

        // --- XOR ---
        if (!strcasecmp(type, "xor")) {
            // Key existe?
            if (keyNotFound) {
                printf("--type xor precisa de uma key\n");
                return 1;
            }
            
            xor_decrypt(input, key);
            return 0;
        }
    }

    printf("Type ou mode são inválidos\n");
    return 1;
}

// Transforma char em valor hex (0-15)
int charToHex(char c) {
    if (c >= '0' && c <= '9') return c-'0';
    if (c >= 'a' && c <= 'f') return c-'a'+10;
    if (c >= 'A' && c<= 'F') return c-'A'+10;
    printf("Caractere inválido inserido no input\n");
    return 1;
}

