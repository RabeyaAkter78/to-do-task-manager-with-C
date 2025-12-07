#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Task
{
    int id;
    char title[20];
    char description[100];
    char startTime[20];
    char endTime[20];
    char dueDate[20];
    char priority[10];
    char status[10];
};

// Add  a task

void addTask(struct Task *t, int *n)
{
    int newId;
    printf("Enter the Task Id: ");
    scanf("%d", &newId);
    getchar();

    for (int i = 0; i < *n; i++)
    {
        if (t[i].id == newId)
        {
            printf("Task Id already exists");
            return;
        }
    };

    t[*n].id = newId;
    printf("Enter The Task Title: ");
    fgets(t[*n].title, sizeof(t[*n].title), stdin);
    printf("Enter the task Description: ");
    fgets(t[*n].description, sizeof(t[*n].description), stdin);
    printf("Enter the Start Time: ");
    fgets(t[*n].startTime, sizeof(t[*n].startTime), stdin);
    printf("Enter the End Time: ");
    fgets(t[*n].endTime, sizeof(t[*n].endTime), stdin);
    printf("Enter the Due Date: ");
    fgets(t[*n].dueDate, sizeof(t[*n].dueDate), stdin);
    printf("Enter the Priority: ");
    fgets(t[*n].priority, sizeof(t[*n].priority), stdin);
    printf("Enter the Status: ");
    fgets(t[*n].status, sizeof(t[*n].status), stdin);

    (*n)++;
    return;
};

void viewAllTasks(struct Task *t, int n)
{
    if (n == 0)
    {
        printf("No tasks found");
        return;
    }

    printf("\n================Task List================\n");
    for (int i = 0; i < n; i++)
    {
        printf("\n--------------------------------------------------------------");
        printf("Task ID: %d\n", t[i].id);
        printf("Task Title: %s", t[i].title);
        printf("Task Description: %s", t[i].description);
        printf("Start Time: %s", t[i].startTime);
        printf("End Time: %s", t[i].endTime);
        printf("Due Date: %s", t[i].dueDate);
        printf("Priority: %s", t[i].priority);
        printf("Status: %s", t[i].status);
           printf("--------------------------------------------------------------");
    }
};

int main()
{
    struct Task tasks[100];
    int n = 0;
    int choice;
    while (1)
    {
        printf("\n===========================================================\n");
        printf("                            TASK MANAGER \n                            \n");
        printf("===========================================================\n");

        printf("[1] Add Task\n");
        printf("[2] View Task\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addTask(tasks, &n);
        case 2:
            viewAllTasks(tasks, n);

            break;

        default:
            break;
        }
    }

    addTask(tasks, &n);
    system("pause");
    return 0;
}