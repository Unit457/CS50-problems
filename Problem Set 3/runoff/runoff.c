#include <stdio.h>
#include <string.h>
#include "../cs50.h"

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Para cada candidato
    for (int i = 0; i<candidate_count; i++)
    {
        // Se existir um candidato com aquele nome
        if (!candidates[i].eliminated && !strcmp(name, candidates[i].name))
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Para cada voter
    for (int i = 0; i < voter_count; i++)
    {
        // Para cada candidato
        for (int j = 0; j < candidate_count; j++)
        {
            // Pega o número do candidato
            int candidateNum = preferences[i][j];
            // Se o candidato não estiver eliminado
            if (!candidates[candidateNum].eliminated)
            {
                // Aumenta seu número de votos
                candidates[candidateNum].votes++;
                // Break faz com que apenas o top candidato tenha seus votos aumentados
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Para cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        // Se o candidato não foi eliminado e seus votos correspondem a mais da metade da quantidade de voters
        if (!candidates[i].eliminated && candidates[i].votes*2 > voter_count)
        {
            // O candidato é um ganhador
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_vote = voter_count;

    // Para cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        // Se o candidato não foi eliminado e seus votos são menores do que min_vote
        if (!candidates[i].eliminated && candidates[i].votes < min_vote)
        {
            // Atualize min_vote, dessa forma encontrando o menor número de votos
            min_vote = candidates[i].votes;
        }
    }
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Para cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        // Se o candidato não foi eliminado e seus votos não são iguais a "min"
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            // Então um dos candidatos possui mais votos do que a menor quantidade de votos, fazendo com que não exista um empate
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Para cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        // Se o candidato não foi eliminado e seus votos correspondem ao menor número de votos
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            // Ele foi eliminado
            candidates[i].eliminated = true;
        }
    }
    return;
}