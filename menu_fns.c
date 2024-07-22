#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_fns.c" //calls login.c




// TEST FUNCTION
// to print struct institution
void print_struct(int details_len, struct institution inst_details[])
{
    printf("\n\nelements of inst array:");
    for (int i = 0; i < details_len; i++)
    {
        printf("\n%s", (inst_details + i)->inst);
        printf(" %s", (inst_details + i)->branch);
        printf(" %d", (inst_details + i)->seats);
        printf(" %d", (inst_details + i)->fees);
        printf("\n\n");
    }
}

// stores option in preference list
void save_to_saved(int *len, char saved[][2][10], char *inst, char *branch)
{
    strncpy(saved[*len][0], inst, strlen(inst) + 1);
    strncpy(saved[*len][1], branch, strlen(branch) + 1);
    (*len)++;
}

//fns to create sample data...not reqd for main project
void set_values_adv_cleared(int* len,struct adv_cleared_struct adv_cleared[],int roll)
{
    (adv_cleared+(*len))->roll=roll;
    (adv_cleared+(*len))->adv_rank=(*len)+1;
    (*len)++;

}
void set_values_mains_cleared(int* len,struct mains_cleared_struct mains_cleared[(*len)],int roll)
{
    (mains_cleared+(*len))->roll=roll;
    (mains_cleared+(*len))->mains_rank=(*len)+1;
    (*len)++;
}


// displays inst data(inst,branch) from struct institution
void display_options(int details_len, struct institution inst_details[details_len], int saved_len, char saved[100][2][10])
{
    for (int _ = 0; _ < details_len; _++)
    {
        char *inst = (inst_details + _)->inst;
        char *branch = (inst_details + _)->branch;
        bool not_saved = true;
        for (int row = 0; row < saved_len; row++)
        {
            if (strcmp(saved[row][0], inst) == 0 && strcmp(saved[row][1], branch) == 0)
            {
                not_saved = false;
                break;
            }
        }
        if (not_saved)
        {
            printf("\n%d-%s %s", _ + 1, inst, branch);
        }
    }
}

// displays preference list
void display_preferences(int saved_len, char saved[][2][10])
{
    for (int _ = 0; _ < saved_len; _++)
    {
        char *inst = saved[_][0];
        char *branch = saved[_][1];
        printf("\n%d-%s %s", _ + 1, inst, branch);
    }
}

//gets the option by the number which user entered
void get_option(int num, int details_len, struct institution inst_details[50], int saved_len, char saved[100][2][10])
{
    for (int _ = 0; _ < details_len; _++)
    {
        char *inst = (inst_details + _)->inst;
        char *branch = (inst_details + _)->branch;
        bool not_saved = true;
        for (int row = 0; row < saved_len; row++)
        {
            if (strcmp(saved[row][0], inst) == 0 && strcmp(saved[row][1], branch) == 0)
            {
                not_saved = false;
                break;
            }
        }
        if (not_saved && num == (_ + 1))
        {
            save_to_saved(&saved_len, saved, inst, branch);
        }
    }
}

// deletes preference from pref list
void del_preference(int num, int *len, char saved[100][2][10])
{
    for (int _ = num - 1; _ < (*len) - 1; _++)
    {
        char *inst = saved[_ + 1][0];
        char *branch = saved[_ + 1][1];
        strncpy(saved[_][0], inst, strlen(inst) + 1);
        strncpy(saved[_][1], branch, strlen(branch) + 1);
    }
    (*len)--;
}

void switch_preferences(int pref_1, int pref_2, char saved[][2][10])
{
    char temp_inst[10];
    char temp_branch[10];

    strncpy(temp_inst, saved[(pref_1)-1][0], strlen(saved[(pref_1)-1][0]) + 1);
    strncpy(temp_branch, saved[(pref_1)-1][1], strlen(saved[(pref_1)-1][1]) + 1);

    strncpy(saved[(pref_1)-1][0], saved[(pref_2)-1][0], strlen(saved[(pref_2)-1][0]) + 1);
    strncpy(saved[(pref_1)-1][1], saved[(pref_2)-1][1], strlen(saved[(pref_2)-1][1]) + 1);

    strncpy(saved[(pref_2)-1][0], temp_inst, strlen(temp_inst) + 1);
    strncpy(saved[(pref_2)-1][1], temp_branch, strlen(temp_branch) + 1);
}