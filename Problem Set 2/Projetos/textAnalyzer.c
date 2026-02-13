#include <stdio.h>
#include "cs50.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{
    printf("Text analyzer\n\n");
    char *text = get_string("Insert text: ");

    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = toupper(text[i]);
    }

    int characters = strlen(text);
    float letters = 0;
    int vowels = 0;
    int consonants = 0;
    float words = 1;
    float sentences = 0;

    for (int i = 0; i < characters; i++)
    {
        char character = text[i];
        if (isalpha(character))
        {
            letters++;
            if (character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U')
            {
                vowels++;
            }
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