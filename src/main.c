#include <stdio.h>
#include "vector.h"

int main(){
    vector* vec = vecCreate();
    
    vecResize(vec, 5); //No IntelliSense 

    printf("%i\n", vecGetSize(vec));

    return 0;
}