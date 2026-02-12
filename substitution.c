#include <stdio.h>
#include <stdlib.h>
#include "cs50.h"
#include <ctype.h>
#include <string.h>

// Recebe uma chave de 26 caracteres como argumento aonde cada caractere corresponde a sua respectiva letra no alfabeto (Chave: "EFGH...", input "ABCD" retornaria "EFGH") e depois pede por um texto para criptografar a partir da chave inserida
int main(int argc, char *argv[])
{
    int len = 26;

    // Se o programa tiver menos do que dois argumentos, acaba aqui
    if (argc > 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }

    // Se o segundo argumento não tiver 26 caracteres, acaba aqui
    else if (strlen(argv[1]) != len)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }

    char *input = argv[1];

    // Para cada caractere da chave:
    for (int i = 0; i < len; i++)
    {
        // Se não for alfabético, acaba aqui
        if (!isalpha(input[i]))
        {
            printf("Key must contain alphabetical characters only.\n");
            exit(1);
        }
    }

    // Armazena a chave em upper
    char *inputUpper = malloc(len * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        inputUpper[i] = toupper(input[i]);
    }

    // Armazena a chave em lower
    char *inputLower = malloc(len * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        inputLower[i] = tolower(input[i]);
    }

    // Para cada caractere da chave:
    for (int i = 0; i < len; i++)
    {
        // Vamos procurar um caractere igual a esse na chave
        char checkingfordup = inputUpper[i];
        
        // Checa se algum caractere (menos o que está armazenado) é igual ao que está armazenado
        for (int j = 0; j < len; j++)
        {
            if (j != i)
            {
                // Se for, o programa acaba aqui
                if (inputUpper[j] == checkingfordup)
                {
                    printf("Key mustn't contain duplicate letters.\n");
                    exit(1);
                }
            }
        }
    }

    // Pede pelo texto para criptografar
    char *plaintext = get_string("plaintext: ");

    // Malloc para o texto criptografado
    char *ciphertext = malloc(strlen(plaintext) * sizeof(char));

    // Para cada caractere do texto normal:
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Se for alfabético:
        if (isalpha(plaintext[i]))
        {
            // Se for lowercase:
            if (islower(plaintext[i]))
            {
                // Encontra o correspondente em inputLower
                ciphertext[i] = inputLower[plaintext[i] - 97];
            }

            // Se for uppercase:
            if (isupper(plaintext[i]))
            {
                // Encontra o correspondente em inputUpper
                ciphertext[i] = inputUpper[plaintext[i] - 65];
            }
        }
        // Se for qualquer outra coisa que não seja alfabético:
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    
    printf("ciphertext: ");
    printf("%s\n", ciphertext);
    return 0;
}