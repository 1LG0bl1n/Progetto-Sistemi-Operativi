#include<stdio.h>
#include<assert.h>
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

void Print_Buddy(BitMap* bitmap){

    printf("%d \n" , bitmap->num_bits);
    int bit_on_levl_to_print = 0;
    int levl_ctr = -1;
    int levl_tot = level_index(bitmap->num_bits)-1;
    for(int i= 0; i<bitmap->num_bits; i++) {
        if(bit_on_levl_to_print == 0) {
            if(levl_ctr == levl_tot){
                break;
            }
            printf("\nLIVELLO %d : \t" ,++levl_ctr);
            for (int j = 0; j<(1<<levl_tot)-(1<<levl_ctr);j++){
                printf(" ");
            }
            bit_on_levl_to_print=1<<levl_ctr;
        }
        if(BitMap_bit(bitmap,i) == 0) printf("0 ");
        if(BitMap_bit(bitmap,i) == 1) printf("1 ");
        bit_on_levl_to_print--;
    }
    printf("\n");

}

 int BuddyAllocator_init(BuddyAllocator* buddy,char* memory_buff, int mem_buff_size, int num_lev,uint8_t* bitmap_buff, int bitmap_buff_size, int min_bucket_size){
    if(num_lev > MAX_LEVEL){
        printf("ERROR: LEVEL NUMBER EXCEED MAXIMUM");
        return 0;
    }
    int num_bits= (1<< (num_lev+1))-1;
    if(BitMap_getBytes(num_bits)> bitmap_buff_size){
        printf("ERROR: MEMORY  INSUFFICIENT");
        return 0;
    }
    if(level_index(mem_buff_size) != log2(mem_buff_size)) {
        printf("\nWarning: Memory is not a power of 2 so a chunk of it will not be usable\n");
    }
    mem_buff_size = min_bucket_size << num_lev; //the actual memory size to be handled
    
    buddy->num_levels = num_lev;
    buddy->buffer= memory_buff;
    buddy->buffer_size = mem_buff_size;
    buddy->minimum_bucket_size= min_bucket_size;

    printf("BUDDY ALLOCATOR INITIALIZING  ...\n");
    printf("\tlevels: %d \n", num_lev);
    printf("\tmax list entries %d bytes\n", mem_buff_size);
    printf("\tbucket size:%d\n", min_bucket_size);
    printf("\tmanaged memory %d bytes\n", (1<<num_lev)*min_bucket_size);

    BitMap_init(&buddy->bitmap,num_bits,bitmap_buff);
    printf("\ninitialized bitmap\n");
    printf("\n BUDDY ALLOCATOR READY FOR DUTY\n");
    Print_Buddy(&buddy->bitmap);
    return 1;
}