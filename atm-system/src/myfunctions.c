#include "stdio.h"
#include "header.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>



void registration(struct User *u)
{
    FILE *fp;
    char pass[50];
    char fileLogin[50], filePassword[50];
    int id;
    char *passchiff;//for registrer the cenccrypt of the password

reinscript:
    system("clear");
    printf("\n\n\n\t\t\t\t\t  Welcome to page of Registration\n\t\t\t\t\t \n");
    printf("\n\n\n\t\t\t\t\t  username: ");
    scanf("%s", u->name);
    ViderBuffer();
    printf("\n\n\n\t\t\t\t\t  password: ");
    scanf("%s", u->password);
    ViderBuffer();
    printf("\n\n\n\t\t\t\t\t  Confirm password: ");
    scanf("%s", pass);
    ViderBuffer();

    if (strcmp(u->password, pass) != 0)
    {
        printf("Unmatched password, please try again.\n");
        registration(u);
    }
    else
    {
        if ((fp = fopen("./data/users.txt", "a+")) == NULL)
        {
            printf("Error! Opening file.\n");
            exit(1);
        }
        else
        {
            u->id = countLines("./data/users.txt") + 1;
            while (fscanf(fp, "%d %49s %49s", &id, fileLogin, filePassword) == 3)
            {
                // Comparaison des logins et mots de passe
                if (strcmp(u->name, fileLogin) == 0)
                {
                    fclose(fp);
                    printf("username already exits please try again");
                    goto reinscript;
                }
            }

            passchiff=chiffrementCesar(u->password,3);

            fprintf(fp, "%d %s %s\n", u->id, u->name, passchiff);
            fclose(fp);
            success((*u));
        }
    }
}

void updateAccount(struct User u)
{
    int idaccount;
    int test;
    int choiceUpdate;
    int phone;
    int ligne;
    char country[50];
    int line;
   system("clear");
    printf("\n\n\n\t\t\t\t\t  Menu of update Account \n\t\t\t\t\t \n");

    printf("\n\n\n\t\t\t\t\t  enter the id of the account: ");
    scanf("%d", &idaccount);
    ViderBuffer();
    //  printf("%d", idaccount);
    test = existaccount(idaccount, u.id, &line);
    if (test == 0)
    {
        printf("compte inexistant \n");
        exit(1);
    }
    else
    {
    update:
        system("clear");
        printf("\n\n\n\t\t\t\t\t  witch field do you want to change: \n\t\t\t\t\t \n");
        printf("\n\n\n\(1)-------->Phone Number \n\t\t\t\t\t \n");
        printf("\n\n\n\(2)-------->Country \n\t\t\t\t\t \n");
        scanf("%d", &choiceUpdate);
        ViderBuffer();
        ligne = (2 * line);
        switch (choiceUpdate)
        {
        case 1:
            printf("\n\n\n\t\t\t\t\t  Enter the new phone Number:");
            scanf("%d", &phone);
            ViderBuffer();
            updateField(ligne, phone, "", 0);
            break;
        case 2:
            printf("\n\n\n\t\t\t\t\t  Enter the new country:");
            scanf("%s", country);
            ViderBuffer();
            updateField(ligne, 0, country, 0);
            break;
        default:
            printf("\n\n\n\t\t\t\t\tinvalid input");
            goto update;
        }

        success(u);
    }
}

void checkExistAccount(struct User u)
{
    struct Record r;
    int idaccount;
    // char tab[5][50];
    int test;
    double interet;
    char *typeacount;
    int date;;
    double amount;
    int line;
    char chaine[50];

    system("clear");
input:
    printf("\t\t\t===== For checking existing account =====\n\n\n");
    printf("\t\t\t===== please tape the id of the  account:\n\n\n\n\n\n ");
    scanf("%d", &idaccount);
    // printf("%d",idaccount);
    ViderBuffer();
    test = existaccount(idaccount, u.id, &line);
    // printf("%d",test);
    if (test == 0)
    {
        printf("compte inexistant \n");
        goto input;
    }

    typeacount = getaccounttype(line, &date, &amount);
    // typeacount="xxxxxxxx";
    // printf("%s", typeacount);
    strcpy(chaine, typeacount);
    // printf("%s\n",chaine);
    if (strcmp(chaine, "current") == 0)
    {
        printf("\t\t\t\tYou will not get interests because the account is of type current\n\n");
        success(u);
    }
    else if ((strcmp(chaine, "saving") == 0))
    {
        interet = round(((amount * 7) / 1200));
        printf("\t\t\t\tYou will get %.2f interest on day %d of every month\n\n", interet, date);
        success(u);
    }
    else if ((strcmp(chaine, "fixed01") == 0))
    {
        interet = round(((amount * 4) / 1200));
        printf("\t\t\t\tYou will get %.2f interest on day %d of every month\n\n", interet, date + 1);
        success(u);
    }
    else if ((strcmp(chaine, "fixed02") == 0))
    {
        interet = round(((amount * 5) / 1200));
        printf("\t\t\t\tYou will get %.2f interest on day %d of every month\n\n", interet, date + 2);
        success(u);
    }
    else if ((strcmp(chaine, "fixed03") == 0))
    {
        interet = round(((amount * 8) / 1200));
        
        printf("\t\t\t\tYou will get %.2f interest on day %d of every month\n\n", interet, date + 3);
        success(u);
    }
}

