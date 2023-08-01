#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int counte() {
    FILE *f = fopen("hang.txt", "r");
    if (f == NULL) {
        printf("Error opening the file.\n");
        return -1;
    }

    char ch;
    int i = 1;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n')
            i++;
    }
    fclose(f);
    return i;
}

int verif( char ch[20]) {
    size_t i = 0;
    while (i < strlen(ch)) {
        if (!isalpha(ch[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

char* transfert(char t[][100], int n) {
    FILE *f = fopen("hang.txt", "r");
    if (f == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        if (fgets(t[i], 100, f) == NULL) {
            break;
        }
        t[i][strcspn(t[i], "\n")] = '\0';
    }
    fclose(f);
    int indice = rand() % n;
    return t[indice];
}

char* saisir() {
    char nom[20];
    printf("Veuillez saisir votre nom: ");
    scanf("%s", nom);
    while (verif(nom) == 0) {
        printf("Veuillez saisir votre nom: ");
        scanf("%s", nom);
    }
    return strdup(nom);
}

void versus( char player1[100],  char player2[100],  char word[100]) {
    
}

void solo( char player[100],  char word[100]) {
    
}

void play( char word[100]) {
    char nom[100];
    strcpy(nom, saisir());
    printf("Welcome %s to the Hangman game.\n", nom);
    printf("What do you want to play:\n1 - Play VERSUS 1V1\n2 - Solo Play\nPress any other button to exit.\n");

    int x;
    scanf("%d", &x);
    while (x != 1 && x != 2) {
        printf("Please choose only 1 or 2: ");
        scanf("%d", &x);
    }

    if (x == 1) {
        char name2[100];
        strcpy(name2, saisir());
        versus(nom, name2, word);
    } else if (x == 2) {
        solo(nom, word);
    }
}

int main() {
    int n = counte();
    char t[n][100];
    char* ch = transfert(t, n);
    if (ch == NULL) {
        printf("Failed to load word from file.\n");
        return 1;
    }

    play(ch);
    free(ch);

    return 0;
}
