#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hangman.h"

int main()
{
    srand(time(NULL));
    char secret[15];
    get_word(secret);
    hangman(secret);
    return 0;
}
