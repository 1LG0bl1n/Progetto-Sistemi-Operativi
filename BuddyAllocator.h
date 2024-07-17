#pragma once
#include"bitmap.h"

#define MAX_LEVEL 16

typedef struct{
    BitMap*bitmap;
    int num_levels;
    char* buffer;
    int minimum_bucket_size;
    int buffer_size;
} BuddyAllocator;

//funzione per inizializzare il buddyallocator
void BuddyAllocator_init(BuddyAllocator* buddy ,BitMap* bitmap,int num_lev, char* mem, int min_buck_size, int buff_size);

//funzione per allocare memoria col buddy system
void* BuddyAllocator_malloc(BuddyAllocator* buddy_allocator, int size);

//funzione per liberare la memoria allocata
void BuddyAllocator_free(BuddyAllocator* buddy,void* mem);
