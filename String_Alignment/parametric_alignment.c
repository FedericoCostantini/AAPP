#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

int gap, miss;

typedef struct{
    int score;
    int dir;
}cell;

void computeScore(char *, char *);
void computeCell(char, char, int, int, cell **);
int getMin(int, int, int);
void printMatrix(char *, char *, int, int, cell **);
void printAlignment(char *, char *, int, int, cell **);

int main(){
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];
    char ans;
    gap = 2;
    miss = 5;

    printf("This is a program meant to receive two strings of max length %d and compute the score for their alignment.\n"
            "It doesn't handle input errors. Current penalty scores are:\n"
            "Gap penalty: %d\n"
            "Mismatch penalty: %d\n", MAX_SIZE - 1, gap, miss);

    do{
        printf("Do you want to change the values of the penalty scores? y/n\n");
        scanf("%c", &ans);
        if(ans == 'y' || ans == 'Y'){
            printf("Insert the value of the gap score:\n");
            scanf("%d", &gap);
            printf("Insert the value of the miss score:\n");
            scanf("%d", &miss);
        }


        printf("Please insert the first string:\n");
        scanf("%s", s1);
        printf("Please insert the second string:\n");
        scanf("%s", s2);

        computeScore(s1, s2);
        
        printf("Do you want to do it again? y/n\n");
        while (getchar() != '\n');
        scanf("%c", &ans);
        while (getchar() != '\n');
    }while(ans == 'y' || ans == 'Y');

    return 0;
}

void printAlignment(char * s1, char * s2, int l1, int l2, cell ** matrix){
    int max_length = l1 + l2 - 1;
    int i = l1 - 1;
    int j = l2 - 1;
    int index;
    int dir;

    char * new_s1 = (char *)malloc(sizeof(char) * max_length);
    char * new_s2 = (char *)malloc(sizeof(char) * max_length);

    new_s1[max_length - 1] = '\0';
    new_s2[max_length - 1] = '\0';
    index = max_length - 2;

    while(!(i == 0 || j == 0)){
        dir = matrix[i][j].dir;
        if(dir == 1){
            new_s1[index] = s1[i - 1];
            new_s2[index] = '_';
            i--;
        }
        else if(dir == -1){
            new_s1[index] = '_';
            new_s2[index] = s2[j - 1];
            j--;
        }
        else{
            if(matrix[i][j].score == matrix[i-1][j-1].score){
                new_s1[index] = s1[i - 1];
                new_s2[index] = s2[j - 1];
            }
            else{
                new_s1[index] = '*';
                new_s2[index] = '*';
            }
            i--;
            j--;
        }
        index--;
    }

    while (i != 0)
    {
        new_s1[index] = s1[i - 1];
        new_s2[index] = '_';
        i--;
        index--;
    }
    while(j != 0){
        new_s1[index] = '_';
        new_s2[index] = s2[j - 1];
        j--;
        index--;
    }
    

    index++;

    printf("\n\nALIGNMENT\n%s\n%s\nAlignment score: %d\n\n", &(new_s1[index]), &(new_s2[index]), matrix[l1-1][l2-1].score);
    free(new_s1);
    free(new_s2);
}

void printMatrix(char * s1, char * s2, int l1, int l2, cell ** matrix){
    int i, j;

    printf("\n\nMATRIX SCORE\n\n ");
    for(i = 0; i < l2; i++){
        printf("%10c", i == 0? ' ' : s2[i - 1]);
    }

    printf("\n");

    for(i = 0; i < l1; i++){
        printf("%c", i == 0 ? ' ' : s1[i - 1]);
        for(j = 0; j < l2; j++){
            printf("%10d", matrix[i][j].score);
        }
        printf("\n");
    }
}

int getMin(int val1, int val2, int val3){
    if(val1 < val2){
        return val1 < val3 ? 1 : 0;
    }
    return val2 < val3 ? -1 : 0;
}

void computeCell(char c1, char c2, int i, int j, cell ** mat){
    int val1 = mat[i - 1][j].score + gap;
    int val2 = mat[i][j - 1].score + gap;
    int val3 = mat[i-1][j-1].score + (c1 == c2 ? 0 : miss * 2);

    int dir = getMin(val1, val2, val3);

    if(dir == 1){
        mat[i][j].score = val1;
    }
    else if(dir == -1){
        mat[i][j].score = val2;
    }
    else{
        mat[i][j].score = val3;
    }
    mat[i][j].dir = dir;
}

void computeScore(char * s1, char * s2){
    int i, j;
    int l1 = strlen(s1) + 1;
    int l2 = strlen(s2) + 1;

    // Instantiating the matrix score
    cell ** matrix = (cell **)malloc(sizeof(cell *) * l1);

    for(i = 0; i < l1; i++){
        matrix[i] = (cell *)malloc(sizeof(cell) * l2);
    }

    matrix[0][0].score = 0;

    for(j = 1; j < l2; j++){
        matrix[0][j].score = matrix[0][j - 1].score + gap;
        matrix[0][j].dir = -1;
    }

    for(i = 1; i < l1; i++){
        matrix[i][0].score = matrix[i -1][0].score + gap;
        matrix[i][0].dir = 1;
    }

    for(i = 1; i < l1; i++){
        for(j = 1; j < l2; j++){
            computeCell(s1[i - 1], s2[j - 1], i, j, matrix);
        }
    }


    printMatrix(s1, s2, l1, l2, matrix);

    printAlignment(s1, s2, l1, l2, matrix);

    for(i = 0; i < l1; i++){
        free(matrix[i]);
    }
    free(matrix);
}