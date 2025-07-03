//   FOCP Project (Daily Task Manager and Reminder)

// Using standard C libraries and some additional headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // For time-related functions.
#include <conio.h> 
#include <windows.h> // For Sleep function used in the intro. part for a better interface.

#define TASK_LIMIT 100 //Defining a macro named TASK_LIMIT with the value 100.

// Defining two files: One for storing uncompleted tasks and the other for completed tasks:
#define FILENAME ".\\text.txt"
#define FILENAME2 ".\\complete.txt"

// Defining a structure Task having two members: char description and time_t reminder_time:
/*struct Task {
    char description[100];
    time_t reminder_time; // It will store the reminder time for the task as UNIX timestamp.
};*/

//Initializing the functions we will use in this program:

void add_task(char tasks[TASK_LIMIT][100], int* num_tasks);
void show_task(const char tasks[TASK_LIMIT][100], int num_task);
void edit_tasks(char tasks[TASK_LIMIT][100], int num_tasks);
void remove_task(char tasks[TASK_LIMIT][100], int* num_tasks);
void complete_task(char tasks[TASK_LIMIT][100], int* num_tasks);
void display_complete_tasks(const char* filename);
void save_tasks(char tasks[TASK_LIMIT][100], int num_tasks);
void load_tasks(char tasks[TASK_LIMIT][100], int* num_tasks);
void set_reminder(char tasks[TASK_LIMIT][100], int numTasks);
int parseDateTime(const char* dateTimeString, struct tm* dateTimeStruct);

// Onto the main function now:
int main() {
    int choice;
    char todo_list[TASK_LIMIT][100]; //Initializing a 2D array that is able to hold upto 'TASK_LIMIT' tasks, each having upto 99 characters.  
    int num_tasks = 0;
    load_tasks(todo_list, &num_tasks);

    // Printing the Intro:
    printf("\n");
    printf("\t\t\t       *****************\n");
    printf("\t\t\t       *   Welcome to Daily Task Manager and Reminder  *\n");
    printf("\t\t\t       *****************\n");
    printf("\n");
    Sleep(700);
    printf("\t-> Hi! This program is designed to help you become more efficient.\n");
    
    Sleep(700); // We have used Sleep function defined under "windows.h" header file to create a good interface for the user.
    printf("\t-> Be desciplined and boost your dopamine upon completion of a task.\n");
    Sleep(700);
    printf("\t-> The manual is as simple as it can be.\n");
    Sleep(700);
    printf("\t-> Add, remove, or edit tasks on the go, and eventually, you will know \"What color your Bugatti is!\" \n");
    Sleep(700);
    printf("\t-> Press Enter key to start: ");
    while (getchar() != '\n') {}
    printf("\n");
    do {
        printf("***********************\n");
        printf("Menu:\n");
        printf("  1. Add Task\n");
        printf("  2. Set reminder\n");
        printf("  3. Display To-Do List\n");
        printf("  4. Edit Task\n");
        printf("  5. Remove Task\n");
        printf("  6. Mark Task as Completed\n");
        printf("  7. Show Completed Tasks\n");
        printf("  0. Exit\n");
        printf("----------------------------\n");
        printf("\nEnter your choice: ");


        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid option.\n");

            // Clear the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            continue;  // Skip the rest of the loop and restart
        }

        // Consume any remaining characters in the buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        // Using 'Switch Statement' to call different functions for different user inputs:
        switch (choice) {
        case 1:
            add_task(todo_list, &num_tasks);
            break;
        case 2:
            set_reminder(todo_list, num_tasks);
            break;
        case 3:
            show_task(todo_list, num_tasks);
            break;
        case 4:
            edit_tasks(todo_list, num_tasks);
            break;
        case 5:
            remove_task(todo_list, &num_tasks);
            break;
        case 6:
            complete_task(todo_list, &num_tasks);
            break;
        case 7:
            display_complete_tasks(FILENAME2);
            break;
        case 0:
            printf("\n");
            printf("\t\t     ***********************\n");
            printf("\t\t     *   Thanks for using \"Daily Task Manager and Reminder\" EXITING...   *\n");
            printf("\t\t     ***********************\n");
            printf("\n");
            break;
        default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
        // Save tasks after each operation
        save_tasks(todo_list, num_tasks);

    } while (choice != 0);
    

    return 0;
}

// *****(We are defining a function to load tasks from the file to the 2D array we initialized earlier) *****

