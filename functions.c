#include "functions.h"

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

typedef struct interventionStackNode{
    struct intervention *intervention;
    struct interventionStackNode *next;
}interventionStackNode;

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

incident *santinelaIncident(){
    incident *santinela = (incident*)malloc(sizeof(incident));
    santinela->next = santinela;
    santinela->prev = santinela;
    santinela->id = 0;
    strcpy(santinela->priority, "low");
    santinela->description = (char*)malloc(14*sizeof(char));
    strcpy(santinela->description, "test incident");
    strcpy(santinela->status, "solved");
    return santinela;
}

intervention *santinelaIntervention(){
    intervention *santinela = (intervention*)malloc(sizeof(intervention));
    santinela->next = santinela;
    santinela->prev = santinela;
    santinela->incident = NULL;
    santinela->unit = NULL;
    return santinela;
}

incident *addIncident(incident *santinela, int id, char *des, char pri[7]){
    incident *newIncident = (incident*)malloc(sizeof(incident));
    newIncident->id = id;
    strcpy(newIncident->priority, pri);
    newIncident->description = (char*)malloc((strlen(des)+1)*sizeof(char));
    strcpy(newIncident->description, des);
    strcpy(newIncident->status, "queued");
    incident *last = santinela->prev;
    newIncident->next = santinela;
    newIncident->prev = last;
    last->next = newIncident;
    santinela->prev = newIncident;
    return newIncident;
}

intervention* addIntervention(intervention *santinela, unit *unit, incident *incident){
    intervention *newIntervention = (intervention*)malloc(sizeof(intervention));
    newIntervention->unit = unit;
    newIntervention->incident = incident;
    intervention *last = santinela->prev;
    newIntervention->next = santinela;
    newIntervention->prev = last;
    last->next = newIntervention;
    santinela->prev = newIntervention;
    unit->availability=0;
    strcpy(incident->status, "intervened");
    return newIntervention;
}

void enqueueIncident(queue_priority *q, incident *i){
    queuePriorityNode *nod = (queuePriorityNode*)malloc(sizeof(queuePriorityNode));
    nod->incident = i;
    nod->next = NULL;
    if(q->front !=NULL && q->rear !=NULL){
        q->rear->next = nod;
        q->rear = nod;
    }
    else{
        q->front = nod;
        q->rear = nod;
    }
    q->size++;
}

void enqueueAvailableUnits(queue_available_units *q, unit *i){
    queueAvailableNode *nod = (queueAvailableNode*)malloc(sizeof(queueAvailableNode));
    nod->unit = i;
    nod->next = NULL;
    if(q->front !=NULL && q->rear !=NULL){
        q->rear->next = nod;
        q->rear = nod;
    }
    else{
        q->front = nod;
        q->rear = nod;
    }
}

unit* dequeueAvailableUnits(queue_available_units *q){
    if(q->front == NULL )
        return NULL;
    queueAvailableNode *temp = q->front;
    unit *u = temp->unit;
    q->front = q->front->next;
    if(q->front == NULL)
        q->rear = NULL;
    free(temp);
    q->size--;
    return u;
}

incident* dequeueIncident(queue_priority *p){
    if(p->front == NULL)
        return NULL;
    queuePriorityNode *temp = p->front;
    incident *i = temp->incident;
    p->front = p->front->next;
    if(p->front == NULL)
        p->rear = NULL;
    free(temp);
    p->size--;
    return p;
}

void push(interventionStackNode **stack_top, intervention *intervention){
    interventionStackNode *newIntervention = (interventionStackNode*)malloc(sizeof(interventionStackNode));
    newIntervention->intervention = intervention;
    newIntervention->next = *stack_top;
    *stack_top = newIntervention;
}

intervention* pop(interventionStackNode **stack_top){
    intervention *inter = *stack_top;
    
}
