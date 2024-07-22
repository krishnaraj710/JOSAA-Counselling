#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "algo_fns.c" //calls menu_fns.c //calls file_fns.c //calls login.c

int main()
{
    // READ ALL FILES

    // reading start_allocation status
    FILE *fp = fopen("allocation_started.txt", "r");
    int allocation_started;
    fscanf(fp, "%d ", &allocation_started);
    fclose(fp);

    // sample data
    // STUDENTS_ONLY FILE TO STRUCT(for checking student login and maybe displaying details after student logins)
    struct Student students_only[100];
    int students_only_len = 0;
    read_students_only(&students_only_len, students_only);

    // ADV AND MAINS RANK LISTS
    int adv_cleared_len = 0;
    struct adv_cleared_struct adv_cleared[100];
    read_adv_cleared(&adv_cleared_len, adv_cleared);

    int mains_cleared_len = 0;
    struct mains_cleared_struct mains_cleared[100];
    read_mains_cleared(&mains_cleared_len, mains_cleared);

    struct student_allotment_struct allocated_seats[100];
    int allocated_len = 0;

    // NIT AND IIT INST DETAILS
    int iit_details_len = 0, nit_details_len = 0;
    // to get lengths of inst details
    FILE *file1 = fopen("IIT_Details.csv", "r");
    char line1[1000];
    while (fgets(line1, sizeof(line1), file1))
    {
        iit_details_len += 1;
    }
    fclose(file1);
    file1 = fopen("NIT_Details.csv", "r");
    while (fgets(line1, sizeof(line1), file1))
    {
        nit_details_len += 1;
    }
    fclose(file1);

    struct institution iit_details[iit_details_len], nit_details[nit_details_len];

    read_inst_details("IIT_Details.csv", iit_details_len, iit_details);
    //print_struct(iit_details_len, iit_details);
    read_inst_details("NIT_Details.csv", nit_details_len, nit_details);
    //print_struct(nit_details_len, nit_details);


    int admin_or_student = 1;
    while (admin_or_student < 3)
    {
        printf("\nMENU:\n1-Admin\n2-Student\n3-Exit");
        printf("\n\nEnter choice:");
        scanf("%d", &admin_or_student);
        if (admin_or_student == 1)
        {
            if (admin_login())
            {
                printf("\n\n\t\tLogged in!");
                if (allocation_started == 0)
                {
                    int choice = 1;
                    while ((choice > 0) && (choice < 3))
                    {
                        printf("\nMENU:\n1-Add institutional details\n2-Start Allocation\n3-Log out as Admin");
                        printf("\n\nEnter choice:");
                        scanf("%d", &choice);
                        if (choice == 1)
                        {
                            int i = 2;
                            while (i < 3)
                            {
                                printf("\n\nInstitutions:\n");
                                printf("1-IITs\n");
                                printf("2-NITs\n");
                                printf("3-Done\n\n");
                                printf("Enter your choice: ");
                                scanf("%d", &i);

                                switch (i)
                                {

                                case 1:
                                    add_inst_details(&iit_details_len, "IIT", iit_details);
                                    printf("\n\n\t\tData Added Successfully\n");
                                    break;

                                case 2:
                                    add_inst_details(&nit_details_len, "NIT", nit_details);
                                    printf("\n\n\t\tData Added Successfully\n");
                                    break;
                                }
                            }
                        }
                        else if (choice == 2)
                        {
                            int allocate = 0;
                            printf("Are you sure you want to start allocation? 1-Yes 2-No:");
                            scanf("%d", &allocate);
                            if (allocate == 1)
                            {
                                printf("\nAllocating....");
                                allocation_started = 1;
                                start_allocation(adv_cleared_len, adv_cleared,
                                                 mains_cleared_len, mains_cleared,
                                                 iit_details_len, iit_details,
                                                 nit_details_len, nit_details,
                                                 &allocated_len, allocated_seats);

                                printf("\n\n\t\tINSTITUTE WISE ALLOTMENT:");
                                display_inst_wise_allotment(mains_cleared_len, mains_cleared);

                                printf("\n\nEnter 0 to logout:");
                                scanf("%d", &choice);
                            }
                        }
                    }
                }
                else if (allocation_started == 1)
                {
                    printf("\n\n\t\tINSTITUTE WISE ALLOTMENT:");
                    display_inst_wise_allotment(mains_cleared_len, mains_cleared);
                    printf("\n\nEnter 0 to logout:");
                    scanf("%d", &admin_or_student);
                }
                printf("\n\n\t\tLogged out!\n");
            }
            else
            {
                printf("\n\n\t\tLogin failed. Invalid password.\n");
            }
        }
        else if (admin_or_student == 2)
        {
            int reqd_roll_no = 6; // adv=4 mains=6
            // printf("Enter roll:");                                              // temp code
            // scanf("%d", &reqd_roll_no);
            if (student_login(&reqd_roll_no, students_only_len, students_only)) // student_login(&reqd_roll_no,??))students_only struct (to be implemented)
            {
                printf("\n\n\t\tLogged in!\n");
                // printf("allocation started? %d",allocation_started);
                //  display students_only details??
                if (allocation_started == 0)
                {
                    if (cleared_adv(reqd_roll_no, adv_cleared_len, adv_cleared))

                    {
                        int j = getj_adv(reqd_roll_no, adv_cleared_len, adv_cleared);
                        // printf("Index of roll %d=%d",reqd_roll_no,j);
                        // print_iit_pref(adv_cleared_len,adv_cleared);

                        int choice = 0, i;
                        while (choice < 6)
                        {
                            printf("\n\n");
                            printf("MENU:\n");
                            printf("(1)\tView available options\n");
                            printf("(2)\tAdd option\n");
                            printf("(3)\tSwitch options\n");
                            printf("(4)\tView selected options\n");
                            printf("(5)\tDelete option\n");
                            printf("(6)\tLog out as Student\n\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            printf("\n\n");

                            if (choice == 1)
                            {
                                i = 1;
                                while (i < 3)
                                {
                                    printf("\nInstitutions:\n");
                                    printf("1-IITs\n");
                                    printf("2-NITs\n");
                                    printf("3-Go back\n\n");
                                    printf("Enter your choice: ");
                                    scanf("%d", &i);
                                    printf("\n");

                                    switch (i)
                                    {

                                    case 1:
                                        printf("IITs:");
                                        display_options(iit_details_len, iit_details, (adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                        break;

                                    case 2:
                                        printf("NITs:");
                                        display_options(nit_details_len, nit_details, (adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                        break;
                                    }
                                }
                            }
                            else if (choice == 2)
                            {
                                i = 1;
                                while (i < 3)
                                {
                                    printf("\nInstitutions:\n");
                                    printf("1-IITs\n");
                                    printf("2-NITs\n");
                                    printf("3-Go back\n\n");
                                    printf("Enter your choice: ");
                                    scanf("%d", &i);
                                    printf("\n");

                                    int num;

                                    switch (i)
                                    {
                                    case 1:
                                        printf("IITs:");
                                        display_options(iit_details_len, iit_details, (adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                        printf("\n\nEnter number to add:");
                                        scanf("%d", &num);
                                        get_option(num, iit_details_len, iit_details, (adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                        ((adv_cleared + j)->pref_len) += 1;
                                        printf("\n\n\t\tAdded Successfully!\n");
                                        break;

                                    case 2:
                                        printf("NITs:");
                                        display_options(nit_details_len, nit_details, (adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                        printf("\n\nEnter number to add:");
                                        scanf("%d", &num);
                                        get_option(num, nit_details_len, nit_details, (adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                        ((adv_cleared + j)->pref_len) += 1;
                                        printf("\n\n\t\tAdded Successfully!\n");
                                        break;
                                    }
                                }
                            }

                            else if (choice == 3)
                            {

                                printf("\nYour preference list:");
                                display_preferences((adv_cleared + j)->pref_len, (adv_cleared + j)->pref);

                                printf("\n\nEnter preference numbers to be switched : ");
                                int pref_1, pref_2;
                                scanf("%d %d", &pref_1, &pref_2);
                                switch_preferences(pref_1, pref_2, (adv_cleared + j)->pref);
                                printf("\n\n\t\tSwitched Successfully!\n");
                            }

                            else if (choice == 4)
                            {

                                printf("\nYour preference list:");
                                display_preferences((adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                            }
                            else if (choice == 5)
                            {

                                int num;
                                display_preferences((adv_cleared + j)->pref_len, (adv_cleared + j)->pref);
                                printf("\n\nEnter number to delete:");
                                scanf("%d", &num);
                                del_preference(num, &((adv_cleared + j)->pref_len), (adv_cleared + j)->pref);
                                printf("\n\n\t\tDeleted Successfully!\n");
                            }
                        }
                        printf("\n\n\t\tLogged out!");
                    }
                    else
                    {
                        int j = getj_mains(reqd_roll_no, mains_cleared_len, mains_cleared);

                        int choice = 0, i;
                        while (choice < 6)
                        {
                            printf("\n\n");
                            printf("MENU:\n");
                            printf("(1)\tView available options\n");
                            printf("(2)\tAdd option\n");
                            printf("(3)\tSwitch options\n");
                            printf("(4)\tView selected options\n");
                            printf("(5)\tDelete option\n");
                            printf("(6)\tLog out as Student\n\n");
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            printf("\n\n");

                            if (choice == 1)
                            {

                                printf("NITs:");
                                display_options(nit_details_len, nit_details, (mains_cleared + j)->nit_pref_len, (mains_cleared + j)->nit_pref);
                            }

                            else if (choice == 2)
                            {

                                int num;
                                printf("NITs:");
                                display_options(nit_details_len, nit_details, (mains_cleared + j)->nit_pref_len, (mains_cleared + j)->nit_pref);
                                printf("\n\nEnter number to add:");
                                scanf("%d", &num);
                                get_option(num, nit_details_len, nit_details, (mains_cleared + j)->nit_pref_len, (mains_cleared + j)->nit_pref);
                                (mains_cleared + j)->nit_pref_len += 1;
                                printf("\n\n\t\tAdded Successfully!\n");
                            }

                            else if (choice == 3)
                            {

                                printf("\nYour preference list:");
                                display_preferences((mains_cleared + j)->nit_pref_len, (mains_cleared + j)->nit_pref);

                                printf("\n\nEnter preference numbers to be switched : ");
                                int pref_1, pref_2;
                                scanf("%d %d", &pref_1, &pref_2);
                                switch_preferences(pref_1, pref_2, (mains_cleared + j)->nit_pref);
                                printf("\n\n\t\tSwitched Successfully!\n");
                            }

                            else if (choice == 4)
                            {
                                printf("\nYour preference list:");
                                display_preferences((mains_cleared + j)->nit_pref_len, (mains_cleared + j)->nit_pref);
                            }
                            else if (choice == 5)
                            {
                                int num;
                                display_preferences((mains_cleared + j)->nit_pref_len, (mains_cleared + j)->nit_pref);
                                printf("\n\nEnter number to delete:");
                                scanf("%d", &num);
                                del_preference(num, &((mains_cleared + j)->nit_pref_len), (mains_cleared + j)->nit_pref);
                                printf("\n\n\t\tDeleted Successfully!\n");
                            }
                        }
                        printf("\n\n\t\tLogged out!");
                    } // closing if for cleared_adv or not
                }     // closing if for checking if allocation_started=0
                else if (allocation_started == 1)
                {
                    if(display_allocated_seat(reqd_roll_no, mains_cleared_len, mains_cleared))
                    {
                    get_fees(reqd_roll_no, students_only_len, students_only,
                             mains_cleared_len, mains_cleared, iit_details_len, iit_details,
                             nit_details_len, nit_details);
                    }

                    printf("\n\nEnter 0 to logout:");
                    scanf("%d", &admin_or_student);
                }
            } // closing if for student login
            else
            {
                printf("\n\n\t\tLogin failed. Invalid username or password.\n");
            }
        } // closing else if for whether admin_or_student=2

    } // closing while for menu:admin,student,exit
    //printf("STORING ALL DATA IN FILES\nEXITING...");

    // storing start_allocation status
    fp = fopen("allocation_started.txt", "w");
    // printf("allocation_started=%d",allocation_started);
    fprintf(fp, "%d ", allocation_started);
    fclose(fp);

    // storing adv_cleared
    store_adv_cleared(adv_cleared_len, adv_cleared);
    // storing mains_cleared (can have allocated course or not)
    store_mains_cleared(mains_cleared_len, mains_cleared);

    //storing inst details
    //print_inst_details(iit_details_len,iit_details);
    store_inst_details("IIT_Details.csv",iit_details_len,iit_details);
    store_inst_details("NIT_Details.csv",nit_details_len,nit_details);


    return 0;
}
