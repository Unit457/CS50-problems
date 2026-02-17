// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 50021

// Hash table
node *table[N];

// Number of words in dictionary
unsigned int numberWords = 0;
bool isLoaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Pega o hashNumber da word
    int hashNumber = hash(word);

    // Se existir, criamos o node para caminhar pela linha
    node *traversalNode = table[hashNumber];

    // Enquanto o node não for NULL
    while (traversalNode != NULL)
    {
        // Checamos se encontramos a palavra
        if (strcasecmp(traversalNode->word, word) == 0)
        {
            return true;
        }
        // Se não encontramos, avançamos
        traversalNode = traversalNode->next;
    }

    // Se o código passar pelo while sem retornar true, a palavra não existe
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Pesquisando no google rapidamente, descobrimos que um bom approach para hashing de strings é o hash rolante polinomial
    // Sua fórmula é: s[0] * p⁰ + s[1] * p¹ + s[2] * p² ... até o final da string
    // s é a variável que contém a string
    // p é um número primo que deve ser próximo ao número de caracteres possíveis na string
    // Por exemplo, para o alfabeto romano (26 caracteres), 31 é uma boa escolha (número primo mais próximo de 26)

    // Acontece que potências são computacionalmente caras, então, o ideal, seria poder remover elas da fórmula
    // Com o método de horner, isso é possível
    // Exemplo do método de Horner: 2x⁰ + 3x¹ + 5x² + 7x³ = ((2x + 3)x + 5)x + 7, dessa forma, usamos apenas multiplicações
    // Fazendo isso para: s[0]p⁰ + s[1]p¹ + s[2]p² + s[3]p³ ... obtemos:
    // ((s[0]p + s[1])p + s[2])p + s[3]
    // Isso pode ser traduzido para:
    unsigned int hash = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = hash * 31 + toupper(word[i]);
        // Como hash vai começar sendo 0, ele começa como s[0]
        // Depois, percorre a estrutura da fórmula fazendo hash = s[0] * 31 + s[1], hash = hash * 31 + s[2] e assim por diante até o final da palavra
    }

    // Depois, basta obter o resto de hash / número de buckets da hashTable
    // O número de buckets, sendo um número primo, faz com que o resto seja diferente em mais casos
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Abre o arquivo do dicionário
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Armazena espaço para variável que será usada como buffer de palavras
    char word[LENGTH+1];

    // Mantém controle do index aonde paramos de escrever em word
    int i = 0;

    // Espaço para letra que será carregada
    char letter;

    // Carrega letras em "word" e insere word na hashTable
    while ((fread(&letter, sizeof(char), 1, dict)))
    {
        // Se o caractere for um newline:
        if (letter == '\n')
        {
            // Chegamos ao final da palavra
            word[i] = '\0';

            // Cria um node para ser inserido na table
            node *createNode = malloc(sizeof(node));
            if (createNode == NULL)
            {
                printf("createNode malloc failed");
                fclose(dict);
                return false;
            }

            // Copia "word" para o word do novo node
            strcpy(createNode->word, word);

            // Pega o hashNum da palavra
            int hashNum = hash(word);

            // Para inserir no começo da table sem perder contato com a linha de nodes
            // Fazemos com que o novo node aponte para o antigo começo da table
            createNode->next = table[hashNum];

            // Substituimos o começo pelo node criado
            table[hashNum] = createNode;

            // Implementamos o número de palavras e zeramos o index de word
            numberWords++;
            i = 0;
        }
        // Se o caractere não for o final da palavra
        else
        {
            // Se i for menor que LENGTH
            if (i < LENGTH)
            {
                // Adiciona a letra em word
                word[i] = letter;
                i++;
            }
            // Se i for maior que length
            else
            {
                printf("There is a word over %i characters long.", LENGTH);
                fclose(dict);
                return false;
            }
        }
    }
    fclose(dict);
    isLoaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (isLoaded == false)
    {
        return 0;
    }
    else
    {
        return numberWords;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Para cada bucket na hashTable
    for (int i = 0; i < N; i++)
    {
        // Variável que será usada para apagar os nodes
        node *deleterNode = table[i];

        // Enquanto deleterNode não for vazio
        while (deleterNode != NULL)
        {
            // traversalNode será o próximo
            node *traversalNode = deleterNode->next;
            // deleterNode será liberado
            free(deleterNode);
            // delterNode se tornará traversalNode
            deleterNode = traversalNode;
        }

        // Evita que table[i] fique apontando para um endereço que foi liberado (boa prática)
        table[i] = NULL;
    }
    return true;
}
