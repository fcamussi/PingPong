
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define HEIGHT 400
#define WIDTH 400
#define BAT_HEIGHT 80
#define BAT_WIDTH 16
#define BALL_HEIGHT 16
#define BALL_WIDTH 16



void Draw_Screen();
gboolean Configure_Event(GtkWidget *, GdkEventConfigure *, gpointer);
gboolean Expose_Event(GtkWidget *, GdkEventExpose *, gpointer);



#endif
