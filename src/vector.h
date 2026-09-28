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
void vecDestroy(vector* v);

int* vecAt(const vector* v, size_t index);
int* vecFront(vector* v);
int* vecBack(vector* v);
int* vecData(vector* v);
int vecIsEmpty(vector* v);
size_t vecGetSize(const vector* v);
void vecReserve(vector* v, size_t new_cap);
size_t vecGetCapacity(vector* v);
void vecShrinkToFit(vector* v);
void vecClear(vector* v);
void insert(vector* v, int* pos, size_t count, int value);
//insert range
//emplace
//erease
void vecPushBack(vector* v, int n);
//emplace back
//appedn range
void vecPopBack(vector* v);
void vecResize(vector* v, size_t new_size, int value);
//swap






#endif