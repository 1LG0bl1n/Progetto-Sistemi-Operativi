#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/mman.h>
#include"BuddyAllocator.h"

typedef struct{
    BuddyAllocator BuddyAllocator;
    char* mem_start;
    char* mem_end ;
}Allocator;

int Allocator_init(Allocator* alloc);

void * pseudo_malloc(Allocator* alloc,int size);
void pseudo_free(Allocator* alloc, void* memory );
void* Mmap_malloc(int size);
void Mmap_free(void* memory);