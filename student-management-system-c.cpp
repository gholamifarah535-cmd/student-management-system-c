#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float moyenne;
} etudiant;

void ajouter() {
    FILE *f = fopen("AJ.txt", "ab");
    etudiant e;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        exit(1);
    }

    printf("Entrer le nom : ");
    scanf(" %[^\n]", e.name);

    printf("Entrer l'age : ");
    scanf("%d", &e.age);

    printf("Entrer la moyenne : ");
    scanf("%f", &e.moyenne);

    fwrite(&e, sizeof(etudiant), 1, f);
    fclose(f);

    printf("Etudiant ajoute avec succes.\n");
}

void affich() {
    FILE *f = fopen("AJ.txt", "rb");
    etudiant e;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        exit(1);
    }

    printf("\n LISTE DES ETUDIANTS \n");

    while (fread(&e, sizeof(etudiant), 1, f)) {
        printf("Nom : %s\n", e.name);
        printf("Age : %d\n", e.age);
        printf("Moyenne : %.2f\n", e.moyenne);
    }

    fclose(f);
}

void modif() {
    FILE *f = fopen("AJ.txt", "rb+");
    etudiant e;
    char nomrech[50];
    int trouve = 0;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        exit(1);
    }

    printf("Entrer le nom a modifier : ");
    scanf(" %[^\n]", nomrech);

    while (fread(&e, sizeof(etudiant), 1, f)) {
        if (strcmp(e.name, nomrech) == 0) {
            printf("Nouvelle moyenne : ");
            scanf("%f", &e.moyenne);

            fseek(f, -sizeof(etudiant), SEEK_CUR);
            fwrite(&e, sizeof(etudiant), 1, f);

            trouve = 1;
            printf("Modification reussie.\n");
            break;
        }
    }

    if (!trouve) {
        printf("Etudiant non trouve.\n");
    }

    fclose(f);
}

void suppr() {
    FILE *f = fopen("AJ.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    etudiant e;
    char nomrech[50];
    int trouve = 0;

    if (f == NULL || temp == NULL) {
        printf("Erreur ouverture fichier\n");
        exit(1);
    }
    printf("Entrer le nom a supprimer : ");
    scanf(" %[^\n]", nomrech);

    while (fread(&e, sizeof(etudiant), 1, f)) {
        if (strcmp(e.name, nomrech) != 0) {
            fwrite(&e, sizeof(etudiant), 1, temp);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove("AJ.txt");
    rename("temp.txt", "AJ.txt");

    if (trouve) {
        printf("Etudiant supprime avec succes.\n");
    } else {
        printf("Etudiant non trouve.\n");
    }
}

int main() {
    int choix;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Ajouter Etudiant\n");
        printf("2. Afficher Etudiants\n");
        printf("3. Modifier Etudiant\n");
        printf("4. Supprimer Etudiant\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouter(); break;
            case 2: affich(); break;
            case 3: modif(); break;
            case 4: suppr(); break;
            case 0: printf("Au revoir.\n"); break;
            default: printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
