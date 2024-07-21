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

void set_bit_children(BitMap* bitmap, int num_bit,int value){ // implemented throug recourtion to not use a queue 
    if(num_bit< bitmap->num_bits){
        BitMap_setBit(bitmap,num_bit,value);
        set_bit_children(bitmap,(num_bit*2)+1,value);
        set_bit_children(bitmap,(num_bit*2)+2,value);
    }
}

void set_bit_ancestors(BitMap* bitmap,int num_bit, int value) {
    BitMap_setBit(bitmap,num_bit,value);
    if(num_bit==0) return;
    else {
        BitMap_setBit(bitmap,num_bit,value);
        set_bit_ancestors(bitmap,parent_index(num_bit),value);
    }
}



//prints the bitmap as a buddyAllocator tree
void Print_Buddy(BitMap* bitmap){
    printf("\n%d \n" , bitmap->num_bits);
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
        printf("ERROR: LEVEL NUMBER EXCEED MAXIMUM\n");
        return 0;
    }
    int num_bits= (1<< (num_lev+1))-1;
    if(BitMap_getBytes(num_bits)> bitmap_buff_size){
        printf("ERROR: MEMORY  INSUFFICIENT\n");
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

void* BuddyAllocator_malloc(BuddyAllocator* buddY_allocator,int size) {
    if(size == 0){
        printf("\nERROR: CANNOT ALLOCATE 0 BYTES");
        return NULL;
    }
    
    printf("\nALLOCATING %d BYTES + %ld BYTES TO STORE INDEX : %ld BYTES TOTAL . . .", size,sizeof(int),size+sizeof(int));
    size+=sizeof(int);

    if(size>buddY_allocator->buffer_size){
        printf("\nERROR: memory request exceed available memory\n");
        return NULL;
    }
    int block_level;
    int block_size;

    printf("\nLOOKING FOR THE APROPRIATE BLOCK LEVEL . . .");

    if (size>(buddY_allocator->buffer_size)/2){
        block_level =0;
        block_size= buddY_allocator->buffer_size;
    }
    else{
        block_level=buddY_allocator->num_levels;
        block_size =buddY_allocator->minimum_bucket_size;
        for(int i= 0; i<=buddY_allocator->num_levels; i++){
            if(size<= block_size){
                break;
            }
            else{
                block_level--;
                block_size*=2;
            }
        }

    }

    printf("\nBLOCK LEVEL FOUND :\t %d", block_level);

    //now let's find a free item on the level 
    /*
    int block_index = -1;
    int j;
    if(block_level == 0){
        if(!BitMap_bit(&buddY_allocator->bitmap,0)){
            block_index = 0;
        }
    }
    else{

    }*/

    printf("\n");
    set_bit_children(&buddY_allocator->bitmap,10,1);
    set_bit_ancestors(&buddY_allocator->bitmap,10,1);

    Print_Buddy(&buddY_allocator->bitmap);
    printf("\n");
}