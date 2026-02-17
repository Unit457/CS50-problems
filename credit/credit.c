#include <stdio.h>
#include <stdlib.h>
#include "../cs50.h"

// Função que retorna a quantidade de dígitos do cartão
int len(long long num)
{
    int len = 0;
    // Enquanto o número não for 0
    while (num != 0)
    {
        // Divida o número do cartão por 10 e adicione +1 a quantidade de dígitos
        num/=10;
        len++;
        // Quando a divisão resultar em 0 (o número não for divisível por 10), atingimos o último dígito do cartão
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

    // Agora vamos colocar cada dígito do cartão na array
    // Porém, ao contrário, para enxergamos com mais facilidade quais números devem e não devem ser multiplicados
    int digit;
    int divisor = 10;
    // Para cada dígito no cartão:
    for (int i = cardLen-1; i > -1; i++)
    {
        // Se for o primeiro dígito
        if (i == 0)
        {
            // Basta realizar módulo por 10
            digit = card % divisor;
        }
        // Se não for o primeiro nem o último dígito
        else if (i != cardLen-1)
        {
            // Basta dividir card por divisor e realizar módulo por 10
            digit = (card / divisor) % 10;
            // Depois, multiplicamos o divisor por 10 (12345 / 10 = 1234, 1234 % 10 = 4 | 12345 / 100 = 123, 123 % 10 = 3 | ...)
            divisor*=10;
        }
        // Quando chegarmos no último dígito
        else
        {
            // Basta dividir pelo divisor (12345 / 10000 = 1)
            digit = card / divisor;
        }
        digits[i] = digit;
    }

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
    }

    // Agora vamos realizar a checksum
    int checksum = 0;
    int doubleChoice = 0;
    int digit;
    
    // Para cada dígito em digits
    for (int i = 0; i < cardLen; i++)
    {
        // Se ele deve ser multiplicado
        if (doubleChoice)
        {
            // Multiplique-o
            digit = digits[i] * 2;

            // Se o resultado tiver mais que 1 dígito
            if (digit > 9)
            {
                // Adicione os dígitos separadamente na checksum
                checksum+=(digit/10)+(digit%10);
            }
            // Se o resultado tiver apenas 1 dígito
            else
            {
                // Adicione normalmente
                checksum+=digit;
            }

            // O próximo dígito não deve ser multiplicado
            doubleChoice = 0;
        }
        // Se ele não deve ser multiplicado
        else
        {
            // Adicione-o normalmente
            checksum+=digits[i];

            // O próximo dígito deve ser multiplicado
            doubleChoice = 1;
        }
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