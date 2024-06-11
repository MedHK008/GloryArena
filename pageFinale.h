#ifndef PAGEFINALE_H_INCLUDED
#define PAGEFINALE_H_INCLUDED



void Replay(GtkWidget* f,gpointer data)
{
  gtk_widget_hide(GTK_WIDGET(data));
  Reset_Function(NULL,NULL);
  return;
}
//void winners(int type)
//{
//
//    GtkWidget *image;
//    GdkPixbufAnimation *animation;
//    GdkPixbufLoader *loader;
//    GError *error = NULL;
//    gchar *contents;
//    gsize length;
//
//    Fenetre* fenetre = add_window("the winner","assets/backgrounds/WIN.jpg","FFFFF",NULL,450,300,GTK_WIN_POS_CENTER,100,200,1,TRUE);
//    /// for the header bar
//    GtkWidget *header_bar = gtk_header_bar_new();// declaration
//    gtk_widget_set_name(header_bar, "headerbar");// donner un nom au headerBar
//    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "GLORY ARENA");// affecter le titre
//    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);// pour quiter le jeu seulement par le boutton quitter
//    gtk_window_set_titlebar(GTK_WINDOW(fenetre->window), header_bar);// affecter le HeaderBar a note fenetre
//
//
//    Fixed* fix = init_gtk_fixed();
//    gtk_container_add(GTK_CONTAINER(fenetre->window),fix->fixed);
//
//
//    g_file_get_contents("assets\backgrounds\WINNNER.gif", &contents, &length, &error);
//    loader = gdk_pixbuf_loader_new();
//    gdk_pixbuf_loader_write(loader, (const guchar *)contents, length, &error);
//    g_free(contents);
//    animation = gdk_pixbuf_loader_get_animation(loader);
//    image = gtk_image_new_from_animation(animation);
//    add_widget_to_fixed(fix, image, 0, 0);
//
//
//    texte* txt=initialiser_texte(20,30," the winner are :",1,NULL,10,NULL,NULL,"white","#000000",NULL);
//    frame *fr = initialiser_frame(NULL,"FR", 0.5,0.5, txt, GTK_SHADOW_NONE);
//    creer_frame(fr);
//    gtk_widget_set_size_request(fr->widget, 200, 200);
//    gtk_fixed_put(GTK_FIXED(fix->fixed),fr->widget,200,120);
//    const char* frame_names[] = {"fr_arabe", "fr_aztic", "fr_iran", "fr_roman", "fr_viking"};
//    if (type >= 0 && type < 5) {
//        gtk_widget_set_name(fr->widget, frame_names[type]);
//    }
//
//    bouton *Reset = add_button("Reset", "Rejouer",40, 80,220,320);
//    add_widget_to_fixed(fix, Reset->button, Reset->pos_x,Reset->pos_y);
//    g_signal_connect(Reset->button, "clicked", G_CALLBACK(Reset_Function),NULL);
//    g_signal_connect(Reset->button, "clicked", G_CALLBACK(on_destroy_parent_window), fenetre->window);
//    g_signal_connect(fenetre->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
//    gtk_widget_show_all(fenetre->window);
//    gtk_main();
//}

void winners(int type)
{
    Fenetre* fenetre = add_window("the winner", "assets/backgrounds/WIN.jpg", "FFFFF", NULL, 450, 300, GTK_WIN_POS_CENTER, 100, 200, 1, TRUE);
    GtkWidget* warrior;
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_widget_set_name(header_bar, "headerbar");
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "GLORY ARENA");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(fenetre->window), header_bar);

    Fixed* fix = init_gtk_fixed();
    gtk_container_add(GTK_CONTAINER(fenetre->window), fix->fixed);

    GtkWidget* winner=gtk_image_new_from_file("assets/backgrounds/winnerBorder.png");
    add_widget_to_fixed(fix,winner,25,0);
    switch(type)
    {
        case 0: warrior=gtk_image_new_from_file("assets/sprites/descriptionIdle/ARAB.gif");
                break;
        case 1: warrior=gtk_image_new_from_file("assets/sprites/descriptionIdle/AZTEC.gif");
                break;
        case 2: warrior=gtk_image_new_from_file("assets/sprites/descriptionIdle/IRAN.gif");
                break;
        case 3: warrior=gtk_image_new_from_file("assets/sprites/descriptionIdle/ROMAN.gif");
                break;
        case 4: warrior=gtk_image_new_from_file("assets/sprites/descriptionIdle/MONGOL.gif");
                break;
    }

    add_widget_to_fixed(fix,warrior,175,130);

    bouton *Reset = add_button("Reset", "Rejouer", 40, 80,185,250);
    add_widget_to_fixed(fix, Reset->button, Reset->pos_x, Reset->pos_y);
    g_signal_connect(Reset->button, "clicked", G_CALLBACK(Reset_Function), NULL);
    g_signal_connect(Reset->button, "clicked", G_CALLBACK(on_destroy_parent_window), fenetre->window);
    g_signal_connect(fenetre->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(fenetre->window);
    gtk_main();
}


#endif // PAGEFINALE_H_INCLUDED
