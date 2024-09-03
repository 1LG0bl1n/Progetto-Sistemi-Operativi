#include"Allocator.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>



Allocator allocator;

int main(int argc,char** argv) {
    //initialize allocator
    int ris;
    
    ris = Allocator_init(&allocator);
    if (ris == 0) printf("\n\033[1;31mERROR:\033[0m \t Allocator_init failed\n");

    sleep(1);

    printf("\n\n<-------------------------------ALLOCATOR TESTING------------------------------->\n\n");

    void*p1 = pseudo_malloc(&allocator,2000);

        sleep(1);
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p1);

    sleep(1);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void* p2 = pseudo_malloc(&allocator,500);

        sleep(1);


    pseudo_free(&allocator,p2);

        sleep(1);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

        sleep(1);


    void*p3 = pseudo_malloc(&allocator,600);

        sleep(1);

    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p4 = pseudo_malloc(&allocator,600);

        sleep(1);

    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p5 = pseudo_malloc(&allocator,600);
        sleep(1);


    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    void*p6 = pseudo_malloc(&allocator,500);

        sleep(1);

    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    

    void*p8 = pseudo_malloc(&allocator,200);

        sleep(1);

    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

   
    pseudo_free(&allocator,p3);

        sleep(1);


    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p4);

        sleep(1);


    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p5);

        sleep(1);


    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p6);


        sleep(1);

    
    printf("\n\n<------------------------------------------------------------------------------->\n\n");

    pseudo_free(&allocator,p8);

        sleep(1);

    
   printf("\n\n<-------------------------------TESTING IS OVER------------------------------->\n\n");

    

    return 0;
}