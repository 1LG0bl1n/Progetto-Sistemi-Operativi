#pragma once

#include<math.h>
#include"BuddyAllocator.h"

//returns the level of a specific node
int level_index(int idx){
    return (int) floor(log(idx+1));
}

// return buddy index
int buddy_index(int idx){
    if(idx == 0) return 0;
    if(idx & 0x01) return idx+1;
    else return idx-1;
}




 //void BuddyAllocator_init(BuddyAllocator* buddy,BitMap* bitmap,int num_lev, char* mem, int min_buck_size, int buff_size){
   // buddy->bitmap = bitmap;

//}