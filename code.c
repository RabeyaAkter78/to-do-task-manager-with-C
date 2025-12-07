#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Task
{
    int id;
    char title[50];
    char description[200];
    char startTime[30];
    char endTime[30];
    char dueDate[30];
    char priority[20];
    char status[20];
};


void saveToFile(struct Task t)
{
    FILE *fp = fopen("task.txt", "a");
    if(fp == NULL)
    {
        printf(" Error opening file\n");
        return;
    }

    fprintf(fp, "ID = %d\n", t.id);
    fprintf(fp, "Title = %s", t.title);
    fprintf(fp, "Description = %s", t.description);
    fprintf(fp, "Start = %s", t.startTime);
    fprintf(fp, "End = %s", t.endTime);
    fprintf(fp, "Due Date = %s", t.dueDate);
    fprintf(fp, "Priority = %s", t.priority);
    fprintf(fp, "Status = %s", t.status);
    fprintf(fp, "---\n"); // separator for tasks

    fclose(fp);
    printf("\n✅ Task successfully saved!\n");
}


void addTask(struct Task *t, int *n)
{
    printf("\nEnter Task ID: ");
    scanf("%d", &t[*n].id);
    getchar();

    printf("Enter Title: ");
    fgets(t[*n].title, sizeof(t[*n].title), stdin);
    printf("Enter Description: ");
    fgets(t[*n].description, sizeof(t[*n].description), stdin);
    printf("Enter Start Time: ");
    fgets(t[*n].startTime, sizeof(t[*n].startTime), stdin);
    printf("Enter End Time: ");
    fgets(t[*n].endTime, sizeof(t[*n].endTime), stdin);
    printf("Enter Due Date: ");
    fgets(t[*n].dueDate, sizeof(t[*n].dueDate), stdin);
    printf("Enter Priority: ");
    fgets(t[*n].priority, sizeof(t[*n].priority), stdin);
    printf("Enter Status: ");
    fgets(t[*n].status, sizeof(t[*n].status), stdin);

    saveToFile(t[*n]);
    (*n)++;
}


void viewAllTasks()
{
    FILE *fp = fopen("task.txt", "r");
    if(fp == NULL)
    {
        printf("\n❌ No saved tasks found!\n");
        return;
    }

    char line[300];
    printf("\n================ SAVED TASKS ================\n\n");

    while(fgets(line, sizeof(line), fp))
    {
        if(strcmp(line, "---\n") == 0)
        {
            printf("--------------------------------------------\n\n");
        }
        else
        {
            printf("%s", line);
        }
    }

    fclose(fp);
}


int main()
{
    struct Task tasks[100];
    int n = 0, choice;

    while(1)
    {
        printf("\n=============== TASK MANAGER ===============\n");
        printf("[1] Add Task\n");
        printf("[2] View All Tasks\n");
        printf("[3] Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addTask(tasks, &n);
                break;
            case 2:
                viewAllTasks();
                break;
            case 3:
                return 0;
            default:
                printf("\n Invalid option! Try again.\n");
        }
    }
}
