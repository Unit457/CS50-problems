#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cs50.h"
#include <windows.h>

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
        int option = get_int("Option: ");
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

void atmSimulator(void)
{
    printf("\nBrazilian ATM Simulator\n\n");
    bool repeat = true;
    while (repeat)
    {
        bool repeatWithdraw = true;
        int sumWithdraw = 0;
        int twoHundQnt = get_int("How many R$200 notes should be in the atm? ");
        while (twoHundQnt < 0)
        {
            twoHundQnt = get_int("How many R$200 notes should be in the atm? ");
        }

        int oneHundQnt = get_int("How many R$100 notes should be in the atm? ");
        while (oneHundQnt < 0)
        {
            oneHundQnt = get_int("How many R$100 notes should be in the atm? ");
        }

        int fiftyQnt = get_int("How many R$50 notes should be in the atm? ");
        while (fiftyQnt < 0)
        {
            fiftyQnt = get_int("How many R$50 notes should be in the atm? ");
        }

        int twentyQnt = get_int("How many R$20 notes should be in the atm? ");
        while (twentyQnt < 0)
        {
            twentyQnt = get_int("How many R$20 notes should be in the atm? ");
        }

        int tenQnt = get_int("How many R$10 notes should be in the atm? ");
        while (tenQnt < 0)
        {
            tenQnt = get_int("How many R$10 notes should be in the atm? ");
        }

        int fiveQnt = get_int("How many R$5 notes should be in the atm? ");
        while (fiveQnt < 0)
        {
            fiveQnt = get_int("How many R$5 notes should be in the atm? ");
        }

        int twoQnt = get_int("How many R$2 notes should be in the atm? ");
        while (twoQnt < 0)
        {
            twoQnt = get_int("How many R$2 notes should be in the atm? ");
        }
        printf("\n");

        while (repeatWithdraw)
        {
            printf("%ix 200\n", twoHundQnt);
            printf("%ix 100\n", oneHundQnt);
            printf("%ix 50\n", fiftyQnt);
            printf("%ix 20\n", twentyQnt);
            printf("%ix 10\n", tenQnt);
            printf("%ix 5\n", fiveQnt);
            printf("%ix 2\n\n", twoQnt);
            printf("You've withdrawed R$%i in total\n", sumWithdraw);

            int note = get_int("Which note would you like to withdraw (1 to cancel)? ");

            if (note == 1)
            {
                repeatWithdraw = false;
                printf("Leaving...\n");
            }

            if (note == 200 && twoHundQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 200)
            {
                bool qntLoop = true;
                while (qntLoop)
                {
                    int twoHundWithdraw = get_int("How many notes? ");
                    if (twoHundQnt-twoHundWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        twoHundQnt-=twoHundWithdraw;
                        sumWithdraw+=twoHundWithdraw*200;
                        printf("Notes withdrawed successfully.\n\n");

                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }

            else if (note == 100 && oneHundQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 100)
            {
                bool qntLoop = true;
                while (qntLoop)
                {
                    int oneHundWithdraw = get_int("How many notes? ");
                    if (oneHundQnt-oneHundWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        oneHundQnt-=oneHundWithdraw;
                        sumWithdraw+=oneHundWithdraw*100;
                        printf("Notes withdrawed successfully.\n\n");

                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }

            else if (note == 50 && fiftyQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 50)
            {
                bool qntLoop = true;
                while (qntLoop == true)
                {
                    int fiftyWithdraw = get_int("How many notes? ");
                    if (fiftyQnt-fiftyWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        fiftyQnt-=fiftyWithdraw;
                        sumWithdraw+=fiftyWithdraw*50;
                        printf("Notes withdrawed successfully.\n\n");
                        
                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }

            else if (note == 20 && twentyQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 20)
            {
                bool qntLoop = true;
                while (qntLoop)
                {
                    int twentyWithdraw = get_int("How many notes? ");
                    if (twentyQnt-twentyWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        twentyQnt-=twentyWithdraw;
                        sumWithdraw+=twentyWithdraw*20;
                        printf("Notes withdrawed successfully.\n\n");
                        
                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }

            else if (note == 10 && tenQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 10)
            {
                bool qntLoop = true;
                while (qntLoop)
                {
                    int tenWithdraw = get_int("How many notes? ");
                    if (tenQnt-tenWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        tenQnt-=tenWithdraw;
                        sumWithdraw+=tenWithdraw*10;
                        printf("Notes withdrawed successfully.\n\n");
                        
                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }

            else if (note == 5 && fiveQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 5)
            {
                bool qntLoop = true;
                while (qntLoop)
                {
                    int fiveWithdraw = get_int("How many notes? ");
                    if (fiveQnt-fiveWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        fiveQnt-=fiveWithdraw;
                        sumWithdraw+=fiveWithdraw*5;
                        printf("Notes withdrawed successfully.\n\n");
                        
                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }

            else if (note == 2 && twoQnt == 0)
            {
                printf("Note is unavailable.\n\n");
                Sleep(3000);
            }
            else if (note == 2)
            {
                bool qntLoop = true;
                while (qntLoop)
                {
                    int twoWithdraw = get_int("How many notes? ");
                    if (twoQnt-twoWithdraw < 0)
                    {
                        printf("That amount is unavailable.\n\n");
                        Sleep(3000);
                    }
                    else
                    {
                        twoQnt-=twoWithdraw;
                        sumWithdraw+=twoWithdraw*2;
                        printf("Notes withdrawed successfully.\n\n");
                        
                        if (askYesNo("Would you like to finish this action (y/n)? "))
                        {
                            qntLoop = false;
                        }
                    }
                }
            }
            else
            {
                printf("Invalid note.\n");
            }
        }

        if (askYesNo("Do you wish to finish the simulation (y/n)? "))
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