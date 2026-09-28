#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* array;
    size_t size;
    size_t capacity;

}vector;

vector* vCreate();
void vPushBack(vector* v, int n);
void vPopBack(vector* v);
size_t vGetSize(const vector* v);
int vAt(const vector* v, size_t index);
//void vClear(vector* v);
void vReserve(vector* v, size_t new_cap);
//void vInsert(vector* v, size_t pos, int n);
void vDestroy(vector* v);

#endif