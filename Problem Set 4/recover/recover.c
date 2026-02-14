#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Verifica os argumentos do programa
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    // Abre o arquivo fornecido como read binary
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open forensics image.\n");
        return 1;
    }

    // Cria o buffer
    BYTE buffer[512];

    // Define o primeiro e segundo bytes
    const uint8_t firstByte = 0xFF;
    const uint8_t secondByte = 0xD8;

    // Monitora a quantidade de arquivos lidos
    int i = 0;
    // Declara variável para abrir arquivo a ser escrito
    FILE *openFile;
    // Monitora se estamos abrindo o primeiro arquivo ou não
    int firstOpen = 1;
    // Cria uma array para armazenar o nome do arquivo a se escrever
    char filename[8];

    // Enquanto estiver lendo blocos de um jpeg
    while ((fread(buffer, sizeof(uint8_t), 512, input) != 0))
    {
        // Se ainda não lemos 50 arquivos:
        if (i < 50)
        {
            // O primeiro, segundo e terceiro bytes do começo de um arquivo jpeg são sempre os mesmos
            // Já o último, é diversificado, mas sempre começando com "0x" (1110)
            // Então, estamos pegando o quarto byte e zerando os últimos 4 bits usando uma operação and quando fazemos:
            // (buffer[3] & 0xf0 (0xf0 = 11110000)) vai zerar os 4 últimos bits e preservar os 4 primeiros
            // Dessa forma, podemos verificar se os 4 primeiros bits do terceiro byte correspondem a "0x" (1110)
            // (0xe0 = 11100000), que é como o byte deve ficar após ter os últimos 4 bits zerados

            // Se o bloco no buffer for o começo do arquivo jpeg:
            if (buffer[0] == firstByte && buffer[1] == secondByte && buffer[2] == firstByte && (buffer[3] & 0xf0) == 0xe0)
            {
                // Se for o primeiro arquivo:
                if (firstOpen)
                {
                    // sprintf formata uma string
                    // filename é aonde vamos armazenar essa string
                    // 03i significa: "Se i tiver menos de 3 dígitos, preencha sua esquerda com 0's"
                    // Dessa forma, "1.jpg" se torna "001.jpg"
                    sprintf(filename, "%03i.jpg", i);

                    // Abre um arquivo (wb = write binary) para armazenar o conteúdo do buffer
                    openFile = fopen(filename, "wb");

                    // Escreve o conteúdo do buffer no arquivo novo
                    fwrite(buffer, sizeof(uint8_t), 512, openFile);

                    // Os próximos arquivos não são mais o primeiro a ser aberto
                    firstOpen = 0;
                }
                // Se não for o primeiro arquivo
                else
                {
                    // Fecha o arquivo anterior
                    fclose(openFile);

                    // Mais um arquivo lido com sucesso
                    i++;

                    // Formata o nome como explicado anteriormente
                    sprintf(filename, "%03i.jpg", i);

                    // Abre o arquivo a se escrever como "write binary"
                    openFile = fopen(filename, "wb");

                    // Escreve o conteúdo do buffer no arquivo novo
                    fwrite(buffer, sizeof(uint8_t), 512, openFile);
                }
            }
            // Se o bloco no buffer não for o começo de um jpeg:
            else
            {
                // Se já estivermos encontrado o primeiro arquivo
                if (!firstOpen)
                {
                    // Escreve o conteúdo do buffer no arquivo novo (que já foi aberto anteriormente)
                    fwrite(buffer, sizeof(uint8_t), 512, openFile);
                }
            }
        }
    }
    // Fecha o último arquivo aberto e o input
    fclose(openFile);
    fclose(input);
    return 0;
}
