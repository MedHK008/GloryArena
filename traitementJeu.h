#ifndef TRAITEMENTJEU_H_INCLUDED
#define TRAITEMENTJEU_H_INCLUDED

///les fonctions de ce fichier
void on_combobox_changed(GtkComboBox*,gpointer);
void switch_field(GtkWidget*,gpointer);
gboolean on_draw(GtkWidget*,cairo_t*, gpointer);
void force_dans_sa_place(Guerier*);
void ajouter_img(Guerier*,int);
void ajouterGuerier(int);
void traitement_struct(int);
void on_image_clicked(GtkWidget*,gpointer);
void Reset_Function(GtkWidget*,gpointer);
void Arreter_jeu(GtkWidget*,gpointer);
gboolean on_clavier_press(GtkWidget*,GdkEventKey*);

/// Fonction pour gérer le changement de sélection dans la combobox
void on_combobox_changed(GtkComboBox *widget, gpointer data)
{
    /// Récupérer le texte de l'élément sélectionné
    const gchar *player = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widget));
    /// Affecter le type de joueur en fonction du texte
   if(PLAY!=0) return;
    if (g_strcmp0(player, "Arab") == 0) {
        type_player = 0; /// Arab
    } else if (g_strcmp0(player, "Aztec") == 0) {
        type_player = 1; /// Aztec
    } else if (g_strcmp0(player, "Persian") == 0) {
        type_player = 2; /// Persian
    } else if (g_strcmp0(player, "Roman") == 0) {
        type_player = 3; /// Roman
    } else if (g_strcmp0(player, "Mongol") == 0) {
        type_player = 4; /// Mongol
    } else {
        type_player = -1; /// Aucun joueur sélectionné
    }
    g_free((gpointer) player);
}

///pour changer l'arene
void switch_field(GtkWidget *widget, gpointer data)
{
    if(NB==0)
    {
        /// Verifie si le nom actuel du widget est "frame_field"
        if (strcmp("sahara", gtk_widget_get_name(GTK_WIDGET(data))) == 0 ) {
            /// Change le nom du widget a "frame_field_Forest" s'il est actuellement "frame_field"
            gtk_widget_set_name(GTK_WIDGET(data), "forest");
            type_field=1;
        }
        else
        {
            /// Change le nom du widget a "frame_field" s'il n'est pas actuellement "frame_field"
            gtk_widget_set_name(GTK_WIDGET(data), "sahara");
            type_field=0;
        }
    }
}

/// Fonction qui dessine les guerriers en fonction de leur état et de leur type
gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    /// Conversion du pointeur de type gpointer en entier représentant le type de groupe
    int type = GPOINTER_TO_INT(data);
    /// Obtient le groupe de guerriers correspondant au type
    Gueriers *groupeType = groupe[type];
    /// Boucle à travers chaque guerrier dans le groupe
    for (int i = 0; i < groupeType->nbrGuerier; i++)
    {
        /// Pointeur vers le guerrier actuel
        Guerier *g = groupeType->guerrier[i];
        /// Vérifie que le guerrier et ses indices d'état et d'image sont valides
        if (g && g->etat >= 0 && g->etat < 6 && g->index_img >= 0 && g->index_img < 7)
        {
            /// Vérifie que l'image correspondant à l'état et à l'index est valide
            if (g && g->img[g->etat][g->index_img])
            {
                /// Définition de la source pour le dessin avec l'image du guerrier
                gdk_cairo_set_source_pixbuf(cr, g->img[g->etat][g->index_img], g->pos_x, g->pos_y);
                /// Dessine l'image sur le contexte cairo
                cairo_paint(cr);
            }
            else
            {
                /// Message d'erreur si l'image du guerrier est invalide
                fprintf(stderr, "Erreur: GdkPixbuf invalide pour guerrier %d,%d\n", i, g->type);
            }
        }
        else
        {
            /// Message d'erreur si l'état ou l'index de l'image du guerrier est invalide
            fprintf(stderr, "Erreur: Etat ou index_img invalide pour guerrier (%d,%d)\n", type, i);
        }
    }
    /// Retourne TRUE pour indiquer que le dessin est terminé
    return TRUE;
}

