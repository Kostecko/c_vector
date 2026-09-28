#include <stdio.h>
#include "vector.h"

int main(){
    vector* vec = vecCreate();

    vecDestroy(vec);
    return 0;
}