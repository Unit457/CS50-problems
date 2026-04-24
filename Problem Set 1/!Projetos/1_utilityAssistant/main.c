#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "../../cs50.h"
#include "utilities.h"
#include "auxiliary.h"

int main(void)
{
    bool repeat = true;
    while (repeat) {
        printf("------ Utility assistant ------\n");
        printf("\n");
        printf("1 - ATM\n");
        printf("2 - Unit conversor\n");
        printf("3 - Grade point average calculator\n");
        printf("4 - Exit\n");
        
        int option = 0;
        while (option < 1 || option > 4) {
            option = get_int("Option: ");
        }

        switch (option) {
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