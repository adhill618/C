#include <gtk/gtk.h>
#include "utility.h"


int board[4][4];


void (*move_functions[4])(int board[4][4]) = {move_up, move_down, move_left, move_right};

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    static const guint keys[4] = { GDK_KEY_w, GDK_KEY_s, GDK_KEY_a, GDK_KEY_d };

    for (int i = 0; i < 4; i++) {
        if (event->keyval == keys[i]) {
            move_functions[i](board); 
            placeRandomTile(board);    
            gtk_widget_queue_draw(widget);  
            break;
        }
    }

    return FALSE;
}

gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    int cell_size = 100; 
    cairo_set_line_width(cr, 1);  

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int x = j * cell_size;
            int y = i * cell_size;
            int tile_value = board[i][j];

            
            if (tile_value == 0) {
                cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);  
            } else {
                cairo_set_source_rgb(cr, 0.9, 0.9, 0.5);  
            }
            cairo_rectangle(cr, x, y, cell_size, cell_size);
            cairo_fill(cr);

            
            cairo_set_source_rgb(cr, 0, 0, 0); 
            cairo_stroke(cr);

            
            if (tile_value != 0) {
                cairo_set_source_rgb(cr, 0, 0, 0);  
                cairo_set_font_size(cr, 30);  
                char text[8];
                snprintf(text, sizeof(text), "%d", tile_value);
                
                
                cairo_text_extents_t extents;
                cairo_text_extents(cr, text, &extents);
                double x_text = x + (cell_size - extents.width) / 2;
                double y_text = y + (cell_size - extents.height) / 2 + extents.height;

                cairo_move_to(cr, x_text, y_text); 
                cairo_show_text(cr, text);  
            }
        }
    }

    return FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    srand(time(NULL));

    
    gameBoard(board);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "2048 Game");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 400);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
