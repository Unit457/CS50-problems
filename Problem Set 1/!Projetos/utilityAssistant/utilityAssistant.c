#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "../../cs50.h"

bool checkForLeave(char* value);

bool checkForLeave(char* value)
{
    if (strcmp(value, "y") == 0 || strcmp(value, "yes") == 0)
    {
        return true;
    }

    else if (strcmp(value, "n") == 0 || strcmp(value, "no") == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

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

        validChar = checkForLeave(yn);
    }

    return (strcmp(yn, "y") == 0 || strcmp(yn, "yes") == 0);
}

int getNotesQnt(int num)
{
    int qnt = get_int("How many R$%i notes should be in the atm? ", num);
    while (qnt < 0)
    {
        qnt = get_int("How many R$%i notes should be in the atm? ", num);
    }

    return qnt;
}

void mediumCalc(void);

void mediumCalc(void)
{
    printf("\nGrade point average calculator\n\n");
    bool repeat = true;
    while (repeat)
    {
        int qntNotas = get_int("How many grades are there? ");

        float sum = 0;
        printf("Insert the grades' values: \n");
        for (int i = 0; i < qntNotas; i++)
        {
            float nota = get_float("Grade %i: ", i+1);
            sum+=nota;
        }

        printf("The student's average is: %.2f\n", sum/qntNotas);

        if (askYesNo("Do you wish to leave (y/n)? "))
        {
            repeat = false;
        }
    }
}

void unitConv(void);

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

void atmSimulator(void);

#define numOfValues 7

void atmSimulator(void)
{
    printf("\nBrazilian ATM Simulator\n\n");
    bool repeat = true;
    while (repeat)
    {
        bool repeatWithdraw = true;
        int sumWithdraw = 0;
        
        int values[numOfValues] = {200, 100, 50, 20, 10, 5, 2};
        int noteQnt[numOfValues];

        for (int i = 0; i < numOfValues; i++)
        {
            noteQnt[i] = getNotesQnt(values[i]);
        }

        printf("\n");

        while (repeatWithdraw)
        {
            for (int i = 0; i < numOfValues; i++)
            {
                printf("%ix R$%i\n\n", noteQnt[i], values[i]);
            }
            printf("You've withdrawed R$%i in total\n", sumWithdraw);

            int note = get_int("Which note would you like to withdraw (1 to cancel)? ");

            if (note == 1)
            {
                repeatWithdraw = false;
                printf("Leaving...\n");
            }

            else
            {
                for (int i = 0; i < numOfValues; i++)
                {
                    if (note == values[i] && noteQnt[i] == 0)
                    {
                        printf("Note is unavailable.\n\n");
                        Sleep(1000);
                    }

                    else if (note == values[i])
                    {
                        bool qntLoop = true;
                        while (qntLoop)
                        {
                            int withdrawQnt = get_int("How many notes? ");
                            if (noteQnt[i]-withdrawQnt < 0)
                            {
                                printf("That amount is unavailable.\n\n");
                                Sleep(1000);
                            }

                            else
                            {
                                noteQnt[i]-=withdrawQnt;
                                sumWithdraw+=withdrawQnt*values[i];
                                printf("Notes withdrawed successfully.\n\n");
                            }

                            if (askYesNo("Would you like to finish this action (y/n)? "))
                            {
                                qntLoop = false;
                            }
                        }
                    }
                }
            }
        }
        if (askYesNo("Would you like to end the simulation (y/n)? "))
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
        while (option != 1 && option != 2 && option != 3 && option != 4)
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