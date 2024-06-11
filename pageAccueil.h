#ifndef PAGEACCUEIL_H_INCLUDED
#define PAGEACCUEIL_H_INCLUDED



void destroy_window(GtkWidget *widget, gpointer data)
{
    GtkWidget *win = (GtkWidget *)data;
    gtk_widget_destroy(win);
    gtk_main_quit();
    exit(1);
}

void show_units_description(GtkWidget *widget, gpointer data)
{

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    Fenetre *F=add_window("Units Description","assets/backgrounds/gamelogo.png","descriptionWindow","#282828",1280,720,GTK_WIN_POS_CENTER,0,0,0,TRUE);

    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_widget_set_name(header_bar, "headerbar");
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Description");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(F->window), header_bar);

    ScrolledWindow *scrolledWindow = add_scrolledWindow(F->window, "scrolled_window", 1280, 720, TRUE, "#282828");
    gtk_container_add(GTK_CONTAINER(scrolledWindow->widget),vbox);

    ///to add the units description
    for (int i = 0; i < 5; i++)
    {
        GtkWidget *card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
        gtk_box_pack_start(GTK_BOX(vbox), card, TRUE, TRUE, 0);
        gtk_widget_set_name(card, "card");
        gtk_widget_set_size_request(card, 300, -1);
        GtkWidget *image = gtk_image_new_from_file(characters[i].image_path);
        gtk_box_pack_start(GTK_BOX(card), image, FALSE, FALSE, 0);
        GtkWidget *label = gtk_label_new(characters[i].description);
        gtk_widget_set_name(label,"unitDescription");
        gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
        gtk_widget_set_size_request(label, 600, -1);
        gtk_widget_set_margin_top(label, 10);
        gtk_box_pack_start(GTK_BOX(card), label, TRUE, TRUE, 10);
    }
    gtk_widget_show_all(F->window);
    gtk_main();
    free_scrolled_window(scrolledWindow);
    free_window(F);
}

/**
 * Fonction pour afficher la fenêtre du tutoriel avec les images et descriptions fournies.
 * Cette fonction crée une fenêtre avec une barre d'en-tête, une fenêtre défilante et une boîte verticale.
 * Elle remplit ensuite la boîte verticale avec 6 cartes de tutoriel, chacune contenant une image et une description.
 * La fonction est appelée lorsque l'utilisateur clique sur le bouton "tutoriel".
 *
 * @param widget Le widget qui a déclenché le signal.
 * @param data Les données définies par l'utilisateur associées au signal.
 */
void show_tutoriel(GtkWidget *widget, gpointer data)
{
    // Create a new window for the tutorial
    Fenetre *F=add_window("Tutorial","assets/backgrounds/gamelogo.png","tutorialWindow","#282828",800,600,GTK_WIN_POS_CENTER,0,0,0,TRUE);

    // Create a header bar for the window
    GtkWidget *header_bar = gtk_header_bar_new();
    gtk_widget_set_name(header_bar, "headerbar");
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Tutoriel");
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_window_set_titlebar(GTK_WINDOW(F->window), header_bar);

    // Create a vertical box for the tuto cards
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Create a scrolled window for the tutorial content
    ScrolledWindow *scrolledWindow = add_scrolledWindow(F->window, "scrolled_window", 800, 600, TRUE, "#282828");
    gtk_container_add(GTK_CONTAINER(scrolledWindow->widget),vbox);

    // Define the size of the images and the number of tuto cards
    const int image_width = 120;
    const int image_height = 100;
    const int num_tuto_cards = 6;



    // Add the tuto cards to the vertical box
    for (int i = 0; i < num_tuto_cards; i++) {
        GtkWidget *tuto_card = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_box_pack_start(GTK_BOX(vbox), tuto_card, TRUE, TRUE, 0);
        gtk_widget_set_name(tuto_card, "tutoCard");
        gtk_widget_set_size_request(tuto_card, 400, -1);
        GtkWidget *image = gtk_image_new_from_file(tutorial[i].image_path);
        gtk_widget_set_name(image, "tutoGif");
        gtk_widget_set_size_request(image, image_width, image_height);
        gtk_box_pack_start(GTK_BOX(tuto_card), image, FALSE, FALSE, 0);
        GtkWidget *label = gtk_label_new(tutorial[i].description);
        gtk_widget_set_name(label, "gameTuto");
        gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
        gtk_widget_set_size_request(label, 300, -1);
        gtk_widget_set_margin_top(label, 10);
        gtk_box_pack_start(GTK_BOX(tuto_card), label, TRUE, TRUE, 10);
    }

    // Show the tutorial window
    gtk_widget_show_all(F->window);
    gtk_main();
    free_scrolled_window(scrolledWindow);
    free_window(F);
}

