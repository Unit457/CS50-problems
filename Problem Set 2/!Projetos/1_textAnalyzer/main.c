#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include "../../cs50.h"

// Realiza a contagem
void count(float *letters, float *sentences, float *words, int *vowels, int *consonants, const int characters, const char *text);

// Analisador de texto que combina várias funções dos exercícios do PSET2
int main(void)
{
    printf("------ Text analyzer ------\n\n");
    char *text = get_string("Insert text: ");

    // Transforma o texto inteiro em maiúsculo
    for (int i = 0; i < strlen(text); i++) {
        text[i] = toupper(text[i]);
    }

    // Declara e realiza a contagem desses elementos no texto
    const int characters = strlen(text);
    float letters = 0, sentences = 0, words = 1; //"Olá." possui uma palavra e não possui espaços, logo, words = 1
    int vowels = 0, consonants = 0;
    count(&letters, &sentences, &words, &vowels, &consonants, characters, text);
    
    // Calcula Grade-Level score
    const float avgL = (letters / words) * 100;
    const float avgS = (sentences / words) * 100;
    const int score = round(0.0588 * avgL - 0.296 * avgS - 15.8);

    printf("\n");
    printf("Characters: %i\n", characters);
    printf("Letters: %.0f\n", letters);
    printf("Vowels: %i\n", vowels);
    printf("Consonants: %i\n", consonants);
    printf("Words: %.0f\n", words);
    printf("Sentences: %.0f\n", sentences);
    printf("Grade level: ");

    if (score < 1) printf("Below 1\n");
    else if (score > 16) printf("Above 16\n");
    else printf("%i\n", score);
    return 0;
}

// Realiza a contagem
void count(float *letters, float *sentences, float *words, int *vowels, int *consonants, const int characters, const char *text) {
    for (int i = 0; i < characters; i++) {
        char character = text[i];

        // É alfabético?
        if (isalpha(character)) {
            *letters++;

            // Se for algum desses, é vogal
            if (character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U') {
                *vowels++;
            }
            // Se não, é consoante
            else *consonants++;
        }
        else if (isspace(character)) {
            *words++;
        }
        // Se for algum desses, final de uma frase
        else if (character == '!' || character == '.' || character == '?') {
                *sentences++;
        }
    }
}
