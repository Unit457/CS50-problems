// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open first file.\n");
        return 2;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open second file.\n");
        return 3;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Cria o buffer do tamanho do header do arquivo
    uint8_t headerBuffer[HEADER_SIZE];
    // Lê o header
    fread(headerBuffer, HEADER_SIZE, 1, input);
    // Escreve o buffer no arquivo novo
    fwrite(headerBuffer, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // Cria o buffer para as samples
    int16_t sampleBuffer;
    // Enquanto estiver lendo para o buffer(não chegar no EOF)
    while (fread(&sampleBuffer, sizeof(int16_t), 1, input))
    {
        // Multiplica o valor do sample pelo factor
        sampleBuffer *= factor;
        // Escreve no output
        fwrite(&sampleBuffer, sizeof(int16_t), 1, output);
    }

    // Fecha os arquivos
    fclose(input);
    fclose(output);
}