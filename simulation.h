#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED



///les fonction de ce fichier
void playGame(GtkWidget*, gpointer);
void initialize_movement_states(Guerier*);
gboolean update_animation(gpointer);
void change_pos_PR(Guerier*);
void update_guerriers(Guerier*);
int update_movement_state(Guerier*);
void move_towards_enemy(Guerier*, Guerier*);
gboolean supprimer_delayed(gpointer);
void supprimer(Guerier *);
void death(Guerier *);
void attaque(Guerier *, Guerier*);
gboolean update_animation_attack(gpointer);
gboolean update_animation_death(gpointer);
void dans_la_zone(Guerier*);
int compare_proches(const void*, const void*);
void info_enemis(Guerier*,int*);

/// Fonction qui démarre la partie
void playGame(GtkWidget *widget, gpointer data)
{
    /// Vérifie si le jeu est déjà en cours ou s'il ne reste qu'un seul groupe de guerriers
    if (PLAY == 1 || NB == 1) return;
    /// Démarre le jeu en mettant PLAY à 1
    PLAY = 1;
    deja_visit=-1;
    /// Parcourt tous les groupes de guerriers
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < groupe[i]->nbrGuerier; j++)
        {
            /// Vérifie si le guerrier appartient au joueur actuel et s'il n'est pas le premier du joueur
            if ((i != type_player) || (j != 0))
            {
                /// Récupère le guerrier courant
                Guerier *g = groupe[i]->guerrier[j];
                /// Vérifie si le guerrier existe, s'il n'est pas mort et s'il n'a pas déjà une animation en cours
                if (g != NULL && g->etat != 3 && !g->animation_en_cours)
                {
                    /// Initialise les états de mouvement du guerrier
                    initialize_movement_states(g);
                    /// Active l'animation du guerrier en appelant la fonction update_animation
                    g->animation_en_cours = TRUE;
                    g_timeout_add(150, update_animation, g);
                }
            }
        }
    }
}

void initialize_movement_states(Guerier *g)
{
    /// Génère une direction aléatoire sur 8 directions pour le mouvement
    int dir = rand() % NUM_DIRECTIONS;

    /// Affecte la direction générée à l'état de mouvement du guerrier
    movement_states[g->id][g->type].direction = dir;

    /// Définit l'état du guerrier en fonction de la direction
    if ((dir >= 0 && dir <= 2) || dir == 4 || dir == 5)
        g->etat = 1; /// Si la direction est vers le haut-droite, droite, ou bas-droite
    else
        g->etat = 4; /// Si la direction est vers le bas-gauche, gauche, ou haut-gauche
    ///a propos de la direction haut et bas dependent de l'etat precedente si 1 vers la droite.
    ///si 4 vers la gauche

    /// Initialise le nombre de pas restants avant de changer de direction
    movement_states[g->id][g->type].steps_remaining = STEPS_BEFORE_DIRECTION_CHANGE;
}

gboolean update_animation(gpointer data)
{
    Guerier *g = (Guerier *)data;

    if (NB == 0 ||(g->lignevie <= 0)) {
        return FALSE;
    }

    if ((g->etat == 0 || NB == 1) && g->lignevie > 0)
    {
        g->etat = 0;
        g->index_img = 0;
         if (g->area == NULL) {
            g_warning("Le widget est NULL");
        } else if (!GTK_IS_WIDGET(g->area)) {
            g_warning("Widget GTK invalide");
        } else {
            gtk_widget_queue_draw(g->area);
        }
        g->animation_en_cours = FALSE;

        if(NB==1 && deja_visit==-1)
        {
            PLAY=0;
            deja_visit++;
            winners(g->type);

        }

        return FALSE;
    }
     if(PLAY==0)  return FALSE;

    if (g->etat == 1 || g->etat == 4 || g->combat == 1) {
        g->index_img = (g->index_img + 1) % 7;
        gtk_widget_queue_draw(g->area);

        if (g->etat == 1 || g->etat == 4) {
            change_pos_PR(g);
        }

        update_guerriers(g);
    }

    return TRUE;
}

