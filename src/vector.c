#include "vector.h"
#define vsize v->size
#define vcap v->capacity
#define varr v->array
#define dtype_size sizeof *varr

//----------INTERNAL FUNCTIONS--------------------------------

static int vecMalloc(vector* v, const size_t n_of_elems){
    int* new_arr = NULL;

    if(!varr && n_of_elems){
        if(new_arr = malloc(n_of_elems * 2 * dtype_size)){
            //printf("MALLOC\n");
            varr = new_arr;
            vcap = n_of_elems * 2;
            return 1;
        }
    }

    free(new_arr);
    printf("Memory allocation failed!\n\n");
    return 0;
}

static int vecRealloc(vector* v, const size_t new_cap){
    if(!new_cap){
        vsize = 0;
        vcap = 0;
        free(varr);
        varr = NULL;
        return 1;
    }

    int* new_arr = realloc(varr, new_cap * dtype_size);

    if(new_arr){
        varr = new_arr;
        vcap = new_cap;
        return 1;
    }
    return 0;
}

static int isMyElement(ciptrc objBegin, const size_t objSize, ciptrc ptr1, ciptrc ptr2){
    int p1b = 0;
    int p2b = 0;

    if(ptr1){
        for(size_t i = 0; i < objSize; i++){
            if(ptr1 == objBegin + i){
                p1b = 1;
                break;
            }
        }
    }
    if(ptr2){
        for(size_t i = 0; i < objSize; i++){
            if(ptr2 == objBegin + i){
                p2b = 1;
                break;
            }
        }
    }
    return p1b * p2b;
}

//----------EXTERNAL FUNCTIONS--------------------------------

vector* vecCreate(void){
    vector* v = malloc(sizeof *v);
    if(!v) { free(v); return NULL; }

    varr = NULL;
    vsize = 0;
    vcap = 0;

    return v;
}

void vecDestroy(vector* v){
    if(v){
        if(varr) free(varr);
        free(v);
    }
}


ciptrc vecAt(const vector* v, size_t index){
    if(!v) return NULL;
    if(index >= vsize){
        printf("Index out of range! Are you crazy?\n");
        return NULL;
    }
    return &(varr[index]);
}

ciptrc vecFront(const vector* v){
    if(!v) return NULL;
    if(!vsize) return NULL;
    return varr;
}

ciptrc vecBack(const vector* v){
    if(!v || !varr || !vsize) return NULL;
    return varr+vsize-1;
}

ciptrc vecData(const vector* v){
    if(!v) return NULL;
    return varr;
}

ciptrc vecBegin(const vector* v){
    if(!v) return NULL;
    return varr;
}

ciptrc vecEnd(const vector* v){
    if(!v || !varr) return NULL;
    return varr+vsize;
}

int vecEmpty(const vector* v){
    if(!v) return 1;
    if(!vsize) return 1;
    return 0;
}

size_t vecSize(const vector* v){
    if(!v){
        printf("vector uninitialized\n");
        return 0;
    }
    
    return vsize;
}

void vecReserve(vector* v, const size_t new_cap){
    if (!v || new_cap <= vcap) return;

    vecRealloc(v, new_cap);
}

size_t vecCapacity(const vector* v){
    if(!v) return 0;
    return vcap;
}

void vecShrinkToFit(vector* v){
    if(!v || !varr || vsize == vcap) return;

    vecRealloc(v, vsize);
}

void vecClear(vector* v){
    if(!v || !vsize) return;
    vsize = 0;
}

void vecInsert(vector* v, const size_t index, const size_t count, const int value){
    if(!v || !count || index > vsize) return;
    if(!varr) if(!vecMalloc(v, count)) return;
    if(vsize+count > vcap)
        if(!vecRealloc(v, (count+vcap)*2)) return;

    memmove(varr + index + count, varr + index, (vsize - index) * dtype_size);

    for(size_t i = 0; i < count; i++) varr[index+i] = value;
    vsize += count;
}

void vecInsertRange(vector* v, const size_t index, const size_t count, ciptrc rg){
    if(!v|| !count || !rg) return;
    if(index > vsize) return; 
    if(!varr) if(!vecMalloc(v, count)) return;
    
    const int* rgptr = rg;
    int* buffer = NULL;

    if(isMyElement(v->array, v->size, rg, rg + count - 1)){
        buffer = malloc(count * dtype_size);
        if(!buffer) return;
        memcpy(buffer, rg, count * dtype_size);

        rgptr = buffer;
    }

    if(vsize + count > vcap){
        if(!vecRealloc(v, (vsize + count) * 2)){ 
            if(buffer) free(buffer);
            return; 
        }
    }
    memmove(varr + index + count, 
        varr + index, 
        (vsize - index) * dtype_size);

    for(size_t i = 0; i < count; i++) varr[i + index] = rgptr[i];

    vsize += count;
    if(buffer) free(buffer);
}

void vecEmplace(vector* v, const size_t index, const int value){
    if(!v) return;
    if(index > vsize) return;
    if(!varr) if(!vecMalloc(v, 1)) return;
    if(vsize == vcap) if(!vecRealloc(v, vcap*2)) return;

    memmove(varr + index + 1, varr + index, (vsize - index) * dtype_size);
    varr[index] = value;
    vsize++;
}

void vecErase(vector* v, const size_t index){
    if(!v || !varr || !vsize || index >= vsize) return;
    if(index == vsize - 1) {vsize--; return;}

    size_t len = vsize - (index + 1);
    memmove(varr + index, varr + index + 1, len * dtype_size);
    vsize--;
}

void vecEraseRange(vector* v, const size_t first, const size_t last){
    if(!v || last >= vsize || first > last) return;

    size_t len = last - first + 1;

    if(len == 0) return;
    if(len == 1){ vecErase(v, first); return; }
    if(last == vsize - 1) { vsize -= len; return; }

    size_t lentomove = vsize - (last + 1);

    memmove(varr + first, varr + last + 1, lentomove * dtype_size);
    vsize -= len;
}

void vecPushBack(vector* v, const int value){
    if(!v) return;
    if(!varr) if(!vecMalloc(v, 1)) return;

    //printf("%p\n", varr);

    if(vsize == vcap)
        if(!vecRealloc(v, vcap * 2)) return;

    varr[++vsize - 1] = value;
}

void vecEmplaceBack(vector* v, const int value){
    vecPushBack(v, value);
}

void vecAppendRange(vector* v, const size_t count, ciptrc rg){
    if(!v) return;
    vecInsertRange(v, vsize, count, rg);
}

void vecPopBack(vector* v){
    if(!v) return;
    if(vsize > 0) vsize--;
    else printf("Vector is empty!\n");
}

void vecResize(vector* v, const size_t new_size, const int value){
    if(!v) return;
    if(new_size == vsize) return;
    if(new_size < vsize){ vsize = new_size; return; }
    if(new_size > vcap)
        if(!vecRealloc(v, (vcap+new_size)*2)) return;
    
    for(size_t i = vsize; i<new_size;i++) *(varr + i) = value;
    
    vsize = new_size;
}

void vecSwap(vector* v, vector* other){
    if(!v || !other) return;
    vector vv = *v;

    *v = *other;
    *other = vv;
}
