#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../cs50.h"

typedef struct
{
    char *name;
    int votes;
} candidate;

#define MAX 9

int main(int argc, char *argv[])
{
    // Se tiver menos de dois argumentos, acaba aqui
    if (argc < 2)
    {
        printf("Usage: ./plurality [candidates...]\n");
        return 1;
    }

    int candAmount = argc-1;
    // Se tiver mais candidatos do que o máximo, acaba aqui
    if (candAmount > MAX+1)
    {
        printf("Max of %i candidates.\n", MAX);
        return 1;
    }

    // Malloc para array dos candidatos
    candidate *candidates = malloc(sizeof(candidate) * candAmount);
    if (candidates == NULL)
    {
        printf("Malloc error\n");
        return 1;
    }

    // Para cada candidato, defina:
    for (int i = 0; i < candAmount; i++)
    {
        // Seu nome
        candidates[i].name = argv[i+1];
        // Seus votos
        candidates[i].votes = 0;
    }

    int voters = get_int("Number of voters: ");

    // Para cada voter:
    for (int i = 0; i < voters; i++)
    {
        bool found = false;
        while (found == false)
        {
            // Peça o voto
            char *vote = get_string("Vote %i: ", i+1);

            // Se o nome inserido corresponder ao nome do candidato sendo checado:
            for (int j = 0; j < candAmount; j++)
            {
                if (strcmp(vote, candidates[j].name) == 0)
                {
                    // Incremente seus votos
                    candidates[j].votes++;
                    // Encontramos o candidato
                    found = true;
                }
            }
            // Se não tivermos encontrado, repita
            if (found == false)
            {
                printf("Invalid vote.\n");
            }
        }
        
    }

    // Maior voto
    int highest = 0;
    // Para cada candidato:
    for (int i = 0; i < candAmount; i++)
    {
        // Se sua quantidade de votos for maior que highestvote, atualize highest vote
        if (candidates[i].votes > highest)
        {
            highest = candidates[i].votes;
        }
    }

    // Para cada candidato:
    for (int i = 0; i < candAmount; i++)
    {
        // Se a quantidade de votos deste candidato for igual a highestvote, ele é um ganhador
        if (candidates[i].votes == highest)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    free(candidates);
    return 0;
}