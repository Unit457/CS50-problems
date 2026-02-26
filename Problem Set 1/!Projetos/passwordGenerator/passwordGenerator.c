#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int random(int min, int max);

int main(void)
{
    srand(time(NULL));

    const int passSize = random(12, 16);

    const char *letters = "ABCDEFGHJKMNPQRSTUVWXYZ";
    const int lettersLen = strlen(letters);

    const char *numbers = "123456789";
    const int numbersLen = strlen(numbers);

    const char *specials = "!@#$%^&*-_+{.";
    const int specialsLen = strlen(specials);

    char password[passSize+1];

    password[0] = letters[rand() % lettersLen];
    password[1] = numbers[rand() % numbersLen];
    password[2] = specials[rand() % specialsLen];

    for (int i = 3; i < passSize; i++)
    {
        int typeRoll = random(1, 5);

        switch(typeRoll)
        {
            case 1:
                password[i] = letters[rand() % lettersLen];
                break;

            case 2:
            case 3:
                password[i] = tolower(letters[rand() % lettersLen]);
                break;

            case 4:
                password[i] = numbers[rand() % numbersLen];
                break;

            case 5:
                password[i] = specials[rand() % specialsLen];
                break;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int tradedIndex = rand() % passSize;

        while (tradedIndex < 3)
        {
            tradedIndex = rand() % passSize;
        }

        char storage = password[i];
        password[i] = password[tradedIndex];
        password[tradedIndex] = storage;
    }

    printf(password);
}

int random(int min, int max)
{
    const int number = rand() % (max - min + 1) + min;

    return number;
}