void maketransactin(struct User u)
{
    int idaccount;
    int choix;
    int test;
    int line;
    double deposit, rising;
    double extract;
    double amount;
    char *typeacount;
    int date;
input:

    system("clear");
    printf("\t\t\t===== menu for transactions =====\n");
    printf("\t\t\t===== please tape the id of the  account: ");
    scanf("%d", &idaccount);
    ViderBuffer();
    test = existaccount(idaccount, u.id, &line);
    if (test == 0)
    {
        printf("compte inexistant \n");
        goto input;
    }
    system("clear");
    printf("\t\t\t=======================================\n\n\n");
switching:
    printf("\t\t\t  to withdrawing tape (1)\n");
    printf("\t\t\t  To depose money tape (2)\n");
    scanf("%d", &choix);
    ViderBuffer();

    typeacount = getaccounttype(line, &date, &amount);
    if (strcmp(typeacount, "saving") != 0 && strcmp(typeacount, "current") != 0)
    {
        printf("error the type of this account not permit you this operation\n");
        exit(1);
    }

    switch (choix)
    {
    case 1:
        printf("\t\t\t withdraw: $ ");
        scanf("%lf", &rising);
        ViderBuffer();
        if (amount < rising)
        {
            printf("solde not permit this operation, try again\n");
        }
        else
        {
            updateField(2 * line, 0, "", rising * (-1));
            success(u);
            break;
        }

        //
        break;
    case 2:
        printf("\t\t\tdéposit: $ ");
        scanf("%lf", &deposit);
        ViderBuffer();
        // printf("%f",deposit);
        updateField(2 * line, 0, "", deposit);
        success(u);
        break;

    default:
        printf("choice not available");
        goto switching;
        break;
    }
}

void removeaccount(struct User u)

{
    int test, line;
    int idaccount;

    FILE *file;
    int ID, x, z, a, b, m, e;
    char y[50], d[50], g[50];
    // char cont[50]=*country;
    float f;
    int temp;
    char valeur[1000];
    char lines[1000][1000];
    FILE *fp;
    double totaldeposit;
    int ligne;
    system("clear");
    printf("\t\t\t===== menu for transactions =====\n");
input:
    printf("\t\t\t===== please tape the id of the  account: ");
    scanf("%d", &idaccount);
    ViderBuffer();
    test = existaccount(idaccount, u.id, &line);
    if (test == 0)
    {
        printf("compte inexistant \n");
        goto input;
    }

    ligne = 2 * line;
    file = fopen("./data/records.txt", "r");

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    printf("%d", ligne);

    int currentLine = 0;
    // int currentLine;
    while (fgets(lines[currentLine], 1000, file) && currentLine < 1000)
    {
        currentLine++;
    }

    fclose(file);
    if ((fp = fopen("./data/records.txt", "r")) == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    while (fscanf(fp, "%d %d %49s %d %d/%d/%d %49s %d %f %49s",
                  &ID, &x, y, &z, &a, &b, &m, d, &e, &f, g) == 11)
    {
        temp++;
        if ((ID * 2) == ligne)
        {

            snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, x, y, z, a, b, m, d, e, f, g);
        }
    }
    fclose(fp);
    removeExtraSpaces(valeur);

    if (ligne >= 0 && ligne < 1000)
    {
        int len = snprintf(NULL, 0, "%s\n\n", valeur);
        snprintf(lines[ligne], len, "%s\n", valeur);
    }
    else
    {
        printf("Numéro de ligne invalide.\n");
        exit(1);
    }
    int taille = countLines("./data/records.txt");
    FILE *fil = fopen("./data/records.txt", "w");
    if (file == NULL)
    {
        printf("Impossible d'écrire dans le fichier.\n");
        exit(1);
    }

    for (int i = 0; i < taille; i++)
    {
        if (i == ligne)
        {
            i++;
            continue;
        }
        fprintf(fil, "%s", lines[i]);
    }

    fclose(file);
    success(u);
}
void makeowntransfer(struct User u)
{

    FILE *file;
    int ID, x, z, a, b, m, e;
    char y[50], d[50], g[50];
    // char cont[50]=*country;
    float f;
    int temp;
    char valeur[1000];
    char lines[1000][1000];
    FILE *fp;
    double totaldeposit;
    int idaccount, line, ligne;
    char usernw[50];
    system("clear");
    printf("\t\t\t===== Transfert ownship=====\n");
input:
    printf("\t\t\t===== please tape the id of the  account: ");
    scanf("%d", &idaccount);
    ViderBuffer();
    int test = existaccount(idaccount, u.id, &line);
    printf("%d\n",idaccount);
    printf("%d\n",line);
    //printf("%d\n",ligne);
    if (test == 0)
    {
        printf("compte inexistant \n");
        goto input;
    }

    ligne = 2 * line;
    printf("%d",ligne);
    printf("\t\t\t===== name of the the new user of this account: ");
    scanf("%s", usernw);
    ViderBuffer();
    int nwid = existuser(usernw);
    if (nwid == -1)
    {
        printf("useranme does not exist\n");
        exit(1);
    }

    file = fopen("./data/records.txt", "r");

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int currentLine = 0;
    while (fgets(lines[currentLine], 1000, file) && currentLine < 1000)
    {
        currentLine++;
    }

    fclose(file);

    if ((fp = fopen("./data/records.txt", "r")) == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }


    while (fscanf(fp, "%d %d %49s %d %d/%d/%d %49s %d %f %49s",
                  &ID, &x, y, &z, &a, &b, &m, d, &e, &f, g) == 11)
    {
        if ((ID * 2) == ligne)
        {
            snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, nwid, usernw, z, a, b, m, d, e, f, g);
        }
    }
    fclose(fp);
    removeExtraSpaces(valeur);

    if (ligne >= 0 && ligne < 1000)
    {
        int len = snprintf(NULL, 0, "%s\n\n", valeur);
        snprintf(lines[ligne], len, "%s\n", valeur);
    }
    else
    {
        printf("Numéro de ligne invalide.\n");
        exit(1);
    }
    saveLinesToFile(lines);
    success(u);
}
int existaccount(int idaccount, int iduser, int *line)

