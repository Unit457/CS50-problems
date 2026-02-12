#include <stdio.h>
#include "cs50.h"

int main(void)
{
    int height;
    // Enquanto a height não for entre 1 e 8, pergunte-a novamente
    do
    {
        height = get_int("Height: ");
    }
    while ((height < 1) || (height > 8));

    // Para cada unidade de height
    for (int i = 1; i < height+1; i++)
    {   
        // A quantidade de espaços antes das tags será a altura total da pirâmide - (a iteração que estivermos)
        // Por exemplo: 
        // Se estamos printando a primeira tag de uma pirâmide com 4 de altura, precisamos de 3 (4-1) espaços antes de printar a tag 
        int spaces = height-(i);
        // A quantidade de tags se dá pela iteração que estivermos
        int tags = i;

        // Printar espaços
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }

        // Printar tags
        for (int k = 0; k < tags; k++)
        {
            printf("#");
        }

        // Printar espaço do meio
        printf("  ");

        // Printar tags restantes
        for (int k = 0; k < tags; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}