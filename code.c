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

int loadFromFile(struct Task *t)
{
    FILE *fp = fopen("task.txt", "r");
    if (!fp)
    {
        printf("No saved tasks found!\n");
        return 0;
    }

    int count = 0;

    while (!feof(fp))
    {
        fscanf(fp, "ID = %d\n", &t[count].id);
        fgets(t[count].title, sizeof(t[count].title), fp);
        fgets(t[count].description, sizeof(t[count].description), fp);
        fgets(t[count].startTime, sizeof(t[count].startTime), fp);
        fgets(t[count].endTime, sizeof(t[count].endTime), fp);
        fgets(t[count].dueDate, sizeof(t[count].dueDate), fp);
        fgets(t[count].priority, sizeof(t[count].priority), fp);
        fgets(t[count].status, sizeof(t[count].status), fp);

        char sep[10];
        fgets(sep, sizeof(sep), fp);

        count++;
    }

    fclose(fp);
    return count;
}

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
    printf("\n Task successfully saved!\n");
}

void addTask(struct Task *t, int *n)
{
    int newId;
    printf("\n Enter Task ID: ");
    scanf("%d", &newId);
    getchar();

    for (int i = 0; i < *n; i++)
    {
        if (t[i].id == newId)
        {
            printf("\n Task ID already exists!\n");
            return;
        }
    }
    t[*n].id = newId;
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

// Search a Task:

void searchTask(struct Task *t, int n)
{
    int id;
    char input[50];
    int found = 0;

    printf("\nSearch by:\n1. Task ID\n2. Task Title\n3. Priority (Low/Med/High)\nEnter choice: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        printf("Enter Task ID: ");
        scanf("%d", &id);
        getchar();

        for (int i = 0; i < n; i++)
        {
            if (t[i].id == id)
            {
                printf("\n---------- Task Found ----------\n");
                printf("ID: %d\nTitle: %sDescription: %sDue: %sPriority: %sStatus: %s\n",
                       t[i].id, t[i].title, t[i].description, t[i].dueDate, t[i].priority, t[i].status);
                found = 1;
                break;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter Task Title: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        for (int i = 0; i < n; i++)
        {
            // Trim newline from stored title
            t[i].title[strcspn(t[i].title, "\n")] = '\0';
            if (strstr(t[i].title, input) != NULL)
            {
                printf("\n---------- Task Found ----------\n");
                printf("ID: %d\nTitle: %sDescription: %sDue: %sPriority: %sStatus: %s\n",
                       t[i].id, t[i].title, t[i].description, t[i].dueDate, t[i].priority, t[i].status);
                found = 1;
            }
        }
    }
    else if (choice == 3)
    {
        printf("Enter Priority (Low/Med/High): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        for (int i = 0; i < n; i++)
        {
            t[i].priority[strcspn(t[i].priority, "\n")] = '\0';
            if (strcmp(t[i].priority, input) == 0)
            {
                printf("\n---------- Task Found ----------\n");
                printf("ID: %d\nTitle: %sDescription: %sDue: %sPriority: %sStatus: %s\n",
                       t[i].id, t[i].title, t[i].description, t[i].dueDate, t[i].priority, t[i].status);
                found = 1;
            }
        }
    }
    else
    {
        printf("\nInvalid choice!\n");
        return;
    }

    if (!found)
    {
        printf("\nTask Not Found!\n");
        printf("\nSuggested Tasks:\n");
        int suggested = 0;

        for (int i = 0; i < n && suggested < 5; i++)
        {
            // Trim newlines
            t[i].priority[strcspn(t[i].priority, "\n")] = '\0';
            t[i].status[strcspn(t[i].status, "\n")] = '\0';

            if ((strcmp(t[i].priority, "High") == 0 || strcmp(t[i].priority, "Med") == 0) &&
                strcmp(t[i].status, "pending") == 0)
            {
                printf("ID: %d | Title: %s | Priority: %s | Status: %s\n",
                       t[i].id, t[i].title, t[i].priority, t[i].status);
                suggested++;
            }
        }

        if (suggested == 0)
        {
            printf("No pending high/medium-priority tasks found.\n");
        }
    }
}

// Sort All Tasks
int getPriorityValue(char *priority)
{
    if (strncmp(priority, "High", 4) == 0)
    {
        return 3;
    }
    else if (strncmp(priority, "Med", 3) == 0)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}

void sortTask(struct Task *t, int n)
{
    struct Task tasks[100];
    int totalTasks = loadFromFile(tasks);
    if (n == 0)
    {
        printf("\n No saved tasks found!\n");
        return;
    }

    struct Task temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (getPriorityValue(t[i].priority) < getPriorityValue(t[j].priority))
            {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
    printf("\n Tasks Sorted by Priority!\n");


}


// void updateTask()

void updateTask(){
    
}
int main()
{
    struct Task tasks[100];
    int n = loadFromFile(tasks), choice;

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
            searchTask(tasks, n);
            break;
        case 4:
            sortTask(tasks, n);
            break;
            case 5:
                updateTask();
                break;
            // case 6:
            //     showTaskStatistics();
            //     break;
            // case 7:
            //     deleteTask();
            //     break;

        case 5:
            return 0;
        default:
            printf("\n Invalid option! Try again.\n");
        }
    }
}
