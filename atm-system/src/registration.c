#include "stdio.h"
#include "header.h"

void registration()
{
    FILE *fp;
    struct User u;
    char pass[50];

    system("clear");
    printf("\n\n\n\t\t\t\t Welcome to pzge of Regisration\n\t\t\t\t\t \n");
    printf("username");
    scanf("%s", (&u)->name);
    printf("password");
    scanf("%s", (&u)->password);
    printf("Confirm password");
    scanf("%s", &pass);

    if (strcmp(u.password, pass) != 0)
    {
        printf("unmatched pasword try again");
        registration();
    }
    else
    {
        if ((fp = fopen("./data/users.txt", "a")) == NULL)
        {
            printf("Error! opening file");
            exit(1);
        }else{
            fprintf(fp,"%s %s",u.name,u.password);
            Success(u);
        }
    }
}