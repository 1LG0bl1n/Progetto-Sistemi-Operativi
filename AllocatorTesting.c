#include"Allocator.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


Allocator allocator;

int main(int argc,char** argv) {
    //initialize allocator
    int ris;
    
    ris = Allocator_init(&allocator);
    if (ris == 0) printf("\n\033[1;31mERROR:\033[0m \t Allocator_init failed\n");

    printf("\n\n<-------------------------------ALLOCATOR TESTING------------------------------->\n\n");

    void*p1 = pseudo_malloc(&allocator,2000);

    pseudo_free(&allocator,p1);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void* p2 = pseudo_malloc(&allocator,500);

    pseudo_free(&allocator,p2);
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p3 = pseudo_malloc(&allocator,600);
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p4 = pseudo_malloc(&allocator,600);
    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p5 = pseudo_malloc(&allocator,600);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p6 = pseudo_malloc(&allocator,500);
    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    

    void*p8 = pseudo_malloc(&allocator,200);
    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

   void* p9;//= pseudo_malloc(&allocator,200);
   //printf("\n\n%p\n\n",p9);
   
    pseudo_free(&allocator,p3);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p4);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p5);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p6);
    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    //printf("\n\n%p\n\n",p9);
    pseudo_free(&allocator,p9);
    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p8);
    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    

    return 0;
}