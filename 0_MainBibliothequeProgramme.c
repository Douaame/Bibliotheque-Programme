#include <stdio.h>
#include <string.h>
#include <ctype.h>

// question 1: Définire structure Livre
typedef struct
{
    char Titre[50];
    char Auteur[50];
    int ISBN;
} Livre;

Livre ListeLivre[100];
Livre Corbeille[100];
int NombreDeLivres = 0;
int indexCorbeille = 0;

void AjouterLivreSimple();
void SupprimerLivre();
void RestaurerLivre();

// question 2: fonction Ajouter Livre
void AjouterLivreSimple()
{
    getchar();
    printf("Saisir le titre du livre: ");
    fgets(ListeLivre[NombreDeLivres].Titre, sizeof(ListeLivre[NombreDeLivres].Titre), stdin);
    printf("Saisir le nom de l'auteur: ");
    fgets(ListeLivre[NombreDeLivres].Auteur, sizeof(ListeLivre[NombreDeLivres].Auteur), stdin);
    printf("Saisir le nombre ISBN : ");
    scanf("%d", &ListeLivre[NombreDeLivres].ISBN);

    char TitreEnMinuscules[50];
    strcpy(TitreEnMinuscules, ListeLivre[NombreDeLivres].Titre);
    minuscule(TitreEnMinuscules);

    for (int i = 0; i < NombreDeLivres; i++)
    {
        if (strcmp(ListeLivre[i].Titre, ListeLivre[NombreDeLivres].Titre) == 0)
        {
            char TitreLivreEnMinuscules[50];
            strcpy(TitreLivreEnMinuscules, ListeLivre[i].Titre);
            minuscule(TitreLivreEnMinuscules);

            printf("Ce livre existe deja dans la bibliotheque.\n");
            return;
            
        }
    }
    printf("Le livre '%s' a ete ajoute avec succes.\n", ListeLivre[NombreDeLivres].Titre);
    NombreDeLivres++;
}

void AjouterLivre()
{
    if (NombreDeLivres < 100)
    {
        AjouterLivreSimple();
    }
    else
    {
        int choix;
        printf("La bibliotheque est pleine ! Impossible d'ajouter d'autres livres.\n");
        printf("Voulez-vous supprimer un livre de la bibliotheque ?:\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        printf("Entrez le votre choix: ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            SupprimerLivre();
            printf("Maintenant, vous pouvez ajouter un nouveau livre.\n");
            AjouterLivreSimple();
            break;
        case 2:
            break;
        default:
            printf("Choix invalide.\n");
        }
    }
}

