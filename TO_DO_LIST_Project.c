#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_TASKS 100
#define FILENAME "C:\\Users\\HP\\Desktop\\Project\\text.txt"
#define FILENAME2 "C:\\Users\\HP\\Desktop\\Project\\complete.txt"
struct Task {
    char description[100];
    time_t reminder_time; // Store reminder time as UNIX timestamp
};

void add_task(char tasks[MAX_TASKS][100], int* num_tasks);
void show_task(const char tasks[MAX_TASKS][100], int num_task);
void edit_tasks(char tasks[MAX_TASKS][100], int num_tasks);
void remove_task(char tasks[MAX_TASKS][100], int* num_tasks);
void complete_task(char tasks[MAX_TASKS][100], int* num_tasks);
void display_complete_tasks(const char* filename);
void save_tasks(char tasks[MAX_TASKS][100], int num_tasks);
void load_tasks(char tasks[MAX_TASKS][100], int* num_tasks);
void set_reminder(char tasks[MAX_TASKS][100], int numTasks);
int parseDateTime(const char* dateTimeString, struct tm* dateTimeStruct);
int main() {
    int choice;
    char todo_list[MAX_TASKS][100];
    int num_tasks = 0;

    load_tasks(todo_list, &num_tasks);
    printf("\t\tWelcome to To-Do List\n");
    while (getchar() != '\n') {}
    printf("The program is designed to help you become more efficient and boost your dopamine upon completion of a task.");
    while (getchar() != '\n') {}
    printf("The manual is as simple as it can be.");
    while (getchar() != '\n') {}
    printf("\nAdd, remove, or edit tasks on the go, and eventually, you will know \"What color your Bugatti is!\" \n");
    while (getchar() != '\n') {}
    do {
        printf("--------------------------\n");
        printf("Menu:\n");
        printf("1. Add Task\n");
        printf("2. Set reminder\n");
        printf("3. Display To-Do List\n");
        printf("4. Edit Task\n");
        printf("5. Remove Task\n");
        printf("6. Mark Task as Completed\n");
        printf("7. Show Completed Tasks\n");
        printf("0. Exit\n");
        printf("--------------------------\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        getchar();
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
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

        // Save tasks after each operation
        save_tasks(todo_list, num_tasks);

    } while (choice != 0);

    return 0;
}


void load_tasks(char tasks[MAX_TASKS][100], int* num_tasks) {
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    *num_tasks = 0;
    while (*num_tasks < MAX_TASKS && fgets(tasks[*num_tasks], sizeof(tasks[0]), file) != NULL) {
        size_t len = strlen(tasks[*num_tasks]);
        if (len > 0 && tasks[*num_tasks][len - 1] == '\n') {
            tasks[*num_tasks][len - 1] = '\0';
        }
        (*num_tasks)++;
    }

    fclose(file);
}

void add_task(char tasks[MAX_TASKS][100], int* num_tasks) {
    if (*num_tasks < MAX_TASKS) {
        char input_task[100];
        printf("Enter the task: ");
        fgets(input_task, sizeof(input_task), stdin);

        size_t len = strlen(input_task);
        if (len > 0 && input_task[len - 1] == '\n') {
            input_task[len - 1] = '\0';
        }

        strcpy(tasks[*num_tasks], input_task);
        (*num_tasks)++;
        printf("Task added successfully.\n");
    }
    else {
        printf("Error: Maximum number of tasks reached.\n");
    }
}

void show_task(const char tasks[MAX_TASKS][100], int num_task) {
    time_t currentTime = time(NULL);

    printf("\nTask List:\n");
    for (int i = 0; i < num_task; i++) {
        printf("%d. %s", i + 1, tasks[i]);

        // Extract reminder string (if present)
        const char* reminderString = strstr(tasks[i], "(Reminder:");
        if (reminderString != NULL) {
            // Extract timestamp from the reminder string
            struct tm reminderTime = {0};
            char dateTimeString[50];
            strcpy(dateTimeString, reminderString + 11); // Copy the date/time string
            if (parseDateTime(dateTimeString, &reminderTime)) {
                time_t reminderTimestamp = mktime(&reminderTime);

                if (reminderTimestamp < currentTime) {
                    printf(" (Overdue)"); // Mark as overdue if reminder time has passed
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void edit_tasks(char tasks[MAX_TASKS][100], int num_tasks) {
    int task_index;
    printf("Enter the task number to edit: ");
    scanf("%d", &task_index);

    if (task_index >= 1 && task_index <= num_tasks) {
        task_index--;

        char input_task[100];
        printf("Enter the new task: ");
        getchar(); // Consume the newline character
        fgets(input_task, sizeof(input_task), stdin);

        size_t len = strlen(input_task);
        if (len > 0 && input_task[len - 1] == '\n') {
            input_task[len - 1] = '\0';
        }

        strcpy(tasks[task_index], input_task);
        printf("Task edited successfully.\n");
    }
    else {
        printf("Invalid task number.\n");
    }
}

void remove_task(char tasks[MAX_TASKS][100], int* num_tasks) {
    int task_index;
    //printf("Tasks List\n");
    //show_task(tasks, *num_tasks);
    printf("Enter the task number to remove: ");
    scanf("%d", &task_index);

    if (task_index >= 1 && task_index <= *num_tasks) {
        task_index--;

        for (int i = task_index; i < *num_tasks - 1; ++i) {
            strcpy(tasks[i], tasks[i + 1]);
        }

        (*num_tasks)--;
        printf("Task removed successfully.\n");
    }
    else {
        printf("Invalid task number.\n");
    }
}

void save_tasks(char tasks[MAX_TASKS][100], int num_tasks) {
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num_tasks; ++i) {
        if (fprintf(file, "%s\n", tasks[i]) < 0) {
            perror("Error writing to file");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
}


void complete_task(char tasks[MAX_TASKS][100], int* num_tasks) {
    if (*num_tasks == 0) {
        printf("No tasks to complete.\n");
        return;
    }

    printf("Select a task to mark as completed:\n");
    show_task(tasks, *num_tasks);

    int task_index;
    printf("Enter the task number: ");
    scanf("%d", &task_index);

    if (task_index >= 1 && task_index <= *num_tasks) {
        task_index--;

        // Move the completed task to FILENAME2
        FILE* file2 = fopen(FILENAME2, "a");
        if (file2 == NULL) {
            perror("Error opening file2");
            return;
        }
        fprintf(file2, "%s\n", tasks[task_index]);
        fclose(file2);

        // Remove the completed task from the tasks list
        for (int i = task_index; i < *num_tasks - 1; ++i) {
            strcpy(tasks[i], tasks[i + 1]);
        }

        (*num_tasks)--;
        printf("Task marked as completed.\n");
    }
    else {
        printf("Invalid task number.\n");
    }
}
void display_complete_tasks(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char task[100];
    int taskNumber = 1;

    printf("\nTasks from file \"%s\":\n", filename);
    printf("Completed Tasks\n");
    while (fgets(task, sizeof(task), file) != NULL) {
        size_t len = strlen(task);
        if (len > 0 && task[len - 1] == '\n') {
            task[len - 1] = '\0';
        }

        printf("%d. %s\n", taskNumber, task);
        taskNumber++;
    }
    printf("\n");
    fclose(file);
}

void set_reminder(char tasks[MAX_TASKS][100], int numTasks) {
    printf("Tasks List:\n");
    show_task(tasks, numTasks); // Assuming show_task() function prints tasks with numbers

    int taskIndex;
    printf("Enter the task number to set a reminder: ");
    scanf("%d", &taskIndex);

    if (taskIndex >= 1 && taskIndex <= numTasks) {
        char* reminderString = strstr(tasks[taskIndex - 1], "(Reminder:");

        if (reminderString != NULL) {
            printf("A reminder already exists for this task.\n");
        } else {
            time_t currentTime = time(NULL);
            time_t reminderTime;
            int hours, minutes, day, month, year;
            char choice;

            printf("Do you want to set the reminder for today (Y/N)? ");
            scanf(" %c", &choice);

            if (choice == 'Y' || choice == 'y') {
                // Use today's date
                struct tm* currentDate = localtime(&currentTime);
                day = currentDate->tm_mday;
                month = currentDate->tm_mon + 1; // tm_mon is zero-based
                year = currentDate->tm_year + 1900; // tm_year is years since 1900
            } else {
                printf("Do you want to set the reminder for tomorrow (Y/N)? ");
                scanf(" %c", &choice);

                if (choice == 'Y' || choice == 'y') {
                    // Use tomorrow's date
                    time_t tomorrow = currentTime + 24 * 60 * 60; // 24 hours in seconds
                    struct tm* tomorrowDate = localtime(&tomorrow);
                    day = tomorrowDate->tm_mday;
                    month = tomorrowDate->tm_mon + 1; // tm_mon is zero-based
                    year = tomorrowDate->tm_year + 1900; // tm_year is years since 1900
                } else {
                    // Ask for a manual date
                    printf("Enter reminder date (dd mm yyyy): ");
                    scanf("%d %d %d", &day, &month, &year);
                }
            }

            printf("Enter reminder time (HH:MM in 24-hour format): ");
            scanf("%d:%d", &hours, &minutes);

            struct tm reminderDate = {0}; // Initialize the reminderDate struct
            reminderDate.tm_hour = hours;
            reminderDate.tm_min = minutes;
            reminderDate.tm_mday = day;
            reminderDate.tm_mon = month - 1; // Month in struct tm is 0-indexed
            reminderDate.tm_year = year - 1900; // Year in struct tm is years since 1900

            reminderTime = mktime(&reminderDate);

            if (reminderTime < currentTime) {
                printf("Reminder is not set as the time has passed.\n");
            } else {
                char reminderString[100]; // Buffer to store the formatted reminder string

                // Convert the UNIX timestamp to a human-readable string format
                strftime(reminderString, sizeof(reminderString), "(Reminder: %Y-%m-%d %H:%M:%S)", localtime(&reminderTime));

                // Append the human-readable reminder string to the task description
                strcat(tasks[taskIndex - 1], reminderString);

                printf("Reminder set for task %d successfully.\n", taskIndex);
            }
        }
    } else {
        printf("Invalid task number.\n");
    }
    printf("\n");
}


int parseDateTime(const char* dateTimeString, struct tm* dateTimeStruct) {
    if (dateTimeString == NULL || dateTimeStruct == NULL) {
        return 0; // Invalid input
    }

    int year, month, day, hour, minute, second;
    if (sscanf(dateTimeString, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        return 0; // Parsing failed
    }

    dateTimeStruct->tm_year = year - 1900; // Year is years since 1900
    dateTimeStruct->tm_mon = month - 1;   // Month is 0-indexed
    dateTimeStruct->tm_mday = day;
    dateTimeStruct->tm_hour = hour;
    dateTimeStruct->tm_min = minute;
    dateTimeStruct->tm_sec = second;

    return 1; // Parsing successful
}


