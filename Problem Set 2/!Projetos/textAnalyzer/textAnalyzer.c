#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "../../cs50.h"

// Analisador de texto que combina várias funções dos exercícios do PSET2
int main(void)
{
    printf("Text analyzer\n\n");
    char *text = get_string("Insert text: ");

    // Transforma o texto inteiro em maiúsculo
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = toupper(text[i]);
    }

    int characters = strlen(text);
    float letters = 0;
    int vowels = 0;
    int consonants = 0;
    float sentences = 0;

    // Na frase "Olá." não existem espaços e mesmo assim existe uma palavra.
    // Incializar words em 1 resolve esse problema.
    float words = 1;

    // Para cada caractere no texto:
    for (int i = 0; i < characters; i++)
    {
        char character = text[i];

        // É alfabético?
        if (isalpha(character))
        {
            // Se sim, incremente letras
            letters++;

            // Se for algum desses, é vogal
            if (character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U')
            {
                vowels++;
            }
            // Se não, é consoante
            else
            {
                consonants++;
            }
        }
        else if (isspace(character))
        {
            words++;
        }
        else
        {
            if (character == '!' || character == '.' || character == '?')
            {
                sentences++;
            }
        }
    }
    
    float avgL = (letters / words) * 100;
    float avgS = (sentences / words) * 100;

    int score = round(0.0588 * avgL - 0.296 * avgS - 15.8);

    printf("\n");
    printf("Characters: %i\n", characters);
    printf("Letters: %.0f\n", letters);
    printf("Vowels: %i\n", vowels);
    printf("Consonants: %i\n", consonants);
    printf("Words: %.0f\n", words);
    printf("Sentences: %.0f\n", sentences);
    printf("Grade level: ");

    if (score < 1)
    {
        printf("Below 1");
    }
    else if (score > 16)
    {
        printf("Above 16");
    }
    else
    {
        printf("%i\n", score);
    }
}