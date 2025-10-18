#include "animation.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_queue(CharQueue* q){
    q->queueSize = 0;
    q->front = NULL;
}

void enqueue(CharQueue* q, char* text){

    CharQueueNode* c = (CharQueueNode*)malloc(sizeof(CharQueueNode));
    c->next = NULL;
    c->data = malloc(sizeof(text));
    strcpy(c->data, text);

    if(q->queueSize <= 0){
        q->front = c;
    }
    else{
        CharQueueNode* p = q->front;
        while(p->next != NULL){
            p = p->next;
        }
        p->next = c;
    }
    q->queueSize++;
}

char* dequeue(CharQueue* q){
    if(q->queueSize == 0){
        return NULL;
    }
    CharQueueNode* c = q->front;
    q->front = c->next;
    char* text = malloc(sizeof(c->data));
    strcpy(text, c->data);
    free(c);
    q->queueSize--;
    return text;
}

char* peek(CharQueue* q){
    if(q->queueSize == 0){
        return NULL;
    }
    return q->front->data;
}

int init_animation(const char* ansqPath){
    CharQueue key;
    CharQueue value;
    init_queue(&key);
    init_queue(&value);

    FILE* ansq = fopen(ansqPath, "r");
    while(!feof(ansq)){
        char text[1024];
        fscanf(ansq, " %[^:]", text);
        enqueue(&key, text);
        fscanf(ansq, " %[^;]", text);
        enqueue(&value, text);
    }
    // while(key.queueSize != 0){
    //     printf("%s", dequeue(&key));
    // }
    while(value.queueSize != 0){
        printf("%s", dequeue(&value));
        printf("\n");
    }
    
    fclose(ansq);
    return 0;
}
int destroy_animation(const char* name){
    return 0;
}