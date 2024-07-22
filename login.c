#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_PASSWORD_LENGTH 20

struct Student
{
    char firstName[50];
    char lastName[50];
    int rollNumber;
    char password[50];
    int mainsRank;
    int advancedRank;
    char email[50];
    char dob[15];
    int income;
};

struct adv_cleared_struct
{
    int adv_rank;
    int roll;
    int pref_len;
    char pref[100][2][10];
    // no need to read below stuff
    int iit_pref_len;
    char iit_pref[100][2][10];
};

struct mains_cleared_struct
{
    int mains_rank;
    int roll;
    int nit_pref_len;
    char nit_pref[100][2][10];
    char allocated_inst[10];
    char allocated_branch[10];
};

struct institution
{
    char inst[10];
    char branch[10];
    int seats;
    int fees;
};

// add record to inst details structure array
void set_values(struct institution s[], int i, char inst[], char branch[], int seats,int fees)
{
    strncpy((s + i)->inst, inst, strlen(inst) + 1);
    strncpy((s + i)->branch, branch, strlen(branch) + 1);
    (s + i)->seats = seats;
    (s+i)->fees=fees;
}

// fn to check student credentials from students_only structure 
int student_login(int *reqd_roll_no, int students_only_len, struct Student students_only[]) 
{

    int inputRollNumber;
    char inputPassword[MAX_PASSWORD_LENGTH];

    printf("Enter rollnumber: ");
    scanf("%d", &inputRollNumber);
    printf("Enter password: ");
    scanf("%s", inputPassword);

    int found = 0;
    int index;
    for (int j = 0; j < students_only_len; j++)
    {
        if (inputRollNumber == students_only[j].rollNumber &&
            strncmp(inputPassword, students_only[j].password, strlen(inputPassword)) == 0)
        {
            found = 1;
            index = j;
            break;
        }
    }

    if (found)
    {
        *reqd_roll_no = inputRollNumber;
        printf("Hello %s %s!\n", students_only[index].firstName, students_only[index].lastName);
    }

    return found;
}

// fn to check if student cleared adv
int cleared_adv(int roll, int adv_cleared_len, struct adv_cleared_struct adv_cleared[100])
{

    int found = 0;
    for (int i = 0; i < adv_cleared_len; i++)
    {
        if (roll == (adv_cleared + i)->roll)
        {
            found = 1;
            break;
        }
    }
    return found;
}

// fn to store inst details in inst structure
void add_inst_details(int *len, char inst_type[5], struct institution inst_details[])
{
    char inst[10];
    char branch[10];
    int seats, j,fees;

    char add_more = 'y';

    while (add_more == 'y' || add_more == 'Y')
    {
        printf("\n\nEnter %s Name: ", inst_type);
        scanf("%s", inst);

        int branch_num = 0;
        printf("Enter no. of branches:");
        scanf("%d", &branch_num);

        for (j = 0; j < branch_num; j++)
        {
            printf("\n\tEnter Branch name: ");
            scanf("%s", branch);

            printf("\tEnter number of seats: ");
            scanf("%d", &seats);

            printf("\tEnter fees: ");
            scanf("%d",&fees);

            set_values(inst_details, (*len), inst, branch, seats,fees);
            (*len)++;
        }
        printf("\nAdd more %ss? y/n:", inst_type);
        scanf(" %c", &add_more);
    }
}

// fn to check admin login
int admin_login()
{
    char inputPassword[10];
    char adminPassword[] = "Admin7";

    printf("\nEnter the password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputPassword, adminPassword) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}