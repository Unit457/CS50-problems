#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "../../cs50.h"
#include "auxiliary.h"
#include "utilities.h"

// Utilidades disponíveis no programa

// Calculadora de médias
void mediumCalc(void) {
    printf("\n------ Grade point average calculator ------\n\n");
    bool repeat = true;

    while (repeat) {
        int qntNotas = get_int("How many grades are there? ");
        
        float sum = 0;
        printf("Insert the grades' values: \n");
        for (int i = 1; i < qntNotas+1; i++) {
            float nota = get_float("Grade %i: ", i);
            sum+=nota;
        }

        printf("The student's average is: %.2f\n", sum/qntNotas);

        if (askYesNo("Do you wish to leave (y/n)? ")) repeat = false;
    }
}

// Conversor de unidades
void unitConv(void) {
    printf("\n------ Unit conversor ------\n\n");
    bool repeat = true;
    
    while (repeat) {
        conversion_menu();

        int option = 0;
        while (option < 1 || option > 6) option = get_int("Option: ");

        float valor = get_float("Insert the value: ");

        switch (option) {
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

        if (askYesNo("Do you wish to leave (y/n)? ")) repeat = false;
    }
}

// Simulador de ATM
#define numValues 7
void atmSimulator(void) {
    printf("\n------ Brazilian ATM Simulator ------\n\n");
    
    bool repeat = true;
    while (repeat) {
        // Valores de nota disponíveis
        const int values[numValues] = {200, 100, 50, 20, 10, 5, 2};
        // Quantidade disponível para cada nota
        int noteQnt[numValues];

        // Pergunta quantas notas de cada valor devem existir
        for (int i = 0; i < numValues; i++) {
            noteQnt[i] = getNotesQnt(values[i]);
        }
        printf("\n");

        // Pergunta quanto de dinheiro o usuário deve ter
        float userMoney = -1;
        while (userMoney < 0) {
            userMoney = get_float("How much money should the user have? ");
        }
        printf("\n");

        // Inicia o menu principal do ATM
        bool repeatActions = true;
        float sumWithdraw = 0;
        while (repeatActions) {
            int option = atmOptionMenu(values, noteQnt, userMoney, sumWithdraw, numValues);
            
            switch (option) {

                // Se escolheu retirada:
                case 1:
                    withdrawal(values, noteQnt, &userMoney, &sumWithdraw, numValues);
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
        if (askYesNo("Would you like to finish this utility (y/n)? ")) repeat = false;
    }
}