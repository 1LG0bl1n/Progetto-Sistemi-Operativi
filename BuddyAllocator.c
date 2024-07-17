#pragma once

#include<math.h>
#include"BuddyAllocator.h"

//returns the level of a specific node
int level_index(int idx){
    return (int) floor(log2(idx+1));
}

// return buddy index
int buddy_index(int idx){
    if(idx == 0) return 0;
    if(idx & 0x01) return idx+1;
    else return idx-1;
}

//returns parend index
int parent_index(int idx) {
    return((idx-1)/2);
}

// return first index of level
int first_level(int level){
    return (2<<level)-1;
}

 void BuddyAllocator_init(BuddyAllocator* buddy,char* memory_buff, int mem_buff_size, BitMap* bitmap, int num_lev,uint8_t* bitmap_buff, int bitmap_buff_size, int min_bucket_size){
    assert("number of levels must be less than 16\n buddy_init aborted\n" && num_lev < MAX_LEVEL);
    int num_bits= 1<< (num_lev+1)-1;
    assert("insufficent bitmap memory\n" && (BitMap_getBytes(num_bits)<= bitmap_buff_size));
    if(level_index(mem_buff_size) != log2(mem_buff_size)) {
        printf("\nWarning: Memory is not a power of 2 so a chunk of it will not be usable\n");
    }
    mem_buff_size = min_bucket_size << num_lev; //the actual memory size to be handled
    
    buddy->num_levels = num_lev;
    buddy->buffer= memory_buff;
    buddy->buffer_size = mem_buff_size;
    buddy->minimum_bucket_size= min_bucket_size;

    printf("BUDDY ALLOCATOR INITIALIZING  ...\n");
    printf("\tlevels: %d", num_lev);
    printf("\tmax list entries %d bytes\n", mem_buff_size);
    printf("\tbucket size:%d\n", min_bucket_size);
    printf("\tmanaged memory %d bytes\n", (1<<num_lev)*min_bucket_size);

    BitMap_init(buddy->bitmap,num_bits,bitmap_buff);
    printf("\ninitialized bitmap\n");
    printf("\n BUDDY ALLOCATOR READY FOR DUTY\n");
    return;



}