#include <stdio.h>
#include <stdlib.h>
#include "structs.c"

//global variable declarations
struct bird birds[NUM_PLAYERS];
struct item items[MAX_NUM_ITEMS];
game_state state_of_game = START_SCREEN;
bool game_over = true;
int scroll_speed = 10;
int LOGIC_SPEED = 1;
int SPAWN_FREQUENCY = 1;
int spawn_loop_count = 0;
int logic_loop_count = 0;

//function declarations
int do_game(void); //done
int start_new_game(void); //done
int load_start_screen(void); //stubbed
int load_background(void); //stubbed
int load_game_over_screen(void); //stubbed
int main_game_loop(void); //finish with hardware
int get_user_input(void); //stubbed
int initialize_data(void); //done
int reset_bird(struct bird *bird, int player_number); //done
int remove_item(struct item *item); //done
int print_game_state(void); //done
int movement_update(void); //done
int update_bird_speed(void); //done
int do_update_bird_speed(struct bird *bird); //done
int bird_movement(struct bird *bird);   //done
int bird_out_of_bounds_check(struct bird *bird); //done
int item_passive_movement(struct item *item); //done
int check_game_over(void); //done
int spawn_item(void);  //done
int collision_detection(void); //done
int do_collision(struct bird *bird, struct item *item); //done
bool check_collision(struct bird *bird, struct item *item);  //done
int bird_collision_detection(struct bird* bird); //done




//functions

int main(int argc, char* argv[])
{
    do_game();
}

int do_game()
{
  initialize_data();
  start_new_game();
  while(true)
  {
    //DEBUGGING***********************************
    print_separator();
    printf("STATE OF THE GAME: %d \n", state_of_game);
    print_separator();
    //END DEBUGGING**********************
    switch(state_of_game)
    {
      case START_SCREEN:
        //load_start_screen();
        while(birds[0].last_input == NO_INPUT)
        {
          //do nothing
          //DEBUG************************
          //print_bird(&birds[0]);
          printf("-------------------------GAME START-----------------------\n");
          //DEBUG END*******************
          get_user_input();
        }
        start_new_game();
        state_of_game = GAME_LOOP;
        break;
      case GAME_LOOP:
        //load_background();
        while(!game_over)
        {
          main_game_loop();
        }
        state_of_game = GAME_OVER;
        break;
      case GAME_OVER:
        //load_game_over_screen();
        for(int i = 0; i <= 10; i ++) //should be roughly 3 seconds
        {
          //do nothing
        }
        //DEBUG**************************
        printf("----------------------------GAME OVER---------------------\n");
        state_of_game = START_SCREEN;
        break;
      default:
        printf("game state error \n:");
        break;
    }
  }
}

int initialize_data()
{
  for(int i = 0; i < NUM_PLAYERS; i ++)
  {
    struct bird new_bird;
    birds[i] = new_bird;
  }
  for(int i = 0; i < MAX_NUM_ITEMS; i ++)
  {
    struct item new_item;
    items[i] = new_item;
  } 
}

int start_new_game()
{
  //load_sprite_assets()
  for(int i = 0; i < NUM_PLAYERS; i ++)
  {
    reset_bird(&birds[i], i);
  }
  for(int i = 0; i < MAX_NUM_ITEMS; i ++)
  {
    remove_item(&items[i]);
  }
  game_over = false;
}

int reset_bird(struct bird *bird, int player_number)
{
  bird->player_number = player_number;
  bird->last_input = NO_INPUT;
  bird->current_animation = NO_FLAP;
  bird->horz_spd = 0;
  bird->vert_spd = 0;
  bird->horz_pos = 5;
  bird->vert_pos = 10 * (player_number+ 1);
  bird->score = 0;
  bird->alive = true;
}

int remove_item(struct item *item)
{
  item->on_screen = false;
}

int get_user_input()
{
  int i = 0;
  for(i = 0; i < NUM_PLAYERS; i ++)
  {
    //DEBUGGING**************************
    //needs to be changed to get the real raw input
    char raw_input[3];
    input fixed_input = 0;
    printf("waiting on player %d input: \n ", i);
    fgets(raw_input, 3, stdin);
    //END DEBUGGING *************************
    switch(raw_input[0])
    {
      case 'n': fixed_input = NO_INPUT;
                //printf("n case\n");
                break;
      case 'u': fixed_input = UP_INPUT;
                //printf("u case\n");
                break;
      case 'd': fixed_input = DOWN_INPUT;
                //printf("d case\n");
                break;
      default : fixed_input = NO_INPUT;
                //printf("here\n");
                break;
    }
    //DEBUGGING***************
    //printf("%s", raw_input);
    //END
    //printf("%d into %d bird\n", fixed_input, i);
    birds[i].last_input = fixed_input;
  }
}

int main_game_loop()
{
  //DEBUGGING****************************
  int i;
  print_game_state();
  for(i = 0; i < NUM_PLAYERS; i ++)
  {
    print_bird(&birds[i]);
    print_separator();
  }
  for(i = 0; i < MAX_NUM_ITEMS; i ++)
  {
    print_item(&items[i]);
    print_separator();
  }
  //END DEBUGGING****************************
  if(logic_loop_count >= LOGIC_SPEED)
  {
    logic_loop_count = 0;
    if(spawn_loop_count >= SPAWN_FREQUENCY)
    {
      spawn_loop_count = 0;
      spawn_item();
    }
    spawn_loop_count ++;
    get_user_input();
    update_bird_speed();
    movement_update();
    collision_detection();
    //update_sprites();
    check_game_over();
  }
  logic_loop_count ++;
  
}

