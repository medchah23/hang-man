#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct jeux1
{
    char nom[20];
    int score ;
};

bool verif(char ch[20])
{
    size_t i = 0;
    bool b = true;
    while (i < strlen(ch) && b)
    {
        if (toupper(ch[i]) < 'A' || toupper(ch[i]) > 'Z')
        {
            b = false;
        }
        else
        {
            i++;
        }
    }
    return b;
}

char* saisir()
{
    char nom[20];
    printf("Veuillez saisir votre nom: ");
    scanf("%s", nom);
    while (verif(nom) == false)
    {
        printf("Veuillez saisir votre nom: ");
        scanf("%s", nom);
    }
    return strdup(nom);
}

void newGame()
{
    struct jeux1 x;
        FILE* fptr;
        fptr = fopen("game.dat", "wb");
        fclose(fptr);
    int secretnumber = rand() % 10 + 1;
    int guess;
    strcpy(x.nom, saisir());
    x.score = 100;
    printf("Bonjour %s dans notre jeu.\nVeuillez choisir un entier entre 0 et 10: ", x.nom);
    scanf("%d", &guess);
    int try = 1;

    while (guess != secretnumber)
    {
        if (guess < secretnumber)
        {
            printf("\nVeuillez choisir un autre nombre :(trop petit)\n");
            scanf("%d", &guess);
            try++;
            x.score -= 15;
        }
        else if (guess > secretnumber)
        {
            printf("Veuillez choisir un autre nombre :(trop grand)\n");
            scanf("%d", &guess);
            try++;
            x.score -= 15;
        }
    }

    if (guess == secretnumber)
    {
        printf("Bravo %s, le nombre secret est %d. Vous avez gagné en %d essai(s). (❁´◡`❁)\n", x.nom, secretnumber, try);
        FILE* fptr;
        fptr = fopen("game.dat", "ab");
        fwrite(&x, sizeof(struct jeux1), 1, fptr);
        fclose(fptr);
    }
    ret main();
}
bool existant(char* nom) {
    FILE* fptr;
    fptr = fopen("game.dat", "rb");
    if (fptr == NULL) {
        printf("Failed to open the file.\n");
        return false;
    }

    struct jeux1 t[100];
    size_t count = fread(t, sizeof(struct jeux1), 100, fptr);
    for (size_t i = 0; i < count; i++) {
        if (strcmp(t[i].nom, nom) == 0) {
            fclose(fptr);
            return true;
        }
    }

    fclose(fptr);
    return false;
}

void modify(char* nom, int score)
{
    struct jeux1 t[100];
    FILE* fptr = fopen("game.dat", "rb");
    if (fptr == NULL)
    {
        printf("Failed to open the file.\n");
        return; // Exit the function
    }
    size_t count = fread(t, sizeof(struct jeux1), 100, fptr);
    fclose(fptr);
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(t[i].nom, nom) == 0)
        {
            t[i].score += score;
        }
    }

    fptr = fopen("game.dat", "wb");
    fwrite(t, sizeof(struct jeux1), count, fptr);
    fclose(fptr);
}

void player()
{
    int secretnumber = rand() % 10 + 1;
    struct jeux1 x;
    int guess;
    x.score = 100;
    strcpy(x.nom, saisir());
    
    printf("Bonjour %s dans notre jeu.\nVeuillez choisir un entier entre 0 et 10: ", x.nom);
    scanf("%d", &guess);
    int try = 1;

    while (guess != secretnumber)
    {
        if (guess < secretnumber)
        {
            printf("\nVeuillez choisir un autre nombre :(trop petit)\n");
            scanf("%d", &guess);
            try++;
            x.score -= 15;
        }
        else if (guess > secretnumber)
        {
            printf("Veuillez choisir un autre nombre :(trop grand)\n");
            scanf("%d", &guess);
            try++;
            x.score -= 15;
        }
    }

    if (guess == secretnumber)
    {
        if (existant(x.nom)==true)
    {
        modify(x.nom,x.score);
    }
    else{
        printf("Bravo %s, le nombre secret est %d. Vous avez gagné en %d essai(s). (❁´◡`❁)\nvotre score est %d", x.nom, secretnumber, try, x.score);
        FILE* fptr;
        fptr = fopen("game.dat", "ab");
        fwrite(&x, sizeof(struct jeux1), 1, fptr);
        fclose(fptr);
    }}
    main();
}
void winner()
{
    FILE* fptr;
    fptr = fopen("game.dat", "rb");
    if (fptr == NULL)
    {
        printf("Failed to open the file.\n");
        return 1; // Exit the function with an error code
    }

    struct jeux1 t[100];
    size_t count = fread(t, sizeof(struct jeux1), 100, fptr);

    fclose(fptr);

    int maxScore = t[0].score;
    int winnerIndex = 0;

    for (size_t i = 1; i < count; i++)
    {
        if (t[i].score > maxScore)
        {
            maxScore = t[i].score;
            winnerIndex = i;
        }
    }

    printf("Le gagnant est : %s avec un score de %d\n", t[winnerIndex].nom, t[winnerIndex].score);

    main();

}


void main()
{
    int x = 1;
    printf("*Number Guessing Game*\n"
        "1 - New game\n"
        "2 - Add player\n"
        "3 - Display the winner\n"
        "4 - Close the game\n");

    scanf("%d", &x);

    switch (x)
    {
    case 1:
        newGame();
        break;

    case 2:
        player();
        break;

    case 3:
        winner();
        break;

    case 4:
        printf("Bye! ☆*: .｡. o(≧▽≦)o .｡.:*☆.\n");
        break;

    default:
    
        printf("Invalid option.\n");
        break;
    }

    
}
