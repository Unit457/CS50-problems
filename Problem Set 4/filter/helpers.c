#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Para cada pixel:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Some todos os valores RGB, divida por 3 e arredonde
            BYTE average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Redefina a cor dos outros pixels
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Para cada pixel da primeira metade da imagem:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            // Guarda o pixel original
            RGBTRIPLE cache = image[i][j];

            // Width tem tamanho 255, esse pixel se torna image[i][254], então, width-1
            // - j faz com que a troca acompanhe os pixels
            // Se width = 255:
            // image[0][0] = image[0][254-0]
            // image[0][1] = image[0][254-1]
            // E assim por diante
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = cache;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Cria uma imagem nova, preservando a original
    RGBTRIPLE newImage[height][width];

    // Para cada pixel:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Cada pixel vai ter uma soma dos valores em sua volta
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            // Preciso saber por qual número dividir as somas para pegar o valor médio entre os pixels
            int divisor = 0;

            // Para cada pixel vizinho:
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Valores utilizados para caminhar aos vizinhos
                    int imageI = i + k;
                    int imageJ = j + l;

                    // Checando se o pixel está dentro da imagem
                    if (!(imageI > height-1 || imageI < 0 || imageJ > width-1 || imageJ < 0))
                    {
                        // Soma todos os valores e adiciona 1 ao divisor (pois encontramos um pixel vizinho válido)
                        sumRed+=image[imageI][imageJ].rgbtRed;
                        sumGreen+=image[imageI][imageJ].rgbtGreen;
                        sumBlue+=image[imageI][imageJ].rgbtBlue;
                        divisor++;
                    }
                }
            }

            // Calcula a média a partir da soma dos valores dos pixels vizinhos
            int newRed = round((float) sumRed/divisor);
            int newGreen = round((float) sumGreen/divisor);
            int newBlue = round((float) sumBlue/divisor);

            // Redefine os valores na nova imagem
            if (newRed > 255)
            {
                newImage[i][j].rgbtRed = 255;
            }
            else
            {
                newImage[i][j].rgbtRed = newRed;
            }

            if (newGreen > 255)
            {
                newImage[i][j].rgbtGreen = 255;
            }
            else
            {
                newImage[i][j].rgbtGreen = newGreen;
            }

            if (newBlue > 255)
            {
                newImage[i][j].rgbtBlue = 255;
            }
            else
            {
                newImage[i][j].rgbtBlue = newBlue;
            }
        }
    }

    // Atualiza a imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = newImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = newImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newImage[i][j].rgbtBlue;
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Essas arrays são os valores dos quais os vizinhos tem que ser multiplicados por
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Cria uma imagem nova, preservando a original
    RGBTRIPLE newImage[height][width];

    // Para cada pixel:
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Cada pixel vai ter duas somas dos valores multiplicados a sua volta, uma soma dos verticais e outra dos horizontais (X e Y)
            int sumRedX = 0, sumRedY = 0;
            int sumGreenX = 0, sumGreenY = 0;
            int sumBlueX = 0, sumBlueY = 0;

            // Para cada vizinho:
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Valores utilizados para caminhar aos vizinhos
                    int imageI = i + k;
                    int imageJ = j + l;

                    // Checando se o pixel vizinho está dentro da imagem
                    if (!(imageI > height-1 || imageI < 0 || imageJ > width-1 || imageJ < 0))
                    {
                        // Posição da array de multiplicadores de acordo com o vizinho (+1 porque não existe gx[-1][-1]))
                        int gi = k+1;
                        int gj = l+1;

                        // Multiplica cada cor de pixel pelo seu multiplicador vertical e horizontal, somando a respectiva variável
                        sumRedX+=image[imageI][imageJ].rgbtRed * gx[gi][gj];
                        sumRedY+=image[imageI][imageJ].rgbtRed * gy[gi][gj];

                        sumGreenX+=image[imageI][imageJ].rgbtGreen * gx[gi][gj];
                        sumGreenY+=image[imageI][imageJ].rgbtGreen * gy[gi][gj];

                        sumBlueX+=image[imageI][imageJ].rgbtBlue* gx[gi][gj];
                        sumBlueY+=image[imageI][imageJ].rgbtBlue * gy[gi][gj];
                    }
                }
            }

            // Atribui os valores de acordo com a fórmula fornecida pelo exercício
            int newRed = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int newGreen = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int newBlue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            // Atualiza os valores na imagem nova
            if (newRed > 255)
            {
                newImage[i][j].rgbtRed = 255;
            }
            else
            {
                newImage[i][j].rgbtRed = newRed;
            }

            if (newGreen > 255)
            {
                newImage[i][j].rgbtGreen = 255;
            }
            else
            {
                newImage[i][j].rgbtGreen = newGreen;
            }

            if (newBlue > 255)
            {
                newImage[i][j].rgbtBlue = 255;
            }
            else
            {
                newImage[i][j].rgbtBlue = newBlue;
            }

        }
    }

    // Atualiza os valores na imagem original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = newImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = newImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = newImage[i][j].rgbtBlue;
        }
    }
    return;
}