#ifndef BIN_TO_BCD_C
#define BIN_TO_BCD_C

int bin_to_bcd(int binary_num, int *thousands, int *hundreds, int *tens, int *ones);
int mod_by_ten(int input_number);

int bin_to_bcd(int binary_num, int *thousands, int *hundreds, int *tens, int *ones)
{
  *ones = mod_by_ten(binary_num);
  binary_num = binary_num / 10;
  *tens = mod_by_ten(binary_num);
  binary_num = binary_num / 10;
  *hundreds = mod_by_ten(binary_num);
  binary_num = binary_num / 10;
  *thousands = mod_by_ten(binary_num);
  return 0;
}



int mod_by_ten(int input_number)
{
  if(input_number < 0) return -1;
  while(input_number >= 1000) input_number = input_number - 1000;
  while(input_number >= 100) input_number = input_number -100;
  while(input_number >= 10) input_number = input_number - 10;
  return input_number;
}

#endif
