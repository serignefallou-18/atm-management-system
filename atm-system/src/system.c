#include "header.h"
#include "time.h"

const char *RECORDS = "./data/records.txt";
time_t timestamp;

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            (&r)->id,
            (&u)->id,
            (&u)->name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    ViderBuffer();
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    struct tm *info;

noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");
    r.id = countLines("./data/records.txt") / 2;

    //automaatisation de la date
    time(&timestamp);
    info = localtime(&timestamp);
    r.deposit.month=info->tm_mon + 1;
    r.deposit.day=info->tm_mday;
    r.deposit.year=info->tm_year + 1900;


    // printf("\nEnter today's date(mm/dd/yyyy):");
    // scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    // ViderBuffer();
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);
    ViderBuffer();

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    ViderBuffer();
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    ViderBuffer();
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    ViderBuffer();
typeAccount:
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
   // printf(r.accountType);
    if ((strcmp(r.accountType, "saving")==0)&&(strcmp(r.accountType, "current")==0)&&(strcmp(r.accountType, "fixed01")==0)&&(strcmp(r.accountType, "fixed02")==0)&&(strcmp(r.accountType, "fixed03")==0)){
        printf("choix non disponnible");
        goto typeAccount;
    }
 
    
    ViderBuffer();
    printf("%d", u.id);
    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}



//recupèration de chaine de caractère qui se trouve dans mon strdup;

char *my_strdup(const char *src) {
    if (src == NULL) {
        return NULL; // Gestion du cas où la source est NULL
    }
    size_t length = strlen(src) + 1; // Taille de la chaîne + 1 pour le caractère nul
    char *dest = malloc(length); // Allocation de mémoire
    if (dest == NULL) {
        return NULL; // Gestion de l'échec d'allocation
    }
    strcpy(dest, src); // Copie de la chaîne source vers la mémoire allouée
    return dest;
}

double getdeposit(int idaccount, int iduser, int *line){

    FILE *fp;
    int ID, x, a, b, m, e;
    int z;
    int numaccount;
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
        numaccount = (int)z;
        if ((numaccount == idaccount) && iduser == x)
        {
            printf("%d", z);
            *line = ID;
            fclose(fp);
            return f; // ID trouvé
        }
    }

    fclose(fp);
    return 0; // ID non trouvé
}