int print_game_state()
{
  printf("********************************************************\n");
  printf("State of game: %d\n", state_of_game);
  printf("spawn loop count: %d, logic_loop_count: %d\n", spawn_loop_count, logic_loop_count);
  printf("********************************************************\n");
}

int update_bird_speed()
{
  for(int i = 0; i < NUM_PLAYERS; i ++)
  {
    if(birds[i].alive)
    {
      do_update_bird_speed(&birds[i]);
    }
  }
}

int do_update_bird_speed(struct bird *bird)
{
  switch(bird->last_input)
  {
    case UP_INPUT: 
      bird->vert_spd -= UP_SPEED_INCREASE;
      break;
    case DOWN_INPUT:
      bird->vert_spd += DOWN_SPEED_INCREASE;
      break;
    case RIGHT_INPUT:
      bird->horz_spd += RIGHT_SPEED_INCREASE;
      break;
    case LEFT_INPUT:
      bird->horz_spd -= LEFT_SPEED_INCREASE;
      break;
    default:
      break;
  }

}

int movement_update()
{
  for(int i = 0; i < MAX_NUM_ITEMS; i ++)
  {
    if(items[i].on_screen)
    {
      item_passive_movement(&items[i]);
    }
  }

  for(int i = 0; i < NUM_PLAYERS; i ++)
  {
    if(birds[i].alive)
    {
      bird_movement(&birds[i]);
      bird_out_of_bounds_check(&birds[i]);
    }
  }
}

int bird_movement(struct bird *bird)
{
  //apply gravity
  bird->vert_spd += GRAV_SPEED_INCREASE;
  //movement based on speed
  bird->horz_pos += bird->horz_spd;
  bird->vert_pos += bird->vert_spd;
}

int bird_out_of_bounds_check(struct bird *bird)
{
  if(bird->vert_pos <= TOP_LOCATION)
  {
    bird->vert_spd = 0;
    bird->vert_pos = TOP_LOCATION+1;
  }
  else if(bird->vert_pos >= BOTTOM_LOCATION)
  {
    bird->alive=false;
    bird->vert_pos = BOTTOM_LOCATION - 1;
    bird->vert_spd = 0;
  }
}

int item_passive_movement(struct item *item)
{
  item->horz_pos -= scroll_speed;
  if(item->horz_pos < LEFT_SIDE_LOCATION)
  {
    remove_item(item);
  }
}

int check_game_over()
{
  bool temp_game_over = true;
  for(int i = 0; i < NUM_PLAYERS; i ++)
  {
    if(birds[i].alive)
    {
      temp_game_over = false;
    }
  }
  game_over = temp_game_over;
  return 0;
}

int spawn_item()
{
  int unused_item_number = MAX_NUM_ITEMS + 1;
  for(int i = 0; i < MAX_NUM_ITEMS; i ++)
  {
    if(!items[i].on_screen)
    {
      unused_item_number = i;
      break;
    }
  }
  if(unused_item_number == MAX_NUM_ITEMS + 1)
  {
    return 0;
  }
  int r = rand();
  items[unused_item_number].type = r % NUMBER_OF_OBJ_TYPES;
  items[unused_item_number].vert_pos = (r % (BOTTOM_LOCATION - TOP_LOCATION)) + TOP_LOCATION;
  items[unused_item_number].horz_pos = RIGHT_SIDE_LOCATION-1;
  items[unused_item_number].on_screen = true;
  return 0;
}

int collision_detection()
{
  for(int i = 0; i < NUM_PLAYERS; i ++)
  {
    bird_collision_detection(&birds[i]);
  }
}

int bird_collision_detection(struct bird* bird)
{
  for(int i = 0; i < MAX_NUM_ITEMS; i ++)
  {
    if(items[i].on_screen)
    {
      if(check_collision(bird, &items[i]))
      {
        do_collision(bird, &items[i]);
      }
    }
  }
}

bool check_collision(struct bird *bird, struct item *item)
{
  //int horz_diff = bird->horz_pos - item->horz_pos;
  //int vert_diff = bird->vert_pos = item->vert_pos;
  if(bird->horz_pos + BIRD_WIDTH > item->horz_pos) // item to left of right edge?
  {
    if(bird->horz_pos < item->horz_pos) //item to the right of left edge?
    {
      if(bird->vert_pos < item->vert_pos) //item below top edge?
      {
        if(bird->vert_pos + BIRD_HEIGHT > item->vert_pos) //item above bottom edge?
        {
          return true;
        }
      }
    }
  }
  return false;
}

int do_collision(struct bird *bird, struct item *item)
{
  switch(item->type)
  {
    case COIN:
      bird->score ++;
      remove_item(item);
      break;
    case BOMB:
      bird->alive = false;
      remove_item(item);
      break;
    default:
      break;
  }
}

