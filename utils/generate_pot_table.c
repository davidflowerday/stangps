#include <stdio.h>

char header[] = \
"**************************************************************\n" \
"* pottable.inc\n" \
"* -------------\n" \
"*\n" \
"* Potentiometer Lookup Table\n" \
"*  This is a table that maps readings from the crab\n" \
"*  potentiometer to binary radians (brads)\n" \
"*\n" \
"*\n" \
"* Copyright 2003 WildStang Robotics Team\n" \
"*\n" \
"* Autogenerated by generate_pot_table.c\n" \
"**************************************************************\n" \
"PotTable:\n";


int main(int argc, char **argv) {
  unsigned int right180, right90, zero, left90, left180;
  float increment;
  int i, temp;
  
  if(argc != 6) {
    fprintf(stderr, "Usage: %s <right 180> <right 90> <zero> <left90> <left180>\n", argv[0]);
    exit(1);
  }
  
  right180 = atoi(argv[1]);
  right90 = atoi(argv[2]);
  zero = atoi(argv[3]);
  left90 = atoi(argv[4]);
  left180 = atoi(argv[5]);
  
  printf("%s", header);
  
  increment = 64.0 / ((right90 * 1.0) - (right180 * 1.0));
  for(i = 0; i < right180; i++) {
      temp = (128.0 - ((right180 - i) * increment)) + 0.5;
      temp &= 0xFF; /* Mask to 8 bits */
      printf("        db %3dt                 ; PotToBrads(%d)\n", temp, i);
  }
  for(i = right180; i < right90; i++) {
      temp = (192.0 - ((right90 - i) * increment)) + 0.5;
      temp &= 0xFF; /* Mask to 8 bits */
      printf("        db %3dt                 ; PotToBrads(%d)\n", temp, i);
  }
  
  increment = 64.0 / ((zero * 1.0) - (right90 * 1.0));
  for(i = right90; i < zero; i++) {
      temp = (256.0 - ((zero - i) * increment)) + 0.5;
      temp &= 0xFF; /* Mask to 8 bits */
      printf("        db %3dt                 ; PotToBrads(%d)\n", temp, i);
  }
  
  increment = 64.0 / ((left90 * 1.0) - (zero * 1.0));
  for(i = zero; i < left90; i++) {
      temp = (64.0 - ((left90 - i) * increment)) + 0.5;
      temp &= 0xFF; /* Mask to 8 bits */
      printf("        db %3dt                 ; PotToBrads(%d)\n", temp, i);
  }

  
  increment = 64.0 / ((left180 * 1.0) - (left90 * 1.0));
  for(i = left90; i < left180; i++) {
      temp = (128.0 - ((left180 - i) * increment)) + 0.5;
      temp &= 0xFF; /* Mask to 8 bits */
      printf("        db %3dt                 ; PotToBrads(%d)\n", temp, i);
  }
  for(i = left180; i < 256; i++) {
      temp = (128 + ((i - left180) * increment)) + 0.5;
      temp &= 0xFF; /* Mask to 8 bits */
      printf("        db %3dt                 ; PotToBrads(%d)\n", temp, i);
  }
}
