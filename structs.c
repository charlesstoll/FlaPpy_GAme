#ifndef STRUCTS_C
#define STRUCTS_C

#include <stdio.h>
#include <string.h>
#include "defines.h"

struct bird
{
  int player_number;
  input last_input;
  int current_animation;
  int horz_spd;
  int vert_spd;
  int horz_pos;
  int vert_pos;
  int score;
  bool alive;
};

struct item
{
  int vert_pos;
  int horz_pos;
  obj_type type;
  bool on_screen;
};

//declarations
int print_bird(struct bird *bird);
int print_item(struct item *item);
int print_separator(void);


int print_bird(struct bird *bird)
{
  if(bird == NULL)
  {
    return NULL_POINTER_EXCEPTION;
  }
  printf("player_number: %d ||", bird->player_number);
  printf("last_player_input: %d ||", bird->last_input);
  printf("current_animation: %d ||", bird->current_animation);
  printf("score: %d ||", bird->score);
   if(bird->alive)
    printf("alive\n");
  else
    printf("dead\n"); 
  
  printf("horz_spd: %d, vert_spd: %d ||", bird->horz_spd, bird->vert_spd);
  printf("horz_pos: %d, vert_pos: %d \n", bird->horz_pos, bird->vert_pos);
  return 0;
}

int print_item(struct item *item)
{
  if(item == NULL)
    return NULL_POINTER_EXCEPTION;

  switch(item->type)
  {
    case BOMB: printf("Bomb ||");
              break;
    case COIN: printf("Coin ||");
              break;
    default: printf("Error ||");
             break;
  }

  if(item->on_screen)
    printf("on Screen ||");
  else
    printf("off screen ||");

  printf("horz_pos: %d, vert_pos: %d \n", item->horz_pos,item->vert_pos);
  return 0;
}

int print_separator()
{
  printf("---------------------------------------------------------------------\n");
  return 0;
}

#endif
