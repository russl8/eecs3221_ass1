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

// init head object
struct node *head = NULL;

// adds a task to the linked list
void add(char *name, int priority, int burst)
{
    // create a pointer to the struct task
    Task *t = malloc(sizeof(Task));
    t->name = name;
    t->burst = burst;
    t->priority = priority;
    t->tid = id_counter++;

    // add task to linked list.
    insert(&head, t);
}

// returns a list of task pointers of size id_counter
Task **get_tasks()
{
    Task **tasks = malloc(sizeof(Task*) * id_counter);

    for (int i = id_counter - 1; i >= 0; i--)
    {
        tasks[i] = head->task;
        struct node *prev= head;
        head = head->next;
        free(prev);
    }

    return tasks;
}

void schedule()
{
    int number_of_tasks = id_counter;
    /**
     *
     * strategy:
     * - add everything to one list (nothing fancy needed)
     * - process them in the order they were added.
     */
    Task **tasks = get_tasks(); // list of node pointers
    float total_burst=0;
    float total_waiting_time=0, total_turnaround=0;
    for (int i = 0; i < number_of_tasks; i++)
    {   
        // waiting time: time from beginning -> start processing task.
        // wt[0] == 0, wt[1] = wt[i-1] + burst[0]

        // turnaround_time = time it took from beginning -> end processing task.
        // turnaround[0] = burst[0], turnaround[1] = burst[0] + burst[1]

        // response time: time from beginning -> start processing task.
        // same as waiting time

        int burst = tasks[i]->burst;
        printf("Running task = [%s] [%d] [%d] for %d units.\n", tasks[i]->name, tasks[i]->priority, tasks[i]->burst, tasks[i]->burst);

        total_waiting_time += total_burst;
        total_burst += burst;

        total_turnaround += total_burst;
        free(tasks[i]); // no longer using task. free
        tasks[i]=NULL;
    }
    free(tasks); 
    tasks=NULL;


    float average_waiting_time = total_waiting_time / number_of_tasks;
    float average_turnaround_time = total_turnaround/ number_of_tasks;
    printf("\nAverage waiting time = %.2lf\n", average_waiting_time);
    printf("Average turnaround time = %.2lf\n", average_turnaround_time);
    printf("Average response time = %.2lf\n", average_waiting_time);

}

