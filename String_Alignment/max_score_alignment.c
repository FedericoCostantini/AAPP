#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gap, miss;
int n, m;

typedef struct{
    int score;
    int dir;
}cell;

int main(){
    char * s1;
    char * s2;
    char ans;
    gap = 2;
    miss = 5;

    printf("This is a program meant to receive two integer values, n and m.\n"
            "It generates two strings of length n and m respectively containing characters A T G C ehich alignment gives us the worst score possible"
            "It doesn't handle input errors. Current penalty scores are:\n"
            "Gap penalty: %d\n"
            "Mismatch penalty: %d\n", gap, miss);

    do{
        printf("Do you want to change the values of the penalty scores?y/n\n");
        scanf("%c", &ans);
        if(ans == 'y' || ans == 'Y'){
            printf("Insert the value of the gap score:\n");
            scanf("%d", &gap);
            printf("Insert the value of the miss score:\n");
            scanf("%d", &miss);
        }


        printf("Please insert the first string length n:\n");
        scanf("%s", &n);
        printf("Please insert the second string length m:\n");
        scanf("%s", &m);
        
        printf("Do you want to do it again? y/n\n");
        while (getchar() != '\n');
        scanf("%c", &ans);
        while (getchar() != '\n');
    }while(ans == 'y' || ans == 'Y');

    return 0;
}