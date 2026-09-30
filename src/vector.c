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

int* vecBegin(const vector* v){
    if(v==NULL) return NULL;
    return v->array;
}

int* vecEnd(const vector* v){
    if(v == NULL || v->array == NULL) return NULL;
    return v->array+v->size;
}

int vecIsEmpty(const vector* v){
    if(v == NULL) return 1;
    if(v->size == 0) return 1;
    return 0;
}

size_t vecSize(const vector* v){
    if(v==NULL){
        printf("vector uninitialized\n");
        return 0;
    }
    
    return v->size;
}

void vecReserve(vector*v, size_t new_cap){
    if(v == NULL) return;
    if(new_cap <= v->capacity) return;

    int* new_arr = realloc(v->array, new_cap * sizeof *v->array);
    
    if(new_arr == NULL){
        printf("Reallocating memory failed! Returned NULL\n");
        return;
    }

    v->capacity = new_cap;
    v->array = new_arr;
}

size_t vecCapacity(const vector* v){
    if(v == NULL) return 0;
    return v->capacity;
}

void vecShrinkToFit(vector* v){
    if(v == NULL)return;
    if(v->size == v->capacity) return;
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

    size_t index;

    if(v->size == 0) index = 0;
    else{
        if(pos == NULL) return;
        index = pos - v->array;
        if(index > v->size) return;
    }

    if(v->size + count > v->capacity){
        size_t new_cap = v->capacity * 2;
        if(new_cap < v->size + count) new_cap = v->size + count;

        int* new_arr = realloc(v->array, new_cap * sizeof *new_arr);
        
        if(new_arr==NULL) return;

        v->array = new_arr;
        v->capacity = new_cap;
    }

    pos = v->array + index;
    
    memmove(pos + count, pos, (v->size - index) * sizeof *v->array);

    for(size_t i = 0; i < count; i++)
        v->array[index+i] = value;
        
    v->size += count;
}

void vecInsertRange(vector* v, int* pos, size_t count, const int* rg){
    if(v ==  NULL || count == 0 || rg == NULL) return;

    //poprawic rg jako v

    size_t index;

    if(v->size == 0) index = 0;
    else{
        if(pos == NULL) return;
        index = pos - v->array;
        if(index > v->size) return;
    }

    if(v->size+count > v->capacity){
        size_t new_cap = v->capacity *2;
        if(new_cap < v->size + count) new_cap = v->size + count;

        int* new_arr = realloc(v->array, new_cap * sizeof *v->array);
        
        if(new_arr == NULL) return;

        v->array = new_arr;
        v->capacity = new_cap;
    }

    pos = v->array + index;

    memmove(pos+count, pos, (v->size - index) * sizeof *v->array);

    for(size_t i=0;i<count;i++)
        v->array[i+index] = rg[i];
    v->size += count;
}

void vecEmplace(vector* v, int* pos, int value){
    if(v == NULL) return;

    if(v->array == NULL){
        v->array = malloc(sizeof *v->array);
        if(v->array == NULL)return;
        v->capacity = 1;
    }

    size_t index;

    if(v->size==0)index=0;
    else{
        if(pos == NULL) return;
        index = pos - v->array;
        if(index > v->size) return;
    }

    if(v->size == v->capacity){
        size_t new_cap = v->capacity * 2;
        int* new_arr = realloc(v->array, new_cap * sizeof*v->array);

        if(new_arr == NULL) return;

        v->capacity = new_cap;
        v->array = new_arr;
    }

    pos = v->array + index;

    memmove(pos + (size_t)1, pos, (v->size - index) * sizeof *v->array);

    v->array[index] = value;
    v->size += 1;
}

void vecErase(vector* v, int* pos){
    if(v == NULL || v->array == NULL || pos == NULL || v->size == 0) return;

    size_t index = pos - v->array;
    if(index >= v->size) return;

    size_t len = v->size - index - 1;

    memmove(pos, pos+1, len * sizeof *v->array);
    v->size-=1;
}

void vecEraseRange(vector* v, int* first, int* last){
    if(v == NULL || first == NULL || last == NULL || last < first) return;
    
    size_t len = last - first + 1;

    if(len == 0) return;
    if(len == 1){
        vecErase(v, first);
        return;
    }

    if(last == (v->array + v->size-1)){
        v->size -= len;
        return;
    }

    size_t lentomove = v->array+v->size-1 - last;

    memmove(first, last+1, lentomove * sizeof *v->array);
    v->size -= len;
}

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

void vecEmplaceBack(vector* v, int value){
    vecPushBack(v, value);
}

void vecAppendRange(vector* v, size_t count, const int* rg){
    vecInsertRange(v, vecEnd(v), count, rg);
}

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

void vecSwap(vector* v, vector* other){
    if(v == NULL || other == NULL) return;
    vector vv = *v;

    *v = *other;
    *other = vv;
}
