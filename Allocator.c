#include"Allocator.h"

#define BUFFER_SIZE 4096
#define BUDDY_LEVELS 6
#define MEMORY_SIZE 256

char bitmap_buff[MEMORY_SIZE];

BuddyAllocator buddy;

int Allocator_init(Allocator* alloc) {
    int buff_size= BUFFER_SIZE;
    int levs = BUDDY_LEVELS;
    int min_buck_size = buff_size>> (levs);

    char buffer[buff_size];
    int res;
    res = BuddyAllocator_init(&alloc->BuddyAllocator,buffer,buff_size,levs,bitmap_buff,MEMORY_SIZE,min_buck_size);
    if(res == 0) {
        printf("\n\033[1;31mERROR:\033[0m  buddy initialization failed\n");
        return res;
    }
    return res;    
}

void* pseudo_malloc(Allocator* alloc, int size){
    printf("\nALLOCATING \033[1;33m%d\033[0m BYTES  . . .",size);
    void * memory;
    
    if(size< 1024){
        printf("\nSIZE IS UNDER 1/4 PAGE-SIZE . . .\n");
        printf("\n\t\t\t\t\033[1;32m BUDDY ALLOCATOR WILL BE USED TO PERFORM THIS TASK\033[0m\n");
        memory= BuddyAllocator_malloc(&alloc->BuddyAllocator,size);
        
        return memory;
    }
    else{
        printf("\nSIZE IS OVER 1/4 PAGE-SIZE . . .\n");
        printf("\n\t\t\t\t\033[1;34mMEMORY WILL BE ALLOCATED BY USING MMAP\033[0m\n");
        memory = Mmap_malloc(size);
        return memory;
        
    }
}

void pseudo_free(Allocator* alloc,void* memory){
    memory-=(sizeof(int)+sizeof(char));
    ((char*)memory)[0];
    printf("\nDEALLOCATING MEMORY POINTED BY %p . . .", memory);
    if(((char*)memory)[0] == 'b'){
        printf("LABEL b BUDDY ALLOCATOR WILL BE USED TO PERFORM FREE . . .");
        BuddyAllocator_free(&alloc->BuddyAllocator,memory);
    }
    if(((char*)memory)[0] == 'm'){
        printf("\nLABEL m MEMORY WILL BE FREED THROUG MUNMAPPING . . .");
        Mmap_free(memory);
    }
    return;
    }

void* Mmap_malloc(int size){
    void*memory;
    size+=sizeof(int);
    size+=sizeof(char);
    printf("\nMAPPING 033[1;33m%d\033[0m BYTES + 033[1;33m%ld\033[0m BYTES TO STORE INDEX + 1 BYTE TO STORE LABEL :033[1;33m%ld\033[0m BYTES TOTAL . . .", size,sizeof(int),size+sizeof(int)+1);
    memory=mmap( 0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );
    if(memory == NULL){
        perror("\n\033[1;31mERROR:\033[0m\t mmap failed\n");
        return NULL;
    }
    printf("\n \033[1;32mSUCCESS:\033[0m A new block of memory has been allocated of size \033[1;33m%d\033[0m  and pointer  \033[1;33m%p\033[0m \n" , size,memory);
    
    ((char*)memory)[0] = 'm';
    memory+= sizeof(char);
    ((int*)memory)[0] = size;
    memory+=sizeof(int);
    return(void*) memory;
}

void Mmap_free(void* memory){
    if(memory == NULL){
        perror("\n\033[1;31mERROR:\033[0m\tNULL pointer\n");
        return;
    }
    memory+=sizeof(char);
    int size= *((int*)memory);
    memory-= sizeof(char);
    printf("\nABOUT TO UNMAP THE MEMORY BLOCK WITH POINTER  \033[1;33m%p\033[0m AND SIZE \033[1;33m%d\033[0m",memory,size);
    munmap((void*)memory,size);
    printf("\n\033[1;32mSUCCESS:\033[0m\t memory unmapped\n");
    return;
}


 