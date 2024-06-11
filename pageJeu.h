#ifndef PAGEJEU_H_INCLUDED
#define PAGEJEU_H_INCLUDED

void startGame()
{
    F1=add_window("GLORY ARENA","assets/backgrounds/gamelogo.png","gamePage",NULL,1280,720,GTK_WIN_POS_CENTER,0,0,1,FALSE);
    // Creer un conteneur fixed pour organiser les widgets
    Fixed* fix = init_gtk_fixed();
    gtk_container_add(GTK_CONTAINER(F1->window), fix->fixed);
    g_signal_connect(F1->window, "key_press_event", G_CALLBACK(on_key_press), F1->window);

    //Choisir le joueur
    ComboBox *playerComboBox = add_comboBox(fix->fixed, "playerComboBox", 30, 40);
    combobox_add(playerComboBox, "Choose your player");
    combobox_add(playerComboBox, "Arab");
    combobox_add(playerComboBox, "Aztec");
    combobox_add(playerComboBox, "Mongol");
    combobox_add(playerComboBox, "Persian");
    combobox_add(playerComboBox, "Roman");
    g_signal_connect(playerComboBox->comboBox, "changed", G_CALLBACK(on_combobox_changed), NULL);


    // Ajouter un cadre pour organiser les widget
    frame *fr=  add_frame(fix->fixed,"sahara",-1,-1,NULL,GTK_SHADOW_NONE,50,100);
    gtk_widget_set_size_request(fr->widget, 1000, 600);

    fixed1=init_gtk_fixed();
    gtk_container_add(GTK_CONTAINER(fr->widget),fixed1->fixed);

    image *arab_image = add_gif_modal(fix->fixed,2,"assets/sprites/buttonsIdle/ARAB_1.gif",GTK_ICON_SIZE_DIALOG, 80, 80, -1, -1);
    bouton *b_arab = add_button("bA",NULL,60,65, 350, 40);
    add_widget_to_fixed(fix, b_arab->button,b_arab->pos_x,b_arab->pos_y);
    gtk_button_set_image(GTK_BUTTON(b_arab->button),arab_image->widget);
    g_signal_connect(b_arab->button, "clicked", G_CALLBACK(on_image_clicked),GINT_TO_POINTER(0));

    image *aztec_image = add_gif_modal(fix->fixed, 2, "assets/sprites/buttonsIdle/AZTEC_1.gif", GTK_ICON_SIZE_DIALOG, 80, 80, -1,-1);
    bouton *b_aztec = add_button("bAz",NULL,60,65, 500, 40);
    add_widget_to_fixed(fix, b_aztec->button,b_aztec->pos_x,b_aztec->pos_y);
    gtk_button_set_image(GTK_BUTTON(b_aztec->button),aztec_image->widget);
    g_signal_connect(b_aztec->button, "clicked", G_CALLBACK(on_image_clicked), GINT_TO_POINTER(1));

    image *viking_image = add_gif_modal(fix->fixed, 2, "assets/sprites/buttonsIdle/MONGOL_1.gif", GTK_ICON_SIZE_DIALOG, 80, 80, -1, -1);
    bouton *b_viking = add_button("bM",NULL,60,65, 650, 40);
    add_widget_to_fixed(fix, b_viking->button,b_viking->pos_x,b_viking->pos_y);
    gtk_button_set_image(GTK_BUTTON(b_viking->button),viking_image->widget);
    g_signal_connect(b_viking->button, "clicked", G_CALLBACK(on_image_clicked), GINT_TO_POINTER(4));

    image *roman_image = add_gif_modal(fix->fixed, 2, "assets/sprites/buttonsIdle/ROMAN_1.gif", GTK_ICON_SIZE_DIALOG, 80, 80, -1, -1);
    bouton *b_roman = add_button("bR",NULL,60,65, 800, 40);
    add_widget_to_fixed(fix, b_roman->button,b_roman->pos_x,b_roman->pos_y);
    gtk_button_set_image(GTK_BUTTON(b_roman->button),roman_image->widget);
    g_signal_connect(b_roman->button, "clicked", G_CALLBACK(on_image_clicked),GINT_TO_POINTER(3));

    image *persian_image = add_gif_modal(fix->fixed, 2, "assets/sprites/buttonsIdle/PERSIAN_1.gif", GTK_ICON_SIZE_BUTTON, 80, 80, -1, -1 );
    bouton *b_persian = add_button("bP",NULL,60,65, 950, 40);
    add_widget_to_fixed(fix, b_persian->button,b_persian->pos_x,b_persian->pos_y);
    gtk_button_set_image(GTK_BUTTON(b_persian->button),persian_image->widget);
    g_signal_connect(b_persian->button, "clicked", G_CALLBACK(on_image_clicked),GINT_TO_POINTER(2) );



    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    add_widget_to_fixed(fix, hbox, 1120, 140); // Position the box

    // Add buttons to the horizontal box

    bouton *play = add_button("play", "PLAY",40, 110,0,0);
    g_signal_connect(play->button, "clicked", G_CALLBACK(playGame), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), play->button, TRUE, TRUE, 0);

    bouton *switcher= add_button("switch", "Switch Field",40, 110,0,0);
    g_signal_connect(switcher->button, "clicked", G_CALLBACK(switch_field), fr->widget);
    gtk_box_pack_start(GTK_BOX(hbox), switcher->button, TRUE, TRUE, 0);

    bouton *sauvegarde = add_button("sauvegarde", "sauvegarde",40, 80,0,0);
    g_signal_connect(sauvegarde->button, "clicked", G_CALLBACK(declencher_sauvegarde), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), sauvegarde->button, TRUE, TRUE, 0);

    bouton *reset = add_button("Reset", "Reset",40, 80,0,0);
    g_signal_connect(reset->button, "clicked", G_CALLBACK(Reset_Function), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), reset->button, TRUE, TRUE, 0);

    bouton *quit = add_button("quit", "Quit Game",40, 80,0,0);
    g_signal_connect(quit->button, "clicked", G_CALLBACK(Reset_Function),NULL);
    g_signal_connect(quit->button, "clicked", G_CALLBACK(on_destroy_parent_window), F1->window);
    gtk_box_pack_start(GTK_BOX(hbox), quit->button, TRUE, TRUE, 0);

    g_signal_connect(F1->window, "key_press_event", G_CALLBACK(on_clavier_press),NULL);

    if(charger_partie==1)
    {
        Guerier* g;
        for(int i=0;i<5;i++)
        {
            for(int j =0 ;j<groupe[i]->nbrGuerier;j++)
            {
                g=groupe[i]->guerrier[j];
                g->area=gtk_drawing_area_new();
                gtk_widget_set_size_request(g->area,1100,600);
                g_signal_connect(g->area,"draw", G_CALLBACK(on_draw),GINT_TO_POINTER(i));
                printf("here\n");
                gtk_fixed_put(GTK_FIXED(fixed1->fixed),g->area,0,0);
            }
        }
    }
    gtk_widget_show_all(F1->window);
    gtk_main();
}

#endif // PAGEJEU_H_INCLUDED