void change_pos_PR(Guerier *g)
{
    /// Tableaux statiques définissant les changements de position pour chaque direction
    static const int dx[NUM_DIRECTIONS] = {10, 0, 10, -10, 0, 10, -10, -10};
    static const int dy[NUM_DIRECTIONS] = {0, -10, 10, 0, 10, -10, -10, 10};

    /// Obtient la direction actuelle du guerrier depuis les états de mouvement
    int direction = movement_states[g->id][g->type].direction;

    /// Met à jour l'état de mouvement et obtient la nouvelle direction si nécessaire
    if (update_movement_state(g)) {
        direction = movement_states[g->id][g->type].direction;
    }

    /// Calcule les nouvelles coordonnées en fonction de la direction
    int new_x = g->pos_x + dx[direction];
    int new_y = g->pos_y + dy[direction];

    /// Vérifie si les nouvelles coordonnées sont dans les limites du terrain
    if (new_x >= 5 && new_y >= bord[type_field].min_hauteur &&
        new_x < bord[type_field].largeur && new_y < bord[type_field].max_hauteur)
    {
        /// Met à jour la position du guerrier
        g->pos_x = new_x;
        g->pos_y = new_y;
    }
    else
    {
        /// Gestion des collisions et des changements de direction
        if (new_x >= bord[type_field].largeur) {
            g->etat = 4; /// Change l'état du guerrier
            movement_states[g->id][g->type].direction = 3; /// Change la direction à gauche
        }
        else if (new_x < 5) {
            g->etat = 1; /// Change l'état du guerrier
            movement_states[g->id][g->type].direction = 0; /// Change la direction à droite
        }
        else if (new_y < bord[type_field].min_hauteur) {
            movement_states[g->id][g->type].direction = 4; /// Change la direction vers le bas
        }
        else if (new_y > bord[type_field].max_hauteur) {
            movement_states[g->id][g->type].direction = 1; /// Change la direction vers le haut
        }
        /// Met à jour la position en tenant compte de la nouvelle direction
        g->pos_x += dx[direction];
        g->pos_y += dy[direction];
        /// Réinitialise le nombre de pas restants avant le prochain changement de direction
        movement_states[g->id][g->type].steps_remaining = STEPS_BEFORE_DIRECTION_CHANGE;
    }
}

void update_guerriers(Guerier *g)
{
    int i;
    Guerier *target;

    /// Vérifie si le guerrier est en combat ou non
    if (g->combat == -1) {
        /// Si le guerrier n'est pas en combat, effectue des actions hors combat
        dans_la_zone(g); /// enregistre dans la structure Lst_Proches les gueriers detectés
        info_enemis(g, &i); /// Obtient des informations sur l'ennemis le plus proche et verifie les conditions
        if (i == -1)
            target = NULL; /// Aucune cible ennemie à proximité
        else
            target = groupe[g->P->proches[i].type]->guerrier[g->P->proches[i].rang]; /// Sélectionne la cible ennemie la plus proche
    } else {
///         Si le guerrier est en combat, sélectionne la cible de combat actuelle
        int ind = g->P->ind_proche;
        target = groupe[g->P->proches[ind].type]->guerrier[g->P->proches[ind].rang];
    }
    /// Vérifie s'il y a une cible valide pour le guerrier
    if (target != NULL) {

        if ((g->combat == 1 && target->combat == 0) || (g->combat == -1 && target->combat == -1))
            move_towards_enemy(g, target); /// Déplace le guerrier vers la cible
    }
    /// Réinitialise le nombre de guerriers proches si le guerrier n'est pas en combat
    if (g->combat == -1)
        g->P->nbproche = 0;
}