void load_tasks(char tasks[TASK_LIMIT][100], int* num_tasks) {

    // Opening the file for reading:
    FILE* file = fopen(FILENAME, "r");

    if (file == NULL) {  // If the file does not open or does not exist.
        perror("Error opening file for reading");
        return;
    }
    *num_tasks = 0;// Initializing *num_tasks to '0' for first index.
    while (*num_tasks < TASK_LIMIT && fgets(tasks[*num_tasks], sizeof(tasks[0]), file) != NULL) {
        size_t len = strlen(tasks[*num_tasks]);

        if (len > 0 && tasks[*num_tasks][len - 1] == '\n') { // Second condition checks whether the last character in the string is '\n' or not.
            tasks[*num_tasks][len - 1] = '\0'; // Replacing '\n' by '\0' for Consistency purposes.
        }
        (*num_tasks)++;// Incrementing the *num_task by 1 for the next task.
    }
    // Closing the file:
    fclose(file);
}

// *****(We are defining a function to add tasks to the 2D array we initialized earlier)*****

void add_task(char tasks[TASK_LIMIT][100], int* num_tasks) {
    if (*num_tasks < TASK_LIMIT) {
        char input_task[100] = { 0 };// We declared an array input_task to store user input and initialized it to zero for proper string handling.
        printf("Enter the task: ");
        fgets(input_task, sizeof(input_task), stdin);// 'fgets' will read the input and pass it to input_task array. The size of array will depend upon input length.

        if (input_task[0] == '\n')
        {
            printf("Task can not be empty\n");// Printing an error message for empty input.
            return;
        }

        size_t len = strlen(input_task);// Finding the length of user input.
        if (len > 0 && input_task[len - 1] == '\n') {  //For the last character in the array.
            input_task[len - 1] = '\0';// Replacing '\n' by '0' for better handling and Consistency purposes.
        }

        strcpy(tasks[*num_tasks], input_task);// Copying the string carrying user's input to the 2D array 'tasks' at position no. '*num_tasks'.
        (*num_tasks)++; //Incrementing the task number by 1 for the next input. Next time, the function will recieve the value of '*num_tasks' incremented by 1.
        printf("Task added successfully.\n");
    }
    else {
        printf("Error: Maximum number of tasks reached.\n");// Printed if the 'if' statement is not satisfied. i.e., Total tasks have reached the max. limit.
    }
}

// *****(We are defining a function that will display tasks along with their reminders)*****

