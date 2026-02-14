#include <stdio.h>
#include <stdlib.h>
#include "../cs50.h"

// Função que retorna a quantidade de dígitos do cartão
int len(long long num)
{
    // Divida o número do cartão por 10.
    // Cada vez que realizar essa divisão, adicione +1 a quantidade de dígitos
    // Quando a divisão resultar em 0 (o número não for divisível por 10), atingimos o último dígito do cartão
    int len = 0;
    while (num != 0)
    {
        num = num / 10;
        len++;
    }
    return len;
}

// Verifica se um número de cartão de crédito é válido (VISA, AMEX, MASTERCARD) ou inválido
int main(void)
{
    // Pega o número do cartão
    long long card = get_long_long("Number: ");
    
    // Pega a quantidade de dígitos do cartão
    int cardLen = len(card);

    // Se a quantidade de dígitos não corresponder a nenhum desses valores, é inválido
    if (cardLen != 13 && cardLen != 15 && cardLen != 16)
    {
        printf("INVALID\n");
        exit(0);
    }

    // Agora, vamos obter separadamente os dígitos do cartão

    // Crie uma array que vai armazenar os dígitos
    int digits[cardLen];

    // Se multiplicamos 1 por 10 (cardLen-1) vezes, obtemos o número pelo qual devemos dividir o cartão para obter o seu primeiro dígito
    // Exemplo:
    // Cartão = 2345
    // cardLen = 4
    // cardlen-1 = 3
    // 1 * 10 = 10
    // 10 * 10 = 100
    // 100 * 10 = 1000
    // 2345 / 1000 = 2 (primeiro dígito)
    long long divisor = 1;
    for (int i = 0; i < cardLen-1; i++)
    {
        divisor = divisor * 10;
    }

    // Agora vamos colocar cada dígito do cartão na array
    // Para cada dígito no cartão, cheque:
    for (int i = 0; i < cardLen; i++)
    {
        int digit;
        // Se for o primeiro dígito, basta dividir o cartão pelo divisor que obtemos anteriormente.
        if (i == 0)
        {
            digit = card / divisor;
            digits[i] = digit;
        }
        // Se for qualquer dígito que não seja o último, vamos remover um zero do divisor, dividir o cartão pelo divisor e obter o resto da divisão deste número dividido por 10.
        // Exemplo:
        // Cartão = 1234
        // Divisor = 100 (anteriormente 1000)
        // 1234 / 100 = 12
        // 12 / 10 = 1, resto 2 (2 é o dígito que buscamos)
        else if (i != cardLen-1)
        {
            divisor = divisor / 10;
            digit = (card / divisor) % 10;
            digits[i] = digit;
        }
        // Se for o último dígito, basta dividir o cartão por 10 e obter o resto.
        // Exemplo:
        // Cartão - 918371350513
        // Cartão / 10 = 91837135051, resto 3 (3 é o dígito que buscamos)
        else
        {
            digit = card % 10;
            digits[i] = digit;
        }
    }

    int doubledDigitsSize;
    int nonDoubledDigitsSize;

    // Para os cartões de tamanho ímpar
    if (cardLen == 13 || cardLen == 15)
    {
        // Se o primeiro dígito não for igual a 4, não pode ser um Visa
        if (digits[0] != 4)
        {
            // Só poderia ser um Amex
            // Se o primeiro dígito não for igual a 3 ou se o segundo dígito não for igual nem a 4 nem a 7, também não pode ser um Amex
            // Logo, o cartão é inválido
            if (digits[0] != 3 || (digits[1] != 4 && digits[1] != 7))
            {
                printf("INVALID\n");
                exit(0);
            }
        }

        // A quantidade de dígitos que serão duplicados será (cardLen-1) / 2
        doubledDigitsSize = (cardLen-1) / 2;
        // A quantidade de dígitos que não serão duplicados será 1 a mais do que aqueles que serão
        nonDoubledDigitsSize = doubledDigitsSize + 1;
    }
    // Para os cartões de tamanho par
    else
    {
        // Se o primeiro dígito não for igual a 4, não pode ser um Visa
        if (digits[0] != 4)
        {
            // Se o primeiro dígito não for igual a cinco ou se o segundo dígito não estiver incluído em [1, 2, 3, 4, 5], também não pode ser um Mastercard
            // Logo, o cartão é inválido
            if (digits[0] != 5 || (digits[1] < 1 || digits[1] > 5))
            {
                printf("INVALID\n");
                exit(0);
            }
        }
        
        // A quantidade de dígitos duplicados será cardLen / 2, e a quantidade de dígitos não duplicados será a mesma (o número é par)  
        doubledDigitsSize = cardLen / 2;
        nonDoubledDigitsSize = doubledDigitsSize;
    }

    // Inicializa a array de ambos
    int doubledDigits[doubledDigitsSize];
    int nonDoubledDigits[nonDoubledDigitsSize];

    // Multiplica todos os dígitos que devem ser multiplicados por 2
    for (int i = cardLen-2, j = 0; i > -1; i-=2, j++)
    {
        doubledDigits[j] = digits[i]*2;
    }

    // Armazena todos aqueles que não devem ser multiplicados
    for (int i = cardLen-1, j = 0; i > -1; i-=2, j++)
    {
        nonDoubledDigits[j] = digits[i];
    }

    int checksum = 0;

    for (int i = 0; i < doubledDigitsSize; i++)
    {
        // Divide o número em dois dígitos, para caso seja um número de duas casas decimais
        int firstDigit = doubledDigits[i] / 10;
        int secondDigit = doubledDigits[i] % 10;
        // Os adiciona a checksum
        checksum += firstDigit + secondDigit;
    }

    for (int i = 0; i < nonDoubledDigitsSize; i++)
    {
        // Adiciona cada número não multiplicado ao checksum
        checksum += nonDoubledDigits[i];
    }

    // Se a checksum for válida
    if (checksum % 10 == 0)
    {   
        // Checando cardLens
        if (cardLen == 13 || cardLen == 16)
        {
            // Se o número começa com 4, é visa
            if (digits[0] == 4)
            {
                printf("VISA\n");
                exit(0);
            }
            // Se não, é mastercard
            else
            {
                printf("MASTERCARD\n");
                exit(0);
            }
        }
        // Se o primeiro dígito é 3 e o segundo é 4 ou 7
        else if (digits[0] == 3 && (digits[1] == 4 || digits[1] == 7))
        {
            // É amex
            printf("AMEX\n");
            exit(0);
        }
        else
        {
            // Qualquer outra coisa, é inválido
            printf("INVALID\n");
            exit(0);
        }
    }
    // Se a checksum for inválida
    else
    {
        printf("INVALID\n");
        exit(0);
    }
}