#include "vector.h"

vector* vCreate(){
    vector* v = malloc(sizeof *v);

    if(v == NULL) return NULL;

    v->array = NULL;
    v->capacity = 0;
    v->size = 0;

    return v;
}

void vPushBack(vector* v, int n){
    if(v->array == NULL){
        v->array = malloc(sizeof n);
        if(v->array == NULL){
            printf("Allocating memory failed! Returned NULL\n");
            return;
        }
        v->capacity = 1;
    }

    else if(v->size == v->capacity){
        int* new_arr = realloc(v->array, v->capacity * sizeof n);
        
        if(new_arr == NULL){
            printf("Reallocating memory failed! Returned NULL");
            return;
        }

        v->capacity *= 2;
        v->array = new_arr;
    }
    *(v->array + v->size++) = n;
}

void vPopBack(vector* v){
    if(v->size > 0) v->size--;
    else printf("Vector is empty!");
}

size_t vGetSize(const vector* v){
    return v->size;
}

//void vClear(vector* v){}

int vAt(const vector* v, size_t index){
    if(index >= v->size){
        printf("Index out of range! Are you crazy? Index: ");
        return index;
    }
    return v->array[index];
}

void vReserve(vector*v, size_t new_cap){
    if(new_cap <= v->capacity) return;

    int* new_arr = realloc(v->array, new_cap * sizeof(int));
    
    if(new_arr == NULL){
        printf("Reallocating memory failed! Returned NULL");
        return;
    }

    v->capacity = new_cap;
    v->array = new_arr;
}

//void vInsert(vector* v, size_t pos, int n){}

void vDestroy(vector* v){
    free(v->array);
    free(v);
}

