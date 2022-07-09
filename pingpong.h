
#ifndef PINGPONG_H
#define PINGPONG_H

#include <gtk/gtk.h>
#include "types.h"

#define BAT_SPEED 4
#define BALL_SPEED 4
#define CPU FALSE



typedef struct {
	uint32 bat_pos_y;
	boolean service;
} Player;


typedef struct {
	uint32 pos_x;
	uint32 pos_y;
	uint32 direction_x;
	uint32 direction_y;
} Ball;



enum {
	PLAYER_1,
	PLAYER_2
};


enum {
	LEFT,
	RIGHT
};


enum {
	UP,
	DOWN
};



gboolean Process_Game(gpointer);
void Initialize(uint32);
void Move_Bats();
void Move_Ball();
boolean Is_On_Bat(uint32);



#endif
