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
 void BuddyAllocator_init(BuddyAllocator* buddy,char* memory_buff, int mem_buff_size, int num_lev,uint8_t* bitmap_buff, int bitmap_buff_size, int min_bucket_size);
//funzione per allocare memoria col buddy system
void* BuddyAllocator_malloc(BuddyAllocator* buddy_allocator, int size);

//funzione per liberare la memoria allocata
void BuddyAllocator_free(BuddyAllocator* buddy,void* mem);
