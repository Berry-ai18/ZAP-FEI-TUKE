#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include "ballsortpuzzle.h"


void game_field(const int rows, const int columns, char field[rows][columns]){
    for (int i = 0; i < rows; i++)
    {
        printf(" %d ",i+1);
        for (int j = 0; j < columns; j++)
        {
            printf("| %c ", field[i][j]);
        }
        printf("|\n");
    }
    printf("    ");
    for (int i = 0; i < columns; i++)
    {
        printf("--- ");
    }
    printf("\n");
    printf("     ");
    for (int i = 0; i < columns; i++)
    {
        printf("%d   ",i+1);
    }
    printf("\n");
}

bool check(const int rows, const int columns, char field[rows][columns]){
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows-1; j++)
        {
            if((field[j+1][i] != field[j][i])){
                return false;
            }
        }
    }
    printf("You win!\n");
    return true;
}

void generator(const int rows, const int columns, char field[rows][columns]){
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            field[j][i] = BLANK;
        }
    }
    if (columns <= 3) {
        printf("Too low colum count \n");
        return;
    }
    if (rows <= 2) {
        printf("Too low row count \n");
        return;
    }
    
    int counter[columns];
    for (int i = 0; i < columns; i++) {
        counter[i] = 0;
    }
    char array[] = "!@#$%^&*()_+";
    int emptycol1 = rand()%columns;
    int emptycol2 = rand()%columns;
    while(emptycol1 == emptycol2){
        emptycol2 = rand()%columns;
    }

    int currChar = 0;
    int is_empty_space = 1;
    int emptySpaceRow = 0;
    int emptySpaceColumn = 0;
    int retries = 0; 
    while (is_empty_space) {
        is_empty_space = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (j == emptycol1 || j == emptycol2) {
                    continue;
                }
                if (field[i][j] == BLANK) {
                    is_empty_space = 1;
                    emptySpaceRow = i;
                    emptySpaceColumn = j;
                }
            }
        }
        if (is_empty_space == 0) {
            break;
        }
        int rr = rand()%rows;
        int rc = rand()%columns;
        while (rc == emptycol1 || rc == emptycol2) {
            rc = rand()%columns;
        }
        if (field[rr][rc] == BLANK) {
            if (counter[currChar] >= rows) {
                currChar++;
            }
            field[rr][rc] = array[currChar];
            retries = 0;
            counter[currChar]++; 
        } else { 
            retries++;
        }
        if (retries > 1000) {
            if (counter[currChar] >= rows) {
                currChar++;
            }
            field[emptySpaceRow][emptySpaceColumn] = array[currChar];
            counter[currChar]++;
            retries = 0;
        }
    }

    ////////////CHECK IF COLUMN WITH ONE CHARACTER EXISTS/////////////////////
    char temp = BLANK;
    int is_same_column = 1;
    for (int i = 0; i < columns; i++) {
        if (i == emptycol1 || i == emptycol2) {
            continue;
        }
        temp = field[0][i];
        is_same_column = 1;
        for (int j = 0; j < rows; j++) {
            if (field[j][i] != temp) {
                is_same_column = 0;
            }
        }
        if (is_same_column == 1) {
            generator(rows,columns,field);
            break;
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    char xChar = BLANK;
    char yChar = BLANK;
    int xPosition = rows -1;
    int yPosition = rows -1;
    x--;
    y--;
    // checking if there is a move to be made
    if(x == y) {
        printf("SAME COLUMN ENTERED \n");
        return;
    }
    // checking if out of bounds
    if(x < 0 || x > columns - 1) {
        printf("IN IS OUT OF BOUNDS \n");
        return;
    }
    if(y < 0 || y > columns - 1) {
        printf("OUT IS OUT OF BOUNDS \n");
        return;
    }
    ///Find x character
    for (int i = 0; i < rows; i++) {
        if (field[i][x] != BLANK) {
            xChar = field[i][x];
            xPosition = i;
            break;
        }
    }

    if(xChar == BLANK){
        printf("Empty in vial \n");
        return;
    }

    ///Find y character
    if (field[0][y] != BLANK) {
        printf("Out vial is full \n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        if (field[i][y] != BLANK) {
            yChar = field[i][y];
            yPosition = i;
            break;
        }
    }

    if(yChar != xChar && yChar != BLANK){
        printf("Out vial not empty or not same character \n");
        return;
    }

    if (yChar != BLANK) {
        yPosition--;
    }
    printf("xChar: %c, xPosition: %d, yChar: %c, yPosition: %d \n", xChar, xPosition, yChar, yPosition);
    while(xChar == field[xPosition][x] && xPosition < rows){
        field[xPosition][x] = BLANK;
        xPosition++;
        field[yPosition][y] = xChar;
        yPosition--;
        if (field[0][y] != BLANK) {
            break;
        }
    }
}

void ball_sort_puzzle(){
    srand(time(0));
    int rows = 5;
    int columns = 5;
    char field[rows][columns];
    generator(rows,columns,field);
    game_field(rows,columns,field);
    while(!check(rows,columns,field)) {
        int x;
        int y;
        printf("Enter column from where you want to move: ");
        scanf("%d", &x);
        printf("Enter column where you want to move: ");
        scanf("%d", &y);
        down_possible(rows,columns,field,x,y);
        game_field(rows,columns,field);
    }
}
