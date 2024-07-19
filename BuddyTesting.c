#include"BuddyAllocator.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 1025
#define BUDDY_LEVELS 5
#define MEMORY_SIZE 256

uint8_t bitmap_buff[MEMORY_SIZE];
BuddyAllocator buddy;

int main(int argc,char** argv) {
    int buff_size= BUFFER_SIZE;
    int levs = MAX_LEVEL;
    int min_buck_size = buff_size>> (levs);

    char buffer[buff_size];

    //intialize buddy allocator

    BuddyAllocator_init(&buddy,buffer,buff_size,levs,bitmap_buff,MEMORY_SIZE,min_buck_size);
    return 0;
}