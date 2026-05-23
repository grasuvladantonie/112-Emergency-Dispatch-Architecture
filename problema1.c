#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    system1 *s = (system1*)malloc(sizeof(system1));
    s->queue_high = (queue_priority*)malloc(sizeof(queue_priority));
    s->queue_high->front = NULL;
    s->queue_high->rear = NULL;

    s->queue_medium = (queue_priority*)malloc(sizeof(queue_priority));
    s->queue_medium->front = NULL;
    s->queue_medium->rear = NULL;

    s->queue_low = (queue_priority*)malloc(sizeof(queue_priority));
    s->queue_low->front = NULL;
    s->queue_low->rear = NULL;
    
    s->queue= (queue_available_units*)malloc(sizeof(queue_available_units));
    s->queue->front = NULL;
    s->queue->rear = NULL;

    s->stack_top = (interventionStackNode*)malloc(sizeof(interventionStackNode));
    s->stack_top = NULL;

    char instructiune[30], priority[7], buffer[256];
    int nr_echipaje, i, N, id_incident;

    s->incidents = santinelaIncident();
    s->interventions = santinelaIntervention();

    FILE *f = fopen("tema1.in", "r");
    FILE *fout = fopen("tema1.out", "a");

    if(f == NULL)
        return 1;

    fscanf(f, "%d", &nr_echipaje);
    fgetc(f);
    s->units = (unit*)malloc(nr_echipaje*sizeof(unit));
    s->queue->size = nr_echipaje;

    for(i = 0; i < nr_echipaje; i++){
        fscanf(f, "%d %c", &s->units[i].id, &s->units[i].type);
        s->units[i].availability = 1;
        enqueueAvailableUnits(s->queue,&s->units[i]);
    }

    fscanf(f, "%d", &N);
    fgetc(f);

    for(i = 0; i < N; i++){
        fscanf(f, "%s", instructiune);
        if(strcmp(instructiune, "ADD_INCIDENT") == 0){
            char c;
            int ct=0;
            fscanf(f, "%d %s", &id_incident, priority);
            fgetc(f);
            fgetc(f);//ia prima ghilimea
            while((c = fgetc(f)) != EOF && c != '"'){
                buffer[ct++] = c;
            }
            buffer[ct] = '\0';
            incident *inc = addIncident(s->incidents, id_incident, buffer, priority);
            if(strcmp(priority, "high") == 0)
                enqueueIncident(s->queue_high, inc);
            else if(strcmp(priority, "medium") == 0)
                enqueueIncident(s->queue_medium, inc);
            else if(strcmp(priority, "low") == 0)
                enqueueIncident(s->queue_low, inc);
        }
        else if(strcmp(instructiune, "CHECK_UNITS_AVAILABILITY") == 0){
            fprintf(fout, "Number of available units: %d", s->queue->size);
        }
        else if(strcmp(instructiune, "DISPATCH") == 0){
            if(s->queue != NULL){
                incident *inc = NULL;
                if(s->queue_high != NULL)
                    inc = dequeueIncident(s->queue_high);
                else if(s->queue_medium != NULL)
                    inc = dequeueIncident(s->queue_medium);
                else if(s->queue_low != NULL)
                    inc = dequeueIncident(s->queue_low);
                
                if(s->queue != NULL){
                    unit *uni = dequeueAvailableUnits(s->queue);
                    intervention *inter = addIntervention(s->interventions, uni, inc);
                    push(&(s->stack_top), inter);
                }
            }
        }
        else if(strcmp(instructiune, "UNDO_LAST_DISPATCH") == 0){
            
        }
    }
    return 0;
}
