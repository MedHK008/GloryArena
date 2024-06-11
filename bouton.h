#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

typedef struct
{
    GtkWidget* button; // bouton widget
    gchar* name;       // Nom du bouton
    gchar* label;      // Le texte sur le bouton
    gchar* lien;       // Chemin icone du bouton
    guint width;       // longueur du bouton
    guint height;      // largeur du bouton
    gchar* bgColor;    // Couleur de fond du GtkGrid
    gint pos_x;
    gint pos_y;
} bouton;

// INITIALISER LE BOUTON
bouton* init_button_simple(gchar* etiq, gchar* name, gint h, gint w, gint x, gint y)
{
    bouton* b = (bouton*)malloc(sizeof(bouton));
    if (!b) {
        printf("\nErreur d'allocation !!\n");
        exit(0);
    }

    b->name = name ? g_strdup(name) : NULL;
    b->label = etiq ? g_strdup(etiq) : NULL;
    b->width = w;
    b->height = h;
    b->lien = NULL;
    b->bgColor = NULL;
    b->pos_x = x;
    b->pos_y = y;
    return b;
}

// LIBERER LE BOUTON
void free_button_simple(bouton* b)
{
    if (b) {
        if (b->name) g_free(b->name);
        if (b->label) g_free(b->label);
        if (b->lien) g_free(b->lien);
        if (b->bgColor) g_free(b->bgColor);
        free(b);
    }
}

// CREER LE BOUTON SIMPLE
void creer_button_Simple(bouton* B)
{
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget* label = NULL;
    if (B->label) {
        label = gtk_label_new(B->label);
        gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
        gtk_widget_set_valign(label, GTK_ALIGN_CENTER);
        gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    }
    B->button = gtk_button_new();
    gtk_container_add(GTK_CONTAINER(B->button), vbox);

    if (B->name)
        gtk_widget_set_name(B->button, B->name);

    if (B->width > 0 && B->height > 0)
        gtk_widget_set_size_request(B->button, B->width, B->height);
}



void style_button(GtkWidget *button)
{
    const char *css_data =
        "button {"
        "background: rgba(0, 0, 0, 0.9);"
        "border: 2px solid #FF4500;"
        "border-radius: 10px;"
        "color: #FFFFFF;"
        "font-family: 'Pacifico', cursive;"
        "font-size: 20px;"
        "font-weight: bold;"
        "box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.3);"
        "transition: all 0.2s ease-in-out;}"
        "button:hover {"
        "background-color: #FF6B00;"
        "border-color: #FF6B00;}"
        "button:active {"
        "background-color: #FF3300;"
        "border-color: #FF3300;"
        "box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.3);"
        "}";

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, css_data, -1, NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(button), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

bouton* add_button(gchar* name, gchar* label, gint height, gint width,gint posx,gint posy)
{
    bouton* simpleButton = init_button_simple(label, name, height, width, posx, posy);
    creer_button_Simple(simpleButton);
    style_button(simpleButton->button);
    return simpleButton;
}


#endif // BOUTON_H_INCLUDED
