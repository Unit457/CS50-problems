#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "../../cs50.h"
#include "auxiliary.h"

// Funções auxiliares para os programas

// Utilizada no conversor de unidades
void conversion_menu() {
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
    printf("----------------------------\n");
    printf("\n");
}

// Utilizada no askYesNo para validar o caractere/string inserido
bool ynValidator(const char *value) {
    // Se o valor inserido for "y" ou "yes" é válido
    if (strcmp(value, "y") == 0 || strcmp(value, "yes") == 0) {
        return true;
    }
    
    // Se o valor inserido for "n" ou "no" é válido
    else if (strcmp(value, "n") == 0 || strcmp(value, "no") == 0) {
        return true;
    }

    // Se não for nenhum desses, é inválido
    else {
        return false;
    }
}

// Utilizada no ATM para perguntar ao usuário se deseja sair ou não de alguma funcionalidade
bool askYesNo(const char *value) {
    char *yn;
    bool validChar = false;

    while (!validChar) {
        yn = get_string("%s", value);

        for (int i = 0; yn[i]; i++) {
            yn[i] = tolower(yn[i]);
        }

        validChar = ynValidator(yn);
    }

    if (strcmp(yn, "y") == 0 || strcmp(yn, "yes") == 0) return true;
    else return false;
}

// Utilizada no ATM para perguntar quantas notas de tal valor estarão na simulação
int getNotesQnt(const int num) {
    int qnt = get_int("How many R$%i notes should be in the atm? ", num);
    while (qnt < 0) {
        qnt = get_int("How many R$%i notes should be in the atm? ", num);
    }

    return qnt;
}

// Utilizada no ATM para mostrar informações de usuário e selecionar opção de ação
int atmOptionMenu(const int values[], const int noteQnt[], const float userMoney, const float sumWithdraw, const int numValues) {
    // Mostra quantas notas estão disponíveis para cada valor
    for (int i = 0; i < numValues; i++) {
        printf("%ix notes of R$%i\n", noteQnt[i], values[i]);
    }

    // Mostra informações do usuário
    printf("\n");
    printf("You have R$%.2f available\n", userMoney);
    printf("You've withdrawed R$%i in total\n", sumWithdraw);
    Sleep(1500);
    printf("\n");

    // Usuário seleciona qual ação deseja realizar
    int option = 0;
    while (option < 1 || option > 3) {
        printf("1 - Withdrawal\n");
        printf("2 - Deposit\n");
        printf("3 - Exit\n");
        option = get_int("Input an option: ");
        printf("\n");
    }

    return option;
}

// Utilizada no ATM para realizar retirada
void withdrawal(const int values[], int noteQnt[], float *userMoney, float *sumWithdraw, const int numValues) {
    bool repeatWithdraw = true;
    while (repeatWithdraw) {
        for (int i = 0; i < numValues; i++) {
            if (i == 0)
                printf("[%ix R$%i, ", noteQnt[i], values[i]);
            else if (i < numValues-1)
                printf("%i R$%i, ", noteQnt[i], values[i]);
            else
                printf("%ix R$%i]\n", noteQnt[i], values[i]);
        }

        //Escolhe a nota que será sacada
        int note, notePos;
        bool noteNotFound = true;
        do {
            note = get_int("Which note would you like to withdraw (0 to cancel)? ");
            if (note == 0) {
                noteNotFound = false;
                repeatWithdraw = false;
            }

            for (int i = 0; i < numValues; i++) {
                if (note == values[i]) {
                    notePos = i;
                    noteNotFound = false;
                }
            }
        } while (noteNotFound);

        if (note != 0) {
            // Checa se a nota escolhida está disponível
            if (noteQnt[notePos] == 0) {
                printf("Note is unavailable.\n\n");
                Sleep(1000);
            }

            // Se estiver
            else {
                bool qntLoop = true;
                while (qntLoop) {
                    // Quantas notas?
                    int withdrawQnt = get_int("How many notes? ");
                    
                    // Checa se a quantidade de notas inserida está disponível
                    if (noteQnt[notePos]-withdrawQnt < 0) {
                        printf("That amount is unavailable.\n\n");
                        Sleep(1000);
                    }

                    // Checa se o usuário possui dinheiro o suficiente para retirar o valor
                    else if (*userMoney < withdrawQnt*values[notePos]) {
                        printf("Your account does not have enough money to withdraw this amount.\n");
                        Sleep(1000);
                    }

                    else {
                        // Atualiza quantidade de notas disponíveis, a soma de dinheiro retirado e o dinheiro do usuário
                        noteQnt[notePos] -= withdrawQnt;
                        *sumWithdraw += withdrawQnt*values[notePos];
                        *userMoney -= withdrawQnt*values[notePos];
                        printf("Notes withdrawed successfully.\n\n");
                        // Pergunta ao usuário se ele deseja sair dessa ação
                        if (askYesNo("Would you like to finish this action (y/n)? ")) qntLoop = false;
                    }
                }
            }
        }
    }
}