void show_task(const char tasks[TASK_LIMIT][100], int num_task) {
    FILE* file = fopen(FILENAME, "r");

    if (file == NULL) {  // If the file does not open or does not exist.
        perror("Error opening file for reading");
        return;
    }
    int isEmpty = fgetc(file);

    fclose(file); // Closing the file

    if (isEmpty == EOF) {
        printf("You have no Tasks in the Task List at the moment.\n");
        return;
    }

    time_t currentTime = time(NULL);

    printf("\nTask List:\n");
    for (int i = 0; i < num_task; i++) {
        printf("%d. %s", i + 1, tasks[i]);

        /* Using 'strstr' function to search for the first occurance of the substring "(Reminder:" in the current string tasks[i]. This function will return 0 if
          the substring is not found in the task[i] string or if it is found then it will return the address of the first character of the substring. We are doing
          to display the reminder of a task too if any. */
        const char* reminderString = strstr(tasks[i], "(Reminder:");
        if (reminderString != NULL) {
            // Extracting the timestamp from the reminder string:
            struct tm reminderTime = { 0 };//Declaring a variable reminderTime of data type struct tm to store the parsed date and time from the 'reminder' substring.
            char dateTimeString[50]; /* We will use this char array to store a character representation of date and time(in YYYY - MM - DD & HH:MM format) extracted
            from the task string.This will then be used for parsing and then, the parsed values will be passed to "reminderTime". */
            
            strcpy(dateTimeString, reminderString + 11); /* Copying the date / time string from the end of reminder substring and further on.The "+ 11" means 
            skipping the 11 characters of "(Reminder:" and just copying the date and time in YYYY - MM - DD & HH:MM format. */
            if (parseDateTime(dateTimeString, &reminderTime)) { /* Calling a function "parseDateTime" to parse the "dateTimeString" and populate the "reminderTime"
                structure. The function returns true if parsing is successful. */
                time_t reminderTimestamp = mktime(&reminderTime);// We used "mktime" function which converts the parsed date and time into a time_t timestamp.

                if (reminderTimestamp < currentTime) { 
                    printf(" (Overdue)"); // Marking the task as overdue if reminder time has passed i.e., reminderTimestamp is greater than the currentTime.
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

// *****(We are defining a function that will allow the user to edit his/her tasks)*****

void edit_tasks(char tasks[TASK_LIMIT][100], int num_tasks) {
    FILE* file = fopen(FILENAME, "r");

    if (file == NULL) {  // If the file does not open or does not exist.
        perror("Error opening file for reading");
        return;
    }
    int isEmpty = fgetc(file);

    fclose(file); // Closing the file

    if (isEmpty == EOF) {
        printf("You have no Tasks in the Task List. There is nothing to edit\n");
        return;
    }
    int task_index; //Declaring a variable to store the user input for which task number he wants to edit.
    show_task(tasks, num_tasks); //Calling the show_task function so that user can easily choose from the tasks.
    printf("Enter the task number to edit: ");
    scanf("%d", &task_index);

    if (task_index >= 1 && task_index <= num_tasks) { //Checking if the number entered by the user is legit or not.
        task_index--; //Decrementing the value by 1 because its index number in string will be 1 less than the original task number.

        char input_task[100]; // Declaring a string to store user's new input.
        printf("Enter the new task: ");
        getchar(); // It will consume the newline character.
        fgets(input_task, sizeof(input_task), stdin); // 'fgets' function will read the input and pass it to input_task array. The size of array will depend upon input length.
        if (input_task[0] == '\n')
        {
            printf("Task can not be left empty\n"); //Showing the user an error message if the input is empty.
            return;
        }

        size_t len = strlen(input_task);
        if (len > 0 && input_task[len - 1] == '\n') { //Checking for the last character in the user input.
            input_task[len - 1] = '\0'; // Replacing '\n' by '\0' for better handling and consistency purposes.
        }

        strcpy(tasks[task_index], input_task); //Copying the new user input from 'input_task' to 'task' array at its position 'task_index'.  
        printf("Task edited successfully.\n");
    }
    else if (scanf("%d", &task_index) != 1 || task_index < 1 || task_index > num_tasks) {

        printf("Invalid task number. Returning...\n");

        // Clearing the input buffer to handle any remaining characters:
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

}

// *****(We are defining a function that will allow the user to remove any task if he wants)*****

void remove_task(char tasks[TASK_LIMIT][100], int* num_tasks) {
    // Opening the file for reading:
    FILE* file = fopen(FILENAME, "r");

    if (file == NULL) {  // If the file does not open or does not exist.
        perror("Error opening file for reading");
        return;
    }
    int isEmpty = fgetc(file);

    fclose(file); // Closing the file

    if (isEmpty == EOF) {
        printf("Error: No current tasks on the list. There is nothing to remove.\n");
        return;
    }
    int task_index; // Declaring an int variable to store the user input for which task number he wants to edit.
    show_task(tasks, *num_tasks);// Calling the show_task function so that user can easily choose from the tasks.
    printf("Enter the task number to remove: ");
    scanf("%d", &task_index);

    if (task_index >= 1 && task_index <= *num_tasks) { //Checking if the task number entered by the user is legit or not.
        task_index--; // Decrementing the value by 1 because its index number in string will be 1 less than the original task number.

        /*Using a for loop to iterate through the tasks array starting from the task_index and move the tasks from there on to one index lower 
        using 'strcpy' function, thus removing the task user wanted to remove. */
        for (int i = task_index; i < *num_tasks - 1; ++i) {
            strcpy(tasks[i], tasks[i + 1]);
        }

        (*num_tasks)--; //Decreasing the total number of tasks by one.
        printf("Task removed successfully.\n");
    }
    else {
        printf("Invalid task number.\n"); //Printing an error message if the choice of task was not legit.
    }
}

// *****(We are defining a function to save the task given by the user into a file)*****

void save_tasks(char tasks[TASK_LIMIT][100], int num_tasks) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) { // When there is an error in opening the file or there is no such file at all. 
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_tasks; i++) {
      
        if (fprintf(file, "%s\n", tasks[i]) < 0) { // "fprintf will write the input tasks[i] to the file in %s\n format.
            perror("Error writing to file"); //Printing an error message if the writing fails.
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file); //Closing the file so our data is properly saved.
}

// *****(We are defining a function to store the tasks meakrd 'completed' into a separate file)*****

void complete_task(char tasks[TASK_LIMIT][100], int* num_tasks) {
    if (*num_tasks == 0) {
        printf("No tasks to complete.\n");
        return;
    }

    printf("Select a task to mark as completed:\n");
    show_task(tasks, *num_tasks); //Showing the task list to the user for user's ease.

    int task_index; //Initializing a variable to store user input.
    printf("Enter the task number: ");
    scanf("%d", &task_index);

    if (task_index >= 1 && task_index <= *num_tasks) { //Checking if the task number entered by the user is legit or not.

        task_index--; // Decrementing the value by 1 because its index number in string will be 1 less than the original task number.

        // Opening the FILENAME2 to store completed tasks separately from uncompleted tasks.
        FILE* file2 = fopen(FILENAME2, "a");
        if (file2 == NULL) {
            perror("Error opening file2"); // Showing error when while there is a problem in opening the file or when there is no such file at all.
            return;
        }
        fprintf(file2, "%s\n", tasks[task_index]); // "fprint" function will copy the task from tasks[task_index] to file2 in %s\n format. 
        fclose(file2); //Closing the file.

        // Removing the completed task from the "tasks list" (which will show uncompleted tasks at any time) using the same strcpy method we used earlier:
        for (int i = task_index; i < *num_tasks - 1; ++i) {
            strcpy(tasks[i], tasks[i + 1]);
        }

        (*num_tasks)--; // Decreasing the total number of tasks in the "tasks list" by 1.
        printf("Task marked as completed.\n");
    }
    else {
        printf("Invalid task number.\n"); //Printing error when an invalid number is entered.
    }
}

// *****(We are defining a function to load the completed tasks from their file and display them)*****

void display_complete_tasks(const char* filename) {
    FILE* file = fopen(filename, "r"); // Opening the file for reading purposes.
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char task[100]; 
    int taskNumber = 1;

    printf("\nTasks from file \"%s\":\n", filename);
    printf("\n");
    printf("Completed Tasks\n");
    printf("\n");
    while (fgets(task, sizeof(task), file) != NULL) { // This will prove "false" only when there is no completed task left in the file.
        size_t len = strlen(task);
        if (len > 0 && task[len - 1] == '\n') {
            task[len - 1] = '\0'; // Replacing '\n' by '\0' for better handling and consistency purposes.
        }

        printf("%d. %s\n", taskNumber, task); // Printing the completed tasks along with indexing.
        taskNumber++; // Incrementing the task number by 1 for the next task.
    }
    printf("\n");
    fclose(file); //Closing the file.
}

// *****(We are defining a function that will allow the user to set reminder on any of the tasks)*****

void set_reminder(char tasks[TASK_LIMIT][100], int numTasks) {
    // Opening the file for reading:
    FILE* file = fopen(FILENAME, "r");

    if (file == NULL) {  // If the file does not open or does not exist.
        perror("Error opening file for reading");
        return;
    }
    int isEmpty = fgetc(file);

    fclose(file); // Closing the file

    if (isEmpty == EOF) { // Only when the characters stored by fgetc from the file into isEmpty are only EOF. It means file is empty.
        printf("Error: No current tasks on the list. Reminder cannot be applied.\n");
        return;
    }

    
    show_task(tasks, numTasks); // Calling show_task function to display tasks for user's ease.
    int taskIndex;
    printf("Enter the task number to set a reminder: ");
    scanf("%d", &taskIndex);


    if (taskIndex >= 1 && taskIndex <= numTasks) { //Checking if the user's input is valid.

        /* Using 'strstr' function to search for the first occurance of the substring "(Reminder:" in the current string tasks[i]. This function will return 0 if
          the substring is not found in the task[i] string or if it is found then it will return the address of the first character of the substring. We are doing
          to display the reminder of a task too if any. */
        char* reminderString = strstr(tasks[taskIndex - 1], "(Reminder:");

        if (reminderString != NULL) { // It shows that there is already a reminder set for that task.
            char choice;

            printf("Do you want to edit the reminder (Y/N)? ");
            scanf(" %c", &choice);

            if (choice == 'N' || choice == 'n') {
                printf("Exiting without editing the reminder.");
                return;
            }
            // In case the user wants to edit the reminder:
            memset(reminderString, '\0', strlen(reminderString)); // We will use the memset function which will fill all the bytes in the "reminderString" by the null character '\0', thus deleting the previous reminder.
        }
        time_t currentTime = time(NULL); // time(NULL) will return the current time in seconds since the epoch(January 1, 1970).
        time_t reminderTime;
        /* The primary purpose of time_t is to represent the number of seconds elapsed since a specific point in time called the "epoch" or "UNIX epoch". */
        int hours, minutes, day, month, year;
        char choice;

        printf("Do you want to set the reminder for today (Y/N)? ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            /* Our program will first take the current time by using "localtime" function('localtime' function takes pointer to a time.h object which the 'currentTime' also is) and will then convert it into 
            a datatype 'struct tm' of 'currentDate'. This structure 'struct tm' is defined in time.h and includes various components of the date and time, including year, month, day, hour, minute, and second. */
            struct tm* currentDate = localtime(&currentTime);

            /* Next, we will use tm_mday, tm_mon, and tm_year members of 'struct tm' structure to retrieve the days (1 to 31), months (1 to 12), and year from the 'struct tm' currentDate. */
            day = currentDate->tm_mday;
            month = currentDate->tm_mon + 1; // tm_mon is zero-based, so we will add 1.
            
            year = currentDate->tm_year + 1900; // tm_year represents the years since 1900 (so we will add 1900 to it)
        }
        else {
            printf("Do you want to set the reminder for tomorrow (Y/N)? ");
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y') {
                // Use tomorrow's date
                time_t tomorrow = currentTime + 24 * 60 * 60; // Adding another 24 hours in terms of seconds since time_t returns time in seconds.
                // Using the same technique again:
                struct tm* tomorrowDate = localtime(&tomorrow);
                day = tomorrowDate->tm_mday;
                month = tomorrowDate->tm_mon + 1; 
                year = tomorrowDate->tm_year + 1900;
            }
            else {
                // Ask for a manual date
                printf("Enter reminder date (dd mm yyyy): ");
                scanf("%d %d %d", &day, &month, &year);
            }
        }

        printf("Enter reminder time (HH:MM in 24-hour format): ");
        scanf("%d:%d", &hours, &minutes);

        struct tm reminderDate = { 0 }; // Declaring a struct reminderDate and intializing all of its members to zero.
        
        // We will now the individual components of the 'reminderDate' structure with the values obtained earlier. Note that we are still in struct tm.
        reminderDate.tm_hour = hours;
        reminderDate.tm_min = minutes;
        reminderDate.tm_mday = day;
        reminderDate.tm_mon = month - 1; // Since the months in struct tm are 0-indexed.
        reminderDate.tm_year = year - 1900; // Since the years in struct tm are counted from 1900.

        // Finally, we will use the 'mktime' function to convert the 'struct tm' representation of the date & time (in reminderDate) into a UNIX timestamp (reminderTime). 
        reminderTime = mktime(&reminderDate);

        if (reminderTime < currentTime) {
            printf("Reminder is not set as the time has passed.\n"); //Printing error if the user sets the reminder to a past time.
        }
        else {
            char reminderString[100]; // Declaring a char array which we will use to store the formatted reminder string.

            // Using the strftime function to convert the UNIX timestamp (reminderTime) to a human-readable string format (reminderString).
            strftime(reminderString, sizeof(reminderString), "(Reminder: %Y-%m-%d %H:%M:%S)", localtime(&reminderTime));

            // Using string catenation method (strcat function) to concatinate the "reminderString" and the associated task "tasks[taskIndex-1]" for better readability:
            strcat(tasks[taskIndex - 1], reminderString);

            printf("Reminder set for task %d successfully.\n", taskIndex);
        }

    }
    else if(scanf("%d", &taskIndex) != 1 || taskIndex < 1 || taskIndex > numTasks) {
        
         printf("Invalid task number. Returning...\n");

         // Clearing the input buffer to handle any remaining characters:
         int c;
         while ((c = getchar()) != '\n' && c != EOF);
    }
    
    printf("\n");
}

// *****(We are defining a parseDateTime function to be used in set_reminder function, etc.)*****

int parseDateTime(const char* dateTimeString, struct tm* dateTimeStruct) {
    if (dateTimeString == NULL || dateTimeStruct == NULL) {
        return 0; // Invalid input.
    }

    int year, month, day, hour, minute, second;
    //sscanf is used to read the data from the string. Cheking if everything is OK.
    if (sscanf(dateTimeString, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        return 0; // Parsing failed when there aren't enough arguments.
    }

    dateTimeStruct->tm_year = year - 1900; // Because years are counted since 1900 in struct tm.
    dateTimeStruct->tm_mon = month - 1;   // Because month is 0-indexed in struct tm.
    dateTimeStruct->tm_mday = day;
    dateTimeStruct->tm_hour = hour;
    dateTimeStruct->tm_min = minute;
    dateTimeStruct->tm_sec = second;

    return 1; // When the parsing is successful.
}

//*****(Thanks for your time.)*****