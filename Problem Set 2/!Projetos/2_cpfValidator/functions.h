#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdbool.h>

// Funções criadas para o programa

// Retorna true se a string tiver apenas dígitos e false caso contrário
bool allDigits(const char string[]);

// Retorna true se a string tiver todos os caracteres repetidos
bool allEquals(const char string[]);

// Retorna true se o dígito for válido
bool valid(const char string[], int pos);

#endif