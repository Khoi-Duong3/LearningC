#include <gtk/gtk.h>
#include "utility.h"
#include <stdio.h>  // for snprintf

static GtkWidget *cells[size][size];   // pointers to grid labels
static int       board[size][size];   // game state

// Refresh all labels to match the board state
static void refresh_board(void) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char buf[16];
            if (board[i][j] == 0)
                snprintf(buf, sizeof buf, ".");
            else
                snprintf(buf, sizeof buf, "%d", board[i][j]);
            gtk_label_set_text(GTK_LABEL(cells[i][j]), buf);
        }
    }
}

// Key-press handler: ignore unused parameters, call move functions
static gboolean on_key_press(GtkWidget *widget,
                             GdkEventKey *event,
                             gpointer      user_data)
{
    (void)widget;
    (void)user_data;

    gboolean moved = FALSE;
    switch (event->keyval) {
        // Arrow keys
        case GDK_KEY_Up:    moved = move_up(board);    break;
        case GDK_KEY_Down:  moved = move_down(board);  break;
        case GDK_KEY_Left:  moved = move_left(board);  break;
        case GDK_KEY_Right: moved = move_right(board); break;
        // WASD keys
        case GDK_KEY_w:
        case GDK_KEY_W:     moved = move_up(board);    break;
        case GDK_KEY_s:
        case GDK_KEY_S:     moved = move_down(board);  break;
        case GDK_KEY_a:
        case GDK_KEY_A:     moved = move_left(board);  break;
        case GDK_KEY_d:
        case GDK_KEY_D:     moved = move_right(board); break;
        // Quit
        case GDK_KEY_q:
        case GDK_KEY_Q:
            gtk_main_quit();
            return TRUE;
        default:
            return FALSE;
    }
    if (moved) {
        add_random_tile(board);
        refresh_board();
    }
    return TRUE;
}

// Build and show the main window, grid, and labels
static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;

    GtkWidget *win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "2048 in GTK");
    gtk_window_set_default_size(GTK_WINDOW(win), 400, 400);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(win), grid);

    // Initialize game state and two starting tiles
    make_board(board);
    add_random_tile(board);
    add_random_tile(board);

    // Create 4×4 labels and attach to grid
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cells[i][j] = gtk_label_new(NULL);
            gtk_widget_set_hexpand(cells[i][j], TRUE);
            gtk_widget_set_vexpand(cells[i][j], TRUE);
            gtk_grid_attach(GTK_GRID(grid), cells[i][j], j, i, 1, 1);
        }
    }

    refresh_board();
    g_signal_connect(win, "key-press-event", G_CALLBACK(on_key_press), NULL);
    gtk_widget_show_all(win);
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new(
        "com.example.Game2048",
        G_APPLICATION_DEFAULT_FLAGS  // use default flags
    );
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}