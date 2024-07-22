#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.c"

#define MAX_LINE_LENGTH 1000

// TEST FNS
// fn to print adv_cleared_struct
void print_adv_cleared(int adv_cleared_len, struct adv_cleared_struct adv_cleared[])
{
  for (int i = 0; i < adv_cleared_len; i++)
  {
    printf("adv_cleared_struct %d:\n", i + 1);
    printf("Advanced adv_rank: %d\n", adv_cleared[i].adv_rank);
    printf("Roll Number: %d\n", adv_cleared[i].roll);
    printf("Preference Length: %d\n", adv_cleared[i].pref_len);
    printf("pref: ");
    for (int j = 0; j < adv_cleared[i].pref_len; j++)
    {
      printf("%s %s, ", adv_cleared[i].pref[j][0], adv_cleared[i].pref[j][1]);
    }
    printf("\n\n");
  }
}
void print_students_only(int students_only_len, struct Student students_only[])
{
  // Display the student details
  for (int i = 0; i < students_only_len; i++)
  {
    printf("Student %d:\n", i + 1);
    printf("First Name: %s\n", students_only[i].firstName);
    printf("Last Name: %s\n", students_only[i].lastName);
    printf("Roll Number: %d\n", students_only[i].rollNumber);
    printf("Password: %s\n", students_only[i].password);
    printf("Mains Rank: %d\n", students_only[i].mainsRank);
    printf("Advanced Rank: %d\n", students_only[i].advancedRank);
    printf("Email: %s\n", students_only[i].email);
    printf("DOB: %s\n", students_only[i].dob);
    printf("\n");
  }
}
void print_mains_cleared(int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{
  for (int i = 0; i < mains_cleared_len; i++)
  {
    printf("mains_cleared_struct %d:\n", i + 1);
    printf("Mains Rank: %d\n", mains_cleared[i].mains_rank);
    printf("Roll Number: %d\n", mains_cleared[i].roll);
    printf("Preference Length: %d\n", mains_cleared[i].nit_pref_len);
    printf("Preferences: ");
    for (int j = 0; j < mains_cleared[i].nit_pref_len; j++)
    {
      printf("%s %s,", mains_cleared[i].nit_pref[j][0],
             mains_cleared[i].nit_pref[j][1]);
    }
    printf("\nallocated inst,branch %s,%s\n", mains_cleared[i].allocated_inst, mains_cleared[i].allocated_branch);
    printf("\n\n");
  }
}

// reading students details
void read_students_only(int *students_only_len, struct Student students_only[])
{

  // Open the CSV file
  FILE *file = fopen("students_only1.csv", "r");
  if (file == NULL)
  {
    printf("Failed to open the file students_only.csv.\n");
  }
  char line[200];
  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\n")] = '\0';
    char *token;
    token = strtok(line, ",");
    strcpy(students_only[*students_only_len].firstName, token);
    token = strtok(NULL, ",");
    strcpy(students_only[*students_only_len].lastName, token);
    token = strtok(NULL, ",");
    students_only[*students_only_len].rollNumber = atoi(token);
    token = strtok(NULL, ",");
    strcpy(students_only[*students_only_len].password, token);
    token = strtok(NULL, ",");
    students_only[*students_only_len].mainsRank = atoi(token);
    token = strtok(NULL, ",");
    students_only[*students_only_len].advancedRank = atoi(token);
    token = strtok(NULL, ",");
    strcpy(students_only[*students_only_len].email, token);
    token = strtok(NULL, ",");
    strcpy(students_only[*students_only_len].dob, token);
    token = strtok(NULL, ",");
    students_only[*students_only_len].income = atoi(token);

    (*students_only_len)++;
  }

  fclose(file);
}

