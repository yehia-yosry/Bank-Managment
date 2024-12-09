// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_LINES 100
#define MAX_LEN 1000
// Structures
typedef struct
{
    char month[10];
    char year[10];
} DOF;
typedef struct
{
    char number[12];
    char name[50];
    char email[50];
    char balance[100];
    char phone[20];
    DOF date;
} Account;
// Global Variables
int numLines, flag, i, input, IsFoundInSearch, IsFoundOnLine;
float Amount;
char userInput;
char buffer[255], userName[30], passWord[30], accNumber[20], filename[30];
char d1[] = ",", d2[] = "-", d3[] = " ";
FILE *f1;
FILE *f2;
char line[255];
//----------------

Account *Load(void);
int Quit(void);
void Menu(void);
void Add(void);
int countLines(void);
int main(void);
void Delete(void);
void Modify(void);
void Advanced_Search(void);
char *convertMonth(char *month);
void Deposit(Account *c);
int isValidAccNum(char number[]);
int isValidName(char number[]);
void Login(void);
void Print(void);
void Report(Account *c);
int Save(void);
void Search(Account *c);
void SortByBalance(void);
void SortByDate(void);
void SortByName(void);
void Transfer(Account *c);
void Withdraw(Account *c);

int main(void)
{
    printf("Hello User !\n--------\n");
    printf("(1)Login\n(2)Quit\n--------\n");
    do
    {
        scanf(" %c", &userInput);
        if (userInput == '1')
            Login();
        else if (userInput == '2')
            exit(0);
        else
        {
            printf("Invalid Choice.\n");
            printf("(1)Retry\n(2)Quit\n");
            while (getchar() != '\n')
            {
                continue;
            }
        }
    } while (userInput != '1' && userInput != '2');
}

int countLines(void)
{
    numLines = 0;
    f1 = fopen("accounts.txt", "r");
    if (f1 == NULL)
    {
        printf("Accounts File Not Found...\n");
        main();
    }
    while (fgets(buffer, sizeof(buffer), f1) != NULL)
        numLines++;
    fclose(f1);
    return numLines;
}

int Quit(void)
{
    exit(0);
}

Account *Load(void)
{
    i = 0;
    f1 = fopen("accounts.txt", "r");
    if (f1 == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }
    Account *A = malloc(sizeof(Account) * 100);
    while (fgets(buffer, 255, f1) != NULL)
    {
        char *number = strtok(buffer, ",");
        strncpy(A[i].number, number, 12);
        // printf("Number:%s\n",A[i].number);
        char *name = strtok(NULL, ",");
        strncpy(A[i].name, name, 50);
        // printf("Name:%s\n",A[i].name);
        char *email = strtok(NULL, ",");
        strncpy(A[i].email, email, 50);
        // printf("Email:%s\n",A[i].email);
        char *balance = strtok(NULL, ",");
        strncpy(A[i].balance, balance, 100);
        // printf("Balance:%s $\n",A[i].balance);
        char *telephone_number = strtok(NULL, ",");
        strncpy(A[i].phone, telephone_number, 20);
        // printf("Mobile:%s \n",A[i].phone);
        char *month = strtok(NULL, "-");
        strncpy(A[i].date.month, month, 10);
        // printf("Date Opened:%s-",A[i].date.month);
        char *year = strtok(NULL, "\0");
        strncpy(A[i].date.year, year, 10);
        // printf("%s\n\n",A[i].date.year);
        // printf("%s\n",A[i].number);
        strcpy(filename, A[i].number);
        strcat(filename, " History.txt");
        FILE *acchistory = fopen(filename, "a");
        fclose(acchistory);
        strcpy(filename, A[i].number);
        strcat(filename, ".txt");
        FILE *acc = fopen(filename, "w");
        fprintf(acc, "%s,%s,%s,%s,%s,%s-%s", A[i].number, A[i].name, A[i].email, A[i].balance, A[i].phone, A[i].date.month, A[i].date.year);
        fclose(acc);
        i++;
    }
    return A;
}