void force_dans_sa_place(Guerier *g)
{
    if(place[g->type]==type_field)
    {
      g->attaque+=10;
      g->defense+=10;
      g->vitesse+=5;
      g->endurance+=10;
      g->rayon+=20;
    }
    else
    {
      g->attaque-=10;
      g->defense-=10;
      g->vitesse-=5;
      g->endurance-=10;
      g->rayon-=20;
    }
}

void ajouter_img(Guerier *G, int type)
{
    char *types[] = {"arab", "aztec", "persian", "roman", "mongole"};
    char filename[100];
    GdkPixbuf *img=NULL;

    if (type < 0 || type > 4) {
        fprintf(stderr, "Erreur: Type de guerrier invalide\n");
        return;
    }

    char *folder = types[type];
    for (int i =1; i <= 7; i++) {
        sprintf(filename, "assets/sprites/%s/run/run (%d).png", folder, i);
        img = gdk_pixbuf_new_from_file(filename, NULL);
        if (img == NULL) {
            fprintf(stderr, "Erreur: Impossible de charger l'image %s\n", filename);
            continue;
        }
        if(i==1) G->img[0][0] = img;
        G->img[1][i-1] = img;
    }

    /// Load attack images
    for (int i = 1; i <= 7; i++) {
        sprintf(filename, "assets/sprites/%s/atk/atk (%d).png", folder, i);
        img = gdk_pixbuf_new_from_file(filename, NULL);
        if (img == NULL) {
            fprintf(stderr, "Erreur: Impossible de charger l'image %s\n", filename);
            continue;
        }
        G->img[2][i-1] = img;
    }

    /// Load death images
    for (int i = 1; i <= 7; i++) {
        sprintf(filename, "assets/sprites/%s/death/death (%d).png", folder, i);
        img = gdk_pixbuf_new_from_file(filename, NULL);
        if (img == NULL) {
            fprintf(stderr, "Erreur: Impossible de charger l'image %s\n", filename);
            continue;
        }
        G->img[3][i-1] = img;
    }

    /// Load inverse run images
    for (int i = 1; i <= 7; i++) {
        sprintf(filename, "assets/sprites/%s_inverse/run/run (%d).png", folder, i);
        img = gdk_pixbuf_new_from_file(filename, NULL);
        if (img == NULL) {
            fprintf(stderr, "Erreur: Impossible de charger l'image %s\n", filename);
            continue;
        }
        G->img[4][i-1] = img;
    }

    /// Load inverse attack images
    for (int i = 1; i <= 7; i++) {
        sprintf(filename, "assets/sprites/%s_inverse/atk/atk (%d).png", folder, i);
        img = gdk_pixbuf_new_from_file(filename, NULL);
        if (img == NULL) {
            fprintf(stderr, "Erreur: Impossible de charger l'image %s\n", filename);
            continue;
        }
        G->img[5][i-1] = img;
    }
}

void ajouterGuerier(int type)
{
    int nbr=groupe[type]->nbrGuerier;
    groupe[type]->guerrier[nbr]=(Guerier*)g_malloc(sizeof(Guerier));
    groupe[type]->guerrier[nbr]->lignevie=100;
    groupe[type]->guerrier[nbr]->index_img=0;
    groupe[type]->guerrier[nbr]->frame_img=7;
    groupe[type]->guerrier[nbr]->etat=0;
    groupe[type]->guerrier[nbr]->P=(Lst_Proches*)malloc(sizeof(Lst_Proches));
    groupe[type]->guerrier[nbr]->P->nbproche=0;
    groupe[type]->guerrier[nbr]->id = nbr;
    groupe[type]->guerrier[nbr]->type=type;
    groupe[type]->guerrier[nbr]->attaque=carac[type][0];
    groupe[type]->guerrier[nbr]->defense=carac[type][1];
    groupe[type]->guerrier[nbr]->endurance=carac[type][2];
    groupe[type]->guerrier[nbr]->vitesse=carac[type][3];
    groupe[type]->guerrier[nbr]->pos_x=rand()%bord[type_field].largeur;
    int hauteur=bord[type_field].max_hauteur - bord[type_field].min_hauteur;
    groupe[type]->guerrier[nbr]->pos_y=rand()%hauteur + bord[type_field].min_hauteur;
    force_dans_sa_place(groupe[type]->guerrier[nbr]);///modifier les caracteristique par rapport a ;ascene choisie
    groupe[type]->guerrier[nbr]->power=(groupe[type]->guerrier[nbr]->attaque + groupe[type]->guerrier[nbr]->defense)*0.35 + groupe[type]->guerrier[nbr]->endurance*0.2 +groupe[type]->guerrier[nbr]->vitesse*0.1;
    groupe[type]->guerrier[nbr]->rayon=carac[type][4];
    ajouter_img(groupe[type]->guerrier[nbr],type);
    groupe[type]->guerrier[nbr]->combat=-1;
    groupe[type]->guerrier[nbr]->mat=0;
    groupe[type]->guerrier[nbr]->animation_en_cours=FALSE;
    if(nbr==0) NB++;
    groupe[type]->nbrGuerier++;
}

