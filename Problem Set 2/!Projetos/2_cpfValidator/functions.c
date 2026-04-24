#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.h"

// Retorna true se a string tiver apenas dígitos e false caso contrário
bool allDigits(const char string[]) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (!isdigit(string[i])) {
            return false;                
        }
    }
    return true;
}

// Retorna true se a string tiver todos os caracteres repetidos
bool allEquals(const char string[]) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[0] != string[i]) {
            return false;                
        }
    }
    return true;
}

// Retorna true se o dígito for válido
bool valid(const char string[], int pos) {
    int mult = pos, checksum = 0;

    // Obtém checksum
    for (int i = 0; i < pos-1; i++) {
        checksum += (string[i] - '0') * mult;
        mult--;
    }

    // Obtém resto e localiza o dígito que deveria ser igual ao dígito calculado
    int resto = checksum % 11, digito = string[pos-1] - '0', digitoCalculado;

    // Define o dígito calculado a partir do resto
    if (resto < 2) digitoCalculado = 0;
    else digitoCalculado = 11 - resto;

    if (digitoCalculado != digito) {
        printf("Dígito %i não corresponde ao cálculo\n", pos);
        return false;
    }
    return true;
}