/**
 * Fonction pour activer la page d'accueil du jeu.
 * Cette fonction configure la fenêtre principale, le barre d'outils, le conteneur fixe,
 * l'image de fond, les étiquettes, les boutons et d'autres éléments d'interface utilisateur.
 * Elle connecte également les signaux pour les boutons.
 **/
void debut_jeu(Fenetre *F)
{
    GtkWidget *background;
    GdkPixbufAnimation *animation;
    GdkPixbufLoader *loader;
    GError *error = NULL;
    gchar *contents;
    gsize length;

    load_css();
    /// for the header bar
    GtkWidget *header_bar = gtk_header_bar_new();// declaration
    gtk_widget_set_name(header_bar, "headerbar");// donner un nom au headerBar
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "GLORY ARENA");// affecter le titre
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), FALSE);// pour quiter le jeu seulement par le boutton quitter
    gtk_window_set_titlebar(GTK_WINDOW(F->window), header_bar);// affecter le HeaderBar a note fenetre


    /// for the fixed
    Fixed *fixed=init_gtk_fixed();
    gtk_container_add(GTK_CONTAINER(F->window), fixed->fixed);
    /// process of making the gif as background
    g_file_get_contents("assets/backgrounds/startBackground.gif", &contents, &length, &error);
    loader = gdk_pixbuf_loader_new();
    gdk_pixbuf_loader_write(loader, (const guchar *)contents, length, &error);
    g_free(contents);
    animation = gdk_pixbuf_loader_get_animation(loader);
    background = gtk_image_new_from_animation(animation);
    add_widget_to_fixed(fixed, background, 0, 0);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(hbox,"landingBox");

    texte *texteGauche = initialiser_texte(400,-1,"Jeu GTK3+ !!\nPROMOTION ILISI 2023-2026\nMODULE : Atelier de programmation\nENCADRER PAR: A. BEKKHOUCHA.",3,"cursive",18,NULL,"bold","#FF4500","#282828",NULL);
    Etiquette *labelGauche = add_label(hbox,texteGauche,FALSE,TRUE,0,0);
    gtk_box_pack_start(GTK_BOX(hbox), labelGauche->widget, TRUE, TRUE, 0);

    image *logo=add_image(1,"assets/backgrounds/gamelogo.png",GTK_ICON_SIZE_BUTTON,200,200);
    /// the buttons , assigning the signal and adding them to the the fixed
    bouton * button1=add_button("button","entrer jeu",30,300,0,0);
    bouton * button2=add_button("button","description guerrier",30,300,0,0);
    bouton * button3=add_button("button","comment jouer",30,300,0,0);
    bouton * button4=add_button("button","charger partie",30,300,0,0);
    bouton * button5=add_button("button","quitter",30,300,0,0);

    g_signal_connect(button1->button, "clicked", G_CALLBACK(startGame), NULL);
    g_signal_connect(button2->button, "clicked", G_CALLBACK(show_units_description), NULL);
    g_signal_connect(button3->button, "clicked", G_CALLBACK(show_tutoriel), NULL);
    g_signal_connect(button4->button, "clicked", G_CALLBACK(charger_partie_function),GINT_TO_POINTER(1));
    g_signal_connect(button5->button, "clicked", G_CALLBACK(destroy_window), F->window);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    gtk_box_pack_start(GTK_BOX(vbox), logo->widget, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button1->button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2->button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3->button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button4->button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button5->button, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(hbox), vbox, TRUE, TRUE, 0);

    texte *texteDroit = initialiser_texte(400,-1,"MADE BY :\nELBOUAZAOUI SALAH EDDINE\nCHROQUI HAMZA\nHERAK MOHAMMED\nMOUJAHID MOHAMED",3,"cursive",18,NULL,"bold","#FF4500","#282828",NULL);
    Etiquette *labelDroit = add_label(hbox,texteDroit,FALSE,TRUE,0,0);
    gtk_box_pack_start(GTK_BOX(hbox), labelDroit->widget, TRUE, TRUE, 0);


    add_widget_to_fixed(fixed,hbox , 10,0);

    gtk_widget_show_all(F->window);
    gtk_main();

    free_button_simple(button1);
    free_button_simple(button2);
    free_button_simple(button3);
    free_button_simple(button4);
    free_button_simple(button5);
    free_texte(texteDroit);
    free_texte(texteGauche);
    free_etiquette(labelDroit);
    free_etiquette(labelGauche);
    free(hbox);
    free(vbox);
    free_gtk_fixed_info(fixed);
    free(header_bar);
}

#endif // PAGEACCUEIL_H_INCLUDED
