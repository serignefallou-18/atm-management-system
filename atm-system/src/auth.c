#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(int id, char login[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", login);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);
    id=getUserID(login, pass);
    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }

};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%*d %s %s", userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *password = userChecker.password;
            return password;
        }
    }

    fclose(fp);
    return "no user found";
}


int getUserID(char username[50],char pass[50])
{
    FILE *fp;
    int userID = -1;
    char name[20], password[20]; // Assurez-vous que ces tailles sont adaptées à votre fichier

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userID, name, password) != EOF)
    {
        if (strcmp(name, username) == 0 && strcmp(password,pass)==0)
        {
            fclose(fp);
            return userID;
        }
    }

    fclose(fp);
    printf("user inexitante");
    return -1; // Retourne -1 si aucun utilisateur correspondant n'est trouvé
}
