#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

int main(void)
{
    char cpf[50] = "";
    bool apenasDigitos;
    bool todosIguais;
    do {
        // Pega a string e substitui o \n do fgets com \0
        printf("Insira o CPF (xxxxxxxxxxx): ");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';
    } while (strlen(cpf) != 11 || !allDigits(cpf) || allEquals(cpf));

    // check do primeiro dígito
    bool digito10Valido = valid(cpf, 10);
    
    // check do segundo dígito
    bool digito11Valido = valid(cpf, 11);

    if (!digito10Valido || !digito11Valido) {
        printf("CPF inválido\n");
        return 1;
    }

    printf("O CPF é válido\n");
}