
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "window.h"
#include "pingpong.h"
#include "graphics.h"



GtkWidget *window;
GtkWidget *drawing_area;
Keys keys[2];
gboolean cpu;



void Create_Window()
{
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Ping pong");
	gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);
	gtk_widget_add_events(window, GDK_KEY_RELEASE_MASK);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request(GTK_WIDGET(drawing_area), WIDTH,
	                            HEIGHT);

	gtk_container_add(GTK_CONTAINER(window), drawing_area);

	g_signal_connect(G_OBJECT(window), "delete_event", 
	                 G_CALLBACK(Delete_Event), NULL);
	g_signal_connect(G_OBJECT(window), "key_press_event", 
	                 G_CALLBACK(Key_Press_Event), NULL);
	g_signal_connect(G_OBJECT(window), "key_release_event", 
	                 G_CALLBACK(Key_Release_Event), NULL);
	g_signal_connect(GTK_OBJECT(drawing_area), "configure_event",
	                 (GtkSignalFunc)Configure_Event, NULL);
	g_signal_connect(GTK_OBJECT(drawing_area), "expose_event",
	                 (GtkSignalFunc)Expose_Event, NULL);

	gtk_widget_show_all(window);
}


gint Create_Dialog()
{
    GtkWidget *dialog, *label;
    gchar *text = "\n  Puedes jugar contra otro jugador o contra la CPU.  \n\n\
                   Teclas Jugador 1:\n\
                         Cursor arriba -> ARRIBA\n\
                         Cursor abajo -> ABAJO\n\
                         Tecla espacio -> SACAR\n\n\
                   Teclas Jugador 2:\n\
                         Tecla Q -> ARRIBA\n\
                         Tecla A -> ABAJO\n\
                         Tecla Z -> SACAR\n\n";

    dialog = gtk_dialog_new_with_buttons(gtk_window_get_title(GTK_WINDOW(window)),
                                         GTK_WINDOW(window),
                                         GTK_DIALOG_MODAL,
                                         "Jugador 1 vs Jugador 2", 1,
                                         "Jugador 1 vs CPU", 2,
                                         NULL);

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    label = gtk_label_new(text);

    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox),
                      label);
    gtk_widget_show_all(GTK_WIDGET(dialog));
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    
    switch(result)
    {
        case 1:
            cpu = FALSE;
            break;
        case 2:
            cpu = TRUE;
            break;
    }
    gtk_widget_destroy(dialog);

    return result;
}


gboolean Delete_Event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	gtk_main_quit();
	return TRUE;
}



void Key_Press_Event(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	switch(event->keyval)
	{
		case GDK_Up:
			keys[PLAYER_1].up = TRUE;
			break;
		case GDK_Down:
			keys[PLAYER_1].down = TRUE;
			break;
		case GDK_space:
			keys[PLAYER_1].serve = TRUE;
			break;
		case GDK_q:
			keys[PLAYER_2].up = TRUE;
			break;
		case GDK_a:
			keys[PLAYER_2].down = TRUE;
			break;
		case GDK_z:
			keys[PLAYER_2].serve = TRUE;
			break;
	}
}



void Key_Release_Event(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	switch(event->keyval)
	{
		case GDK_Up:
			keys[PLAYER_1].up = FALSE;
			break;
		case GDK_Down:
			keys[PLAYER_1].down = FALSE;
			break;
		case GDK_space:
			keys[PLAYER_1].serve = FALSE;
			break;
		case GDK_q:
			keys[PLAYER_2].up = FALSE;
			break;
		case GDK_a:
			keys[PLAYER_2].down = FALSE;
			break;
		case GDK_z:
			keys[PLAYER_2].serve = FALSE;
			break;
	}
}
