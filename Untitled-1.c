#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Virement {
    float montant;
    char compte_source[20];
    char compte_beneficiaire[20];
    char date[20];
    struct Virement* suivant;
} Virement;

Virement* tete = NULL;


Virement* creerVirement(float montant, char* source, char* beneficiaire, char* date) {
    Virement* nouveau = (Virement*)malloc(sizeof(Virement));
    nouveau->montant = montant;
    strcpy(nouveau->compte_source, source);
    strcpy(nouveau->compte_beneficiaire, beneficiaire);
    strcpy(nouveau->date, date);
    nouveau->suivant = NULL;
    return nouveau;
}


void ajouterVirement() {
    float montant;
    char source[20], beneficiaire[20], date[20];

    printf("Montant: ");
    scanf("%f", &montant);
    printf("Compte source: ");
    scanf("%s", source);
    printf("Compte bénéficiaire: ");
    scanf("%s", beneficiaire);
    printf("Date (YYYY-MM-DD): ");
    scanf("%s", date);

    Virement* v = creerVirement(montant, source, beneficiaire, date);
    if (tete == NULL) {
        tete = v;
    } else {
        Virement* temp = tete;
        while (temp->suivant != NULL)
            temp = temp->suivant;
        temp->suivant = v;
    }

    printf("virement ajouté avec succès.\n");
}


void afficherVirements() {
    Virement* temp = tete;
    int i = 1;

    while (temp != NULL) {
        printf("Virement %d:\n", i++);
        printf("  Montant: %.2f MAD\n", temp->montant);
        printf("  Compte source: %s\n", temp->compte_source);
        printf("  Compte bénéficiaire: %s\n", temp->compte_beneficiaire);
        printf("  Date: %s\n", temp->date);
        printf("-------------------------\n");
        temp = temp->suivant;
    }

    if (tete == NULL)
        printf("Aucun virement enregistré.\n");
}


void rechercherVirement() {
    char source[20];
    printf("Entrez le compte source à rechercher : ");
    scanf("%s", source);

    Virement* temp = tete;
    int trouve = 0;
    while (temp != NULL) {
        if (strcmp(temp->compte_source, source) == 0) {
            printf("Virement trouvé :\n");
            printf("  Montant: %.2f MAD\n", temp->montant);
            printf("  Bénéficiaire: %s\n", temp->compte_beneficiaire);
            printf("  Date: %s\n", temp->date);
            trouve = 1;
        }
        temp = temp->suivant;
    }

    if (!trouve)
        printf("aucun virement trouvé avec ce compte source.\n");
}


void modifierVirement() {
    char source[20];
    printf("Entrez le compte source du virement à modifier : ");
    scanf("%s", source);

    Virement* temp = tete;
    while (temp != NULL) {
        if (strcmp(temp->compte_source, source) == 0) {
            printf("Nouveau montant : ");
            scanf("%f", &temp->montant);
            printf("Nouveau compte bénéficiaire : ");
            scanf("%s", temp->compte_beneficiaire);
            printf("Nouvelle date : ");
            scanf("%s", temp->date);
            printf("virement modifié avec succès.\n");
            return;
        }
        temp = temp->suivant;
    }
    printf("virement non trouvé.\n");
}


void supprimerVirement() {
    if (tete == NULL) {
        printf("aucun virement à supprimer.\n");
        return;
    }

    Virement* temp = tete;
    tete = tete->suivant;
    free(temp);
    printf("️ Virement supprimé avec succès.\n");
}


void effectuerVirements() {
    Virement* temp = tete;
    int i = 1;

    while (temp != NULL) {
        printf("Virement %d:\n", i++);
        printf("  Transfert de %.2f MAD du compte %s vers %s\n",
               temp->montant, temp->compte_source, temp->compte_beneficiaire);

     
        if (temp->montant <= 600)
            printf("  succès\n");
        else
            printf("  Échec - Solde insuffisant\n");

       
        temp = temp->suivant;
    }
}

int main() {
    int choix;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Ajouter un virement\n");
        printf("2. Modifier un virement\n");
        printf("3. Supprimer un virement\n");
        printf("4. Rechercher un virement\n");
        printf("5. Afficher les virements\n");
        printf("6. Effectuer les virements\n");
        printf("7. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: ajouterVirement(); break;
            case 2: modifierVirement(); break;
            case 3: supprimerVirement(); break;
            case 4: rechercherVirement(); break;
            case 5: afficherVirements(); break;
            case 6: effectuerVirements(); break;
            case 7: printf("Fermeture du programme...\n"); break;
            default: printf("choix invalide !\n");
        }
    } while (choix != 7);

    return 0;
}