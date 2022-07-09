
#include <gtk/gtk.h>
#include "pingpong.h"
#include "window.h"
#include "graphics.h"



extern Keys keys[2];
extern GtkWidget *drawing_area;
extern gboolean cpu;

Player players[2];
Ball ball;



gboolean Process_Game(gpointer data)
{
	Move_Bats();
	Move_Ball();
	Draw_Screen();
	return TRUE;
}



void Initialize(uint32 numplayer)
{
	players[PLAYER_1].bat_pos_y = HEIGHT / 2;
	players[PLAYER_2].bat_pos_y = HEIGHT / 2;
	ball.pos_y = HEIGHT / 2;
	switch(numplayer)
	{
		case PLAYER_1:
			ball.pos_x = BAT_WIDTH + BALL_WIDTH / 2;
			ball.direction_x = RIGHT;
			ball.direction_y = DOWN;
			players[PLAYER_1].service = TRUE;
			players[PLAYER_2].service = FALSE;
			break;
		case PLAYER_2:
			ball.pos_x = WIDTH - BAT_WIDTH - BALL_WIDTH / 2;
			ball.direction_x = LEFT;
			ball.direction_y = UP;
			players[PLAYER_2].service = TRUE;
			players[PLAYER_1].service = FALSE;
			break;
	}
}



static void Move_Bat_Up(Player *player)
{
    if (player->bat_pos_y > BAT_HEIGHT / 2) // para que no se salga de la pantalla
        player->bat_pos_y -= BAT_SPEED;
}



static void Move_Bat_Down(Player *player)
{
    if (player->bat_pos_y < HEIGHT - BAT_HEIGHT / 2) // para que no se salga de la pantalla
        player->bat_pos_y += BAT_SPEED;
}



static gboolean Player_CPU_service(gpointer data)
{
    players[PLAYER_2].service = FALSE;
}



void Move_Bats()
{
	/* Movemos la paleta del player 1 */
	if (keys[PLAYER_1].up == TRUE)
		Move_Bat_Up(&players[PLAYER_1]);
	if (keys[PLAYER_1].down == TRUE)
        Move_Bat_Down(&players[PLAYER_1]);
	if (keys[PLAYER_1].serve == TRUE)
		players[PLAYER_1].service = FALSE;

	/* Movemos la paleta del player 2 */
	if (cpu == TRUE)
	{
        if (players[PLAYER_2].service == TRUE)
        {
          	g_timeout_add(2000, Player_CPU_service, NULL);
            
        }
        if (players[PLAYER_2].bat_pos_y > ball.pos_y)
        {
            if (abs(players[PLAYER_2].bat_pos_y - ball.pos_y) > BAT_SPEED / 2)
            {
                Move_Bat_Up(&players[PLAYER_2]);
            }
        }
        else
        {
            if (abs(players[PLAYER_2].bat_pos_y - ball.pos_y) > BAT_SPEED / 2)
            {
                Move_Bat_Down(&players[PLAYER_2]);
            }
        }
	}
	else
	{
		if (keys[PLAYER_2].up == TRUE)
            Move_Bat_Up(&players[PLAYER_2]);
		if (keys[PLAYER_2].down == TRUE)
			Move_Bat_Down(&players[PLAYER_2]);
		if (keys[PLAYER_2].serve == TRUE)
			players[PLAYER_2].service = FALSE;
	}
}



void Move_Ball()
{
	/* Movemos la pelota */
	if (players[PLAYER_1].service == TRUE)
	{
		ball.pos_y = players[PLAYER_1].bat_pos_y;
	}
	else if (players[PLAYER_2].service == TRUE)
	{
		ball.pos_y = players[PLAYER_2].bat_pos_y;
	}
	else
	{
		if (ball.pos_y >= HEIGHT - BALL_HEIGHT / 2 - 1)
		{
			ball.direction_y = UP;
		}
		if (ball.pos_y <= BALL_HEIGHT / 2)
		{
			ball.direction_y = DOWN;
		}
		if (ball.pos_x <= BAT_WIDTH + BALL_WIDTH / 2)
		{
			if (Is_On_Bat(PLAYER_1))
			{
				ball.direction_x = RIGHT;
				if (keys[PLAYER_1].up == TRUE)
				{
					ball.direction_y = UP;
				}
				else if (keys[PLAYER_1].down == TRUE)
				{
					ball.direction_y = DOWN;
				}
			}
			else /* Se fue afuera */
			{
				Initialize(PLAYER_2);
				return;
			}
		}
		if (ball.pos_x >= WIDTH - BAT_WIDTH - BALL_WIDTH / 2)
		{
			if (Is_On_Bat(PLAYER_2))
			{
				ball.direction_x = LEFT;
				if (keys[PLAYER_2].up == TRUE)
				{
					ball.direction_y = UP;
				}
				else if (keys[PLAYER_2].down == TRUE)
				{
					ball.direction_y = DOWN;
				}
			}
			else /* Se fue afuera */
			{
				Initialize(PLAYER_1);
				return;
			}
		}
		if (ball.direction_x == RIGHT)
		{
			ball.pos_x += BALL_SPEED;
		}
		else
		{
			ball.pos_x -= BALL_SPEED;
		}
		if (ball.direction_y == DOWN)
		{
			ball.pos_y += BALL_SPEED;
		}
		else
		{
			ball.pos_y -= BALL_SPEED;
		}
	}
}



boolean Is_On_Bat(uint32 numplayer)
{
	/*g_print("%d %d %d\n", players[numplayer].bat_pos_y - BAT_HEIGHT / 2
	        - BALL_HEIGHT / 2, ball.pos_y, players[numplayer].bat_pos_y +
	        BAT_HEIGHT / 2 + BALL_HEIGHT / 2);*/
	return (players[numplayer].bat_pos_y - BAT_HEIGHT / 2
	        - BALL_HEIGHT / 2 <= ball.pos_y &&
	        ball.pos_y <= players[numplayer].bat_pos_y +
	        BAT_HEIGHT / 2 + BALL_HEIGHT / 2);
}