int update_movement_state(Guerier *g)
{
    /// Vérifie si le nombre de pas restants est inférieur ou égal à 0
    if (movement_states[g->id][g->type].steps_remaining <= 0) {
        /// Réinitialise l'état de mouvement du guerrier
        initialize_movement_states(g);
        /// Retourne 1 pour indiquer que l'état a été réinitialisé
        return 1;
    }

    /// Décrémente le nombre de pas restants
    movement_states[g->id][g->type].steps_remaining--;
    /// Retourne 0 pour indiquer que l'état n'a pas été réinitialisé
    return 0;
}

void move_towards_enemy(Guerier *g, Guerier *enemy)
{
    /// Affiche un message de débogage indiquant que la fonction de déplacement commence
    printf("ENTRER MOVE\n");

    /// Calcule les différences en position entre le guerrier et l'ennemi
    int dx = enemy->pos_x - g->pos_x;
    int dy = enemy->pos_y - g->pos_y;

    /// Vérifie si l'ennemi est à portée pour lancer une attaque
    if (abs(dx) <= 20 && abs(dy) <= 10)
    {
        /// Affiche un message de débogage indiquant le début du combat
        printf("DEBUT COMBAT\n");

        /// Marque les guerriers comme engagés dans le combat
        g->combat = 1;
        enemy->combat = 0;

        /// Change l'état des guerriers en état d'attaque
        g->etat = (g->etat == 4) ? 5 : 2;
        enemy->etat = (g->etat == 5) ? 2 : 5;

        /// Lance une attaque du guerrier sur l'ennemi
        attaque(g, enemy);

        /// Diminue les points de vie de l'ennemi en fonction de l'attaque du guerrier
        enemy->lignevie -= (g->attaque - enemy->defense * 0.9);

        /// Vérifie si l'ennemi est mort après l'attaque
        if (enemy->lignevie <= 0) {
            /// Si l'ennemi est mort, lance l'animation de mort de l'ennemi et planifie sa suppression
            death(enemy);
            g->etat = 1;
            g->combat = -1;
            g_timeout_add(1000, supprimer_delayed, enemy);
            return;
        } else {

            if(enemy->type!= type_player && g->P->proches[g->P->ind_proche].rang!=0)
            {
                /// Si l'ennemi est toujours vivant, lance une attaque de l'ennemi sur le guerrier
                  attaque(enemy, g);
                  /// Diminue les points de vie du guerrier en fonction de l'attaque de l'ennemi
                 g->lignevie -= (enemy->attaque - g->defense * 0.9);

                /// Vérifie si le guerrier est mort après l'attaque de l'ennemi
                if (g->lignevie <= 0)
                {
                    /// Si le guerrier est mort, lance l'animation de mort du guerrier et planifie sa suppression
                    death(g);
                    enemy->etat = 1;
                    enemy->combat = -1;
                    g_timeout_add(1000, supprimer_delayed, g);
                    return;
                }
            }


        }
    } else {

        g->combat=-1;
        /// Si l'ennemi n'est pas à portée, calcule les pas vers lui dans les axes X et Y
        int step_x = (dx != 0) ? dx / abs(dx) : 0;
        int step_y = (dy != 0) ? dy / abs(dy) : 0;

        /// Définit l'état du guerrier en fonction de la direction du déplacement
        g->etat = (step_x > 0) ? 1 : 4;

        /// Calcule la nouvelle position du guerrier après le déplacement
        int new_x = g->pos_x + step_x * 10;
        int new_y = g->pos_y + step_y * 10;

        /// Vérifie si la nouvelle position est à l'intérieur des limites du terrain
        if (new_x >= 5 && new_y >= bord[type_field].min_hauteur &&
            new_x < bord[type_field].largeur &&
            new_y < bord[type_field].max_hauteur)
        {
            /// Déplace le guerrier vers la nouvelle position
            g->pos_x = new_x;
            g->pos_y = new_y;
        }
    }
}

gboolean supprimer_delayed(gpointer data)
{
    /// Convertit le pointeur générique en pointeur de type Guerier
    Guerier *g = (Guerier *)data;
    /// Appelle la fonction supprimer pour supprimer le guerrier
    supprimer(g);
    /// Retourne FALSE pour indiquer que le délai est terminé et ne doit pas se répéter
    return FALSE;
}

