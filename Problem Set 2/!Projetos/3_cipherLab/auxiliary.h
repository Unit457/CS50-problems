#ifndef AUXILIARY_H
#define AUXILIARY_H

// Menu help
void help();

// Valida o modo inserido, 1 = inválido
int validate_mode(char *argv[], int argc, int i);

// Valida o type inserido, 1 = inválido
int validate_type(char *argv[], int argc, int i);

// Encontra os argumentos do programa
int findArgs(char *argv[], const int argc,
    int *modeNotFound, char **mode,
    int *typeNotFound, char **type,
    int *keyNotFound, char **key);

// Encontra a função associada ao mode e type
int findFunction(const char *type, const int typeNotFound,
    const char *key, const int keyNotFound,
    const char *input, const char *mode);

int charToHex(char c);

#endif