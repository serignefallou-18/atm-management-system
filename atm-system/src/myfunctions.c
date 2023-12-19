
#include "stdio.h"
#include "header.h"

void registration(struct User *u)
{
    FILE *fp;
    char pass[50];
    char fileLogin[50], filePassword[50];
    int id;

    u->id = countLines();
reinscript:
    system("clear");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t  Welcome to page of Registration\n\t\t\t\t\t \n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t  username: ");
    scanf("%s", u->name);
    printf("\n\n\n\t\t\t\t\t\t\t\t\t  password: ");
    scanf("%s", u->password);
    printf("\n\n\n\t\t\t\t\t\t\t\t\t  Confirm password: ");
    scanf("%s", pass);

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
            while (fscanf(fp, "%d %49s %49s", &id, fileLogin, filePassword) == 3)
            {
                // Comparaison des logins et mots de passe
                if (strcmp(u->name, fileLogin) == 0 || strcmp(u->password, filePassword) == 0)
                {
                    fclose(fp);
                    printf("username or password already exits please try again");
                    goto reinscript;
                }
            }

            fprintf(fp, "\n%d %s %s", u->id, u->name, u->password);
            fclose(fp);
            success((*u));
        }
    }
}

int countLines()
{
    FILE *file;
    int count = 0;
    char c;

    file = fopen("./data/users.txt", "r");

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