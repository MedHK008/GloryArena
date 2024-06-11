#ifndef MOUVEMENT_H_INCLUDED
#define MOUVEMENT_H_INCLUDED




gboolean attack_vs_player(gpointer data)
{
    Guerier *enemy = (Guerier*)data;
    Guerier *player = groupe[type_player]->guerrier[0];
    int dx = enemy->pos_x - player->pos_x;
    int dy = enemy->pos_y - player->pos_y;

    // V�rifie si le joueur est � port�e d'attaque
    if (abs(dx) > 35 || abs(dy) > 20)
    {
        enemy->etat = 1;  // Retourne � l'�tat normal
        enemy->combat = -1;
        return FALSE;
    }

    // Lance l'attaque de l'ennemi sur le joueur
    attaque(enemy, player);
    player->lignevie -= (enemy->attaque - player->defense * 0.8);

    // V�rifie si le joueur est mort apr�s l'attaque
    if (player->lignevie <= 0)
    {
        death(player);
        enemy->combat = -1;
        enemy->etat = 0;
        g_timeout_add(1000, supprimer_delayed, player);
        return FALSE;
    }

    return TRUE;
}

void mouvement_player(gpointer data)
{
   int direction=GPOINTER_TO_INT(data);
   Guerier *g=groupe[type_player]->guerrier[0];
   int new_x=g->pos_x , new_y=g->pos_y;

        g->index_img=(g->index_img+1)%7;
        gtk_widget_queue_draw(g->area);

    if(direction==1)
    {
        printf("BAAS\n");
        new_y-=10;
            if(new_y>bord[type_field].min_hauteur)
              groupe[type_player]->guerrier[0]->pos_y=new_y;
            return ;
    }
     if(direction==2)
     {
          printf("HAUT\n");
          new_y+=10;
          if(new_y<bord[type_field].max_hauteur)
              groupe[type_player]->guerrier[0]->pos_y=new_y;
            return ;
    }

    if(g->etat==1 )
    {
        new_x+=10;
        if(new_x <=bord[type_field].largeur)
        {
           printf("gauche\n");
           groupe[type_player]->guerrier[0]->pos_x=new_x;
          return ;
        }

    }
    else if(g->etat==4)
    {
       new_x-=10;
        if(new_x>5)
          g->pos_x=new_x;
        return ;
    }
      if ((g->etat == 2 || g->etat == 5)&& g->frame_img >=0 )
    {

         if(g->frame_img > 0)
             g->frame_img--;
         else
         {
             if(g->combat!=-1)
             {
                 Guerier*enemy= groupe[g->P->proches->type]->guerrier[g->P->proches->rang];
                 enemy->lignevie -= (g->attaque - enemy->defense * 0.8);

                // V�rifie si l'ennemi est mort apr�s l'attaque
                if (enemy->lignevie <= 0)
                {
                    // Si l'ennemi est mort, lance l'animation de mort de l'ennemi et planifie sa suppression
                    death(enemy);
                    g->combat = -1;
                    g->etat=0;
                    g_timeout_add(1000, supprimer_delayed, enemy);
                    return;
                }
                else if(enemy->power < g->power)
                {
                    enemy->combat=0;
                    enemy->etat=(g->etat==2)? 5 :2;
                    g_timeout_add(100,attack_vs_player,enemy);
                }
             }
             g->frame_img=7;
             return;

         }
    }

}

void attaque_player(GtkWidget *widget,gpointer data)
{
    if(PLAY==0 ) return;
    Guerier* g=groupe[type_player]->guerrier[0];
    g->P->nbproche=0;

   if(g->combat==-1)
   {
      for (int i = 0; i < 5; i++)
        {
            if (i != g->type)
            {
                for (int j = 0; j < groupe[i]->nbrGuerier; j++)
                {
                   if(abs(g->pos_x - groupe[i]->guerrier[j]->pos_x )<=35 && abs(g->pos_y - groupe[i]->guerrier[j]->pos_y)<=20 )
                    {
                       g->P->proches->rang=j;
                       g->P->proches->type=i;
                       g->P->nbproche++;
                       g->combat=1;
                       break;
                    }

                }
            }
        }
   }

    if(groupe[type_player]->guerrier[0]->etat==4)
           groupe[type_player]->guerrier[0]->etat=5;
    else groupe[type_player]->guerrier[0]->etat=2;
    groupe[type_player]->guerrier[0]->animation_en_cours=TRUE;
    mouvement_player(NULL);


}

void run_inv_player(GtkWidget *widget ,gpointer data)
{

   if(PLAY==0|| groupe[type_player]->guerrier[0]->combat==0) return;
    groupe[type_player]->guerrier[0]->combat=-1;
    groupe[type_player]->guerrier[0]->etat=4;
    mouvement_player(NULL);
}

void run_player(GtkWidget *widget, gpointer data )
{

    if(PLAY==0 || groupe[type_player]->guerrier[0]->combat==0) return;
      groupe[type_player]->guerrier[0]->combat=-1;
    groupe[type_player]->guerrier[0]->etat=1;
    mouvement_player(NULL);
}

void haut_player(GtkWidget *widget,gpointer data)
 {
    int direct=GPOINTER_TO_INT(data) ;
    if(PLAY==0 || groupe[type_player]->guerrier[0]->combat==0) return;
    groupe[type_player]->guerrier[0]->combat=-1;
    groupe[type_player]->guerrier[0]->etat=1;
    mouvement_player(GINT_TO_POINTER(direct));
}

void bas_player(GtkWidget *widget,gpointer data)
 {
    int direct=GPOINTER_TO_INT(data) ;
   if(PLAY==0|| groupe[type_player]->guerrier[0]->combat==0) return;
    groupe[type_player]->guerrier[0]->combat=-1;
   groupe[type_player]->guerrier[0]->etat=1;
    mouvement_player(GINT_TO_POINTER(direct));

}

#endif // MOUVEMENT_H_INCLUDED
