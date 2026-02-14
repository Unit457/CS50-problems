#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "../cs50.h"

// Mostra o grade reading level da frase inserida
int main(void)
{
    char *text = get_string("Text: ");
    int textLen = strlen(text);

    // Na frase "Olá." não existem espaços e mesmo assim existe uma palavra.
    // Incializar words em 1 resolve esse problema.
    float words = 1;
    float sentences;
    float letters;

    // Percorre pelo texto inserido
    for (int i = 0; i < textLen; i++)
    {   
        // Se encontramos um espaço, incremente words
        if (isspace(text[i]))
        {
            words++;
        }

        // Se encontrarmos algum terminador de frase, incremente sentences
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        
        // Se encontrarmos algo alfabético, incremente letras 
        else if (isalpha(text[i]))
        {
            letters++;
        }
    }

    // Calcula o average letters per words
    float avgL = (letters / words) * 100;
    // Calcula o average setences per word
    float avgS = (sentences / words) * 100;

    // Calcula o index a partir o avgL e avgS
    int index = round(0.0588 * avgL - 0.296 * avgS - 15.8);

    // A partir do index, printa o grade reading level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}