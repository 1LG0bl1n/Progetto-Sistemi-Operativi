#include"Allocator.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


Allocator allocator;

int main(int argc,char** argv) {
    //initialize allocator
    int ris;
    
    ris = Allocator_init(&allocator);
    if (ris == 0) printf("\\033[1;31mERROR:\033[0m \t Allocator_init failed");

    void*p1 = pseudo_malloc(&allocator,1000);

    pseudo_free(&allocator,p1);
    




    return 0;
}