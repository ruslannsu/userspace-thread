#define THREADS_MAX_COUNT 512
#define PAGE_SIZE 1024
#define FILE_NAME_SIZE 128
#define STACK_SIZE 1024 * 10

typedef struct uthread_t {
    char *thread_name;
    void (*func)(void*);
    void *args;
} uthread_t;

int uthread_create(uthread_t **uthread_struct, void (*func)(void*), void *args);


