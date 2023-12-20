
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define FILENAME "C:\\Users\\HP\\Desktop\\VS Code\\file.txt"

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
    printf("Task List:\n");
    for (int i = 0; i < num_task; ++i) {
        printf("%d. %s\n", i + 1, tasks[i]);
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
    printf("\nAdd, remove, or edit tasks on the go, and eventually, you will know \"What color your Bugatti is!\"  ");
    while (getchar() != '\n') {}
    do {
        printf("Menu:\n");
        printf("1. Add Task\n");
        printf("2. Display To-Do List\n");
        printf("3. Edit Task\n");
        printf("4. Remove Task\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        getchar(); // Consume the newline character in the buffer

        switch (choice) {
        case 1:
            add_task(todo_list, &num_tasks);
            break;
        case 2:
            show_task(todo_list, num_tasks);
            break;
        case 3:
            edit_tasks(todo_list, num_tasks);
            break;
        case 4:
            remove_task(todo_list, &num_tasks);
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