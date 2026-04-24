#ifndef AUXILIARY_H
#define AUXILIARY_H
#include <stdbool.h>

// Funções auxiliares para os programas

// Utilizada no askYesNo para validar o caractere/string inserido
bool ynValidator(const char *value);

// Utilizada para perguntar ao usuário se deseja sair ou não
bool askYesNo(const char *value);

// Utilizada no conversor de unidades
void conversion_menu();

// Utilizada no ATM para perguntar quantas notas de tal valor estarão na simulação
int getNotesQnt(const int num);

// Utilizada no ATM para mostrar informações de usuário e selecionar opção de ação
int atmOptionMenu(const int values[], const int noteQnt[], const float userMoney, const float sumWithdraw, const int numValues);

// Utilizada no ATM para realizar retirada
void withdrawal(const int values[], int noteQnt[], float *userMoney, float *sumWithdraw, const int numValues);

#endif