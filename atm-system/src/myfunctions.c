#include "stdio.h"
#include "header.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

void registration(struct User *u)
{
    FILE *fp;
    char pass[50];
    char fileLogin[50], filePassword[50];
    int id;

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

            fprintf(fp, "\n%d %s %s", u->id, u->name, u->password);
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
    system("clear");
    printf("\n\n\n\t\t\t\t\t  Menu of update Account \n\t\t\t\t\t \n");

    printf("\n\n\n\t\t\t\t\t  enter the id of the account: ");
    scanf("%d", &idaccount);
    ViderBuffer();
    //  printf("%d", idaccount);
    test = existaccount(idaccount, u.id);
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
        ligne = (2 * idaccount);
        switch (choiceUpdate)
        {
        case 1:
            printf("\n\n\n\t\t\t\t\t  Enter the new phone Number:");
            scanf("%d", &phone);
            ViderBuffer();
            updateField(ligne, phone, "");
            break;
        case 2:
            printf("\n\n\n\t\t\t\t\t  Enter the new country:");
            scanf("%s", &country);
            updateField(ligne, 0, country);
            break;
        default:
            printf("\n\n\n\t\t\t\t\tinvalid input");
            goto update;
        }

        success(u);
    }
}

void chackExistAccount(struct User u)
{
    struct Record r;
    int idaccount;
    // char tab[5][50];
    int test;
    double interet;
    char *typeacount;
    int date;
    double amount;

    system("clear");
    printf("\t\t\t===== For checking existing account =====\n");
input:
    printf("\t\t\t===== please tape the id of the  account: ");
    scanf("%d", &idaccount);
    test = existaccount(idaccount, u.id);
    if (test == 0)
    {
        printf("compte inexistant \n");
        goto input;
    }

    typeacount = getaccounttype(idaccount, &date,&amount);
   // printf("%s", typeacount);
    if (strcmp(typeacount, "current") == 0)
    {
        printf("You will not get interests because the account is of type current\n");
    }
    else if ((strcmp(typeacount, "saving") == 0))
    {
        interet = round(((amount * 7) / 1200));
        printf("You will get %.2f interest on day %d of every month", interet, date);
    }
    else if ((strcmp(typeacount, "fixed01") == 0))
    {
        interet = round(((amount * 4) / 1200));
        printf("You will get %.2f interest on day %d of every month", interet, date);
    }
    else if ((strcmp(typeacount, "fixed02") == 0))
    {
        interet = round(((amount * 5) / 1200));
        printf("You will get %.2f interest on day %d of every month", interet, date);
    }
    else if ((strcmp(typeacount, "fixed03") == 0))
    {
        interet = round(((amount * 8) / 1200));
        printf("You will get %.2f interest on day %d of every month", interet, date);
    }
}

int existaccount(int idaccount, int iduser)
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
        if ((ID == idaccount) && iduser == x)
        {
            fclose(fp);
            return 1; // ID trouvé
        }
    }

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

void updateField(int ligne, int newPhoneNumber, char country[50])
{
    FILE *file;
    int ID, x, z, a, b, m, e;
    char y[50], d[50], g[50];
    float f;
    int temp;
    char valeur[1000];
    char lines[1000][1000];
    FILE *fp;

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
            if (country == "")
            {
                snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, x, y, z, a, b, m, d, newPhoneNumber, f, g);
            }
            if (strcmp(country, "") != 0)
            {
                snprintf(valeur, sizeof(valeur), "%d %d %49s %d %d/%d/%d %49s %d %f %49s", ID, x, y, z, a, b, m, country, e, f, g);
            }
        }
    }
    removeExtraSpaces(valeur);

    if (ligne >= 0 && ligne < 1000)
    {
        snprintf(lines[ligne], 1000, "%s\n", valeur);
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

char *getaccounttype(int id, int *date,double *amount)
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
           *date=a;
           *amount= round(f * 100.0) / 100.0;
           // r->accountType=g;
            return strdup(g);
        }
    }
}