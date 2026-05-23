#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct unit{
    int id;
    char type;
    int availability;
}unit;

typedef struct incident{
    int id;
    char priority[7];
    char *description;
    char status[11];
    struct incident *prev;
    struct incident *next;
}incident;

typedef struct intervention{
    struct incident *incident;
    struct unit *unit;
    struct intervention *prev;
    struct intervention *next;
}intervention;

typedef struct queuePriorityNode{
    struct incident *incident;
    struct queuePriorityNode *next;
}queuePriorityNode;

typedef struct queue_priority{
    struct queuePriorityNode *front;
    struct queuePriorityNode *rear;
    int size;
}queue_priority;

typedef struct queueAvailableNode{
    struct unit *unit;
    struct queueAvailableNode *next;
}queueAvailableNode;

typedef struct queue_available_units{
    struct queueAvailableNode *front;
    struct queueAvailableNode *rear;
    int size;
}queue_available_units;

typedef struct system1{
    struct unit *units;
    struct incident *incidents;
    struct intervention *interventions;
    struct queue_priority *queue_high;
    struct queue_priority *queue_medium;
    struct queue_priority *queue_low;
    struct queue_available_units *queue;
    struct interventionStackNode *stack_top;
}system1;

typedef struct interventionStackNode{
    struct intervention *intervention;
    struct interventionStackNode *next;
}interventionStackNode;

incident *santinelaIncident();
intervention *santinelaIntervention();
incident *addIncident(incident *santinela, int id, char *des, char pri[7]);
intervention *addIntervention(intervention *santinela, unit *unit, incident *incident);
void enqueueIncident(queue_priority *q, incident *i);
void enqueueAvailableUnits(queue_available_units *q, unit *i);
unit* dequeueAvailableUnits(queue_available_units *q);
incident* dequeueIncident(queue_priority *p);
void push();

#endif