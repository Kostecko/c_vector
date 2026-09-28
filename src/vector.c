#include "vector.h"


vector* vecCreate(void){
    vector* v = malloc(sizeof *v);

    if(v == NULL) return NULL;

    v->array = NULL;
    v->capacity = 0;
    v->size = 0;

    return v;
}

void vecDestroy(vector* v){
    if(v==NULL) return;
    free(v->array);
    free(v);
}


int* vecAt(const vector* v, size_t index){
    if(v==NULL) return NULL;
    if(index >= v->size){
        printf("Index out of range! Are you crazy?\n");
        return NULL;
    }
    return &(v->array[index]);
}

int* vecFront(const vector* v){
    if(v == NULL) return NULL;
    if(v->size == 0) return NULL;
    return v->array;
}

int* vecBack(const vector* v){
    if(v == NULL) return NULL;
    if(v->size == 0) return NULL;
    return v->array+(v->size-1);
}

int* vecData(const vector* v){
    if(v==NULL) return NULL;
    return v->array;
}

int vecIsEmpty(const vector* v){
    if(v == NULL) return 1;
    if(v->size == 0) return 1;
    return 0;
}

size_t vecGetSize(const vector* v){
    if(v==NULL){
        printf("vector uninitialized\n");
        return 0;
    }
    
    return v->size;
}

void vecReserve(vector*v, size_t new_cap){
    if(new_cap <= v->capacity) return;

    int* new_arr = realloc(v->array, new_cap * sizeof *v->array);
    
    if(new_arr == NULL){
        printf("Reallocating memory failed! Returned NULL\n");
        return;
    }

    v->capacity = new_cap;
    v->array = new_arr;
}

size_t vecGetCapacity(const vector* v){
    if(v==NULL) return;
    return v->capacity;
}

void vecShrinkToFit(vector* v){
    if(v == NULL)return;
    if(v->size == v->capacity || v->size == 0) return;
    size_t new_cap = v->size;

    int* new_arr = realloc(v->array, new_cap*sizeof *new_arr);
    if(new_arr == NULL) return;

    v->array = new_arr;
    v->capacity = new_cap;
}

void vecClear(vector* v){
    if(v == NULL) return;
    if(v->size == 0) return;

    v->size = 0;
}

void vecInsert(vector* v, int* pos, size_t count, int value){
    if(v == NULL || count == 0) return;

    size_t new_space_index;

    if(v->size == 0) new_space_index = 0;
    else{
        if(pos == NULL) return;
        new_space_index = pos - v->array;
        if(new_space_index > v->size) return;
    }

    if(v->size + count > v->capacity){
        size_t new_cap = v->capacity * 2;
        if(new_cap < v->size + count) new_cap = v->size + count;

        int* new_arr = realloc(v->array, new_cap * sizeof *new_arr);
        
        if(new_arr==NULL) return;

        v->array = new_arr;
        v->capacity = new_cap;
    }

    pos = v->array + new_space_index;
    
    memmove(pos + count, pos, (v->size - new_space_index) * sizeof *v->array);
    
    for(size_t i = 0; i < count; i++)
        v->array[new_space_index+i] = value;
        
    v->size += count;
}

//insert range, emplace, erease

void vecPushBack(vector* v, int n){
    if(v==NULL) return;
    if(v->array == NULL){
        v->array = malloc(sizeof n);
        if(v->array == NULL){
            printf("Allocating memory failed! Returned NULL\n");
            return;
        }
        v->capacity = 1;
    }

    else if(v->size == v->capacity){
        size_t new_cap = v->capacity*2;

        int* new_arr = realloc(v->array, new_cap * sizeof *new_arr);
        
        if(new_arr == NULL){
            printf("Reallocating memory failed! Returned NULL\n");
            return;
        }

        v->capacity = new_cap;
        v->array = new_arr;
    }
    *(v->array + v->size++) = n;
}

//emplace back, append reange

void vecPopBack(vector* v){
    if(v==NULL) return;
    if(v->size > 0) v->size--;
    else printf("Vector is empty!\n");
}

void vecResize(vector* v, size_t new_size, int value){
    if(v == NULL) return;
    if(new_size == v->size) return;

    if(new_size < v->size){
        v->size = new_size;
        return;
    }

    if(new_size > v->capacity){
        size_t new_cap = v->capacity + new_size;

        int* new_arr = realloc(v->array, new_cap * sizeof *new_arr);
        if(new_arr == NULL){
            printf("Reallocating memory failed! Returned NULL\n");
            return;
        }
        v->array = new_arr;
        v->capacity = new_cap;
    }
    
    for(size_t i = v->size; i<new_size;i++) *(v->array + i) = value;
    
    v->size = new_size;
}

//swap

