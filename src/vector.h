#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* array;
    size_t size;
    size_t capacity;

}vector;

typedef struct{
    vector* v;
    size_t new_size;
    int value;
} VEC_INTERNAL_RES_ARGS;

int VEC_INTERNAL_VAR_RES(VEC_INTERNAL_RES_ARGS in);


vector* vecCreate();
void vecPushBack(vector* v, int n);
void vecPopBack(vector* v);
size_t vecGetSize(const vector* v);
int vecAt(const vector* v, size_t index);
void vecReserve(vector* v, size_t new_cap);
void vecDestroy(vector* v);
#define vecResize(vec, size, ...) \
    VEC_INTERNAL_VAR_RES((VEC_INTERNAL_RES_ARGS){.v = (vec), .new_size = (size), __VA_ARGS__})

#endif