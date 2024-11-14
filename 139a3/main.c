#include <stdio.h>
#include "umem.h"

void test_malloc_best() {
	//Test for BEST FIT
    printf("Testing Memory Allocator for Best Fit:\n");

    int result = umeminit(4096, BEST_FIT);
    if (result != 0) {
        printf("Memory initialization failed...\n");
        return;
    }

    void *ptr1 = umalloc(100);
    if (ptr1 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at %p\n", ptr1);

    void *ptr2 = umalloc(300);
    if (ptr2 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at: %p\n", ptr2);

    umemdump();

    ufree(ptr1);
    printf("Freed memory block at: %p\n", ptr1);

    umemdump();

    ufree(ptr2);
    printf("Freed memory block at: %p\n", ptr2);

    umemdump();
}
	
	
void test_malloc_worst() {
	//Test for WORST FIT
	printf("Testing Memory Allocator for Worst Fit:\n");

    int result = umeminit(4096, WORST_FIT);
    if (result != 0) {
        printf("Memory initialization failed...\n");
        return;
    }

    void *ptr1 = umalloc(100);
    if (ptr1 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at %p\n", ptr1);

    void *ptr2 = umalloc(300);
    if (ptr2 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at: %p\n", ptr2);

    umemdump();

    ufree(ptr1);
    printf("Freed memory block at: %p\n", ptr1);

    umemdump();

    ufree(ptr2);
    printf("Freed memory block at: %p\n", ptr2);

    umemdump();
}
	
void test_malloc_first() {	
	//Test for FIRST FIT
	printf("Testing Memory Allocator for First Fit:\n");

    int result = umeminit(4096, FIRST_FIT);
    if (result != 0) {
        printf("Memory initialization failed...\n");
        return;
    }

    void *ptr1 = umalloc(100);
    if (ptr1 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at %p\n", ptr1);

    void *ptr2 = umalloc(300);
    if (ptr2 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at: %p\n", ptr2);

    umemdump();

    ufree(ptr1);
    printf("Freed memory block at: %p\n", ptr1);

    umemdump();

    ufree(ptr2);
    printf("Freed memory block at: %p\n", ptr2);

    umemdump();
}
	
void test_malloc_next() {
	//Test for NEXT FIT
	printf("Testing Memory Allocator for Next Fit:\n");

    int result = umeminit(4096, NEXT_FIT); // Initialize with NEXT_FIT algorithm
    if (result != 0) {
        printf("Memory initialization failed...\n");
        return;
    }

    void *ptr1 = umalloc(100);
    if (ptr1 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at %p\n", ptr1);

    void *ptr2 = umalloc(300);
    if (ptr2 == NULL) {
        printf("Memory allocation failed...\n");
        return;
    }
    printf("Allocated memory block at: %p\n", ptr2);

    umemdump();

    ufree(ptr1);
    printf("Freed memory block at: %p\n", ptr1);

    umemdump();

    ufree(ptr2);
    printf("Freed memory block at: %p\n", ptr2);

    umemdump();
}

int main() {
    test_malloc_best();
	test_malloc_worst();
	test_malloc_first();
	test_malloc_next();
    return 0;
}
