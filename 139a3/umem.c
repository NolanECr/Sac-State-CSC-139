#include "umem.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stddef.h>

#define PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef struct Node {
    size_t size;
    struct Node *next;
} Node;

static void *ptr = NULL; //ptr for the memory region
static Node *free_list = NULL;

static int allocationAlgorithm; 
static Node *last_allocated = NULL;

int umeminit(size_t sizeOfRegion, int allocationAlgo) {
    if (ptr != NULL || sizeOfRegion <= 0) return -1;

    int fd = open("/dev/zero", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    ptr = mmap(NULL, sizeOfRegion, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(1);
    }

    close(fd);

    allocationAlgorithm = allocationAlgo;
	
	Node *initial_block = (Node *)ptr;
    initial_block->size = sizeOfRegion - sizeof(Node);
    initial_block->next = NULL;
    free_list = initial_block;
	
    return 0;
}

void *umalloc(size_t size) {
    //implement memory allocation logic
    if (size <= 0) return NULL;

    //ensure alignment
    size_t aligned_size = (size + 7) & ~7;

    Node *prev = NULL;
    Node *curr = free_list;
    Node *best_fit = NULL;

    switch (allocationAlgorithm) {
        case BEST_FIT:
            //smallest block that fits
            while (curr != NULL) {
                if (curr->size >= aligned_size && (best_fit == NULL || curr->size < best_fit->size)) {
                    best_fit = curr;
                }
                prev = curr;
                curr = curr->next;
            }
            break;

        case WORST_FIT:
            //largest block that fits
            while (curr != NULL) {
                if (curr->size >= aligned_size && (best_fit == NULL || curr->size > best_fit->size)) {
                    best_fit = curr;
                }
                prev = curr;
                curr = curr->next;
            }
            break;

        case FIRST_FIT:
            while (curr != NULL) {
                if (curr->size >= aligned_size) {
                    best_fit = curr;
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
            break;

        case NEXT_FIT:
            //continue searching from the last allocated block
            static Node *last_allocated = NULL;
            curr = last_allocated ? last_allocated->next : free_list;
            while (curr != NULL) {
                if (curr->size >= aligned_size) {
                    best_fit = curr;
                    break;
                }
                prev = curr;
                curr = curr->next;
            }
            break;

        default:
            return NULL; 
    }

    void *alloc_ptr = (void *)(best_fit + 1);
    if (best_fit->size >= aligned_size + sizeof(Node)) {
        Node *new_block = (Node *)((char *)alloc_ptr + aligned_size);
        new_block->size = best_fit->size - aligned_size - sizeof(Node);
        new_block->next = best_fit->next;
        best_fit->size = aligned_size;
        best_fit->next = new_block;
    }

    last_allocated = best_fit;

    if (prev == NULL) {
        free_list = best_fit->next;
    } else {
        prev->next = best_fit->next;
    }

    return alloc_ptr;
}

int ufree(void *ptr) {
    //frees the memory
    if (ptr == NULL) return -1;

    Node *block_to_free = (Node *)((char *)ptr - sizeof(Node));

    //add the freed block to the free list again
    block_to_free->next = free_list;
    free_list = block_to_free;

    return 0;
}

void umemdump() {
    //memory dump used for debugging
    Node *curr = free_list;
    printf("Memory Dump:\n");
    while (curr != NULL) {
        printf("Block at %p, Size: %zu\n", (void *)curr, curr->size);
        curr = curr->next;
		break;
    }
    printf("--------------\n");
}