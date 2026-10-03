#include <stdio.h>
#include "vector.h"

void vprint(const vector* v){
    printf("{");
    for(int i=0;i<vecSize(v); i++){
        //printf("vec[%i]:\t\t%i\n", i, *vecAt(v, i));
        printf(" %i", *vecAt(v, i));
    }
    printf(" }\n");
}

void vinit(vector* v, int size){
    for(int i= 0;i<size;i++)
        vecPushBack(v, i+1);
}

void vinfo(vector* v){
    printf("size:\t %zu\ncapacity:\t %zu\n\n",vecSize(v), vecCapacity(v));
}

int main(){
    vector* vec = vecCreate();
    vinit(vec, 10);

    printf("vecAt(0):\t %p\t*vecAt(0):\t %i\n", vecAt(vec, 0), *vecAt(vec, 0));
    printf("vecFront(0):\t %p\t*vecFront(0):\t %i\n", vecFront(vec), *vecFront(vec));
    printf("vecBack(0):\t %p\tvecBack(0):\t %i\n", vecBack(vec), *vecBack(vec));
    printf("vecData(0):\t %p\tvecData(0):\t %i\n", vecData(vec), *vecData(vec));
    printf("vecBegin(0):\t %p\tvecBegin(0):\t %i\n", vecBegin(vec), *vecBegin(vec));
    printf("vecEnd(0):\t %p\n", vecEnd(vec));
    printf("(bool) vecEmpty:\t %i\n", vecEmpty(vec));
    printf("vecSize:\t %lu\n", vecSize(vec));
    vecReserve(vec, 67);
    printf("vecReserve(vec, 67)\nvecCapacity:\t %lu\n", vecCapacity(vec));
    vecShrinkToFit(vec);
    printf("cap after vecShrinkToFit:\t %lu\n", vecCapacity(vec));
    vecClear(vec);
    printf("size after vecClear:\t %lu\n", vecSize(vec));
    vecInsert(vec, 0, 3, 3);
    printf("vec after vecInsert(vec, 0, 3, 3):\t ");
    vprint(vec);
    int rg[] = {4, 8, 12, 16};
    vecInsertRange(vec, 3, 4, rg);
    printf("vec after vecInsertRange(vec, 3, 4, rg):\t ");
    vprint(vec);
    vecEmplace(vec, 3, 0);
    printf("vec after vecEmplace(vec, 3, 0):\t ");
    vprint(vec);
    vecErase(vec, 3);
    printf("vec after vecErase(vec, 3):\t ");
    vprint(vec);
    vecEraseRange(vec, 0, 2);
    printf("vec after vecEraseRange(vec, 0, 2):\t ");
    vprint(vec);
    vecPushBack(vec, 20);
    printf("vec after vecPushBack(vec, 20):\t ");
    vprint(vec);
    vecPopBack(vec);
    printf("vec after vecPopBack:\t ");
    vprint(vec);
    vecResize(vec, 10, 11);
    printf("size after vecResize(vec, 10, 11):\t %lu\n", vecSize(vec));
    vector* vec_to_swap = vecCreate();
    int rg2[] = {1,2,3,4,5};
    vecInsertRange(vec_to_swap, 0, 5, rg2);
    printf("\nvecs before swap:\t \nvec:\t ");
    vprint(vec);
    printf("vec_to_swap:\t ");
    vprint(vec_to_swap);
    vecSwap(vec, vec_to_swap);
    printf("vecs after swap:\t \nvec:\t ");
    vprint(vec);
    printf("vec_to_swap:\t ");
    vprint(vec_to_swap);


    vecDestroy(vec_to_swap);
    vecDestroy(vec);
    return 0;
}