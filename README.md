login.c - contains functions for student login, admin login, manipulating institutional details and checking if student cleared mains.

file_fns.c - includes functions for reading data from csv files into specifically defined structures and for copying data from structures to the files.

menu_fns.c - contains functions that manage the students’ preference list such as adding, deleting and switching the records and also for displaying the available courses.

algo_fns.c - contains all the main functions responsible for allocation step 1 (IIT allocation) and step 2 (NIT allocation).

menu.c - the file to be compiled and resultant executable file should be run. 
Other files are already linked to this file. It contains the integrated code and 
multiple menu driven functions.

To reset the entire process:
• Delete files of NIT_Details.csv, IIT_Details.csv
• Deleting preference lists & allocated courses columns in adv_cleared.csv 
and mains_cleared.csv
• Change data of allocation_started.txt file from 1 to 0
