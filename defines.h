#ifndef DEFINES_H
#define DEFINES_H

//error definitions
#define NULL_POINTER_EXCEPTION -1

//game options declarations
#define NUM_PLAYERS (1)
#define MAX_NUM_ITEMS (10)

//constant definitions
#define UP_SPEED_INCREASE 5
#define DOWN_SPEED_INCREASE 5
#define RIGHT_SPEED_INCREASE 5
#define LEFT_SPEED_INCREASE 5
#define GRAV_SPEED_INCREASE 1
#define LEFT_SIDE_LOCATION 0
#define RIGHT_SIDE_LOCATION 100
#define TOP_LOCATION 0
#define BOTTOM_LOCATION 100
#define BIRD_WIDTH 50
#define BIRD_HEIGHT 30

//type definitions
typedef int bool;
enum { false, true };

typedef int obj_type;
enum { BOMB, COIN, NUMBER_OF_OBJ_TYPES };

typedef int game_state;
enum { START_SCREEN, GAME_LOOP, GAME_OVER, NUMBER_OF_GAME_STATES };

typedef int input;
enum { NO_INPUT, UP_INPUT, DOWN_INPUT, RIGHT_INPUT, LEFT_INPUT, NUMBER_OF_INPUTS };

typedef int bird_animation;
enum { NO_FLAP, FLAP, NUMBER_OF_BIRD_ANIMATIONS };

#endif
