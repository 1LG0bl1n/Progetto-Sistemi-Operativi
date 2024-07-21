#include"BuddyAllocator.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 4096
#define BUDDY_LEVELS 6
#define MEMORY_SIZE 256

char bitmap_buff[MEMORY_SIZE];
BuddyAllocator buddy;

int main(int argc,char** argv) {
    int buff_size= BUFFER_SIZE;
    int levs = BUDDY_LEVELS;
    int min_buck_size = buff_size>> (levs);

    char buffer[buff_size];

    //intialize buddy allocator
    int ris;
    void* res;
    ris = BuddyAllocator_init(&buddy,buffer,buff_size,levs,bitmap_buff,MEMORY_SIZE,min_buck_size);
    if (ris == 0) printf("BUDDY INITIALIZATION FAILED");

    res = BuddyAllocator_malloc(&buddy,500);

    BuddyAllocator_free(&buddy,res);



    return 0;
}