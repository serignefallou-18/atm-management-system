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
    
    char date[11]; // Chaîne pour stocker la date YYYY-MM-DD (10 caractères pour la date + 1 pour le caractère nul)
    snprintf(date, sizeof(date), "%04d-%02d-%02d", r.deposit.year, r.deposit.month, r.deposit.day);


    char sql_command[500];
    snprintf(sql_command, sizeof(sql_command), "sqlite3 ./db/atm.db \"INSERT INTO records(idaccount, login, ussername, datecreation, contry, phone, balance, type) VALUES('%s', '%s');\"",r.accountNbr, (&u)->name, (&u)->name, date, r.country, r.phone, r.amount, r.accountType);
    printf("%s",sql_command);
    system(sql_command);
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
        ViderBuffer();
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
        ViderBuffer();
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
    int year, month, day;
    FILE *pf = fopen(RECORDS, "a+");
    struct tm *info;

    system("clear");
    printf("\t\t\t===== New record =====\n");
noAccount:
    r.id = countLines("./data/records.txt") / 2;

    // automaatisation de la date
    time(&timestamp);
    info = localtime(&timestamp);
    month = info->tm_mon + 1;
    day = info->tm_mday;
    year = info->tm_year + 1900;

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    ViderBuffer();
    if ((r.deposit.year > year))
    {
        printf("year invalid");
        goto noAccount;
    }

    if ((r.deposit.year == year) && (r.deposit.month > month) || (r.deposit.month > 12))
    {
        printf("month invalid");
        goto noAccount;
    }
    if ((r.deposit.year == year) && (r.deposit.month <= month) && (r.deposit.day > day) || (r.deposit.day > 31))
    {
        printf("day invalid");
        goto noAccount;
    }
    if ((r.deposit.month == 2) && (r.deposit.day > 29))
    {
        printf("day invalid");
        goto noAccount;
    }
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
    ViderBuffer();
    // printf(r.accountType);
    if ((strcmp(r.accountType, "saving") == 0) && (strcmp(r.accountType, "current") == 0) && (strcmp(r.accountType, "fixed01") == 0) && (strcmp(r.accountType, "fixed02") == 0) && (strcmp(r.accountType, "fixed03") == 0))
    {
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

double getdeposit(int idaccount, int iduser, int *line)
{

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
