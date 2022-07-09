
#ifndef WINDOW_H
#define WINDOW_H

#include "types.h"



typedef struct {
	boolean up;
	boolean down;
	boolean serve;
} Keys;



void Create_Window();
gint Create_Dialog();
gboolean Delete_Event(GtkWidget *, GdkEvent *, gpointer);
void Key_Press_Event(GtkWidget *, GdkEventKey *, gpointer);
void Key_Release_Event(GtkWidget *, GdkEventKey *, gpointer);



#endif