void supprimer(Guerier *G)
{
    /// Vérifie si le jeu est en pause, si c'est le cas, retourne immédiatement sans déverrouiller le mutex
    if (PLAY == 0) return;

    /// Récupère le type et l'identifiant du guerrier
    int type = G->type;
    int id = G->id;

    /// Si le guerrier n'est pas le dernier de son groupe, remplace-le par le dernier guerrier du groupe
    if (id != groupe[type]->nbrGuerier - 1) {
        /// Remplace le guerrier à supprimer par le dernier guerrier du groupe
        groupe[type]->guerrier[id] = groupe[type]->guerrier[groupe[type]->nbrGuerier - 1];
        /// Met à jour l'identifiant du guerrier déplacé
        groupe[type]->guerrier[id]->id = id;
    }

    /// Libère la mémoire allouée pour le guerrier à supprimer
    free(G->P);
    free(G);

    /// Décrémente le nombre de guerriers dans le groupe
    groupe[type]->nbrGuerier--;

    /// Si le groupe ne contient plus aucun guerrier, décrémente le nombre total de groupes
    if (groupe[type]->nbrGuerier == 0) NB--;
}

void death(Guerier *g)
{
    /// Si le jeu est en pause et qu'aucune animation n'est en cours
    ///pour ce guerrier, retourne immédiatement
    if (PLAY == 0 && !g->animation_en_cours) return;

    /// Si le jeu est en pause, retourne immédiatement
    if (PLAY == 0) return;

    /// Affiche un message de débogage indiquant que le guerrier entre dans l'état de mort
    printf("GUERIER ENTRE SUR DEAD\n");

    /// Change l'état du guerrier pour l'état de mort
    g->etat = 3;

    /// Marque le guerrier comme "mort" mais avec une animation en cours
    g->mat = 1;

    /// Initialise le compteur de frames pour l'animation de mort
    g->frame_img = 7;

    /// Ajoute un timeout pour mettre à jour l'animation de mort toutes les 100 ms
    g_timeout_add(100, update_animation_death, g);
}

void attaque(Guerier *g, Guerier* target)
{
    /// Vérifie si le jeu est en pause (si PLAY est 0)
    if (PLAY == 0) return;

    /// Initialise le compteur de frames pour l'animation d'attaque
    g->frame_img = 7;

    /// Vérifie si une animation n'est pas déjà en cours pour ce guerrier
    if (!g->animation_en_cours) {
        /// Marque que l'animation est maintenant en cours
        g->animation_en_cours = TRUE;

        /// Ajoute un timeout pour mettre à jour l'animation toutes les 100 ms
        g_timeout_add(100, update_animation_attack, g);
    }
}
/// Fonction qui met à jour l'animation d'attaque d'un guerrier
gboolean update_animation_attack(gpointer data)
{
    /// Conversion du pointeur générique en pointeur de type Guerier
    Guerier *g = (Guerier*) data;

    /// Vérifie si l'animation doit être arrêtée (par exemple, si le jeu est en pause)
    if (PLAY == 0) return FALSE;

    /// Incrémente l'index de l'image et le ramène à 0 après avoir atteint 6 (boucle de 0 à 6)
    g->index_img = (g->index_img + 1) % 7;

    /// Redessine le widget pour afficher la nouvelle image
    gtk_widget_queue_draw(g->area);

    /// Vérifie si l'état du guerrier est en train d'attaquer et si le compteur de frames est actif
    if ((g->etat == 2 || g->etat == 5) && g->frame_img >= 0)
    {
        /// Décrémente le compteur de frames s'il est supérieur à 0
        if (g->frame_img > 0) {
            g->frame_img--;
            return TRUE; /// Continue l'animation
        } else {
            /// Si le compteur de frames atteint 0, arrête l'animation
            g->animation_en_cours = FALSE;
            return FALSE; /// Arrête l'animation
        }
    }

    /// Continue l'animation par défaut
    return TRUE;
}
/// Fonction qui met à jour l'animation de mort d'un guerrier
gboolean update_animation_death(gpointer data)
{
    /// Conversion du pointeur générique en pointeur de type Guerier
    Guerier *g = (Guerier*) data;

    /// Vérifie si l'animation doit être arrêtée (par exemple, si le jeu est en pause)
    if (PLAY == 0) return FALSE;

    /// Incrémente l'index de l'image et le ramène à 0 après avoir atteint 6 (boucle de 0 à 6)
    g->index_img = (g->index_img + 1) % 7;

    /// Redessine le widget pour afficher la nouvelle image
    gtk_widget_queue_draw(g->area);

    /// Vérifie si l'état du guerrier est "mort" et si le compteur de frames est actif
    if (g->etat == 3 && g->frame_img >= 0)
    {
        /// Affiche la valeur actuelle du compteur de frames pour le débogage
        printf("g->frame === %d \n", g->frame_img);

        /// Décrémente le compteur de frames s'il est supérieur à 0
        if (g->frame_img > 0)
        {
            g->frame_img--;
            return TRUE; /// Continue l'animation
        }
        else
        {
            /// Si le compteur de frames atteint 0, arrête l'animation et marque le guerrier comme "mort"
            g->animation_en_cours = FALSE;
            g->mat = 2; /// Marque le guerrier comme "mort"
            return FALSE; /// Arrête l'animation
        }
    }

    /// Continue l'animation par défaut
    return TRUE;
}

