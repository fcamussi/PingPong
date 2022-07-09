
#include <gtk/gtk.h>
#include "graphics.h"
#include "pingpong.h"



extern GtkWidget *drawing_area;
extern Player players[2];
extern Ball ball;
GdkPixmap *buffer = NULL;



void Draw_Screen()
{
	uint32 height = drawing_area->allocation.height;
	uint32 width = drawing_area->allocation.width;
	
	/* Limpiamos el buffer */
	gdk_draw_rectangle(buffer,
				 drawing_area->style->white_gc,
				 TRUE,
				 0,
				 0,
				 width,
				 height);
	/* Limpiamos el buffer */
	gdk_draw_rectangle(buffer,
				 drawing_area->style->black_gc,
				 TRUE,
				 0,
				 0,
				 width,
				 height);
	/* Dibuja las paletas */
	gdk_draw_rectangle(buffer,
				 drawing_area->style->white_gc,
				 TRUE,
				 0,
				 players[PLAYER_1].bat_pos_y - BAT_HEIGHT / 2,
				 BAT_WIDTH,
				 BAT_HEIGHT);
	gdk_draw_rectangle(buffer,
				 drawing_area->style->white_gc,
				 TRUE,
				 width - BAT_WIDTH,
				 players[PLAYER_2].bat_pos_y - BAT_HEIGHT / 2,
				 BAT_WIDTH,
				 BAT_HEIGHT);
	/* Dibuja la pelota */
	gdk_draw_rectangle(buffer,
				 drawing_area->style->white_gc,
				 TRUE,
				 ball.pos_x - BALL_WIDTH / 2,
		 		 ball.pos_y - BALL_HEIGHT / 2,
				 BALL_WIDTH,
		 		 BALL_HEIGHT);
	/* Actualizamos la pantalla */
	gtk_widget_queue_draw_area(drawing_area, 0, 0, width, height);
}



gboolean Configure_Event(GtkWidget *drawing_area, GdkEventConfigure *event,
					  gpointer data)
{
	if (buffer) {
		g_object_unref(G_OBJECT(buffer));
	}
	buffer = gdk_pixmap_new(drawing_area->window, drawing_area->allocation.width,
					drawing_area->allocation.height, -1);
	Draw_Screen(NULL);
	return TRUE;
}



gboolean Expose_Event(GtkWidget *darea, GdkEventExpose *event,
				     gpointer data)
{
	gdk_draw_drawable(drawing_area->window,
				drawing_area->style->fg_gc[GTK_WIDGET_STATE(drawing_area)],
				buffer,
				event->area.x, event->area.y,
				event->area.x, event->area.y,
				event->area.width, event->area.height);
	return FALSE;
}
