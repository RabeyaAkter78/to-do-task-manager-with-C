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
    if (fp == NULL)
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
    fprintf(fp, "---\n");

    fclose(fp);
    printf("\n✅ Task successfully saved!\n");
}

// NEW FUNCTION: Load tasks from file into array
void loadTasksFromFile(struct Task *t, int *n)
{
    FILE *fp = fopen("task.txt", "r");
    if (fp == NULL)
    {
        *n = 0;
        return;
    }

    char line[300];
    *n = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "ID = %d", &t[*n].id) == 1)
        {
            fgets(line, sizeof(line), fp);
            sscanf(line, "Title = %[^\n]", t[*n].title);
            
            fgets(line, sizeof(line), fp);
            sscanf(line, "Description = %[^\n]", t[*n].description);
            
            fgets(line, sizeof(line), fp);
            sscanf(line, "Start = %[^\n]", t[*n].startTime);
            
            fgets(line, sizeof(line), fp);
            sscanf(line, "End = %[^\n]", t[*n].endTime);
            
            fgets(line, sizeof(line), fp);
            sscanf(line, "Due Date = %[^\n]", t[*n].dueDate);
            
            fgets(line, sizeof(line), fp);
            sscanf(line, "Priority = %[^\n]", t[*n].priority);
            
            fgets(line, sizeof(line), fp);
            sscanf(line, "Status = %[^\n]", t[*n].status);
            
            (*n)++;
        }
    }

    fclose(fp);
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
    if (fp == NULL)
    {
        printf("\n No saved tasks found!\n");
        return;
    }

    char line[300];
    printf("\n================ SAVED TASKS ================\n\n");

    while (fgets(line, sizeof(line), fp))
    {
        if (strcmp(line, "---\n") == 0)
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

void searchTask(struct Task *t, int n) {
    int id;
    char input[50];
    int found = 0;

    printf("\nSearch by:\n1. Task ID\n2. Task Title\n3. Priority (Low/Med/High)\nEnter choice: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter Task ID: ");
        scanf("%d", &id);
        getchar();

        for (int i = 0; i < n; i++) {
            if (t[i].id == id) {
                printf("\n---------- Task Found ----------\n");
                printf("ID: %d\nTitle: %s\nDescription: %s\nDue: %s\nPriority: %s\nStatus: %s\n",
                       t[i].id, t[i].title, t[i].description, t[i].dueDate, t[i].priority, t[i].status);
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2) {
        printf("Enter Task Title: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        for (int i = 0; i < n; i++) {
            char tempTitle[50];
            strcpy(tempTitle, t[i].title);
            tempTitle[strcspn(tempTitle, "\n")] = '\0';
            
            if (strstr(tempTitle, input) != NULL) {
                printf("\n---------- Task Found ----------\n");
                printf("ID: %d\nTitle: %s\nDescription: %s\nDue: %s\nPriority: %s\nStatus: %s\n",
                       t[i].id, t[i].title, t[i].description, t[i].dueDate, t[i].priority, t[i].status);
                found = 1;
            }
        }
    }
    else if (choice == 3) {
        printf("Enter Priority (Low/Med/High): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        for (int i = 0; i < n; i++) {
            char tempPriority[20];
            strcpy(tempPriority, t[i].priority);
            tempPriority[strcspn(tempPriority, "\n")] = '\0';
            
            if (strcasecmp(tempPriority, input) == 0) {
                printf("\n---------- Task Found ----------\n");
                printf("ID: %d\nTitle: %s\nDescription: %s\nDue: %s\nPriority: %s\nStatus: %s\n",
                       t[i].id, t[i].title, t[i].description, t[i].dueDate, t[i].priority, t[i].status);
                found = 1;
            }
        }
    }
    else {
        printf("\nInvalid choice!\n");
        return;
    }

    if (!found) {
        printf("\nTask Not Found!\n");
        printf("\nSuggested Tasks:\n");
        int suggested = 0;

        for (int i = 0; i < n && suggested < 5; i++) {
            char tempPriority[20], tempStatus[20];
            strcpy(tempPriority, t[i].priority);
            strcpy(tempStatus, t[i].status);
            tempPriority[strcspn(tempPriority, "\n")] = '\0';
            tempStatus[strcspn(tempStatus, "\n")] = '\0';

            if ((strcasecmp(tempPriority, "High") == 0 || strcasecmp(tempPriority, "Med") == 0) &&
                strcasecmp(tempStatus, "pending") == 0) {
                printf("ID: %d | Title: %s | Priority: %s | Status: %s\n",
                       t[i].id, t[i].title, tempPriority, tempStatus);
                suggested++;
            }
        }

        if (suggested == 0) {
            printf("No pending high/medium-priority tasks found.\n");
        }
    }
}

int main()
{
    struct Task tasks[100];
    int n = 0, choice;

    // Load existing tasks from file at startup
    loadTasksFromFile(tasks, &n);
    printf("Loaded %d tasks from file.\n", n);

    while (1)
    {
        printf("\n=============== TASK MANAGER ===============\n");
        printf("[1] Add Task\n");
        printf("[2] View All Tasks\n");
        printf("[3] Search A Tasks\n");
        printf("[4] Sort All Tasks\n");
        printf("[5] Update Single Tasks\n");
        printf("[6] Show Task Statistics\n");
        printf("[7] Delete Tasks\n");
        printf("[8] Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addTask(tasks, &n);
            break;
        case 2:
            viewAllTasks();
            break;
        case 3:
            // Reload tasks before searching to ensure we have latest data
            loadTasksFromFile(tasks, &n);
            searchTask(tasks, n);
            break;
        case 8:
            return 0;
        default:
            printf("\n Invalid option! Try again.\n");
        }
    }
}