#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef const int* const ciptrc;

typedef struct{
    int* array;
    size_t size;
    size_t capacity;

}vector;


vector* vecCreate(void);
void vecDestroy(vector* v);

ciptrc vecAt(const vector* v, const size_t index);
ciptrc vecFront(const vector* v);
ciptrc vecBack(const vector* v);
ciptrc vecData(const vector* v);
ciptrc vecBegin(const vector* v);
ciptrc vecEnd(const vector* v);
int vecEmpty(const vector* v);
size_t vecSize(const vector* v);
void vecReserve(vector* v, const size_t new_cap);
size_t vecCapacity(const vector* v);
void vecShrinkToFit(vector* v);
void vecClear(vector* v);
void vecInsert(vector* v, const size_t index, const size_t count, const int value);
void vecInsertRange(vector* v, const size_t index, const size_t count, ciptrc rg);
void vecEmplace(vector* v, const size_t index, const int value);
void vecErase(vector* v, const size_t index);
void vecEraseRange(vector* v, const size_t first, const size_t last);
void vecPushBack(vector* v, const int value);
void vecEmplaceBack(vector*v, const int value);
void vecAppendRange(vector* v, const size_t count, ciptrc rg);
void vecPopBack(vector* v);
void vecResize(vector* v, const size_t new_size, const int value);
void vecSwap(vector* v, vector* other);


#endif