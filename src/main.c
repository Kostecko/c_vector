#include <stdio.h>
#include "vector.h"

void vprint(const vector* v){
    for(int i=0;i<vecSize(v); i++){
        printf("vec[%i]:\t%i\n", i, *vecAt(v, i));
    }
}

void vinit(vector* v, int size){
    for(int i= 0;i<size;i++)
        vecPushBack(v, i+1);
}

void vinfo(vector* v){
    printf("size: %zu\ncapacity: %zu\n\n",vecSize(v), vecCapacity(v));
}

int main(){
    vector* vec = vecCreate();
    //vinit(vec, 10);

    int arr[] = {1,2,3,4,5};

    vecInsertRange(vec, vecBegin(vec), 5, arr);

    //TODO
    //range functions - check if rg is vector's part
    //optimize lines of code
    //pos ptr not from vector situation
    //ujednolicic metody dzialania i sprawdzania vectorow itd uk
    //fsanitize
    //any type

    vinfo(vec);
    vprint(vec);
    vecDestroy(vec);
    return 0;
}