#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "../../cs50.h"

// Utilizada no askYesNo para validar o caractere/string inserido
bool ynValidator(char* value);

// Utilizada para perguntar ao usuário se deseja sair ou não
bool askYesNo(const char *value);

// Utilizada no ATM para perguntar quantas notas de tal valor estarão na simulação
int getNotesQnt(int num);

void mediumCalc(void)
{
    printf("\nGrade point average calculator\n\n");
    bool repeat = true;
    while (repeat)
    {
        int qntNotas = get_int("How many grades are there? ");

        float sum = 0;
        printf("Insert the grades' values: \n");
        for (int i = 1; i < qntNotas+1; i++)
        {
            float nota = get_float("Grade %i: ", i);
            sum+=nota;
        }

        printf("The student's average is: %.2f\n", sum/qntNotas);

        if (askYesNo("Do you wish to leave (y/n)? "))
        {
            repeat = false;
        }
    }
}

void unitConv(void)
{
    printf("\nUnit conversor\n\n");
    bool repeat = true;
    while (repeat)
    {
        printf("Choose a conversion:\n");
        printf("----------------------------\n");
        printf("1 - Celsius -> Fahrenheit\n");
        printf("2 - Fahrenheit -> Celsius\n");
        printf("----------------------------\n");
        printf("3 - Meters -> Foot\n");
        printf("4 - Foot -> Meters\n");
        printf("----------------------------\n");
        printf("5 - Kilos -> Pounds\n");
        printf("6 - Pounds -> Kilos\n");
        printf("----------------------------\n\n");
        int option = 0;
        while (option < 1 || option > 6)
        {
            option = get_int("Option: ");
        }

        float valor = get_float("Insert the value: ");

        switch (option)
        {
            case 1:
                float valorFahr = (valor * 9/5) + 32;
                printf("%.2f °C = %.2f°F\n\n", valor, valorFahr);
                break;
            
            case 2:
                float valorCels = (valor - 32) * 5/9;
                printf("%.2f °F = %.2f°C\n\n", valor, valorCels);
                break;

            case 3:
                float valorPes = valor * 3.281;
                printf("%.2f meters tall = %.2f foot tall\n\n", valor, valorPes);
                break;

            case 4:
                float valorMetros = valor / 3.281;
                printf("%.2f foot tall = %.2f meters tall\n\n", valor, valorMetros);
                break;
            
            case 5:
                float valorLibras = valor * 2.205;
                printf("%.2fkg = %.2flbs\n\n", valor, valorLibras);
                break;

            case 6:
                float valorQuilos = valor / 2.205;
                printf("%.2flbs = %.2fkg\n\n", valor, valorQuilos);
                break;
            
        }

        if (askYesNo("Do you wish to leave (y/n)? "))
        {
            repeat = false;
        }
    }
}

#define numOfValues 7

