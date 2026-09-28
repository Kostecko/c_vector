#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* array;
    size_t size;
    size_t capacity;

}vector;

vector* vecCreate();
void vecPushBack(vector* v, int n);
void vecPopBack(vector* v);
size_t vecGetSize(const vector* v);
int vecAt(const vector* v, size_t index);
void vecReserve(vector* v, size_t new_cap);
void vecDestroy(vector* v);

#endif