// reading full inst details from inst details excel files
void read_inst_details(const char *filename, int details_len, struct institution inst_details[])
{
  FILE *file = fopen(filename, "r"); // Open the file in read mode
  /*if (file == NULL)
  {
    printf("Failed to open %s\n", filename);
    return;
  }*/

  char line[256];
  int count = 0;

  while (fgets(line, sizeof(line), file))
  {
    // Split the line into fields using the comma as the delimiter
    char *token;
    char *inst;
    char *branch;
    int seats;
    int fees;

    token = strtok(line, ",");
    if (token != NULL)
    {
      inst = token;

      token = strtok(NULL, ",");
      if (token != NULL)
      {
        branch = token;

        token = strtok(NULL, ",");
        if (token != NULL)
        {
          seats = atoi(token);

          token = strtok(NULL, ",");
          if (token != NULL)
          {
            fees = atoi(token);

            // Store the data into the structure
            if (count < details_len)
            {
              strncpy(inst_details[count].inst, inst, sizeof(inst_details[count].inst) - 1);
              inst_details[count].inst[sizeof(inst_details[count].inst) - 1] = '\0';
              strncpy(inst_details[count].branch, branch, sizeof(inst_details[count].branch) - 1);
              inst_details[count].branch[sizeof(inst_details[count].branch) - 1] = '\0';
              inst_details[count].seats = seats;
              inst_details[count].fees = fees;
              count++;
            }
          }
        }
      }
    }
  }

  fclose(file); // Close the file
}

void store_inst_details(char filename[], int inst_details_len, struct institution inst_details[])
{
  FILE *file;

  // Open the CSV file for writing
  file = fopen(filename, "w");
  if (file == NULL)
  {
    printf("Unable to open file %s\n", filename);
  }

  for (int i = 0; i < inst_details_len; i++)
  {
    char row[MAX_LINE_LENGTH];
    snprintf(row, sizeof(row), "%s,%s,%d,%d\n", inst_details[i].inst, inst_details[i].branch, inst_details[i].seats, inst_details[i].fees);
    fputs(row, file);
  }
}

// reading adv_cleared file
void read_adv_cleared(int *adv_cleared_len, struct adv_cleared_struct adv_cleared[])
{
  FILE *file = fopen("adv_cleared.csv", "r");
  if (file == NULL)
  {
    printf("Failed to open %s\n", "adv_cleared.csv");
    return;
  }

  // To read and store the preference list for updation
  char line[10000];

  while (fgets(line, sizeof(line), file))
  {

    // Split the line into fields using the comma as the delimiter
    char *token;
    int roll;
    char *pref_string;
    int count = 0;

    token = strtok(line, ",");
    if (token != NULL)
    {
      adv_cleared[*adv_cleared_len].adv_rank = atoi(token);
      token = strtok(NULL, ",");
      adv_cleared[*adv_cleared_len].roll = atoi(token);

      token = strtok(NULL, ",");
      if (token != NULL)
      {
        pref_string = token;
        int i = 0, j = 0;
        // made change
        while (i < strlen(pref_string) - 1)
        {
          int j = 0;
          while (isspace(pref_string[i]) == 0)
          {
            adv_cleared[*adv_cleared_len].pref[count][0][j] = pref_string[i];
            j++;
            i++;
          }
          adv_cleared[*adv_cleared_len].pref[count][0][j] = '\0';
          i++;

          j = 0;
          while (pref_string[i] != '|')
          {
            adv_cleared[*adv_cleared_len].pref[count][1][j] = pref_string[i];
            j++;
            i++;
          }
          adv_cleared[*adv_cleared_len].pref[count][1][j] = '\0';
          i++;
          count++;
        }
        adv_cleared[*adv_cleared_len].pref_len = count;
      }
    }
    (*adv_cleared_len)++;
  }

  fclose(file);
}

// reading mains_cleared file
void read_mains_cleared(int *mains_cleared_len,
                        struct mains_cleared_struct mains_cleared[])
{

  // Open the CSV file
  FILE *file = fopen("mains_cleared.csv", "r");
  if (file == NULL)
  {
    printf("Failed to open the file.\n");
  }