// question 3: fonction Recherche Livre Par Titre
void minuscule(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void RechercheLivreParTitre()
{
    getchar();
    char Titre[50];
    printf("Saisir le titre du livre qui vous interesse: ");
    fgets(Titre, sizeof(Titre), stdin);
    Titre[strcspn(Titre, "\n")] = 0;

    if (NombreDeLivres == 0)
    {
        printf("Aucun livre dans la bibliotheque.\n");
        return;
    }

    int found = 0;
    char TitreEnMinuscules[50];
    strcpy(TitreEnMinuscules, Titre);
    minuscule(TitreEnMinuscules);

    for (int i = 0; i < NombreDeLivres; i++)
    {
        char TitreLivreEnMinuscules[50];
        strcpy(TitreLivreEnMinuscules, ListeLivre[i].Titre);
        minuscule(TitreLivreEnMinuscules);

        if (strstr(TitreLivreEnMinuscules, TitreEnMinuscules) != NULL)
        {
            printf("Titre: %s, Auteur: %s, ISBN: %d\n", ListeLivre[i].Titre, ListeLivre[i].Auteur, ListeLivre[i].ISBN);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Livre non trouve\n");
    }
}

// question 4: fonction Afficher Bibliotheque
void AfficherBibliotheque()
{
    if (NombreDeLivres == 0)
    {
        printf("Aucun livre dans la bibliotheque.\n");
        return;
    }

    printf("\n===Livres dans la bibliotheque:===\n");
    for (int i = 0; i < NombreDeLivres; i++)
    {
        printf("Livre %d: %s ecrit par %s, Nombre ISBN : %d\n", i + 1, ListeLivre[i].Titre, ListeLivre[i].Auteur, ListeLivre[i].ISBN);
    }
}

// question 5: fonction Supprimer Livre
void SupprimerLivre()
{
    getchar();
    int i, P = -1;
    if (NombreDeLivres == 0)
    {
        printf("Aucun livre dans la bibliotheque.\n");
        return;
    }

    char Titre[50];

    printf("saisir le titre du livre que vous souhaitez supprimer:");
    fgets(Titre, sizeof(Titre), stdin);
    Titre[strcspn(Titre, "\n")] = 0;

    char TitreEnMinuscules[50];
    strcpy(TitreEnMinuscules, Titre);
    minuscule(TitreEnMinuscules);

    for (i = 0; i < NombreDeLivres; i++)
    {
        char TitreLivreEnMinuscules[50];
        strcpy(TitreLivreEnMinuscules, ListeLivre[i].Titre);
        minuscule(TitreLivreEnMinuscules);

        if (strstr(TitreLivreEnMinuscules, TitreEnMinuscules) != NULL)
        {
            P = i;
            break;
        }
    }

    if (P == -1)
    {
        printf("le livre n'existe pas\n");
        return;
    }

    if (indexCorbeille >= 100)
    {
        printf("La corbeille est pleine. Vidage de la corbeille...\n");
        indexCorbeille = 0;
    }
    Corbeille[indexCorbeille] = ListeLivre[P];
    indexCorbeille++;

    for (i = P; i < NombreDeLivres - 1; i++)
    {
        ListeLivre[i] = ListeLivre[i + 1];
    }

    NombreDeLivres--;
    printf("Le livre '%s' a ete supprime avec succes.\n", Titre);
}

// Fonction pour restaurer un livre depuis la corbeille
void RestaurerLivre()
{    getchar();
    int i , P = -1;
    if (indexCorbeille == 0)
    {
        printf("La corbeille est vide.\n");
        return;
    }

    if (NombreDeLivres >= 100)
    {
        printf("La bibliotheque est pleine, impossible de restaurer un livre.\n");
        return;
    }
    char Titre[50];

    printf("saisir le titre du livre que vous souhaitez restaurer:");
    fgets(Titre, sizeof(Titre), stdin);
    Titre[strcspn(Titre, "\n")] = 0;

    char TitreEnMinuscules[50];
    strcpy(TitreEnMinuscules, Titre);
    minuscule(TitreEnMinuscules);

    for (i = 0; i < indexCorbeille; i++)
    {
        char TitreLivreEnMinuscules[50];
        strcpy(TitreLivreEnMinuscules, Corbeille[i].Titre);
        minuscule(TitreLivreEnMinuscules);

        if (strstr(TitreLivreEnMinuscules, TitreEnMinuscules) != NULL)
        {
            P = i;
            break;
        }
    }
    if (P == -1)
    {
        printf("le livre n'existe pas\n");
        return;
    }

    ListeLivre[NombreDeLivres] = Corbeille[P - 1];
    NombreDeLivres++;

    for (i = P; i < indexCorbeille - 1; i++)
    {
        Corbeille[i] = Corbeille[i + 1]; 
    }
    indexCorbeille--;

    printf("Le livre '%s' a ete restaure avec succes.\n", ListeLivre[NombreDeLivres - 1].Titre);
}

// question 6: Programme Principale
int main()
{
    int choix;
    do
    {
        printf("\n===Soyez les bienvenus dans notre bibliotheque===\n");
        printf("Choisis un numero entre 0 et 5 pour selectionner l'une des instructions suivantes:\n ");
        printf("1. Ajouter un livre\n");
        printf(" 2. Rechercher un livre par titre\n");
        printf(" 3. Afficher touts les livres\n");
        printf(" 4. Supprimer un livre\n");
        printf(" 5. Restaurer un livre depuis la corbeille\n");
        printf(" 0. Quitter\n");
        printf("Entrez le votre choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            AjouterLivre();
            break;
        case 2:
            RechercheLivreParTitre();
            break;
        case 3:
            AfficherBibliotheque();
            break;
        case 4:
            SupprimerLivre();
            break;
        case 5:
            RestaurerLivre();
            break;
        case 0:
            break;
        default:
            printf("Choix non valide\n");
        }
    } while (choix != 0);
}