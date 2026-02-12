#include <ctype.h>
#include "cs50.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Pontos que correspondem a cada letra do alfabeto
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);

// Pede por duas palavras e diz qual delas recebe mais pontos em um jogo de Scrabble
int main(void)
{
    char* word1 = get_string("Player 1: ");
    char* word2 = get_string("Player 2: ");

    // Computa a pontuação de cada um
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Printa o vencedor
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    // Retorna a pontuação para uma palavra

    int score = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        // Para maiúsculas:
        if (isupper(word[i]))
        {
            // Seu match em "POINTS" será o seu valor - 65
            score += POINTS[word[i] - 65];
        }
        // Para minúsculas:
        if (islower(word[i]))
        {
            // Seu match em "POINTS" será o seu valor - 97
            score = score + POINTS[word[i] - 97];
        }
    }
    return score;
}