{
    FILE *fp;
    int ID, x, a, b, m, e;
    int z, temp;
    int numaccount;
    char y[50], d[50], g[50];
    float f;

    //printf("-----------------------------%d---------------",idaccount);

    if ((fp = fopen("./data/records.txt", "r")) == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    while (fscanf(fp, "%d %d %49s %d %d/%d/%d %49s %d %f %49s",
                  &ID, &x, y, &z, &a, &b, &m, d, &e, &f, g) == 11)
    {
        // temp++;
        //printf("%d\n", z);
        // numaccount = (int)z;
        if ((idaccount == z) && iduser == x)
        {
           
           //printf("---------------%d------%d", z,ID);
            *line = ID;
            fclose(fp);
            return 1; // ID trouvé
        }
    }
    // printf("%d",temp);

    fclose(fp);
    return 0; // ID non trouvé
}

int countLines(char path[50])
{
    FILE *file;
    int count = 0;
    char c;

    file = fopen(path, "r");

    if (file == NULL)
    {
        printf("Error! Opening file.\n");
        exit(1);
    }

    for (c = getc(file); c != EOF; c = getc(file))
    {
        if (c == '\n')
        {
            count++;
        }
    }

    fclose(file);

    return count;
}

void ViderBuffer()
{

    int c;
    int cmp = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        cmp++;
    }
    if (cmp != 0)
    {
        printf("format invalid instead format attending:\n");
        exit(1);
    }
}

void updateField(int ligne, int newPhoneNumber, char *country, double deposit)
{
    FILE *file;
    int ID, x, z, a, b, m, e;
    char y[50], d[50], g[50];
    // char cont[50]=*country;
    float f;
    int temp;
    char valeur[1000];
    char lines[1000][1000];
    FILE *fp;
    double totaldeposit;

    file = fopen("./data/records.txt", "r");

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int currentLine = 0;
    while (fgets(lines[currentLine], 1000, file) && currentLine < 1000)
    {
        currentLine++;
    }

    if ((fp = fopen("./data/records.txt", "r")) == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    while (fscanf(fp, "%d %d %49s %d %d/%d/%d %49s %d %f %49s",
                  &ID, &x, y, &z, &a, &b, &m, d, &e, &f, g) == 11)
    {
        temp++;
        if ((ID * 2) == ligne)
        {
            if ((country == "") && deposit == 0)
            {
                snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, x, y, z, a, b, m, d, newPhoneNumber, f, g);
            }
            if ((strcmp(country, "") != 0) && deposit == 0)
            {
                snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, x, y, z, a, b, m, country, e, f, g);
            }
            else if (deposit != 0)
            {
                totaldeposit = deposit + f;
                snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, x, y, z, a, b, m, d, e, totaldeposit, g);
            }
        }
    }
    removeExtraSpaces(valeur);

    if (ligne >= 0 && ligne < 1000)
    {
        int len = snprintf(NULL, 0, "%s\n\n", valeur);
        snprintf(lines[ligne], len, "%s\n", valeur);
    }
    else
    {
        printf("Numéro de ligne invalide.\n");
        exit(1);
    }
    saveLinesToFile(lines);
}