void traitement_struct(int type)
{
    ajouterGuerier(type);
    Guerier* g=groupe[type]->guerrier[groupe[type]->nbrGuerier-1];
    g->area=gtk_drawing_area_new();
    gtk_widget_set_size_request(g->area,1000,600);
    g_signal_connect(g->area, "draw", G_CALLBACK(on_draw),GINT_TO_POINTER(type));
    gtk_fixed_put(GTK_FIXED(fixed1->fixed),g->area,0,0);
}

void on_image_clicked(GtkWidget *widget, gpointer user_data)
{
    int choix = GPOINTER_TO_INT(user_data);
    if (choix >= 0 && choix < 5 && groupe[choix]->nbrGuerier <= 4 && PLAY == 0)
    {
        traitement_struct(choix);
        /// Afficher le dernier guerrier ajouté
        gtk_widget_show(groupe[choix]->guerrier[groupe[choix]->nbrGuerier - 1]->area);
    }
}

void Arreter_jeu(GtkWidget*widget,gpointer data)
{
    if(PLAY==0 )return;
    PLAY=0;
    for(int i = 0 ;i<5;i++){
        for(int j=0;j<groupe[i]->nbrGuerier;j++)
        {
             if (((i != type_player) || (j != 0)) && groupe[i]->guerrier[j]->lignevie>0)
             {
                groupe[i]->guerrier[j]->etat = 0;
                groupe[i]->guerrier[j]->animation_en_cours=FALSE;
             }
        }
    }
}

void Reset_Function(GtkWidget*widget,gpointer data)
{

    if(PLAY==1 || NB==0) return;
    PLAY=0;
    for(int i=0;i<5;i++)
    {
        int a=groupe[i]->nbrGuerier;
        for(int j =0 ; j<a ;j++)
        {
            free(groupe[i]->guerrier[j]);
            gtk_widget_queue_draw(groupe[i]->guerrier[j]->area);
        }
        groupe[i]->nbrGuerier=0;
    }
    NB=0;
}

gboolean on_clavier_press(GtkWidget *widget, GdkEventKey *event)
{
    if(PLAY==0 || NB <=1) return FALSE;
    if(type_player!=-1 && groupe[type_player]->guerrier[0]!=NULL && groupe[type_player]->guerrier[0]->etat!=3)
    {
        if (event->keyval ==GDK_KEY_Left)
            run_inv_player(NULL,NULL);
        else if(event->keyval ==GDK_KEY_Right)
            run_player(NULL,NULL);
        else if(event->keyval ==GDK_KEY_Up)
            haut_player(NULL,GINT_TO_POINTER(1));
        else if(event->keyval ==GDK_KEY_Down)
            bas_player(NULL,GINT_TO_POINTER(2));
        else if(event->keyval ==GDK_KEY_a || event->keyval ==GDK_KEY_A)
            attaque_player(NULL,NULL);
    }
    if(event->keyval==GDK_KEY_p)
        Arreter_jeu(NULL,NULL);
    return TRUE;
}

#endif /// TRAITEMENTJEU_H_INCLUDED
