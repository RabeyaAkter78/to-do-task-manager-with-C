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
    while (fscanf(fp, "ID = %d\n", &t[count].id) == 1)
    {
        fgets(t[count].title, sizeof(t[count].title), fp);
        t[count].title[strcspn(t[count].title, "\n")] = '\0';

        fgets(t[count].description, sizeof(t[count].description), fp);
        t[count].description[strcspn(t[count].description, "\n")] = '\0';

        fgets(t[count].startTime, sizeof(t[count].startTime), fp);
        t[count].startTime[strcspn(t[count].startTime, "\n")] = '\0';

        fgets(t[count].endTime, sizeof(t[count].endTime), fp);
        t[count].endTime[strcspn(t[count].endTime, "\n")] = '\0';

        fgets(t[count].dueDate, sizeof(t[count].dueDate), fp);
        t[count].dueDate[strcspn(t[count].dueDate, "\n")] = '\0';

        fgets(t[count].priority, sizeof(t[count].priority), fp);
        t[count].priority[strcspn(t[count].priority, "\n")] = '\0';

        fgets(t[count].status, sizeof(t[count].status), fp);
        t[count].status[strcspn(t[count].status, "\n")] = '\0';

        char sep[10];
        fgets(sep, sizeof(sep), fp); // skip "---"

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
    // int newId;
    // printf("\n Enter Task ID: ");
    // scanf("%d", &newId);
    // getchar();

    // for (int i = 0; i < *n; i++)
    // {
    //     if (t[i].id == newId)
    //     {
    //         printf("\n Task ID already exists!\n");
    //         return;
    //     }
    // }

    t[*n].id = (*n) + 1;
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

void updateTask(struct Task *t, int n)
{
    int index = -1;
    int id;

    printf("\nEnter Task ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < n; i++)
    {
        if (t[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("\nTask Not Found!\n");
        return;
    }

    printf("\nTask Found: ID=%d, Title=%s", t[index].id, t[index].title);

    char ans[5];

    // Update Title
    printf("\nUpdate Title? (Y/N): ");
    fgets(ans, sizeof(ans), stdin);
    if (ans[0] == 'Y' || ans[0] == 'y')
    {
        printf("Enter New Title: ");
        fgets(t[index].title, sizeof(t[index].title), stdin);
    }

    // Update End Date
    printf("Update End Date? (Y/N): ");
    fgets(ans, sizeof(ans), stdin);
    if (ans[0] == 'Y' || ans[0] == 'y')
    {
        printf("Enter New End Date: ");
        fgets(t[index].endTime, sizeof(t[index].endTime), stdin);
    }

    // Update Status
    printf("Update Status? (Y/N): ");
    fgets(ans, sizeof(ans), stdin);
    if (ans[0] == 'Y' || ans[0] == 'y')
    {
        printf("Enter New Status (Pending/Completed): ");
        fgets(t[index].status, sizeof(t[index].status), stdin);
    }

    // Save updated tasks back to file
    FILE *fp = fopen("task.txt", "w");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "ID = %d\n", t[i].id);
        fprintf(fp, "Title = %s", t[i].title);
        fprintf(fp, "Description = %s", t[i].description);
        fprintf(fp, "Start = %s", t[i].startTime);
        fprintf(fp, "End = %s", t[i].endTime);
        fprintf(fp, "Due Date = %s", t[i].dueDate);
        fprintf(fp, "Priority = %s", t[i].priority);
        fprintf(fp, "Status = %s", t[i].status);
        fprintf(fp, "---\n");
    }

    fclose(fp);
    printf("\nTask Updated Successfully and saved to file!\n");
}
// delete tasks
void deleteTask(struct Task *t, int *n)
{
    int id, index = -1;
    printf("\nEnter Task ID to Delete: ");
    scanf("%d", &id);

    // Find the task index
    for (int i = 0; i < *n; i++)
    {
        if (t[i].id == id)
        {
            index = i;
            break;
        }
        t[i].id = i + 1;
    }

    if (index == -1)
    {
        printf("\n Task Not Found!\n");
        return;
    }

    for (int i = index; i < *n - 1; i++)
    {
        t[i] = t[i + 1];
    }

    (*n)--;

    for (int i = 0; i < *n; i++)
    {
        t[i].id = i + 1;
    }

    FILE *fp = fopen("task.txt", "w");
    if (!fp)
    {
        printf("\nError opening file!\n");
        return;
    }

    for (int i = 0; i < *n; i++)
    {
        fprintf(fp, "ID = %d\n", t[i].id);
        fprintf(fp, "Title = %s\n", t[i].title);
        fprintf(fp, "Description = %s\n", t[i].description);
        fprintf(fp, "Start = %s\n", t[i].startTime);
        fprintf(fp, "End = %s\n", t[i].endTime);
        fprintf(fp, "Due Date = %s\n", t[i].dueDate);
        fprintf(fp, "Priority = %s\n", t[i].priority);
        fprintf(fp, "Status = %s\n", t[i].status);
        fprintf(fp, "---\n");
    }

    fclose(fp);

    printf("\n Task Deleted Successfully!\n");
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
        // printf("[6] Show Task Statistics\n");
        printf("[6] Delete Tasks\n");
        printf("[7] Exit\n");
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
            updateTask(tasks, n);
            break;
        // case 6:
        //     showTaskStatistics();
        //     break;
        case 6:
            deleteTask(tasks, &n);
            break;

        case 7:
            return 0;
        default:
            printf("\n Invalid option! Try again.\n");
        }
    }
}