  char line[250];
  while (fgets(line, sizeof(line), file))
  {

    // Split the line into fields using the comma as the delimiter
    char *token;
    int roll;
    char *pref_string;
    int count = 0;

    token = strtok(line, ",");
    if (token != NULL)
    {
      mains_cleared[*mains_cleared_len].mains_rank = atoi(token);
      token = strtok(NULL, ",");
      mains_cleared[*mains_cleared_len].roll = atoi(token);

      token = strtok(NULL, ",");
      if (token != NULL)
      {
        pref_string = token;
        int i = 0, j = 0;
        // made change
        while (i < strlen(pref_string) - 1)
        {
          int j = 0;
          while (isspace(pref_string[i]) == 0)
          {
            mains_cleared[*mains_cleared_len].nit_pref[count][0][j] =
                pref_string[i];
            j++;
            i++;
          }
          mains_cleared[*mains_cleared_len].nit_pref[count][0][j] = '\0';
          i++;

          j = 0;
          while (pref_string[i] != '|')
          {
            mains_cleared[*mains_cleared_len].nit_pref[count][1][j] = pref_string[i];
            j++;
            i++;
          }
          mains_cleared[*mains_cleared_len].nit_pref[count][1][j] = '\0';
          i++;
          count++;
        }
        mains_cleared[*mains_cleared_len].nit_pref_len = count;

        token = strtok(NULL, ",");
        if (token != NULL)
        {
          strncpy(mains_cleared[*mains_cleared_len].allocated_inst, token, strlen(token));
          (mains_cleared[*mains_cleared_len].allocated_inst)[strlen(token)] = '\0';
          token = strtok(NULL, ",");
          if (token != NULL)
          {
            strncpy(mains_cleared[*mains_cleared_len].allocated_branch, token, strlen(token));
            (mains_cleared[*mains_cleared_len].allocated_branch)[strlen(token)] = '\0';
          }
          else
          {
            strncpy((mains_cleared[*mains_cleared_len].allocated_branch), "", 1);
          }
        }
        else
        {
          strncpy((mains_cleared[*mains_cleared_len].allocated_inst), "", 1);
        }
      }
    }

    (*mains_cleared_len)++;
  }

  fclose(file);
}

// storing prefs
int store_adv_cleared(int adv_cleared_len, struct adv_cleared_struct adv_cleared[])
{

  FILE *file;

  // Open the CSV file for writing
  file = fopen("adv_cleared.csv", "w");
  if (file == NULL)
  {
    printf("Unable to open file %s\n", "adv_cleared.csv");
  }

  for (int i = 0; i < adv_cleared_len; i++)
  {
    char line[MAX_LINE_LENGTH];
    char row[MAX_LINE_LENGTH];
    memset(row, '\0', strlen(row));
    memset(line, '\0', strlen(line));

    char *p, *q;
    p = line;

    for (int j = 0; j < adv_cleared[i].pref_len; j++)
    {
      q = (adv_cleared[i].pref)[j][0];
      for (p; *q != '\0'; p++)
      {
        *p = *q;
        q++;
      }
      *p = ' ';
      p++;

      q = (adv_cleared[i].pref)[j][1];

      for (p; *q != '\0'; p++)
      {
        *p = *q;
        q++;
      }
      *p = '|';
      p++;
    }
    snprintf(row, sizeof(row), "%d,%d,%s\n", adv_cleared[i].adv_rank, adv_cleared[i].roll, line);
    fputs(row, file);
  }

  fclose(file);

  return 0;
}

int store_mains_cleared(int mains_cleared_len, struct mains_cleared_struct mains_cleared[])
{

  FILE *file;

  // Open the CSV file for writing
  file = fopen("mains_cleared.csv", "w");
  if (file == NULL)
  {
    printf("Unable to open file %s\n", "mains_cleared.csv");
  }

  for (int i = 0; i < mains_cleared_len; i++)
  {

    char line[MAX_LINE_LENGTH];
    char row[MAX_LINE_LENGTH];
    memset(row, '\0', strlen(row));
    memset(line, '\0', strlen(line));

    char *p, *q;
    p = line;

    for (int j = 0; j < mains_cleared[i].nit_pref_len; j++)
    {

      q = (mains_cleared[i].nit_pref)[j][0];
      for (p; *q != '\0'; p++)
      {
        *p = *q;
        q++;
      }
      *p = ' ';
      p++;

      q = (mains_cleared[i].nit_pref)[j][1];

      for (p; *q != '\0'; p++)
      {
        *p = *q;
        q++;
      }
      *p = '|';
      p++;
    }
    snprintf(row, sizeof(row), "%d,%d,%s,%s,%s\n", mains_cleared[i].mains_rank, mains_cleared[i].roll,
             line, mains_cleared[i].allocated_inst, mains_cleared[i].allocated_branch);
    fputs(row, file);
  }

  fclose(file);
  return 0;
}
