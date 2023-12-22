
#include "stdio.h"
#include "header.h"

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
    int id;
    int test;
    system("clear");
    printf("\n\n\n\t\t\t\t\t  Menu of update Account \n\t\t\t\t\t \n");

    printf("\n\n\n\t\t\t\t\t  enter the id of the account: ");
    scanf("%d", &id);
    ViderBuffer();
    test=existaccount(id);
    if (test==0){
        printf("compte inexistante ");
    }

    
}

int existaccount(int id)
{
    FILE *fp;
    int ID;
    int userID;
    char name[50], password[50]; // Assurez-vous que ces tailles sont adaptées à votre fichier

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %*d %*s %*d %*d/%*d/%*d %*s %*d %*f %*s", &ID)!=EOF)
    {
        if (ID==id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0; // Retourne -1 si aucun utilisateu
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
        printf("invalid format il ne dois pas y avoir d'espace\n");
        exit(1);
    }
}