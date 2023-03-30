#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include "hangman.h"

int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if (result != EOF)
            break;
    } while (1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    int counter = 0;
    for (int i = 0; i < strlen(secret); i++)
    {
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (secret[i] == letters_guessed[j])
            {
                counter++;
            }
        }
    }
    if (counter == strlen(secret))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]){

    for (int i = 0; i < strlen(secret); i++)
    {
        guessed_word[i] = '_';
        for (int j = 0; j < strlen(letters_guessed); j++)
        {
            if (letters_guessed[j] == secret[i])
            {
                guessed_word[i] = secret[i];
            }
        }
    }
    guessed_word[strlen(secret)] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]){
    if(strlen(letters_guessed)==0){
        available_letters[strlen(available_letters)] = '\0';
    }else{
        for (int i = 0; i < strlen(available_letters); i++)
        {
            for (int j = 0; j < strlen(letters_guessed); j++)
            {
                if(letters_guessed[j] == available_letters[i]){
                    for (int k = i; k < strlen(available_letters) - 1; k++)
                    {      
                        available_letters[k] = available_letters[k+1]; 
                    }
                    available_letters[strlen(available_letters)-1] = '\0';
                }
            }
        }
    }
}

void hangman(const char secret[]){

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n",(int)strlen(secret));
    printf("-------------\n");
    int guess = 8;
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char guessedWords[strlen(secret)];
    char lettersGuessed[strlen(alphabet)];
    int letter = 0;
    
    while(guess && !is_word_guessed(secret,lettersGuessed)){
        
        printf("You have %d guesses left.\n",guess);
        printf("Available letters: %s\n", alphabet);
        printf("Please guess a letter: ");
        
        char c;
        while((c = getchar()) != '\n'){
            
            if(!isalpha(c)){
                printf("Oops! '%c' is not a valid letter: ", c);
            }else{
                if(isupper(c)){
                c += 32;
            }
    
                if(strchr(lettersGuessed,c) != NULL && (letter > 1)){
                    printf("Oops! You've already guessed that letter: ");
                    lettersGuessed[letter] = '\0';
                }
                else if(strchr(secret,c) != NULL){
                    printf("Good guess: ");
                    lettersGuessed[letter] = c;
                    letter++;
                }else{
                    printf("Oops! That letter is not in my word: ");
                    guess--;
                    lettersGuessed[letter] = c;
                    letter++;
            }
        }
    }
        
        get_available_letters(lettersGuessed,alphabet);
        get_guessed_word(secret,lettersGuessed,guessedWords);
        
        for (int i = 0; i < strlen(guessedWords)-1; i++)
        {
            printf("%c ",guessedWords[i]);
        }
        
        printf("%c", guessedWords[strlen(guessedWords)-1]);
        
        if(is_word_guessed(secret,lettersGuessed)){
            printf("\n-------------\n");
            printf("Congratulations, you won!\n");
            return;
        }else{
            printf("\n-------------\n");
        }
    }
    printf("Sorry, you ran out of guesses. The word was %s.\n",secret);
}
