
// queue: array of structs:[inst,array of roll]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu_fns.c" //calls file_fns.c //calls login.c

struct waiting_list
{
    char inst[10];
    char branch[10];
    int roll_len;
    int roll_arr[100];
};

struct student_allotment_struct
{
    int roll;
    char inst[10];
    char branch[10];
};

struct branch_roll_struct
{
    char branch[10];
    int roll_len;
    int roll_arr[100];
};

struct inst_wise_allotment_struct
{
    char inst[10];
    int branch_len;
    struct branch_roll_struct branch_roll[20];
};

void display_inst_wise_allotment(int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{

    
    int inst_wise_allotment_len = 0;
    struct inst_wise_allotment_struct inst_wise_allotment[100];

    // Iterating through inst details
    for (int i = 0; i < mains_cleared_len; i++)
    {

        int stu_roll = mains_cleared[i].roll;

        char inst[10];
        strncpy(inst, (mains_cleared + i)->allocated_inst, strlen((mains_cleared + i)->allocated_inst));
        inst[strlen((mains_cleared + i)->allocated_inst)] = '\0';
        char branch[10];
        strncpy(branch, (mains_cleared + i)->allocated_branch, strlen((mains_cleared + i)->allocated_branch));
        branch[strlen((mains_cleared + i)->allocated_branch)] = '\0';

        // checking if both are not empty strings (no allocation)
        if (strlen(inst) != 0 && strlen(branch) != 0)
        {

            // iterating through inst wise allocation to check if inst already exists
            bool inst_found = false;
            for (int _ = 0; _ < (inst_wise_allotment_len); _++)
            {
                // case1: inst exists
                if (strcmp(inst, inst_wise_allotment[_].inst) == 0)
                {
                    inst_found = true;
                    bool branch_found = false;
                    for (int j = 0; j < (inst_wise_allotment[_].branch_len); j++)
                    {
                        // case1a: branch exists
                        if (strcmp(branch, (inst_wise_allotment[_].branch_roll[j].branch)) == 0)
                        {
                            // adding roll
                            int roll_len = (inst_wise_allotment[_].branch_roll)[j].roll_len;
                            (inst_wise_allotment[_].branch_roll)[j].roll_arr[roll_len] = stu_roll;
                            ((inst_wise_allotment[_].branch_roll)[j].roll_len)++;
                            branch_found = true;
                            break;
                        }
                    }

                    // case1b: branch doesnt exist
                    if (!branch_found)
                    {
                        // adding branch
                        strncpy((inst_wise_allotment[_].branch_roll)[(inst_wise_allotment[_].branch_len)].branch, branch, strlen(branch));
                        ((inst_wise_allotment[_].branch_roll)[(inst_wise_allotment[_].branch_len)].branch)[strlen(branch)] = '\0';

                        // adding roll
                        (inst_wise_allotment[_].branch_roll)[(inst_wise_allotment[_].branch_len)].roll_arr[0] = stu_roll;

                        // incrementing roll_len
                        ((inst_wise_allotment[_].branch_roll)[inst_wise_allotment[_].branch_len].roll_len) = 1;
                        // incrementing branch_len
                        (inst_wise_allotment[_].branch_len)++;
                    }
                    break;
                }
            }

            // case2: inst doesnt exist
            if (!inst_found)

            {
                // adding inst
                strncpy(inst_wise_allotment[inst_wise_allotment_len].inst, inst, strlen(inst));
                (inst_wise_allotment[inst_wise_allotment_len].inst)[strlen(inst)] = '\0';

                // adding branch
                strncpy((inst_wise_allotment[inst_wise_allotment_len].branch_roll)[0].branch, branch, strlen(branch));
                ((inst_wise_allotment[inst_wise_allotment_len].branch_roll)[0].branch)[strlen(branch)] = '\0';

                // adding roll to roll_arr in branch_struct
                (inst_wise_allotment[inst_wise_allotment_len].branch_roll)[0].roll_arr[0] = stu_roll;

                // incrementing roll_len
                ((inst_wise_allotment[inst_wise_allotment_len].branch_roll)[0].roll_len) = 1;
                // incrementing branch_len
                (inst_wise_allotment[inst_wise_allotment_len].branch_len) = 1;
                // increment int_wise_allotment_len
                (inst_wise_allotment_len)++;
            }
        }
    }

    // DISPLAYING STRUCT
    // iterating through insts in inst_wise_allotment
    for (int i = 0; i < inst_wise_allotment_len; i++)
    {
        printf("\n\n %s: ", inst_wise_allotment[i].inst);
        // iterating through branches for each inst
        for (int j = 0; j < inst_wise_allotment[i].branch_len; j++)
        {
            printf("\n\t %s: ", inst_wise_allotment[i].branch_roll[j].branch);
            // iterating through rolls for each branch
            for (int k = 0; k < inst_wise_allotment[i].branch_roll[j].roll_len; k++)
            {
                printf("%d ", inst_wise_allotment[i].branch_roll[j].roll_arr[k]);
            }
        }
    }
}

int display_allocated_seat(int roll_num, int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{
    for (int sturec = 0; sturec < mains_cleared_len; sturec++)
    {
        if (mains_cleared[sturec].roll == roll_num)
        {
            if (strlen(mains_cleared[sturec].allocated_inst) != 0 && strlen(mains_cleared[sturec].allocated_branch) != 0)
            {
                printf("\nCONGRATULATIONS!!\nYou have been alloted %s in %s", mains_cleared[sturec].allocated_branch, mains_cleared[sturec].allocated_inst);
                return 1;
            }
            else
            {
                printf("\nYou have not been alloted a seat.");// GO TO SSN");
                return 0;
            }
            break;
        }
    }
}

int get_fees(int roll_num, int students_only_len, struct Student students_only[],
             int mains_cleared_len, struct mains_cleared_struct mains_cleared[],
             int iit_details_len, struct institution iit_details[],
             int nit_details_len, struct institution nit_details[])
{

    char inst[10];
    char branch[10];

    // getting allocated inst,branch
    for (int _ = 0; _ < mains_cleared_len; _++)
    {
        if (roll_num == mains_cleared[_].roll)
        {
            strncpy(inst, mains_cleared[_].allocated_inst, strlen(mains_cleared[_].allocated_inst));
            inst[strlen(mains_cleared[_].allocated_inst)] = '\0';
            strncpy(branch, mains_cleared[_].allocated_branch, strlen(mains_cleared[_].allocated_branch));
            branch[strlen(mains_cleared[_].allocated_branch)] = '\0';
            break;
        }
    }
    int fees;

    // getting fee
    if (inst[0] == 'I')
    {
        for (int _ = 0; _ < iit_details_len; _++)
        {
            if (strcmp(inst, iit_details[_].inst) == 0 && strcmp(branch, iit_details[_].branch) == 0)
            {
                fees = iit_details[_].fees;
                break;
            }
        }
    }
    else if (inst[0] == 'N')
    {
        for (int _ = 0; _ < nit_details_len; _++)
        {
            if (strcmp(inst, nit_details[_].inst) == 0 && strcmp(branch, nit_details[_].branch) == 0)
            {
                fees = nit_details[_].fees;
                break;
            }
        }
    }

    for (int _ = 0; _ < students_only_len; _++)
    {
        if (roll_num == students_only[_].rollNumber)
        {
            int income = students_only[_].income;
            if (income <= 50000)
            {
                printf("\nBased on your income status you have been given a 100%% waiver on your tuition fee!");
                printf("\nTution fee per year = INR %d", 0);
            }
            else if (income > 50000 && income <= 200000)
            {
                printf("\nBased on your income status you have been given a 75%% waiver on your tuition fee!");
                printf("\nTution fee per year = INR %.2f", (float)fees * (0.25));
            }
            else if (income > 200000 && income <= 500000)
            {
                printf("\nBased on your income status you have been given a 50%% waiver on your tuition fee!");
                printf("\nTution fee per year = INR %.2f", (float)fees * (0.5));
            }
            else
            {
                printf("\nTuition fee per year = INR %.2f", (float)fees);
            }
        }
    }
}

// fns to check queue and inst details (test fns)
void display_queues(int queues_len, struct waiting_list queues[])
{
    for (int _ = 0; _ < queues_len; _++)
    {
        struct waiting_list *q = (queues + _);
        printf("\ninst:%s branch: %s \nrolls:", (q)->inst, (q)->branch);
        for (int roll = 0; roll < (q)->roll_len; roll++)
        {
            printf(" %d", (q)->roll_arr[roll]);
        }
    }
}
void print_inst_details(int details_len, struct institution inst_details[])
{
    for (int _ = 0; _ < details_len; _++)
    {
        printf("inst: %s branch: %s seats: %d\n", inst_details[_].inst, inst_details[_].branch, inst_details[_].seats);
    }
}

void remove_roll_from_q(int course, struct waiting_list queues[])
{
    for (int _ = 0; _ < queues[course].roll_len - 1; _++)
    {
        (queues[course].roll_arr)[_] = (queues[course].roll_arr)[_ + 1];
    }
    (queues[course].roll_len)--;
}

void update1_mains_cleared(int roll_num, char inst[], char branch[], struct mains_cleared_struct mains_cleared[], int mains_cleared_len)
{
    for (int sturec = 0; sturec < mains_cleared_len; sturec++)
    {
        if (mains_cleared[sturec].roll == roll_num)
        {
            strncpy(mains_cleared[sturec].allocated_inst, inst, strlen(inst));
            mains_cleared[sturec].allocated_inst[strlen(inst)] = '\0';
            strncpy(mains_cleared[sturec].allocated_branch, branch, strlen(branch));
            mains_cleared[sturec].allocated_branch[strlen(branch)] = '\0';
        }
    }
}

void update_mains_cleared(int allocated_len, struct student_allotment_struct allocated_seats[],
                          int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{
    for (int allot = 0; allot < allocated_len; allot++)
    {
        int roll = allocated_seats[allot].roll;
        for (int sturec = 0; sturec < mains_cleared_len; sturec++)
        {
            if (roll == mains_cleared[sturec].roll)
            {
                strncpy(mains_cleared[sturec].allocated_inst, allocated_seats[allot].inst, strlen(allocated_seats[allot].inst));
                mains_cleared[sturec].allocated_inst[strlen(allocated_seats[allot].inst)] = '\0';
                strncpy(mains_cleared[sturec].allocated_branch, allocated_seats[allot].branch, strlen(allocated_seats[allot].branch));
                mains_cleared[sturec].allocated_branch[strlen(allocated_seats[allot].branch)] = '\0';
                break;
            }
        }
    }
}

int find_pref_number(char inst[], char branch[], int roll_num, int adv_cleared_len, struct adv_cleared_struct adv_cleared[])
{
    int pref_num;
    for (int sturec1 = 0; sturec1 < adv_cleared_len; sturec1++)
    {
        if (roll_num == adv_cleared[sturec1].roll)
        {
            for (int pref = 0; pref < adv_cleared[sturec1].pref_len; pref++) //  pref_len is the name of column storing total number of preferences
            {
                if (strcmp((adv_cleared[sturec1].pref)[pref][0], inst) == 0 && strcmp((adv_cleared[sturec1].pref)[pref][1], branch) == 0)
                {
                    pref_num = pref;
                    return pref_num;
                }
            }
        }
    }
}

int fill_vacancies(char inst[], char branch[],
                   int queues_len, struct waiting_list queues[],
                   int mains_cleared_len, struct mains_cleared_struct mains_cleared[],
                   int adv_cleared_len, struct adv_cleared_struct adv_cleared[],
                   int(*allocated_len), struct student_allotment_struct allocated_seats[],
                   int nit_details_len, struct institution nit_details[],
                   int iit_details_len, struct institution iit_details[])
{
    for (int course = 0; course < queues_len; course++)
    {
        if (strcmp(queues[course].inst, inst) == 0 && strcmp(queues[course].branch, branch) == 0)
        {

            // Iterating through the list of roll numbers waiting for the course
            for (int stu_roll = 0; stu_roll < queues[course].roll_len; stu_roll++)
            {
                print_mains_cleared(mains_cleared_len, mains_cleared);

                for (int sturec = 0; sturec < mains_cleared_len; sturec++)
                {
                    int roll = mains_cleared[sturec].roll;

                    if (roll == queues[course].roll_arr[stu_roll])
                    {

                        // CASE - 1 - Student has not been alloted any seat already
                        if (strlen(mains_cleared[sturec].allocated_inst) == 0 && strlen(mains_cleared[sturec].allocated_branch) == 0)
                        {
                            // Give the student the vacant seat
                            // Now adding the new allotment to the allocated_seats list

                            allocated_seats[(*allocated_len)].roll = queues[course].roll_arr[stu_roll];
                            strncpy(allocated_seats[(*allocated_len)].inst, inst, strlen(inst));
                            (allocated_seats[(*allocated_len)].inst)[strlen(inst)] = '\0';
                            strncpy(allocated_seats[(*allocated_len)].branch, branch, strlen(branch));
                            (allocated_seats[(*allocated_len)].branch)[strlen(branch)] = '\0';
                            (*allocated_len)++;

                            update1_mains_cleared(roll, inst, branch, mains_cleared, mains_cleared_len);

                            remove_roll_from_q(course, queues);

                            // Also updating number of available seats in the institutional details
                            for (int j = 0; j < nit_details_len; j++) // (c) nit_details_len - number of nits in the list
                            {
                                if (strcmp(nit_details[j].inst, inst) == 0 && strcmp(nit_details[j].branch, branch) == 0)
                                {
                                    nit_details[j].seats--;
                                }
                            }
                            return 1;
                        }

                        // CASE - 2 - Student already has an allocated seat
                        else
                        {

                            char alloted_inst[10];
                            char alloted_branch[10];

                            // fetching the already alloted institution and branch

                            for (int i = 0; i < (*allocated_len); i++)
                            {
                                if (allocated_seats[i].roll == queues[course].roll_arr[stu_roll])
                                {
                                    strncpy(alloted_inst, allocated_seats[i].inst, strlen(allocated_seats[i].inst));
                                    (allocated_seats[i].inst)[strlen(allocated_seats[i].inst)] = '\0';
                                    strncpy(alloted_branch, allocated_seats[i].branch, strlen(allocated_seats[i].branch));
                                    (allocated_seats[i].branch)[strlen(allocated_seats[i].branch)] = '\0';

                                    break;
                                }
                            }

                            // Checking if the vacant course is more preferable
                            // But not necessary because the fact that they are in the waiting list implies that what they would've got is a less preferable course

                            int allocated_pref_num = find_pref_number(alloted_inst, alloted_branch, stu_roll, adv_cleared_len, adv_cleared);
                            int vacancy_pref_num = find_pref_number(inst, branch, stu_roll, adv_cleared_len, adv_cleared);

                            if (allocated_pref_num < vacancy_pref_num)
                            {
                                break;
                            }

                            else
                            {
                                // Now modifying the allocated_seats list also

                                for (int alt = 0; alt < (*allocated_len); alt++)
                                {
                                    if (allocated_seats[alt].roll == queues[course].roll_arr[stu_roll])
                                    {

                                        strncpy(allocated_seats[alt].inst, inst, strlen(inst));
                                        (allocated_seats[alt].inst)[strlen(inst)] = '\0';
                                        strncpy(allocated_seats[alt].branch, branch, strlen(branch));
                                        (allocated_seats[alt].branch)[strlen(branch)] = '\0';
                                        break;
                                    }
                                }
                                update1_mains_cleared(roll, inst, branch, mains_cleared, mains_cleared_len);
                                remove_roll_from_q(course, queues);

                                // print_mains_cleared(mains_cleared_len,mains_cleared);

                                // Also decrementing the number of available of the newly alloted course in the iit details
                                for (int j = 0; j < iit_details_len; j++) // i_iits - number of iits in the list
                                {
                                    if (strcmp(iit_details[j].inst, inst) == 0 && strcmp(iit_details[j].branch, branch) == 0)
                                    {
                                        iit_details[j].seats--;
                                    }
                                }

                                // Also incrementing the number of available seats of the newly vacant course in the iit details
                                for (int j = 0; j < iit_details_len; j++) // i_iits - number of iits in the list
                                {
                                    if (strcmp(iit_details[j].inst, alloted_inst) == 0 && strcmp(iit_details[j].branch, alloted_branch) == 0)
                                    {
                                        iit_details[j].seats++;
                                    }
                                }

                                // Onto filling the new vacancy
                                fill_vacancies(alloted_inst, alloted_branch, queues_len, queues,
                                               mains_cleared_len, mains_cleared, adv_cleared_len, adv_cleared,
                                               allocated_len, allocated_seats,
                                               nit_details_len, nit_details, iit_details_len, iit_details);
                                return 1;
                            }
                        }
                    }
                }
            }

            // This point means no one in the waiting list wanted the course
            return 1;
        }
    }
}

int allotment_2(struct mains_cleared_struct mains_cleared[], int sturec, int mains_cleared_len,
                int nit_details_len, struct institution nit_details[],
                int iit_details_len, struct institution iit_details[],
                int(*allocated_len), struct student_allotment_struct allocated_seats[],
                int adv_cleared_len, struct adv_cleared_struct adv_cleared[],
                int queues_len, struct waiting_list queues[])
{

    // Recursion will happen till we check all the students in the mains_cleared list
    if (sturec == (mains_cleared_len))
    {
        return 1;
    }

    int roll = mains_cleared[sturec].roll;

    // * I am accessing the allocated inst and allocated branch stored in the mains_cleared list itself
    if (strlen(mains_cleared[sturec].allocated_inst) == 0 && strlen(mains_cleared[sturec].allocated_branch) == 0)
    {
        for (int pref = 0; pref < mains_cleared[sturec].nit_pref_len; pref++) // nit_pref_len - column storing number of preferences
        {

            char inst[10];
            strncpy(inst, (mains_cleared[sturec].nit_pref)[pref][0], strlen((mains_cleared[sturec].nit_pref)[pref][0]));
            inst[strlen((mains_cleared[sturec].nit_pref)[pref][0])] = '\0';
            char branch[10];
            strncpy(branch, (mains_cleared[sturec].nit_pref)[pref][1], strlen((mains_cleared[sturec].nit_pref)[pref][1]));
            branch[strlen((mains_cleared[sturec].nit_pref)[pref][1])] = '\0';

            // Now iterating through nit institutional details list
            for (int j = 0; j < nit_details_len; j++) // nit_details_len - number of nits in the list
            {
                if (strcmp(nit_details[j].inst, inst) == 0 && strcmp(nit_details[j].branch, branch) == 0)
                {
                    if (nit_details[j].seats != 0)
                    {
                        strncpy(mains_cleared[sturec].allocated_inst, inst, strlen(inst));
                        (mains_cleared[sturec].allocated_inst)[strlen(inst)] = '\0';
                        strncpy(mains_cleared[sturec].allocated_branch, branch, strlen(branch));
                        (mains_cleared[sturec].allocated_branch)[strlen(branch)] = '\0';
                        // Now adding the new allotment to the allocated_seats list

                        allocated_seats[(*allocated_len)].roll = roll;
                        strncpy(allocated_seats[(*allocated_len)].inst, inst, strlen(inst));
                        (allocated_seats[(*allocated_len)].inst)[strlen(inst)] = '\0';
                        strncpy(allocated_seats[(*allocated_len)].branch, branch, strlen(branch));
                        (allocated_seats[(*allocated_len)].branch)[strlen(branch)] = '\0';
                        (*allocated_len)++;

                        //  Also updating number of available seats in the institutional details
                        for (int j = 0; j < nit_details_len; j++)
                        {
                            if (strcmp(nit_details[j].inst, inst) == 0 && strcmp(nit_details[j].branch, branch) == 0)
                            {
                                nit_details[j].seats--;
                            }
                        }

                        // Moving on to the allotment of the next student in the mains_cleared list
                        allotment_2(mains_cleared, sturec + 1, mains_cleared_len, nit_details_len, nit_details, iit_details_len, iit_details,
                                    allocated_len, allocated_seats, adv_cleared_len, adv_cleared, queues_len, queues);
                        return 1;
                    }
                    else
                    {

                        break;
                    }
                }
            }
        }

        // If no seat is allotted to the current student, move on to the next student in the mains_cleared list
        allotment_2(mains_cleared, sturec + 1, mains_cleared_len, nit_details_len, nit_details, iit_details_len, iit_details,
                    allocated_len, allocated_seats, adv_cleared_len, adv_cleared, queues_len, queues);
    }

    else
    {

        char alloted_inst[10];
        strncpy(alloted_inst, (mains_cleared[sturec].allocated_inst), strlen((mains_cleared[sturec].allocated_inst)));
        alloted_inst[strlen((mains_cleared[sturec].allocated_inst))] = '\0';
        char alloted_branch[10];
        strncpy(alloted_branch, (mains_cleared[sturec].allocated_branch), strlen((mains_cleared[sturec].allocated_branch)));
        alloted_branch[strlen((mains_cleared[sturec].allocated_branch))] = '\0';

        // To check if the available nit is preferred to the alloted iit

        // Index of alloted iit in overall preference list

        int allocated_pref_num = find_pref_number(alloted_inst, alloted_branch, roll, adv_cleared_len, adv_cleared);

        // Index of available nit in overall prefrence list
        for (int pref = 0; pref < mains_cleared[sturec].nit_pref_len; pref++) // nit_pref_len - column storing number of preferences
        {

            char inst[10] = {'\0'};
            strncpy(inst, (mains_cleared[sturec].nit_pref)[pref][0], strlen((mains_cleared[sturec].nit_pref)[pref][0]));
            (inst)[strlen((mains_cleared[sturec].nit_pref)[pref][0])] = '\0';

            char branch[10] = {'\0'};
            strncpy(branch, (mains_cleared[sturec].nit_pref)[pref][1], strlen((mains_cleared[sturec].nit_pref)[pref][1]));
            (branch)[strlen((mains_cleared[sturec].nit_pref)[pref][1])] = '\0';

            // Now iterating through nit institutional details list

            for (int j = 0; j < nit_details_len; j++) // nit_details_len - number of nits in the list
            {

                if (strcmp(nit_details[j].inst, inst) == 0 && strcmp(nit_details[j].branch, branch) == 0)
                {
                    // Finding the first nit course with seats available

                    if (nit_details[j].seats != 0)

                    {

                        int nit_pref_num = find_pref_number(inst, branch, roll, adv_cleared_len, adv_cleared);

                        // CASE - 1 - The currently allocated course is preferred to the nit course
                        if (nit_pref_num > allocated_pref_num)
                        {
                            allotment_2(mains_cleared, sturec + 1, mains_cleared_len, nit_details_len, nit_details, iit_details_len, iit_details,
                                        allocated_len, allocated_seats, adv_cleared_len, adv_cleared, queues_len, queues);
                            return 1;
                        }

                        // CASE - 2 - The nit course is preferred to the currently allocated course
                        else
                        {

                            // Now modifying the allocated_seats list also
                            for (int alt = 0; alt < (*allocated_len); alt++)
                            {
                                if (allocated_seats[alt].roll == roll)
                                {
                                    strncpy(allocated_seats[alt].inst, inst, strlen(inst));
                                    (allocated_seats[alt].inst)[strlen(inst)] = '\0';
                                    strncpy(allocated_seats[alt].branch, branch, strlen(branch));
                                    (allocated_seats[alt].branch)[strlen(branch)] = '\0';

                                    update1_mains_cleared(roll, inst, branch, mains_cleared, mains_cleared_len);
                                    break;
                                }
                            }

                            // Also decrementing the number of available seats in the nit details
                            for (int j = 0; j < nit_details_len; j++)
                            {
                                if (strcmp(nit_details[j].inst, inst) == 0 && strcmp(nit_details[j].branch, branch) == 0)
                                {
                                    nit_details[j].seats--;
                                }
                            }

                            // Also incrementing the number of available seats in the iit details
                            for (int j = 0; j < iit_details_len; j++) // iit_details_len - number of iits in the list
                            {
                                if (strcmp(iit_details[j].inst, alloted_inst) == 0 && strcmp(iit_details[j].branch, alloted_branch) == 0)
                                {
                                    iit_details[j].seats++;
                                }
                            }

                            // FILL VACANCIES
                            fill_vacancies(alloted_inst, alloted_branch, queues_len, queues,
                                           mains_cleared_len, mains_cleared, adv_cleared_len, adv_cleared,
                                           allocated_len, allocated_seats,
                                           nit_details_len, nit_details, iit_details_len, iit_details);
                            allotment_2(mains_cleared, sturec + 1, mains_cleared_len, nit_details_len, nit_details, iit_details_len, iit_details,
                                        allocated_len, allocated_seats, adv_cleared_len, adv_cleared, queues_len, queues);
                            return 1;
                        }
                    }
                }
            }
        }
        allotment_2(mains_cleared, sturec + 1, mains_cleared_len, nit_details_len, nit_details, iit_details_len, iit_details,
                    allocated_len, allocated_seats, adv_cleared_len, adv_cleared, queues_len, queues);
    }
}

int mystrcmp(char s1[], char s2[])
{
    for (int index = 0; index < strlen(s1); index++)
    {
        if (s1[index] != s2[index])
        {
            return 0;
        }
    }
    return 1;
}

// fn to check allocated seats
void display_allocated_seats(int allocated_len, struct student_allotment_struct allocated_seats[])
{
    printf("\n");
    printf("\nAllocated Seats:");
    for (int _ = 0; _ < allocated_len; _++)
    {
        char *inst = (allocated_seats + _)->inst;
        char *branch = (allocated_seats + _)->branch;
        {
            printf("\n%d-%s %s", (allocated_seats + _)->roll, inst, branch);
        }
    }
}

// test functions to print split prefs
void print_iit_pref(int adv_cleared_len, struct adv_cleared_struct adv_cleared[])
{
    printf("\noverall prefs and iit prefs:\n");
    for (int _ = 0; _ < adv_cleared_len; _++)
    {
        printf("roll:%d\n", (adv_cleared + _)->roll);
        display_preferences((adv_cleared + _)->pref_len, (adv_cleared + _)->pref);
        display_preferences((adv_cleared + _)->iit_pref_len, (adv_cleared + _)->iit_pref);
    }
}
void print_nit_pref(int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{
    printf("\nnit prefs:\n");
    for (int _ = 0; _ < mains_cleared_len; _++)
    {
        printf("roll:%d\n", (mains_cleared + _)->roll);
        display_preferences((mains_cleared + _)->nit_pref_len, (mains_cleared + _)->nit_pref);
    }
}

// fns to get index of required roll number row
int getj_adv(int roll, int adv_cleared_len, struct adv_cleared_struct adv_cleared[])
{
    for (int j = 0; j < adv_cleared_len; j++)
    {
        if ((adv_cleared + j)->roll == roll)
        {
            return j;
        }
    }
}
int getj_mains(int roll, int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{
    for (int j = 0; j < mains_cleared_len; j++)
    {
        if ((mains_cleared + j)->roll == roll)
        {
            return j;
        }
    }
}

void start_allocation(int adv_cleared_len, struct adv_cleared_struct adv_cleared[],
                      int mains_cleared_len, struct mains_cleared_struct mains_cleared[],
                      int iit_details_len, struct institution iit_details[],
                      int nit_details_len, struct institution nit_details[],
                      int(*allocated_len), struct student_allotment_struct allocated_seats[])
{
    for (int i = 0; i < adv_cleared_len; i++)
    {
        for (int j = 0; j < (adv_cleared + i)->pref_len; j++)
        {
            char *inst = ((adv_cleared + i)->pref)[j][0];
            char *branch = ((adv_cleared + i)->pref)[j][1];
            if (inst[0] == 'I')
            {
                strncpy(((adv_cleared + i)->iit_pref)[(adv_cleared + i)->iit_pref_len][0], inst, strlen(inst));
                ((adv_cleared + i)->iit_pref)[(adv_cleared + i)->iit_pref_len][0][strlen(inst)] = '\0';
                strncpy(((adv_cleared + i)->iit_pref)[(adv_cleared + i)->iit_pref_len][1], branch, strlen(branch));
                ((adv_cleared + i)->iit_pref)[(adv_cleared + i)->iit_pref_len][1][strlen(branch)] = '\0';
                ((adv_cleared + i)->iit_pref_len)++;
            }
            else
            {
                int row = getj_mains((adv_cleared + i)->roll, mains_cleared_len, mains_cleared);

                strncpy(((mains_cleared + row)->nit_pref)[(mains_cleared + row)->nit_pref_len][0], inst, strlen(inst));
                ((mains_cleared + row)->nit_pref)[(mains_cleared + row)->nit_pref_len][0][strlen(inst)] = '\0';
                strncpy(((mains_cleared + row)->nit_pref)[(mains_cleared + row)->nit_pref_len][1], branch, strlen(branch));
                ((mains_cleared + row)->nit_pref)[(mains_cleared + row)->nit_pref_len][1][strlen(branch)] = '\0';
                ((mains_cleared + row)->nit_pref_len)++;
            }
        }
    }

    struct waiting_list queues[100];
    int queues_len = 0;
    for (int i = 0; i < adv_cleared_len; i++)
    {
        int roll = (adv_cleared + i)->roll;
        for (int k = 0; k < (adv_cleared + i)->iit_pref_len; k++)
        {
            char *inst = ((adv_cleared + i)->iit_pref)[k][0];
            char *branch = ((adv_cleared + i)->iit_pref)[k][1];

            // CODE FOR CHECKING IF SEATS ARE LEFT IN PREF IIT, IF YES ALLOCATE
            bool allocated = false;
            for (int j = 0; j < iit_details_len; j++)
            {

                if ((iit_details + j)->inst[4] == inst[4])
                {

                    if (mystrcmp((iit_details + j)->branch, branch))
                    {

                        if ((iit_details + j)->seats != 0)
                        {

                            (allocated_seats + (*allocated_len))->roll = roll;
                            strncpy((allocated_seats + (*allocated_len))->inst, inst, strlen(inst));
                            (allocated_seats + (*allocated_len))->inst[strlen(inst)] = '\0';
                            strncpy((allocated_seats + (*allocated_len))->branch, branch, strlen(branch));
                            (allocated_seats + (*allocated_len))->branch[strlen(branch)] = '\0';
                            (*allocated_len)++;
                            ((iit_details + j)->seats) -= 1;
                            allocated = true;

                            break; // breaking iteration thru inst_details
                        }
                        else
                        {

                            break; // breaking iteration thru inst_details
                            // because inst,branch are found but no seats
                            // so no need to iterate more
                        }
                    }
                }
            }

            if (allocated)
            {
                break; // breaking iteration thru pref list
                // no need to go to queues if student is allocated
            }
            else if (!allocated)
            {
                // CODE FOR ADDING INTO QUEUES
                bool found = false;

                for (int j = 0; j < queues_len; j++)
                {
                    struct waiting_list *q = (queues + j);

                    if ((q)->inst[4] == inst[4])
                    {
                        if (mystrcmp((q)->branch, branch))
                        {
                            q->roll_arr[q->roll_len] = roll; // roll no of student
                            (q->roll_len)++;
                            found = true;

                            break;
                        }
                    }
                }
                if (!found)
                {

                    strncpy((queues + queues_len)->inst, inst, strlen(inst));
                    (queues + queues_len)->inst[strlen(inst)] = '\0';
                    strncpy((queues + queues_len)->branch, branch, strlen(branch));
                    (queues + queues_len)->branch[strlen(branch)] = '\0';

                    (queues + queues_len)->roll_arr[0] = roll;
                    ((queues + queues_len)->roll_len) = 1;
                    queues_len++;
                }
            }
        }
    }

    update_mains_cleared((*allocated_len), allocated_seats, mains_cleared_len, mains_cleared);

    allotment_2(mains_cleared, 0, mains_cleared_len, nit_details_len, nit_details, iit_details_len, iit_details,
                allocated_len, allocated_seats, adv_cleared_len, adv_cleared, queues_len, queues);

    display_allocated_seats((*allocated_len), allocated_seats);
    printf("\n");
}
