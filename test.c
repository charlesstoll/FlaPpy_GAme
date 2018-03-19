#include "structs.c"
#include "defines.h"
#include "bin_to_bcd.c"

int main(int argc, char *argv[])
{
  struct bird myBird;
  myBird.player_number = 5;
  myBird.last_input = 12;
  myBird.current_animation = 0;
  myBird.horz_spd = -3;
  myBird.vert_spd = -12;
  myBird.horz_pos = 15;
  myBird.vert_pos = 12;
  myBird.score = 3;
  myBird.alive = true;
  
  print_bird(&myBird);
  
  print_separator();

  struct item myItem;
  myItem.vert_pos = 20;
  myItem.horz_pos = 300;
  myItem.type = COIN;
  myItem.on_screen = true;

  print_item(&myItem);

  for(int i = 0; i < 5; i ++)
  {
    printf("%d\n", i);
  }


  int x = 3879;
  int hundreds = 0;
  int thousands = 0;
  int tens = 0;
  int ones = 0;
  bin_to_bcd(x, &thousands, &hundreds, &tens, &ones);
  printf("%d = %d, %d, %d, %d\n", x, thousands, hundreds, tens, ones);
}
