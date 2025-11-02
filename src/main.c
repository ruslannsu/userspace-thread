#include <stdio.h>
#include "uthread.h"


void routine(void *args) {
    printf("hello world");
}


int main() {
    uthread_t* usl[1];
    
    uthread_create(&usl[0], )


    uthread_create(NULL, NULL, NULL);

    return 0;
}