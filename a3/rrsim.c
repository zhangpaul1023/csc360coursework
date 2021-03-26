#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include <stdbool.h>
#define MAX_BUFFER_LEN 80
int tick = 0;
taskval_t *event_list = NULL;
int quantum_count = 0;
int dispatch_count = 0;
bool task_begin = false;
bool task_just_finish = false;
int idle_count = 0;
int wait_total = 0;
int ta_total = 0;
int event_count = 0;
void print_task(taskval_t *t, void *arg) {
    printf("task %03d: %5d %3.2f %3.2f\n",
        t->id,
        t->arrival_time,
        t->cpu_request,
        t->cpu_used
    );  
}


void increment_count(taskval_t *t, void *arg) {
    int *ip;
    ip = (int *)arg;
    (*ip)++;
}

taskval_t *simulate(taskval_t *ready_q, int qlen, int dlen){
    taskval_t *task = peek_front(ready_q);
    if (ready_q != NULL){
        if(dispatch_count < dlen){
            dispatch_count++;
            /*
            printf("[%05d] DISPATCHING", tick);
            printf("\n");
            */
        }
        else{
            if(dispatch_count == dlen){
                if(quantum_count < qlen || task_just_finish == false){
                    if(task->cpu_used >= task->cpu_request){
                        task->finish_time = tick;
                        /*printf("[%05d] id=%05d EXIT w=%.2f ta=%.2d\n", tick, task->id, ((task->finish_time - task->arrival_time) - task->cpu_request), (task->finish_time - task->arrival_time));*/
                        wait_total = wait_total + ((task->finish_time - task->arrival_time) - task->cpu_request);
                        ta_total = ta_total + (task->finish_time - task->arrival_time);
                        ready_q = remove_front(ready_q);
                        task_just_finish = true;
                        quantum_count = 0;
                        tick--;
                    }
                    else{
                        /*printf("[%05d] id=%05d req=%.2f used=%.2f\n", tick, task->id, task->cpu_request, task->cpu_used);*/
                        task->cpu_used++;
                        quantum_count++;
                    }
                }
                if(quantum_count == qlen){
                    taskval_t *task_out = peek_front(ready_q);
                    ready_q = remove_front(ready_q);
                    task_out->next = NULL;
                    ready_q = add_end(ready_q, task_out);
                    quantum_count = 0;
                    dispatch_count = 0;
                }
                if(task_just_finish == true){
                    dispatch_count = 0;
                    quantum_count = 0;
                    task_just_finish = false;
                }
            }
        }
    }
    return ready_q;
}

void run_simulation(int qlen, int dlen) {
    taskval_t *ready_q = NULL;
    taskval_t *tempelh = NULL;
    while (event_list != NULL || ready_q != NULL){
        if (event_list != NULL){
            tempelh = peek_front(event_list);
            if(tempelh->arrival_time == tick) {
                event_count++;
                event_list = remove_front(event_list);
                tempelh->next = NULL;
                ready_q = add_end(ready_q,tempelh);
            }
        }
        char *output = "IDLE";
        if (ready_q == NULL){
            /*printf("[%05d] %s", tick, output);
            printf("\n");
            */
        }

        else{
            ready_q = simulate(ready_q, qlen, dlen);
        }
        tick++;
    }
}


int main(int argc, char *argv[]) {
    char   input_line[MAX_BUFFER_LEN];
    int    i;
    int    task_num;
    int    task_arrival;
    float  task_cpu;
    int    quantum_length = -1;
    int    dispatch_length = -1;
    taskval_t *temp_task;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--quantum") == 0 && i+1 < argc) {
            quantum_length = atoi(argv[i+1]);
        }
        else if (strcmp(argv[i], "--dispatch") == 0 && i+1 < argc) {
            dispatch_length = atoi(argv[i+1]);
        }
    }

    if (quantum_length == -1 || dispatch_length == -1) {
        fprintf(stderr, 
            "usage: %s --quantum <num> --dispatch <num>\n",
            argv[0]);
        exit(1);
    }


    while(fgets(input_line, MAX_BUFFER_LEN, stdin)) {
        sscanf(input_line, "%d %d %f", &task_num, &task_arrival,
            &task_cpu);
        temp_task = new_task();
        temp_task->id = task_num;
        temp_task->arrival_time = task_arrival;
        temp_task->cpu_request = task_cpu;
        temp_task->cpu_used = 0.0;
        event_list = add_end(event_list, temp_task);
    }

/*
#ifdef DEBUG
    int num_events;
    apply(event_list, increment_count, &num_events);
    printf("DEBUG: # of events read into list -- %d\n", num_events);
    printf("DEBUG: value of quantum length -- %d\n", quantum_length);
    printf("DEBUG: value of dispatch length -- %d\n", dispatch_length);
#endif
*/
    run_simulation(quantum_length, dispatch_length);
    printf("%d, %d, %.2f, %.2f\n", dispatch_length, quantum_length, (float)wait_total/event_count, (float)ta_total/event_count);
    return (0);
}
