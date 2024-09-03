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
int first_index_level(int level){
    return (1<<level)-1;
}


//return offset from start of level to block
int block_offset(int index){
    return index-first_index_level(level_index(index));
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
    printf("\n\033[1;33mNUMBER OF BITS: %d\033[0m \n" , bitmap->num_bits);
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

 int BuddyAllocator_init(BuddyAllocator* buddy,char* memory_buff, int mem_buff_size, int num_lev,char* bitmap_buff, int bitmap_buff_size, int min_bucket_size){
    if(num_lev > MAX_LEVEL){
        printf("\033[1;31mERROR:\033[0m LEVEL NUMBER EXCEED MAXIMUM\n");
        return 0;
    }
    int num_bits= (1<< (num_lev+1))-1;
    if(BitMap_getBytes(num_bits)> bitmap_buff_size){
        printf("\033[1;31mERROR:\033[0m MEMORY  INSUFFICIENT\n");
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
        printf("\\033[1;31mERROR:\033[0m CANNOT ALLOCATE 0 BYTES");
        return NULL;
    }
    
    printf("\nBUDDY SYSTEM ALLOCATING \033[1;33m%d\033[0m BYTES + \033[1;33m%ld\033[0m BYTES TO STORE INDEX :\033[1;33m%ld\033[0m BYTES TOTAL . . .", size,sizeof(int),size+sizeof(int));
    size+=sizeof(int);



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
    
    int block_index = -1;
    int j;
    if(block_level == 0){
        if(!BitMap_bit(&buddY_allocator->bitmap,0)){
            block_index = 0;
        }
    }
    else{
        for(j = first_index_level(block_level); j<first_index_level(block_level+1);j++) {
            if(BitMap_bit(&buddY_allocator->bitmap,j) == 0){
                block_index=j;
                printf("\n\t\t\t\t\t \033[1;33m FREE BUDDY FOUND AT INDEX: %d\033[0m" , block_index);
                break;
            }

        }
    }
    if (block_index ==-1){
        printf("\n\033[1;31mERROR:\033[0m no free buddy available of size %d\n", size);
        return NULL;
    }
    set_bit_children(&buddY_allocator->bitmap,block_index,1);
    set_bit_ancestors(&buddY_allocator->bitmap,block_index,1);

    char* address = (buddY_allocator->buffer)+(block_offset(block_index)*block_size);
    
   printf("\nA new block of memory has been allocated of size \033[1;33m%d\033[0m located at level \033[1;33m%d\033[0m and whith index \033[1;33m%d\033[0m and pointer  \033[1;33m%p\033[0m \n" , size,block_level,block_index,address);
    
   ((int*)address)[0] = block_index;

    printf("\nResulting BitMap Tree: \n");

    Print_Buddy(&buddY_allocator->bitmap);
    printf("\n");
    address+=sizeof(int);
    return (void*)(address);
}

void BuddyAllocator_free(BuddyAllocator* buddy_allocator,void* mem) {
    if(mem == NULL) {
    printf("\n\033[1;31mERROR:\033[0m\t cannot free an unallocated block\n");
    return;
    }


    
    mem-=sizeof(int);
    int block_index = ((int*)mem)[0];
    printf("\nABOUT TO FREE THE MEMORY BLOCK WITH POINTER  \033[1;33m%p\033[0m AND INDEX \033[1;33m%d\033[0m",mem,block_index);

    

    int dimention =buddy_allocator->minimum_bucket_size* (1<<(buddy_allocator->num_levels - level_index(block_index)));
    char* mem_ptr_check= buddy_allocator->buffer + dimention * block_offset(block_index);

    
     mem =  mem_ptr_check;


    if(BitMap_bit(&buddy_allocator->bitmap,block_index) == 0){
         printf("\n\033[1;31mERROR:\033[0m\tmemory block is already free\n");
         return;
    }
    
    set_bit_children(&buddy_allocator->bitmap,block_index,0);


    printf("\nUPDATATING BUDDYALOCATOR TREE STRUCTURE STRARTING FROM INDEX \033[1;33m%d\033[0m . . .",block_index);
    BuddyAllocator_update(&buddy_allocator->bitmap,block_index);

    printf("\nBUDDYALLOCATOR TREE STRUCTURE AFTER FREE :");
    printf("\n");
    Print_Buddy(&buddy_allocator->bitmap);
    return;
}

void BuddyAllocator_update(BitMap* bitmap,int index){
    BitMap_setBit(bitmap,index,0);
    if(index == 0){
        printf("\nBuddyAllocator_update FINISHED ");
        return;
    }
    if(BitMap_bit(bitmap,index) == 1) {
        printf("\\033[1;31mERROR:\033[0m\tmemory block has to be free\n");
        return;
    }
    if(BitMap_bit(bitmap,buddy_index(index)) == 0){
        BuddyAllocator_update(bitmap,parent_index(index));
    }
    else {
        printf("\n BuddyAllocator_update finished ");
    }
}