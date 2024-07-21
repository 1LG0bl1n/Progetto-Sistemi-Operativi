#include<assert.h>
#include"bitmap.h"

int BitMap_getBytes(int bits){
  int eccesso = ((bits%8)!=0) ? 1 : 0;
  return bits/8 + eccesso; // prendo il numero di bytes (per eccesso) per contenere tutti i bit
}

void BitMap_init(BitMap* bit_map ,int num_bits, uint8_t* buffer) {
    bit_map->buffer = buffer;
    bit_map->num_bits = num_bits;
    bit_map->buffer_size = BitMap_getBytes(num_bits);
    for(int i = 0; i<num_bits;i++){
      BitMap_setBit(bit_map,i,0);
    }
}

void BitMap_setBit(BitMap* bit_map, int bit_num, int status){
  // get byte
  int byte_num=bit_num>>3;
  assert(byte_num<bit_map->buffer_size);
  int bit_in_byte=byte_num&0x07;
  if (status) {
    bit_map->buffer[byte_num] |= (1<<bit_in_byte);
  } else {
    bit_map->buffer[byte_num] &= ~(1<<bit_in_byte);
  }
}



int BitMap_bit(const BitMap* bit_map, int bit_num){
  int byte_num=bit_num>>3; 
  assert(byte_num<bit_map->buffer_size);
  int bit_in_byte=byte_num&0x07;
  return (bit_map->buffer[byte_num] & (1<<bit_in_byte))!=0;
}






