#include "vector.h"

//----------INTERNAL FUNCTIONS--------------------------------

static int isMyElement(int*srcB, int* srcE, int* ptrB, int* ptrE){
    if((srcB == NULL && srcE == NULL) || (ptrB == NULL && ptrE == NULL)) return 0;

    uintptr_t fsrcB =(uintptr_t) srcB;
    uintptr_t fsrcE =(uintptr_t) srcE;
    uintptr_t fptrB =(uintptr_t) ptrB;
    uintptr_t fptrE =(uintptr_t) ptrE;
    
    int output = 1;

    if(fptrB != NULL && (fptrB < fsrcB || fptrB > fsrcE)) output = 0;
    if(fptrE != NULL &&(fptrE < fsrcB || fptrE > fsrcE)) output = 0;

    if(output == 0) printf("NOT YOUR ELEMENT!");

    return output;
}

static int vecMalloc(vector* v, size_t n_of_elems){
    if(v->array = malloc(n_of_elems * sizeof *v->array)){
        v->size = n_of_elems;
        return v->capacity = n_of_elems;
    }
    free(v->array);
    printf("Allocating memory failed!\n\n");
    return 0;
}

static int vecRealloc(vector* v, size_t new_cap){
    if(!new_cap) return 0;

    int* new_arr;
    if(!(new_arr = realloc(v->array, new_cap * sizeof *v->array))){
        free(new_arr);
        return 0;
    } 

    v->array = new_arr;
    v->capacity = new_cap;

    return 1;
}

//----------EXTERNAL FUNCTIONS--------------------------------

vector* vecCreate(void){
    vector* v = malloc(sizeof *v);
    if(!v) { free(v); return NULL; }

    vecMalloc(v, 1);
    v->size = 0;

    return v;
}

void vecDestroy(vector* v){
    if(!v) return;
    free(v->array);
    free(v);
}


int* vecAt(const vector* v, size_t index){
    if(!v) return NULL;
    if(index >= v->size){
        printf("Index out of range! Are you crazy?\n");
        return NULL;
    }
    return &(v->array[index]);
}

int* vecFront(const vector* v){
    if(!v) return NULL;
    if(!v->size) return NULL;
    return v->array;
}

int* vecBack(const vector* v){
    if(!v || !v->array) return NULL;
    if(!v->size) return v->array;
    return v->array+(v->size-1);
}

int* vecData(const vector* v){
    if(!v) return NULL;
    return v->array;
}

int* vecBegin(const vector* v){
    if(!v) return NULL;
    return v->array;
}

int* vecEnd(const vector* v){
    if(!v || !v->array) return NULL;
    return v->array+v->size;
}

int vecIsEmpty(const vector* v){
    if(!v) return 1;
    if(!v->size) return 1;
    return 0;
}

size_t vecSize(const vector* v){
    if(!v){
        printf("vector uninitialized\n");
        return 0;
    }
    
    return v->size;
}

void vecReserve(vector*v, size_t new_cap){
    if (!v || new_cap <= v->capacity) return;

    vecRealloc(v, new_cap);
}

size_t vecCapacity(const vector* v){
    if(!v) return 0;
    return v->capacity;
}

void vecShrinkToFit(vector* v){
    if(!v || v->size == v->capacity)return;
    vecRealloc(v, v->size);
}

void vecClear(vector* v){
    if(!v || !v->size) return;
    v->size = 0;
}

void vecInsert(vector* v, int* pos, size_t count, int value){
    if(!v || !count || 
        !isMyElement(vecBegin(v), 
        vecBack(v), pos, NULL)) return;
    
    size_t index = pos - v->array;

    if(v->size+count > v->capacity)
        if(!vecRealloc(v, (count+v->capacity)*2)) return;

    pos = v->array + index;

    memmove(pos + count, pos, (v->size - index) * sizeof *v->array);

    for(size_t i = 0; i < count; i++)
        v->array[index+i] = value;
        
    v->size += count;
}

void vecInsertRange(vector* v, int* pos, size_t count, const int* rg){
    if(!v|| !count || !rg) return;

    if(!isMyElement(vecBegin(v), vecEnd(v), pos, NULL)) return;
    if(isMyElement(vecBegin(v), vecBack(v), rg, rg+count-1)) return;

    size_t index = pos - v->array;
        
    if(v->size+count > v->capacity)
        if(!vecRealloc(v, (v->size + count) * 2)) return;
        
    pos = v->array + index;

    memmove(pos+count, pos, (v->size - index) * sizeof *v->array);

    for(size_t i=0;i<count;i++)
        v->array[i+index] = rg[i];
    v->size += count;
}

void vecEmplace(vector* v, int* pos, int value){
    if(!v) return;
    if(!isMyElement(vecBegin(v), vecBack(v), pos, NULL)) return;
    
    if(!v->size)
        v->size++;

    size_t index = pos - v->array;

    if(v->size == v->capacity)
        if(!vecRealloc(v, v->capacity*2)) return;

    pos = v->array + index;
    
    memmove(pos + (size_t)1, pos, (v->size - index) * sizeof *v->array);
    
    v->array[index] = value;
    v->size += 1;
}

void vecErase(vector* v, int* pos){
    if(!v || !v->array || !pos || !v->size) return;
    if(!isMyElement(vecBegin(v), vecBack(v), pos, NULL)) return;

    size_t index = pos - v->array;
    size_t len = v->size - index - 1;

    memmove(pos, pos+1, len * sizeof *v->array);

    v->size-=1;
}

void vecEraseRange(vector* v, int* first, int* last){
    if(!v || last < first) return;
    if(!isMyElement(vecBegin(v), 
    vecBack(v), first, last)) return;

    size_t len = last - first + 1;

    if(len == 0) return;
    if(len == 1){ vecErase(v, first); return; }
    if(last == (v->array + v->size-1)){ v->size -= len; return; }

    size_t lentomove = v->array+v->size-1 - last;

    memmove(first, last+1, lentomove * sizeof *v->array);
    v->size -= len;
}

void vecPushBack(vector* v, int n){
    if(!v) return;

    if(!v->size) v->size++;

    if(v->size == v->capacity)
        if(!vecRealloc(v, v->capacity*2)) return;

    *(v->array + v->size++) = n;
}

void vecEmplaceBack(vector* v, int value){
    vecPushBack(v, value);
}

void vecAppendRange(vector* v, size_t count, const int* rg){
    vecInsertRange(v, vecEnd(v), count, rg);
}

void vecPopBack(vector* v){
    if(!v) return;
    if(v->size > 0) v->size--;
    else printf("Vector is empty!\n");
}

void vecResize(vector* v, size_t new_size, int value){
    if(!v) return;
    if(new_size == v->size) return;
    if(new_size < v->size){ v->size = new_size; return; }
    if(new_size > v->capacity)
        if(!vecRealloc(v, (v->capacity+new_size)*2)) return;
    
    for(size_t i = v->size; i<new_size;i++) *(v->array + i) = value;
    
    v->size = new_size;
}

void vecSwap(vector* v, vector* other){
    if(!v || !other) return;
    vector vv = *v;

    *v = *other;
    *other = vv;
}