void dans_la_zone(Guerier *G)
{
    int i, j, dif_X, dif_Y;
    int norme_squared;
    int nb = G->P->nbproche=0;
    int rayon_squared = G->rayon * G->rayon;

    for (i = 0; i < 5; i++)
    {
        if (i != G->type)
        {
            for (j = 0; j < groupe[i]->nbrGuerier; j++)
            {
                dif_X = G->pos_x - groupe[i]->guerrier[j]->pos_x;
                dif_Y = G->pos_y - groupe[i]->guerrier[j]->pos_y;
                norme_squared = dif_X * dif_X + dif_Y * dif_Y;

                if (norme_squared <= rayon_squared)
                {
                    G->P->proches[nb].norme = sqrt(norme_squared);
                    G->P->proches[nb].type = i;
                    G->P->proches[nb].rang = j;
                    nb++;
                    G->P->nbproche++;
                }
            }
        }
    }
}

int compare_proches(const void *a, const void *b)
{
    Proche *pa = (Proche *)a;
    Proche *pb = (Proche *)b;
    return (pa->norme > pb->norme) - (pa->norme < pb->norme);
}

void info_enemis(Guerier *G,int* ind)
{

    int i, type, rang;
    /// Trier le tableau Proches par norme croissante
    qsort(G->P->proches, G->P->nbproche, sizeof(Proche), compare_proches);

    /// Parcourir le tableau tri� pour trouver l'ennemi le plus faible et le plus proche
    for (i = 0; i < G->P->nbproche; i++)
    {
        type = G->P->proches[i].type;
        rang = G->P->proches[i].rang;
        if ((groupe[type]->guerrier[rang]->combat==-1)&&((G->power > groupe[type]->guerrier[rang]->power) ||
            (G->power==groupe[type]->guerrier[rang]->power && (G->lignevie > groupe[type]->guerrier[rang]->lignevie))
            || (G->power==groupe[type]->guerrier[rang]->power && (G->lignevie > groupe[type]->guerrier[rang]->lignevie) && (G->attaque>groupe[type]->guerrier[rang]->attaque))
            ))

        {
             *ind=G->P->ind_proche=i;
             printf("Proche\n");
             return ;
        }

    }
    *ind=-1;
    printf("NOT PROCHE\n");
}

#endif /// SIMULATION_H_INCLUDED
