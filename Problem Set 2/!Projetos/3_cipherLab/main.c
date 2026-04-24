#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ciphers.h"
#include "auxiliary.h"
#define MAXINPUT 1000

int main (int argc, char *argv[])
{
    if (argc < 2) {
        printf("Faltam argumentos. Utilize --help para ajuda\n");
        return 1;
    }

    char *mode = "initialized";
    char *type = "initialized";
    char *key = "initialized";
    // Caso o loop não encontre mode/type/key, seu respectivo notFound será verdadeiro
    int modeNotFound = 1;
    int typeNotFound = 1;
    int keyNotFound = 1;

    // Busca por mode, type, key ou help
    if (findArgs(argv, argc, &modeNotFound, &mode, &typeNotFound, &type, &keyNotFound, &key)) return 1;

    if (modeNotFound == 1 && typeNotFound == 1 && keyNotFound == 1) {
        printf("Argumentos inválidos. Utilize --help para ajuda\n");
        return 1;
    }

    // Pega o input e substitui seu newline por '\0'
    char input[MAXINPUT];
    printf("Insira o input (máximo de %i caracteres):\n", MAXINPUT-1);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Erro de leitura do input\n");
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    // Associa modes e types com suas respectivas funções
    if (findFunction(type, typeNotFound, key, keyNotFound, input, mode)) return 1;
    return 0;
}