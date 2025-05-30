#include "header.h"
#include <stdbool.h>


void mainMenu(struct User u)
{
    int option;
    int c;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Disconnect\n");
     printf("\n\t\t[9]- Exit\n");
swithc:
    scanf("%d", &option);
    //ViderBuffer();
    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        // student TODO : add your **Update account information** function
        // here
        updateAccount(u);
        break;
    case 3:
        checkExistAccount(u);
        // student TODO : add your **Check the details of existing accounts** function
        // here
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        maketransactin(u);
        break;
    case 6:
        // student TODO : add your **Remove existing account** function
        // here
        removeaccount(u);
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
        makeowntransfer(u);
        break;
    case 8:
        deconnect();

    case 9:
        exit(1);
        break;

    default:
        while ((c = getchar()) != '\n' && c != EOF);       
        printf("Invalid operation!\n");
        goto swithc;
    }
};

void initMenu(struct User *u)
{
    int r = 0;
    int option = 0;
    int c;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d",&option);
        //printf("%d",option);

            switch (option)

            {
            case 1:
                loginMenu(u->name, u->password);
                char *chiff=chiffrementCesar(u->password,3);
                //printf("%s",getPassword(*u));
                printf("%s",chiff);
                if (strcmp(chiff, getPassword(*u)) == 0)
                {  

                    printf("\n\nPassword Match!");
                    u->id=getUserID(u->name,u->password);
                    printf("%d",u->id);
                }
                else
                {
                    printf("\nWrong password!! or User Name\n");
                    exit(1);
                }
                r = 1;
                break;
            case 2:
                // student TODO : add your **Registration** function
                // here
                registration(u);
                r = 1;
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Insert a valid operation!\n");
                while ((c = getchar()) != '\n' && c != EOF);
                //option=0;
                break;
            
            }
            
        }
    };

    int main()
    {
        struct User u;

        initMenu(&u);
        mainMenu(u);
        return 0;
    }
