#include <stdio.h>
#include "uthread.h"

void routine1(void *arg) {
    size_t i = 0;
    while(1) {
        printf("hello 1\n");
        fflush(stdout);

        i++;
        
        usleep(100000);

        priority_schedule();
    }   
}

void routine2(void *arg) {
    size_t i = 0;
    while(1) {
        
        i++;
        
        printf("hello 2\n");
        usleep(100000);
        fflush(stdout);
        priority_schedule();
    }
}

void routine3(void *arg) {
    while(1) {
        printf("hello 3\n");
        fflush(stdout);

        usleep(100000);
        priority_schedule();
    }
}

void routine4(void *arg) {
    size_t i = 0;
    while(1) {
        ++i;
       
        printf("hello 4\n");
        fflush(stdout);

        usleep(100000);
        priority_schedule();
    }
}

int main() {

    uthread_t* usl[4];
    
    uthread_t main_thread;

    uthreads_init(&main_thread);

    uthread_create(&usl[0], routine1, NULL);

    uthread_create(&usl[1], routine2, NULL);

    uthread_create(&usl[2], routine3, NULL);
    uthread_create(&usl[3], routine4, NULL);

    for (int i = 0; i < 3; ++i) {
        printf("%p\n", usl[i]->func);
    }
    priority_schedule();

    return 0;
}