void atmSimulator(void)
{
    printf("\nBrazilian ATM Simulator\n\n");
    bool repeat = true;
    while (repeat)
    {   
        // Soma do valor sacado
        int sumWithdraw = 0;
        
        // Valores disponíveis
        int values[numOfValues] = {200, 100, 50, 20, 10, 5, 2};
        // Quantidade disponível para cada nota
        int noteQnt[numOfValues];

        // Pergunta quantas notas de cada valor devem existir
        for (int i = 0; i < numOfValues; i++)
        {
            noteQnt[i] = getNotesQnt(values[i]);
        }

        printf("\n");

        // Pergunta quanto de dinheiro o usuário deve ter
        float userMoney = -1;
        while (userMoney < 0)
        {
            userMoney = get_float("How much money should the user have? ");
        }
        printf("\n");

        bool repeatActions = true;
        while (repeatActions)
        {
            // Mostra quantas notas estão disponíveis para cada valor
            for (int i = 0; i < numOfValues; i++)
            {
                printf("%ix notes of R$%i\n", noteQnt[i], values[i]);
            }
            printf("You have RS%.2f available\n", userMoney);
            printf("You've withdrawed R$%i in total\n", sumWithdraw);
            printf("\n");

            // Usuário seleciona qual ação deseja realizar
            int option = 0;
            while (option < 1 || option > 3)
            {
                printf("Withdrawal: 1\n");
                printf("Deposit: 2\n");
                printf("Exit: 3\n");
                option = get_int("Input an option: ");
                printf("\n");
            }
            
            switch (option)
            {
                // Se escolheu retirada:
                case 1:
                    bool repeatWithdraw = true;
                    while (repeatWithdraw)
                    {
                        //Escolhe a nota que será sacada
                        int note = get_int("Which note would you like to withdraw (1 to cancel)? ");

                        if (note == 1)
                        {
                            repeatWithdraw = false;
                            printf("Leaving...\n");
                        }

                        else
                        {
                            // Checa se a note escolhida está disponível
                            for (int i = 0; i < numOfValues; i++)
                            {
                                if (note == values[i] && noteQnt[i] == 0)
                                {
                                    printf("Note is unavailable.\n\n");
                                    Sleep(1000);
                                }

                                // Se estiver
                                else if (note == values[i])
                                {
                                    bool qntLoop = true;
                                    while (qntLoop)
                                    {
                                        // Quantas notas?
                                        int withdrawQnt = get_int("How many notes? ");
                                        
                                        // Checa se a quantidade de notas inserida está disponível
                                        if (noteQnt[i]-withdrawQnt < 0)
                                        {
                                            printf("That amount is unavailable.\n\n");
                                            Sleep(1000);
                                        }

                                        // Checa se o usuário possui dinheiro o suficiente para retirar o valor
                                        else if (userMoney < withdrawQnt*values[i])
                                        {
                                            printf("Your account does not have enough money to withdraw this amount.\n");
                                            Sleep(1000);
                                        }

                                        // Atualiza quantidade de notas disponíveis, a soma de dinheiro retirado e o dinheiro do usuário
                                        else
                                        {
                                            noteQnt[i]-=withdrawQnt;
                                            sumWithdraw+=withdrawQnt*values[i];
                                            userMoney-=withdrawQnt*values[i];
                                            printf("Notes withdrawed successfully.\n\n");
                                        }

                                        // Pergunta ao usuário se ele deseja sair dessa ação
                                        if (askYesNo("Would you like to finish this action (y/n)? "))
                                        {
                                            qntLoop = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;
                
                // Se escolheu depositar
                case 2:
                    // Quanto deve ser depositado?
                    float addedMoney = -1;
                    while (addedMoney < 0) 
                    {
                        addedMoney = get_float("How much money would you like to deposit to your account? R$");
                    }

                    // Adiciona o dinheiro
                    userMoney+=addedMoney;  
                    break;
                
                // Se escolheu sair
                case 3:
                    repeatActions = false;
                    break;
            }
        }

        // Pergunta se o usuário gostaria de iniciar outro caixa eletrônico
        if (!askYesNo("Would you like to begin another simulation (y/n)? "))
        {
            repeat = false;
        }
    }
}

int main(void)
{
    bool repeat = true;
    while (repeat)
    {
        printf("Utility assistant\n\n");
        printf("1 - ATM\n");
        printf("2 - Unit conversor\n");
        printf("3 - Grade point average calculator\n");
        printf("4 - Exit\n");
        
        int option = 0;
        while (option < 1 || option > 4)
        {
            option = get_int("Option: ");
        }

        switch (option)
        {
            case 1:
                atmSimulator();
                break;
            case 2:
                unitConv();
                break;
            case 3:
                mediumCalc();
                break;
            case 4:
                repeat = false;
        }
    }
    return 0;
}

// Utilizada para validar o caractere/string inserida quando o usuário é perguntando se deseja sair ou não
bool ynValidator(char* value)
{
    // Se o valor inserido for "y" ou "yes" é válido
    if (strcmp(value, "y") == 0 || strcmp(value, "yes") == 0)
    {
        return true;
    }
    
    // Se o valor inserido for "n" ou "no" é válido
    else if (strcmp(value, "n") == 0 || strcmp(value, "no") == 0)
    {
        return true;
    }

    // Se não for nenhum desses, é inválido
    else
    {
        return false;
    }
}

// Utilizada para perguntar ao usuário se deseja sair ou não
bool askYesNo(const char *value)
{
    char *yn;
    bool validChar = false;

    while (!validChar)
    {
        yn = get_string("%s", value);

        for (int i = 0; yn[i]; i++)
        {
            yn[i] = tolower(yn[i]);
        }

        validChar = ynValidator(yn);
    }

    return (strcmp(yn, "y") == 0 || strcmp(yn, "yes") == 0);
}

// Utilizada no ATM para perguntar quantas notas de tal valor estarão na simulação
int getNotesQnt(int num)
{
    int qnt = get_int("How many R$%i notes should be in the atm? ", num);
    while (qnt < 0)
    {
        qnt = get_int("How many R$%i notes should be in the atm? ", num);
    }

    return qnt;
}