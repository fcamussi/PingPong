
#include <gtk/gtk.h>
#include "window.h"
#include "pingpong.h"

#define DELAY 20



int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	Create_Window();
	
	Initialize(PLAYER_1);
	
	g_timeout_add(DELAY, Process_Game, NULL);
	
	gtk_main();
	
	return 0;
}
