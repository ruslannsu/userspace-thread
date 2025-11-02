#define _GNU_SOURCE 
#include "uthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

uthread_t *uthreads[THREADS_MAX_COUNT];

size_t uthreads_size = 0;


int stack_create(off_t size, int thread_id, void **stack_ptr) {
	int stack_fd;
	int err;
	char *stack_f = malloc(FILE_NAME_SIZE);
	if (stack_f == NULL) {
		return -1;
	}

	snprintf(stack_f, FILE_NAME_SIZE, "stack-%d", thread_id);   
	stack_fd = open(stack_f, O_RDWR | O_CREAT, 0660);
	if (stack_fd == -1) {
		return -1;
	}

	int frt_err = ftruncate(stack_fd, 0);
	if (frt_err == -1) {
		return -1;
	}

	frt_err = ftruncate(stack_fd, size);
	if (frt_err == -1) {
		return -1;
	}

	*stack_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, stack_fd, 0);
	if (*stack_ptr == MAP_FAILED) {
		return -1;
	}
	err = mprotect(*stack_ptr, PAGE_SIZE, PROT_NONE);
	if (err != 0) {
		return EAGAIN;
	}

	return 0;
}


void uthread_func_wrapper(void) {
    return;
}


int uthread_create(uthread_t **usl, void (*func)(void*), void *args) {
    int err;

    void *stack;

    err = stack_create(STACK_SIZE, 1, &stack);
    if (err != 0) {
        printf("%s \n", strerror(err));
        return EAGAIN;
    }

    uthread_t *uthread_struct_ptr = (uthread_t*)(stack + STACK_SIZE - sizeof(uthread_t));

    err = getcontext(&uthread_struct_ptr->uc);
    if (err == -1) {
        printf("getcontext failed: %s", strerror(errno));
        return EINVAL;
    }

    uthread_struct_ptr->uc.uc_stack.ss_sp = stack;
    uthread_struct_ptr->uc.uc_stack.ss_size = STACK_SIZE - sizeof(uthread_t);
    uthread_struct_ptr->uc.uc_link = NULL;

    makecontext(&uthread_struct_ptr->uc, uthread_func_wrapper, 0);

    uthread_struct_ptr->args = args;
    uthread_struct_ptr->func = func;

    uthreads[uthreads_size] = uthread_struct_ptr;
    *usl = uthread_struct_ptr;

    return 0;
}



