/**
Author: Simon Lindhorst
Date:   03.04.2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <ctype.h>

int checkStringForAlpha(char *str) {
    while (isalpha((int) *str)) {
        str++;
    }
    return (*str != '\0');
}

void stringToUpper(char* str) {
    while (isalpha((int) *str)) {
        if (islower(*str)) {
            *str -= ('a'-'A');
        }
        str++;
    }
}

int main(int argc, char * argv[]){
    int amount;
    char *word = argv[1];
    char *out;    
    int r;
    int *save;
    char* n;

    if (argc < 3) {
        printf("Two argument expected!\n");
        return 1;
    }
    
    amount = strtol(argv[2], &n, 10);
    if (*n != '\0') {
        printf("Invalid character amount given!\n");
        return 1;
    }

    word = argv[1];
    if (strlen(word) > amount) {
        printf("Given word is longer than amount of characters!\n");
        return 1;
    }
    if (checkStringForAlpha(word)) {
        printf("Invalid word given, only alpha characters allowed!\n");
        return 1;
    }

    stringToUpper(word);

    printf("The word is '%s'!\n", word);
    printf("Hide in %d characters\n", amount);
    
    out = malloc(sizeof(char) * amount);
    if (!out) {
        perror("While reserver space for out buffer");
        return -1;
    }

    srand(time(NULL));
    
    for(int i=0; i<amount; i++) {
        r = rand()%('Z'-'A' + 1)+'A';
        out[i] = (char) r;
    }

    save = malloc(sizeof(int) * strlen(word));
    if (!save) {
        perror("While reserver space for save buffer");
        return 1;
    }

    for(int i=0; i<strlen(word); i++) {
        int redo;
        do {
            redo = 0;
            r = rand()%amount;
            for (int a=0; a<i; a++) {
                if (save[a] == r) {
                    redo = 1;
                    break;
                }
            }
        } while(redo);
        save[i] = r;
        out[r] = word[i];
    }

    printf("%s\n",out);

    free(out); 
    free(save);   
}

