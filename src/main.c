#include <stdio.h>
#include "vector.h"

int main(){
    vector* vec = vecCreate();

    vecReserve(vec, 10);
    //vecResize(vec, 10, 0);

    for(int i=1;i<=5;i++)
        vecPushBack(vec, i);

    //printf("capacity: %zu\nsize: %zu\n\n", vecGetCapacity(vec), vecGetSize(vec));


    vecInsert(vec, vecAt(vec, 3), 6, 32);

    for(int i=0;i<vecGetSize(vec);i++)
        printf("%i. %i\n", i+1, *vecAt(vec, i));

    //printf("\n\ncapacity: %zu\nsize: %zu\n\n", vecGetCapacity(vec), vecGetSize(vec));

    vecDestroy(vec);
    return 0;
}