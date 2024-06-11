#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED


typedef struct
{
  GtkWidget *window;
  gchar *titre;
  gchar *icon;
  gchar *name;
  gchar *bgcolor;
  guint hauteur;
  guint largeur;
  gint posx;
  gint posy;
  GtkWindowPosition position_init;
  guint border_width;
  gboolean modifiable;
} Fenetre;

Fenetre* initialiser_win
(gchar* titre, gchar* icon_path, gchar* name, gchar* bgcolor, guint w, guint h, GtkWindowPosition pos, gint x, gint y, guint border, gboolean resizable)
{
    Fenetre* win = (Fenetre*) malloc(sizeof(Fenetre));
    if (!win) {
        printf("\nErreur d'allocation de mémoire.");
        exit(-1);
    }

    win->window = NULL;

    // Copiez le titre
    win->titre = titre ? g_strdup(titre) : NULL;

    // Copiez le chemin de l'icône
    win->icon = icon_path ? g_strdup(icon_path) : NULL;

    // Copiez le nom de la fenêtre
    win->name = name ? g_strdup(name) : NULL;

    // Copiez la couleur de fond
    win->bgcolor = bgcolor ? g_strdup(bgcolor) : NULL;

    win->hauteur = h;
    win->largeur = w;
    win->position_init = pos;
    win->posx = x;
    win->posy = y;
    win->border_width = border;
    win->modifiable = resizable;

    return win;
}

void create_window(Fenetre *W)
{
    W->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    if (W->titre)
        gtk_window_set_title(GTK_WINDOW(W->window), W->titre);

    if (W->icon)
        gtk_window_set_icon_from_file(GTK_WINDOW(W->window), W->icon, NULL);

    if (W->name)
        gtk_widget_set_name(W->window, W->name);

    if (W->hauteur > 0 && W->largeur > 0)
        gtk_window_set_default_size(GTK_WINDOW(W->window), W->largeur, W->hauteur);

    if (W->posx >= 0 && W->posy >= 0)
        gtk_window_move(GTK_WINDOW(W->window), W->posx, W->posy);

    else
        gtk_window_set_position(GTK_WINDOW(W->window), W->position_init);

    gtk_container_set_border_width(GTK_CONTAINER(W->window), W->border_width);
    gtk_window_set_resizable(GTK_WINDOW(W->window), W->modifiable);
}

void free_window(Fenetre* win)
{
    if (win)
    {
        if (win->titre) g_free(win->titre);
        if (win->icon) g_free(win->icon);
        if (win->name) g_free(win->name);
        if (win->bgcolor) g_free(win->bgcolor);
        free(win);
    }
}

Fenetre* add_window
(gchar* title, gchar* icon_path, gchar* name, gchar* bgcolor, guint width, guint height, GtkWindowPosition pos_init, guint posx, guint posy, guint border_size, gboolean resizable)
{
    Fenetre* ma_fenetre = initialiser_win(title, icon_path, name, bgcolor, width, height, pos_init, posx, posy, border_size, resizable);
    create_window(ma_fenetre);
    return ma_fenetre;
}


#endif // FENETRE_H_INCLUDED
