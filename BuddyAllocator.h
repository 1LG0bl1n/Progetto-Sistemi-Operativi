#pragma once
#include"bitmap.h"

#define MAX_LEVEL 16

typedef struct{
    BitMap bitmap;
    int num_levels;
    char* buffer;
    int minimum_bucket_size;
    int buffer_size;
} BuddyAllocator;

//function to initialize buddy
int BuddyAllocator_init(BuddyAllocator* buddy,char* memory_buff, int mem_buff_size, int num_lev,char* bitmap_buff, int bitmap_buff_size, int min_bucket_size);
//function to allocate memory through buddy allocator
void* BuddyAllocator_malloc(BuddyAllocator* buddy_allocator, int size);

//function to free allocated memory
void BuddyAllocator_free(BuddyAllocator* buddy,void* mem);

//function to print BuddyAllocator tree structure
void Print_Buddy(BitMap* bitmap);

//update the buddy allocato structure afrer free
void BuddyAllocator_update(BitMap* bitmap,int index);
