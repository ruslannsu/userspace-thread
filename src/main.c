#include <stdio.h>
#include "uthread.h"


void routine(void *args) {
    printf("hello world");
    while (1) {

    }
}

int main() {
    uthread_t* usl[2];
    
    uthread_t main_thread;

    uthreads_init(main_thread);

    uthread_create(&usl[0], main, NULL);

    while (1) {
        schedule();
    }
    
    return 0;
}