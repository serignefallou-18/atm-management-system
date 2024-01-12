#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Date
{
    int month, day, year;
};

// all fields for each record of an account
struct Record
{
    int id;
    int userId;
    char name[100];
    char country[100];
    int phone;
    char accountType[10];
    int accountNbr;
    double amount;
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
void registerMenu(char a[50], char pass[50]);
const char *getPassword(struct User u);

// system function
void createNewAcc(struct User u);
void mainMenu(struct User u);
void checkAllAccounts(struct User u);
void success(struct User u);
void stayOrReturn(int notGood, void f(struct User u), struct User u);
void initMenu(struct User *u);



//my own functions
void registration(struct User *u);
int countLines();
void ViderBuffer();
int getUserID(char username[50],char pass[50]);
void updateAccount(struct User u);
int existaccount(int idaccount, int iduser, int *line);
void updateField(int ligne, int newPhoneNumber, char *country, double deposit);
void saveLinesToFile(char lines[1000][1000]);
void removeExtraSpaces(char *str);
void checkExistAccount(struct User u);
char *getaccounttype(int id, int *date, double *amount, int *day, int *year);

void maketransactin(struct User u);
void updatedeposit(double deposit);
double getdeposit(int idaccount, int iduser, int *line);
void removeaccount(struct User u);
void makeowntransfer(struct User u);
int existuser(char *nom);
char* chiffrementCesar(const char *message, int decalage);
void deconnect();