int isValidAccNum(char number[])
{
    if (strlen(number) != 10)
        return 0;
    for (i = 0; i < strlen(number); i++)
    {
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

char *convertMonth(char *month)
{
    int monthnum = atoi(month);
    switch (monthnum)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    }
    return "Invalid Month in Text File";
}

int IsValidName(char name[])
{
    unsigned long n = strlen(name);
    int i;
    for (i = 0; i < n; i++)
    {
        if (name[i] < 65 || name[i] > 122)
            return 0;
        else if (name[i] > 90 && name[i] < 97)
            return 0;
    }
    return 1;
}

void capitalize(char *name)
{
    name[0] = toupper(name[0]);
}

void Advanced_Search(void)
{
    char Name[30];
    flag = 0;
    printf("Enter Name: ");
    scanf("%s", Name);
    if (IsValidName(Name))
    {
        capitalize(Name);
        f1 = fopen("accounts.txt", "r");
        if (f1 == NULL)
        {
            printf("\nAccounts File Not Found...");
            main();
        }
        while ((fgets(buffer, 255, f1)) != NULL)
        {
            char *number = strtok(buffer, ",");
            char *name1 = strtok(NULL, " ");
            char *name2 = strtok(NULL, ",");
            capitalize(name1);
            capitalize(name2);
            if (strcmp(name1, Name) == 0 || strcmp(name2, Name) == 0)
            {
                flag = 1;
                printf("\nAccount Number: %s\n", number);
                printf("Name: %s %s\n", name1, name2);
                char *email = strtok(NULL, ",");
                printf("E-mail: %s\n", email);
                char *balance = strtok(NULL, ",");
                printf("Balance:%s $\n", balance);
                char *telephone = strtok(NULL, ",");
                printf("Mobile:%s\n", telephone);
                char *month = strtok(NULL, "-");
                char *monthstring = convertMonth(month);
                printf("Date Opened: %s ", monthstring);
                char *year = strtok(NULL, " ");
                printf("%s\n\n", year);
            }
        }
        if (flag == 1)
            Menu();
        if (flag == 0)
        {
            printf("\nName Not Found\n");
            printf("\n(1)Retry\n(2)QUIT\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Advanced_Search();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    else
    {
        printf("\nInvalid Name...\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Advanced_Search();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

void Report(Account *c)
{
    flag = 0;
    int l = 0;
    char a[MAX_LINES][MAX_LEN];
    f1 = fopen(filename, "r");
    printf("Please Enter Account Number To Generate Report For:\n");
    scanf("%s", accNumber);
    if (isValidAccNum(accNumber))
    {
        for (i = 0; i < countLines(); i++)
        {
            if (strcmp(accNumber, c[i].number) == 0)
            {
                flag = 1;
                strcpy(filename, c[i].number);
                strcat(filename, " History.txt");
                f1 = fopen(filename, "r");
                break;
            }
        }
    }
    else
    {
        printf("\nInvalid Number\n(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Report(c);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    if (flag == 0)
    {
        printf("\nAccount Number not Found\n(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Report(c);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    while (!feof(f1) && !ferror(f1))
    {
        l++;
        fgets(buffer, 255, f1);
        strcpy(a[l], buffer);
    }
    if ((l - 1) == 0)
    {
        printf("\nNo Previous Transactions Were Done...\n");
        Menu();
    }
    else
    {
        printf("\nThe previous transactions are:\n");
        if (l > 5)
        {
            for (i = l - 5; i < l; i++)
            {
                printf("%s", a[i]);
            }
            Menu();
        }
        else
        {
            for (i = 0; i < l; i++)
            {
                printf("%s", a[i]);
            }
            Menu();
        }
        Menu();
    }
    fclose(f1);
    Menu();
}

void Add(void)
{
    FILE *newacc;
    char filename[100];
    char data[MAX_LINES][MAX_LEN];
    int l = 0;
    time_t t = time(NULL);
    struct tm date1 = *localtime(&t);
    int cmp;
    int count = 0;
    Account an;
    Account *A;
    f1 = fopen("accounts.txt", "r");
    if (f1 == NULL)
    {
        printf("Error opening file.\n");
        Menu();
    }
    while (!feof(f1) && !ferror(f1))
    {
        if (fgets(data[l], MAX_LEN, f1) != NULL)
            l++;
    }
    A = Load();
    fclose(f1);
    printf("Please enter the account number to be added:\n");
    scanf("%s", an.number);
    size_t lenn = strlen(an.number);
    for (i = 0; i < lenn; i++)
    {
        if (!(an.number[i] >= '0' && an.number[i] <= '9'))
        {
            printf("The account number is not inputed as a number, please try again.\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Add();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
        cmp = strcmp(an.number, A[i].number);
        if (cmp == 0)
        {
            printf("The account number already exists. Please try again using an unused account number.\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Add();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    size_t len = strlen(an.number);
    for (i = 0; i < len; i++)
    {
        count++;
    }
    if ((count > 10 || count < 10))
    {
        printf("The account number is not exactly 10 characters, please repeat the entry process again.\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Add();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    else
    {
        getchar();
        printf("Please enter the account user's name:\n");
        scanf("%[^\n]", an.name);
        size_t lena = strlen(an.name);
        for (i = 0; i < lena; i++)
        {
            if (!((((an.name[i] >= 'a' && an.name[i] <= 'z') || (an.name[i] >= 'A' && an.name[i] <= 'Z'))) || an.name[i] == ' '))
            {
                printf("The account name is not inputed as characters, please try again.\n");
                printf("(1)Retry\n(2)Quit\n");
                do
                {
                    scanf(" %c", &userInput);
                    if (userInput == '1')
                        Add();
                    else if (userInput == '2')
                        Menu();
                    else
                    {
                        printf("Invalid Choice.\n");
                        printf("(1)Retry\n(2)Quit\n");
                        while (getchar() != '\n')
                        {
                            continue;
                        }
                    }
                } while (userInput != '1' && userInput != '2');
            }
        }
        printf("Please enter the account user's email:\n");
        scanf("%s", an.email);
        size_t lene = strlen(an.email);
        int f = 0;
        for (i = 0; i < lene; i++)
        {
            if (an.email[i] == '@')
            {
                f = 1;
                continue;
            }
        }
        if (f == 0)
        {
            printf("Invalid Email, please try again.\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Add();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
        printf("Please enter the account user's intial starting balance:\n");
        scanf("%s", an.balance);
        size_t lenb = strlen(an.balance);
        for (i = 0; i < lenb; i++)
        {
            if (!((an.balance[i] >= '0' && an.balance[i] <= '9') || an.balance[i] == '.'))
            {
                printf("The intial starting balance is not inputed as a number, please try again.\n");
                printf("(1)Retry\n(2)Quit\n");
                do
                {
                    scanf(" %c", &userInput);
                    if (userInput == '1')
                        Add();
                    else if (userInput == '2')
                        Menu();
                    else
                    {
                        printf("Invalid Choice.\n");
                        printf("(1)Retry\n(2)Quit\n");
                        while (getchar() != '\n')
                        {
                            continue;
                        }
                    }
                } while (userInput != '1' && userInput != '2');
            }
        }
        printf("Please enter the account user's phone number:\n");
        scanf("%s", an.phone);
        size_t lenp = strlen(an.phone);
        for (i = 0; i < lenp; i++)
        {
            if (!(an.phone[i] >= '0' && an.phone[i] <= '9'))
            {
                printf("The account phone number is not inputed as a number, please try again.\n");
                printf("(1)Retry\n(2)Quit\n");
                do
                {
                    scanf(" %c", &userInput);
                    if (userInput == '1')
                        Add();
                    else if (userInput == '2')
                        Menu();
                    else
                    {
                        printf("Invalid Choice.\n");
                        printf("(1)Retry\n(2)Quit\n");
                        while (getchar() != '\n')
                        {
                            continue;
                        }
                    }
                } while (userInput != '1' && userInput != '2');
            }
        }
        sprintf(an.date.month, "%d", (date1.tm_mon + 1));
        sprintf(an.date.year, "%d", (date1.tm_year + 1900));
        strcpy(filename, an.number);
        strcat(filename, ".txt");
    }
    if (Save())
    {
        f1 = fopen("accounts.txt", "a");
        newacc = fopen(filename, "w");
        if (f1 == NULL)
        {
            printf("Error opening file.\n");
            Menu();
        }
        if (newacc == NULL)
        {
            printf("Error creating new file for additional user.\n");
            Menu();
        }
        fprintf(f1, "\n%s,%s,%s,%s,%s,%s-%s", an.number, an.name, an.email, an.balance, an.phone, an.date.month, an.date.year);
        fprintf(newacc, "%s,%s,%s,%s,%s,%s-%s", an.number, an.name, an.email, an.balance, an.phone, an.date.month, an.date.year);
        fclose(f1);
        fclose(newacc);
        Load();
        Menu();
    }
    else
    {
        Menu();
    }
}
void Delete(void)
{
    FILE *temp;
    char ch;
    char data[MAX_LINES][MAX_LEN];
    int line = 0;
    int c = 0;
    int index = 0;
    int cmp = 0;
    int count = 0;
    Account an;
    Account *A;
    f1 = fopen("accounts.txt", "r");
    if (f1 == NULL)
    {
        printf("Error opening file...\n");
        Menu();
    }
    while (!feof(f1) && !ferror(f1))
    {
        if (fgets(data[line], MAX_LEN, f1) != NULL)
            line++;
    }
    A = Load();

    printf("Please enter the account number to be deleted: \n");
    scanf("%s", an.number);
    size_t len = strlen(an.number);
    for (i = 0; i < len; i++)
    {
        if (!(an.number[i] >= '0' && an.number[i] <= '9'))
        {
            printf("Invalid Account Number, Please Try Again...\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Delete();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    for (i = 0; i < len; i++)
    {
        count++;
    }
    if ((count > 10 || count < 10))
    {
        printf("The account number is not exactly 10 characters, please repeat the account deletion process again.\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Delete();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    for (i = 0; i < line; i++)
    {
        cmp = strcmp(an.number, A[i].number);
        if (cmp == 0)
        {
            index = i + 1;
            break;
        }
    }
    if (cmp != 0)
    {
        printf("The account number does not exist. Please try again using a valid account number.\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Delete();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    float balanceacc = atof(A[index - 1].balance);
    if (balanceacc != 0)
    {
        printf("Account cannot be deleted, there is %s remaining balance.\n", A[index - 1].balance);
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Delete();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    if (Save())
    {
        f1 = fopen("accounts.txt", "w");
        if (f1 == NULL)
        {
            printf("Error opening file.\n");
            Menu();
        }

        while ((ch = getc(f1)) != EOF)
        {
            if (ch == '\n')
                c++;
            if (c != index - 1)
            {
                putc(ch, temp);
            }
        }

        for (i = 0; i < line - 1; i++)
        {
            if (strcmp(an.number, A[i].number) == 0)
                continue;
            fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", A[i].number, A[i].name, A[i].email, A[i].balance, A[i].phone, A[i].date.month, A[i].date.year);
        }
        printf("Account deleted successfully.\n");
        fclose(f1);
        strcpy(filename, an.number);
        strcat(filename, " History.txt");
        remove(filename);
        strcpy(filename, an.number);
        strcat(filename, ".txt");
        remove(filename);
        Menu();
    }
    else
    {
        Menu();
    }
}
void Modify(void)
{
    char ch;
    char inp[10];
    char data[MAX_LINES][MAX_LEN];
    int a;
    int line = 0;
    int index = 0;
    int cmp = 0;
    int count = 0;
    Account an;
    Account *mod;
    f1 = fopen("accounts.txt", "r");
    if (f1 == NULL)
    {
        printf("Error opening file.\n");
        Menu();
    }
    while (!feof(f1) && !ferror(f1))
    {
        if (fgets(data[line], MAX_LEN, f1) != NULL)
            line++;
    }
    mod = Load();
    printf("Please enter the account number to be modified:\n");
    scanf("%s", an.number);
    fflush(stdin);
    size_t len = strlen(an.number);
    for (i = 0; i < len; i++)
    {
        if (!(an.number[i] >= '0' && an.number[i] <= '9'))
        {
            printf("The account number is not inputed as a number, please try again.\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Modify();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    for (i = 0; i < len; i++)
    {
        count++;
    }
    if ((count > 10 || count < 10))
    {
        printf("The account number is not exactly 10 characters, please repeat the account deletion process again.\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Modify();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    for (i = 0; i < line; i++)
    {
        cmp = strcmp(an.number, mod[i].number);
        if (cmp == 0)
        {
            index = i + 1;
            break;
        }
    }
    if (cmp != 0)
    {
        printf("The account number does not exist. Please try again using a valid account number.\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Modify();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    printf("What would you like to modify?\n");
    printf("----------------------\nEnter (1) To Modify The Account User's Name\nEnter (2) To Modify The Account User's Mobile Number\nEnter (3) To Modify The Account User's Email Address\nEnter (4) To Modify The Account User's Name, Mobile Number, and Email Address\n");
    scanf("%s", inp);
    size_t leninp = strlen(inp);
    for (i = 0; i < leninp; i++)
    {
        a = atoi(inp);
        if (!(a >= 1 && a <= 4))
        {
            printf("Invalid input.\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Modify();
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    while (1)
    {
        if (a == 1)
        {
            fflush(stdin);
            printf("Please enter the modified name:\n");
            scanf("%[^\n]", an.name);
            size_t lena = strlen(an.name);
            for (i = 0; i < lena; i++)
            {
                if (!((((an.name[i] >= 'a' && an.name[i] <= 'z') || (an.name[i] >= 'A' && an.name[i] <= 'Z'))) || an.name[i] == ' '))
                {
                    printf("The account name is not inputed as characters, please try again.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    do
                    {
                        scanf(" %c", &userInput);
                        if (userInput == '1')
                            Modify();
                        else if (userInput == '2')
                            Menu();
                        else
                        {
                            printf("Invalid Choice.\n");
                            printf("(1)Retry\n(2)Quit\n");
                            while (getchar() != '\n')
                            {
                                continue;
                            }
                        }
                    } while (userInput != '1' && userInput != '2');
                }
            }
            if (Save())
            {
                f1 = fopen("accounts.txt", "w");
                if (f1 == NULL)
                {
                    printf("Error opening file.\n");
                    Menu();
                }
                strncpy(mod[index - 1].name, an.name, 50);
                for (i = 0; i < line; i++)
                {
                    fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", mod[i].number, mod[i].name, mod[i].email, mod[i].balance, mod[i].phone, mod[i].date.month, mod[i].date.year);
                }
                fclose(f1);
                Load();
                break;
            }
            else
            {
                Menu();
            }
        }
        else if (a == 2)
        {
            printf("Please enter the modified mobile number:\n");
            scanf("%s", an.phone);
            size_t lenp = strlen(an.phone);
            for (i = 0; i < lenp; i++)
            {
                if (!(an.phone[i] >= '0' && an.phone[i] <= '9'))
                {
                    printf("The account phone number is not inputed as a number, please try again.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    do
                    {
                        scanf(" %c", &userInput);
                        if (userInput == '1')
                            Modify();
                        else if (userInput == '2')
                            Menu();
                        else
                        {
                            printf("Invalid Choice.\n");
                            printf("(1)Retry\n(2)Quit\n");
                            while (getchar() != '\n')
                            {
                                continue;
                            }
                        }
                    } while (userInput != '1' && userInput != '2');
                }
            }
            if (Save())
            {
                f1 = fopen("accounts.txt", "w");
                if (f1 == NULL)
                {
                    printf("Error opening file.\n");
                    Menu();
                }
                strncpy(mod[index - 1].phone, an.phone, 20);
                for (i = 0; i < line; i++)
                {
                    fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", mod[i].number, mod[i].name, mod[i].email, mod[i].balance, mod[i].phone, mod[i].date.month, mod[i].date.year);
                }
                fclose(f1);
                Load();
                break;
            }
            else
            {
                Menu();
            }
        }
        else if (a == 3)
        {
            printf("Please enter the modified email address:\n");
            scanf("%s", an.email);
            size_t lene = strlen(an.email);
            int f = 0;
            for (i = 0; i < lene; i++)
            {
                if (an.email[i] == '@')
                {
                    f = 1;
                    continue;
                }
            }
            if (f == 0)
            {
                printf("Invalid Email, please try again.\n");
                printf("(1)Retry\n(2)Quit\n");
                do
                {
                    scanf(" %c", &userInput);
                    if (userInput == '1')
                        Modify();
                    else if (userInput == '2')
                        Menu();
                    else
                    {
                        printf("Invalid Choice.\n");
                        printf("(1)Retry\n(2)Quit\n");
                        while (getchar() != '\n')
                        {
                            continue;
                        }
                    }
                } while (userInput != '1' && userInput != '2');
            }
            if (Save())
            {
                f1 = fopen("accounts.txt", "w");
                if (f1 == NULL)
                {
                    printf("Error opening file.\n");
                    Menu();
                }
                strncpy(mod[index - 1].email, an.email, 50);
                for (i = 0; i < line; i++)
                {
                    fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", mod[i].number, mod[i].name, mod[i].email, mod[i].balance, mod[i].phone, mod[i].date.month, mod[i].date.year);
                }
                fclose(f1);
                Load();
                break;
            }
            else
            {
                Menu();
            }
        }
        else if (a == 4)
        {
            fflush(stdin);
            printf("Please enter the modified name:\n");
            scanf("%[^\n]", an.name);
            size_t lena = strlen(an.name);
            {
                for (i = 0; i < lena; i++)
                {
                    if (!((((an.name[i] >= 'a' && an.name[i] <= 'z') || (an.name[i] >= 'A' && an.name[i] <= 'Z'))) || an.name[i] == ' '))
                    {
                        printf("The account name is not inputed as characters, please try again.\n");
                        printf("(1)Retry\n(2)Quit\n");
                        do
                        {
                            scanf(" %c", &userInput);
                            if (userInput == '1')
                                Modify();
                            else if (userInput == '2')
                                Menu();
                            else
                            {
                                printf("Invalid Choice.\n");
                                printf("(1)Retry\n(2)Quit\n");
                                while (getchar() != '\n')
                                {
                                    continue;
                                }
                            }
                        } while (userInput != '1' && userInput != '2');
                    }
                }
                printf("Please enter the modified mobile number:\n");
                scanf("%s", an.phone);
                size_t lenp = strlen(an.phone);
                for (i = 0; i < lenp; i++)
                {
                    if (!(an.phone[i] >= '0' && an.phone[i] <= '9'))
                    {
                        printf("The account phone number is not inputed as a number, please try again.\n");
                        printf("(1)Retry\n(2)Quit\n");
                        do
                        {
                            scanf(" %c", &userInput);
                            if (userInput == '1')
                                Modify();
                            else if (userInput == '2')
                                Menu();
                            else
                            {
                                printf("Invalid Choice.\n");
                                printf("(1)Retry\n(2)Quit\n");
                                while (getchar() != '\n')
                                {
                                    continue;
                                }
                            }
                        } while (userInput != '1' && userInput != '2');
                    }
                }
                printf("Please enter the modified email address:\n");
                scanf("%s", an.email);
                size_t lene = strlen(an.email);
                int f = 0;
                for (i = 0; i < lene; i++)
                {
                    if (an.email[i] == '@')
                    {
                        f = 1;
                        continue;
                    }
                }
                if (f == 0)
                {
                    printf("Invalid Email, please try again.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    do
                    {
                        scanf(" %c", &userInput);
                        if (userInput == '1')
                            Modify();
                        else if (userInput == '2')
                            Menu();
                        else
                        {
                            printf("Invalid Choice.\n");
                            printf("(1)Retry\n(2)Quit\n");
                            while (getchar() != '\n')
                            {
                                continue;
                            }
                        }
                    } while (userInput != '1' && userInput != '2');
                }
                if (Save())
                {
                    f1 = fopen("accounts.txt", "w");
                    if (f1 == NULL)
                    {
                        printf("Error opening file.\n");
                        Menu();
                    }

                    strncpy(mod[index - 1].name, an.name, 50);
                    strncpy(mod[index - 1].phone, an.phone, 20);
                    strncpy(mod[index - 1].email, an.email, 50);
                    for (i = 0; i < line; i++)
                    {
                        fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", mod[i].number, mod[i].name, mod[i].email, mod[i].balance, mod[i].phone, mod[i].date.month, mod[i].date.year);
                    }
                    fclose(f1);
                    Load();
                    break;
                }
                else
                {
                    Menu();
                }
            }
        }
    }
    Menu();
}

void Search(Account *A)
{
    flag = 0;
    printf("Enter Account Number To Search For: ");
    scanf("%s", accNumber);
    if (isValidAccNum(accNumber))
    {
        for (i = 0; i < countLines(); i++)
        {
            if (strcmp(accNumber, A[i].number) == 0)
            {
                flag = 1;
                printf("Account Number: %s\n", A[i].number);
                printf("Name: %s\n", A[i].name);
                printf("E-mail: %s\n", A[i].email);
                printf("Balance: %s\n", A[i].balance);
                printf("Mobile: %s\n", A[i].phone);
                char *monthstring = convertMonth(A[i].date.month);
                printf("Date Opened %s ", monthstring);
                printf("%s", A[i].date.year);
                Menu();
            }
        }
    }
    else
    {
        printf("Invalid Account Number...\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Search(A);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    if (flag == 0)
    {
        printf("\nAccount Number Not Found...\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Search(A);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

int Save(void)
{
    printf("\nDo You Want To Save Changes? \n");
    printf("(1)Save\n(2)Discard\n");
    scanf("%c", &userInput);
    if (userInput == '1')
        return 1;
    else if (userInput == '2')
        return 0;
    else
    {
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                return 1;
            else if (userInput == '2')
                return 0;
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
    return 0;
}

void Deposit(Account *c)
{
    flag = 0;
    int lines = countLines();

    printf("Enter Account Number: ");
    scanf("%s", accNumber);
    if (isValidAccNum(accNumber))
    {
        for (i = 0; i < countLines(); i++)
        {
            if (strcmp(accNumber, c[i].number) == 0)
            {
                strcpy(filename, c[i].number);
                strcat(filename, " History.txt");
                FILE *acchistory = fopen(filename, "a");
                flag = 1;
                printf("\nEnter Amount To Deposit: \n");
                scanf("%f", &Amount);
                if (Amount > 0 && Amount <= 10000)
                {
                    if (Save())
                    {
                        f1 = fopen("accounts.txt", "w");
                        float NewBalance;
                        float InitialBalance = atof(c[i].balance);
                        NewBalance = InitialBalance + Amount;
                        sprintf(c[i].balance, "%.*f", 2, NewBalance);
                        fprintf(acchistory, "%.2f is deposited into account and current balance is %.2f\n", Amount, NewBalance);
                        fclose(acchistory);
                        printf("\nOld Balance Is: $%.2f\n", InitialBalance);
                        printf("New Balance Is: $%s\n", c[i].balance);

                        for (i = 0; i < lines; i++)
                        {
                            fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", c[i].number, c[i].name, c[i].email, c[i].balance, c[i].phone, c[i].date.month, c[i].date.year);
                        }

                        fclose(f1);

                        Load();
                        Menu();
                    }
                    else
                    {
                        Menu();
                    }
                }
                else
                {
                    printf("\nInvalid Amount. Must Be Greater Than 0$ and Less Than 10,000$\n");
                    printf("(1)Retry\n(2)Quit\n");
                    do
                    {
                        scanf(" %c", &userInput);
                        if (userInput == '1')
                            Deposit(c);
                        else if (userInput == '2')
                            Menu();
                        else
                        {
                            printf("Invalid Choice.\n");
                            printf("(1)Retry\n(2)Quit\n");
                            while (getchar() != '\n')
                            {
                                continue;
                            }
                        }
                    } while (userInput != '1' && userInput != '2');
                }
                break;
            }
        }
        if (flag == 0)
        {
            printf("\nAccount Not Found...\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Deposit(c);
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    else
    {
        printf("\nInvalid Account Number\n");
        printf("(1)Try Again\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Deposit(c);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

void Withdraw(Account *c)
{
    flag = 0;
    int lines = countLines();
    printf("Enter Account Number: ");
    scanf("%s", accNumber);
    if (isValidAccNum(accNumber))
    {
        for (i = 0; i < countLines(); i++)
        {
            if (strcmp(accNumber, c[i].number) == 0)
            {
                flag = 1;
                printf("\nEnter Amount To Withdraw: \n");
                scanf("%f", &Amount);

                if (Amount > 0 && Amount <= 10000)
                {
                    if (Amount > atof(c[i].balance))
                    {
                        printf("\nNo Enough Balance For Withdrawal...\n");
                        printf("(1)Another Service\n(2)Quit\n");
                        do
                        {
                            scanf(" %c", &userInput);
                            if (userInput == '1')
                                Menu();
                            else if (userInput == '2')
                                Quit();
                            else
                            {
                                printf("Invalid Choice.\n");
                                printf("(1)Retry\n(2)Quit\n");
                                while (getchar() != '\n')
                                {
                                    continue;
                                }
                            }
                        } while (userInput != '1' && userInput != '2');
                    }
                    if (Save())
                    {
                        float NewBalance;
                        f1 = fopen("accounts.txt", "w");
                        float InitialBalance = atof(c[i].balance);
                        NewBalance = InitialBalance - Amount;
                        printf("\nIntial Balance is: %.2f\n", InitialBalance);
                        sprintf(c[i].balance, "%.*f", 2, NewBalance);
                        printf("Current Balance is: %s\n", c[i].balance);
                        strcpy(filename, c[i].number);
                        strcat(filename, " History.txt");
                        FILE *acchistory = fopen(filename, "a");
                        fprintf(acchistory, "%.2f is withdrawn from the account and current balance is %.2f\n", Amount, NewBalance);
                        fclose(acchistory);

                        for (i = 0; i < lines; i++)
                        {
                            fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", c[i].number, c[i].name, c[i].email, c[i].balance, c[i].phone, c[i].date.month, c[i].date.year);
                        }
                        fclose(f1);
                        Load();
                    }
                    else
                        Menu();
                }
                else
                {
                    printf("\nInvalid Amount. Must Be Greater Than 0$ and Less Than 10,000$\n");
                    printf("(1)Retry\n(2)Quit\n");
                    do
                    {
                        scanf(" %c", &userInput);
                        if (userInput == '1')
                            Withdraw(c);
                        else if (userInput == '2')
                            Menu();
                        else
                        {
                            printf("Invalid Choice.\n");
                            printf("(1)Retry\n(2)Quit\n");
                            while (getchar() != '\n')
                            {
                                continue;
                            }
                        }
                    } while (userInput != '1' && userInput != '2');
                }
                break;
            }
        }
        Menu();
        if (flag == 0)
        {
            printf("\nAccount Not Found...\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Withdraw(c);
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    else
    {
        printf("\nInvalid Account Number\n");
        printf("(1)Try Again\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Withdraw(c);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

void Transfer(Account *c)
{
    int lines = countLines();
    int k, l;
    float transferAmount, newDonorBalance, newReceiverBalance;
    flag = 0;
    char donor[20];
    char receiver[20];
    printf("Enter Donor Account Number: ");
    scanf(" %s", donor);
    printf("Enter Receiver Account Number: ");
    scanf(" %s", receiver);
    if (isValidAccNum(donor) && isValidAccNum(receiver) && (strcmp(donor, receiver) != 0))
    {
        for (k = 0; k < countLines(); k++)
        {
            if (strcmp(donor, c[k].number) == 0)
            {
                for (l = 0; l < countLines(); l++)
                {
                    if (strcmp(receiver, c[l].number) == 0)
                    {
                        flag = 1;
                        printf("Enter Transfer Amount: ");
                        scanf("%f", &transferAmount);
                        if (transferAmount <= atof(c[k].balance))
                        {
                            if (Save())
                            {
                                f1 = fopen("accounts.txt", "w");
                                printf("\nDonor Intial Balance: %s\n", c[k].balance);
                                printf("Receiver Intial Balance: %s\n", c[l].balance);
                                newDonorBalance = atof(c[k].balance) - transferAmount;
                                sprintf(c[k].balance, "%.*f", 2, newDonorBalance);
                                newReceiverBalance = atof(c[l].balance) + transferAmount;
                                sprintf(c[l].balance, "%.*f", 2, newReceiverBalance);
                                strcpy(filename, c[k].number);
                                strcat(filename, " History.txt");
                                FILE *acchistoryd = fopen(filename, "a");
                                fprintf(acchistoryd, "%.2f is Transfered From Account, Current Balance is %.2f\n", transferAmount, newDonorBalance);
                                fclose(acchistoryd);
                                strcpy(filename, c[l].number);
                                strcat(filename, " History.txt");
                                FILE *acchistoryr = fopen(filename, "a");
                                fprintf(acchistoryr, "%.2f is Transfered To account, Current Balance is %.2f\n", transferAmount, newReceiverBalance);
                                fclose(acchistoryd);
                                printf("Donor Current Balance: %s\n", c[k].balance);
                                printf("Receiver Current Balance: %s\n", c[l].balance);

                                for (i = 0; i < lines; i++)
                                {
                                    fprintf(f1, "%s,%s,%s,%s,%s,%s-%s", c[i].number, c[i].name, c[i].email, c[i].balance, c[i].phone, c[i].date.month, c[i].date.year);
                                }
                                fclose(f1);
                                Menu();
                            }
                            else
                            {
                                Menu();
                            }
                        }
                        else
                        {
                            printf("\nNot Enough Balance For Transfer: \n");
                            printf("(1)Retry\n(2)Quit\n--------\n");
                            do
                            {
                                scanf(" %c", &userInput);
                                if (userInput == '1')
                                    Transfer(c);
                                else if (userInput == '2')
                                    Menu();
                                else
                                {
                                    printf("Invalid Choice.\n");
                                    printf("(1)Retry\n(2)Quit\n");
                                    while (getchar() != '\n')
                                    {
                                        continue;
                                    }
                                }
                            } while (userInput != '1' && userInput != '2');
                        }
                    }
                }
            }
        }
        if (flag == 0)
        {
            printf("\nMake Sure Both Accounts Are Intact\n");
            printf("(1)Retry\n(2)Quit\n");
            do
            {
                scanf(" %c", &userInput);
                if (userInput == '1')
                    Transfer(c);
                else if (userInput == '2')
                    Menu();
                else
                {
                    printf("Invalid Choice.\n");
                    printf("(1)Retry\n(2)Quit\n");
                    while (getchar() != '\n')
                    {
                        continue;
                    }
                }
            } while (userInput != '1' && userInput != '2');
        }
    }
    else
    {
        printf("\nMake Sure That Both Account Numbers are Valid And Not Equal\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Transfer(c);
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

void SortByName(void)
{
    Account *A = Load();
    numLines = countLines();
    int issorted = 0, pass;
    Account temp;
    for (pass = 1; pass < numLines && !(issorted); pass++)
    {
        issorted = 1;
        for (i = 0; i < numLines - pass; i++)
        {
            capitalize(A[i].name);
            capitalize(A[i + 1].name);
            if (strcmp(A[i].name, A[i + 1].name) > 0)
            {
                issorted = 0;
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
    }
    printf("\n\n----Accounts Sorted By Name:----\n\n");
    for (i = 0; i < numLines; i++)
    {
        printf("Account Number: %s\n", A[i].number);
        printf("Name: %s\n", A[i].name);
        printf("Email: %s\n", A[i].email);
        printf("Balance: %s\n", A[i].balance);
        printf("Phone: %s\n", A[i].phone);
        printf("Date Opened: %s-", A[i].date.month);
        printf("%s\n\n", A[i].date.year);
    }
    Menu();
}

void SortByBalance(void)
{
    Account *A = Load();
    numLines = countLines();
    int issorted = 0, pass;
    Account temp;
    for (pass = 1; pass < numLines && !issorted; pass++)
    {
        issorted = 1;
        for (i = 0; i < numLines - pass; i++)
        {
            float floatValue1 = atof(A[i].balance);
            float floatValue2 = atof(A[i + 1].balance);
            if (floatValue1 < floatValue2)
            {
                issorted = 0;
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
    }
    printf("\n\n----Accounts Sorted By Balance:----\n\n");
    for (i = 0; i < numLines; i++)
    {
        printf("Account Number: %s\n", A[i].number);
        printf("Name: %s\n", A[i].name);
        printf("Email: %s\n", A[i].email);
        printf("Balance: %s\n", A[i].balance);
        printf("Phone: %s\n", A[i].phone);
        printf("Date Opened: %s-", A[i].date.month);
        printf("%s\n\n", A[i].date.year);
    }
    Menu();
}

void SortByDate(void)
{
    Account *A = Load();
    numLines = countLines();
    int issorted = 0, pass;
    Account temp;
    for (pass = 1; pass < numLines && !issorted; pass++)
    {
        issorted = 1;
        for (i = 0; i < numLines - pass; i++)
        {
            if (atoi(A[i].date.year) < atoi(A[i + 1].date.year))
            {
                issorted = 0;
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
    }
    for (pass = 1; pass < numLines; pass++)
    {
        for (i = 0; i < numLines - pass; i++)
        {
            if (atoi(A[i].date.year) == atoi(A[i + 1].date.year) && atoi(A[i].date.month) < atoi(A[i + 1].date.month))
            {
                temp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = temp;
            }
        }
    }

    printf("\n\n----Accounts Sorted By Date:----\n\n");
    for (i = 0; i < numLines; i++)
    {
        printf("Account Number: %s\n", A[i].number);
        printf("Name: %s\n", A[i].name);
        printf("Email: %s\n", A[i].email);
        printf("Balance: %s\n", A[i].balance);
        printf("Phone: %s\n", A[i].phone);
        printf("Date Opened: %s-", A[i].date.month);
        printf("%s\n\n", A[i].date.year);
    }
    Menu();
}

void Print(void)
{
    printf("Sort Based On...\n(1)Name\n(2)Balance\n(3)Date Opened\n");
    scanf(" %c", &userInput);
    if (userInput == '1')
        SortByName();
    else if (userInput == '2')
        SortByBalance();
    else if (userInput == '3')
        SortByDate();
    else
    {
        printf("\nInvalid Input...\n");
        printf("(1)Try Again\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Print();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

void Menu(void)
{
    Account *x = Load();
    printf("\n----Choose Option----\n");
    printf("(1) ADD\n");
    printf("(2) DELETE\n");
    printf("(3) MODIFY\n");
    printf("(4) SEARCH\n");
    printf("(5) ADVANCED SEARCH\n");
    printf("(6) WITHDRAW\n");
    printf("(7) DEPOSIT\n");
    printf("(8) TRANSFER\n");
    printf("(9) REPORT\n");
    printf("(10) PRINT\n");
    printf("(11) QUIT\n");
    printf("----------------\n");

    printf("==>");
    scanf("%d", &input);
    if (input >= 1 && input <= 11)
    {
        switch (input)
        {
        case 1:
            Add();
            break;
        case 2:
            Delete();
            break;
        case 3:
            Modify();
            break;
        case 4:
            Search(x);
            break;
        case 5:
            Advanced_Search();
            break;
        case 6:
            Withdraw(x);
            break;
        case 7:
            Deposit(x);
            break;
        case 8:
            Transfer(x);
            break;
        case 9:
            Report(x);
            break;
        case 10:
            Print();
            break;
        case 11:
            Quit();
            break;
        }
    }
    else
    {
        printf("\nInvalid Input\n(1)Try Again\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Menu();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}

void Login(void)
{
    flag = 0;
    printf("----Login In----\n");
    printf("Enter Username: ");
    scanf("%s", userName);
    printf("Enter Password: ");
    scanf("%s", passWord);
    f2 = fopen("users.txt", "r");
    if (f2 == NULL)
    {
        printf("\nUsers File Not Found...");
        main();
    }
    while (fgets(buffer, sizeof(buffer), f2) != NULL)
    {
        char *user = strtok(buffer, " ");
        char *pass = strtok(NULL, "\n");
        if (strcmp(userName, user) == 0)
        {
            if (strcmp(passWord, pass) == 0)
            {
                printf("\n\n----Successful Login!----\n\n");
                flag = 1;
                Menu();
            }
        }
    }
    fclose(f2);
    if (!flag)
    {
        printf("\nUser Not Found...\n");
        printf("(1)Retry\n(2)Quit\n");
        do
        {
            scanf(" %c", &userInput);
            if (userInput == '1')
                Login();
            else if (userInput == '2')
                Menu();
            else
            {
                printf("Invalid Choice.\n");
                printf("(1)Retry\n(2)Quit\n");
                while (getchar() != '\n')
                {
                    continue;
                }
            }
        } while (userInput != '1' && userInput != '2');
    }
}
