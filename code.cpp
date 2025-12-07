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

int main()
{
    struct Task tasks[100];
    int n = 0;
    addTask(tasks, &n);
    system("pause");
    return 0;
}