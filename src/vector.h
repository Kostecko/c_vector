#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct{
    int* array;
    size_t size;
    size_t capacity;

}vector;


vector* vecCreate(void);
void vecDestroy(vector* v);

int* vecAt(const vector* v, size_t index);
int* vecFront(const vector* v);
int* vecBack(const vector* v);
int* vecData(const vector* v);
int* vecBegin(const vector* v);
int* vecEnd(const vector* v);
int vecIsEmpty(const vector* v);
size_t vecSize(const vector* v);
void vecReserve(vector* v, size_t new_cap);
size_t vecCapacity(const vector* v);
void vecShrinkToFit(vector* v);
void vecClear(vector* v);
void vecInsert(vector* v, int* pos, size_t count, int value);
void vecInsertRange(vector* v, int* pos, size_t count, const int* rg);
void vecEmplace(vector* v, int* pos, int value);
void vecErase(vector* v, int* pos);
void vecEraseRange(vector* v, int* first, int* last);
void vecPushBack(vector* v, int n);
void vecEmplaceBack(vector*v, int value);
void vecAppendRange(vector* v, size_t count, const int* rg);
void vecPopBack(vector* v);
void vecResize(vector* v, size_t new_size, int value);
void vecSwap(vector* v, vector* other);






#endif