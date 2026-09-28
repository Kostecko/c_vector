#include "vector.h"

//INTERNAL

static int VEC_INTERNAL_RESIZE_BASE(vector* v, size_t new_size, int value){
    if(new_size == v->size) return new_size;
    if(new_size < v->size){
        v->size = new_size;
        return new_size;
    }
    if(new_size > v->capacity){
        size_t new_capacity = v->capacity + new_size;

        int* new_arr = realloc(v->array, new_capacity * sizeof *new_arr);
        if(new_arr == NULL){
            printf("Reallocating memory failed! Returned NULL\n");
            return 0;
        }
        v->array = new_arr;
        v->capacity = new_capacity;
    }
    
    for(size_t i = v->size; i<new_size;i++) *(v->array + i) = value;
    
    v->size = new_size;
    return new_size;
}

int VEC_INTERNAL_VAR_RES(VEC_INTERNAL_RES_ARGS in){
    vector* vec_out = in.v ? in.v : NULL;
    size_t size_out = in.new_size ? in.new_size : (vec_out ? vec_out->size : 0);
    int value_out = in.value ? in.value : 0;

    return VEC_INTERNAL_RESIZE_BASE(vec_out,size_out,value_out);
}


//EXTERNAL

vector* vecCreate(){
    vector* v = malloc(sizeof *v);

    if(v == NULL) return NULL;

    v->array = NULL;
    v->capacity = 0;
    v->size = 0;

    return v;
}

void vecPushBack(vector* v, int n){
    if(v->array == NULL){
        v->array = malloc(sizeof n);
        if(v->array == NULL){
            printf("Allocating memory failed! Returned NULL\n");
            return;
        }
        v->capacity = 1;
    }

    else if(v->size == v->capacity){
        size_t new_capacity = v->capacity*2;
        int* new_arr = realloc(v->array, new_capacity * sizeof *new_arr);
        
        if(new_arr == NULL){
            printf("Reallocating memory failed! Returned NULL\n");
            return;
        }

        v->capacity = new_capacity;
        v->array = new_arr;
    }
    *(v->array + v->size++) = n;
}

void vecPopBack(vector* v){
    if(v->size > 0) v->size--;
    else printf("Vector is empty!\n");
}

size_t vecGetSize(const vector* v){
    return v->size;
}

int vecAt(const vector* v, size_t index){
    if(index >= v->size){
        printf("Index out of range! Are you crazy?\n");
        return 0;
    }
    return v->array[index];
}

void vecReserve(vector*v, size_t new_cap){
    if(new_cap <= v->capacity) return;

    int* new_arr = realloc(v->array, new_cap * sizeof(int));
    
    if(new_arr == NULL){
        printf("Reallocating memory failed! Returned NULL\n");
        return;
    }

    v->capacity = new_cap;
    v->array = new_arr;
}

void vecDestroy(vector* v){
    free(v->array);
    free(v);
}