void saveLinesToFile(char lines[1000][1000])
{
    int taille = countLines("./data/records.txt");
    FILE *file = fopen("./data/records.txt", "w");
    if (file == NULL)
    {
        printf("Impossible d'écrire dans le fichier.\n");
        exit(1);
    }

    for (int i = 0; i < taille; i++)
    {
        fprintf(file, "%s", lines[i]);
    }

    fclose(file);
}

void removeExtraSpaces(char *str)
{
    int count = 0;
    int i;

    for (i = 0; str[i]; i++)
    {
        if (!isspace((unsigned char)str[i]) || (i > 0 && !isspace((unsigned char)str[i - 1])))
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

char *getaccounttype(int id, int *date, double *amount)
{
    FILE *fp;
    int ID, x, z, a, b, m, e;
    char y[50], d[50], g[50];
    float f;

    if ((fp = fopen("./data/records.txt", "r")) == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    while (fscanf(fp, "%d %d %49s %d %d/%d/%d %49s %d %f %49s",
                  &ID, &x, y, &z, &a, &b, &m, d, &e, &f, g) == 11)
    {
        if (ID == id)
        {
            printf("\t\t\t\t-----------------------------------------------------\n");
            printf("\t\t\t\tAccount number: %d\n",z);
            printf("\t\t\t\tDeposit Date: %d/%d/%d\n", a, b, m);
            printf("\t\t\t\tPhone Number: %d\n",e);
            printf("\t\t\t\tAmount deposited: %.2f\n",f);
            printf("\t\t\t\tType of account: %s\n",g);
            printf("\t\t\t\t---------------------------------------------------\n\n\n");
            *date = a;
            *amount = round(f * 100.0) / 100.0;
            // r->accountType=g;
            return strdup(g);
            // return NULL;
        }
    }
    fclose(fp); // N'oubliez pas de fermer le fichier après utilisation
    return NULL;
}

int existuser(char *nom)
{
    FILE *fp;
    int userID;
    char name[50], password[50]; // Assurez-vous que ces tailles sont adaptées à votre fichier

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %49s %49s", &userID, name, password) == 3)
    {
        if (strcmp(name, nom) == 0)
        {
            fclose(fp);
            return userID;
        }
    }

    fclose(fp);
    return -1;
}

//fonction de chiffrement des données avec césar 

char* chiffrementCesar(const char *message, int decalage) {
    int i = 0;
    char *chiffre = (char*)malloc((strlen(message) + 1) * sizeof(char));

    while (message[i] != '\0') {
        if (message[i] >= 'a' && message[i] <= 'z') {
            chiffre[i] = 'a' + (message[i] - 'a' + decalage) % 26;
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            chiffre[i] = 'A' + (message[i] - 'A' + decalage) % 26;
        } else if (message[i] >= '0' && message[i] <= '9') {
            chiffre[i] = '0' + (message[i] - '0' + decalage) % 10;
        } else {
            chiffre[i] = message[i]; // Garde les autres caractères inchangés
        }
        i++;
    }
    chiffre[i] = '\0'; // Ajoute le caractère de fin de chaîne
    return chiffre;
}


//ddéchiffrement du chiffrement de césar

/* char* dechiffrementCesar(const char *message, int decalage) {
    int i = 0;
    char *dechiffre = (char*)malloc((strlen(message) + 1) * sizeof(char));

    while (message[i] != '\0') {
        if (message[i] >= 'a' && message[i] <= 'z') {
            dechiffre[i] = 'a' + (message[i] - 'a' - decalage + 26) % 26;
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            dechiffre[i] = 'A' + (message[i] - 'A' - decalage + 26) % 26;
        } else if (message[i] >= '0' && message[i] <= '9') {
            dechiffre[i] = '0' + (message[i] - '0' - decalage + 10) % 10;
        } else {
            dechiffre[i] = message[i]; // Garde les autres caractères inchangés
        }
        i++;
    }
    dechiffre[i] = '\0'; // Ajoute le caractère de fin de chaîne
    return dechiffre;
} */