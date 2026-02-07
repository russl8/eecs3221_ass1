/**
 * Russell Liu, 219616150
 * FCFS Scheduler
 * Citations of external code snippets:
 *   - None
 */
#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "list.h"

// initialize id counter to keep track of tid
int id_counter = 0;

struct node *head = NULL;
// adds a task to the linked list
void add(char *name, int priority, int burst)
{
    Task *t = malloc(sizeof(Task));
    t->name = name;
    t->priority = priority;
    t->burst = burst;
    t->tid = id_counter++;
    // printf(" %s",name);
    insert(&head, t);
}

// get tasks in an array
Task **get_tasks_in_array()
{
    // array of task pointers
    Task **taskArray = malloc(id_counter * sizeof(Task *));
    struct node *temp = head;

    int i = 0;
    while (temp != NULL)
    {
        taskArray[i] = temp->task;
        temp = temp->next;
        i++;
    }
    return taskArray;
}

// mergesort
Task **sort(Task **taskArray, int size)
{

    if (size <= 1)
    {
        return taskArray;
    }
    int half, sizeA, sizeB;

    half = size / 2;
    sizeA = half;
    sizeB = size - half;

    // split task array into 2 smaller arrays
    Task **a = malloc(sizeA * sizeof(Task *));

    for (int i = 0; i < sizeA; i++)
    {
        a[i] = taskArray[i];
    }

    Task **b = malloc(sizeB * sizeof(Task *));
    for (int i = 0; i < sizeB; i++)
    {
        b[i] = taskArray[sizeA + i];
    }

    // printf("\n\n");
    a = sort(a, sizeA);
    b = sort(b, sizeB);

    // merge a and b
    Task **merged = malloc(size * sizeof(Task *));
    int l = 0, r = 0;
    int i = 0;
    while (l < sizeA && r < sizeB)
    {
        if (a[l]->burst < b[r]->burst)
        {
            merged[i] = a[l];
            l++;
        }
        else
        {
            merged[i] = b[r];
            r++;
        }
        i++;
    }
    while (l < sizeA)
    {
        merged[i] = a[l];
        l++;
        i++;
    }
    while (r < sizeB)
    {
        merged[i] = b[r];
        r++;
        i++;
    }
    free(a);
    free(b);
    return merged;
}

void schedule()
{
    int arraySize = id_counter;
    Task **taskArray = get_tasks_in_array();

    // sort task array based on task->burst
    taskArray = sort(taskArray, arraySize);

    float turnaround = 0, waiting = 0, response = 0;
    float totalTurnaround = 0, totalWaiting = 0, totalResponse = 0;
    /**
     * for each element in taskArray, process like we do in fcfs
     */
    for (int i = 0; i < arraySize; i++)
    {
        // printf("\n %d ",taskArray[i]->burst);
        int burst = taskArray[i]->burst;

        totalWaiting += waiting;
        waiting += burst;

        turnaround += burst;
        totalTurnaround += turnaround;

        totalResponse += response;
        response += burst;

        printf("Running task = [%s] [%d] [%d] for %d units.\n", taskArray[i]->name, taskArray[i]->priority, taskArray[i]->burst, taskArray[i]->burst);
    }

    float average_waiting_time = totalWaiting / arraySize;
    float average_response_time = totalResponse / arraySize;
    float average_turnaround_time = totalTurnaround / arraySize;
    printf("\nAverage waiting time = %.2lf\n", average_waiting_time);
    printf("Average turnaround time = %.2lf\n", average_turnaround_time);
    printf("Average response time = %.2lf\n", average_response_time);
}
