#define THREADS_MAX_COUNT 512
#define PAGE_SIZE 1024
#define FILE_NAME_SIZE 128
#define STACK_SIZE 1024 * 10
#define BASE_PRI 6
#define MAX_PRI 12
#define SLEEP 0
#define RUNABLE 1
#define RUNNING 2
#define MAIN 1
#define DEFAULT 0

#include <ucontext.h>

typedef struct uthread_t {
    char *thread_name;
    ucontext_t uc;
    void (*func)(void*);
    void *args;
    int pri;
    int proc;
    int state;
    int type;
} uthread_t;

void uthreads_init();


int uthread_create(uthread_t **uthread_struct, void (*func)(void*), void *args);

void schedule();

void priority_schedule();

void uthread_set_sleepstate();
