#ifndef SAVING_H_INCLUDED
#define SAVING_H_INCLUDED



FILE* ouvrir_fichier(const char*);
FILE* sauvegarde_partie(FILE*);
void declencher_sauvegarde(GtkWidget*,gpointer);
FILE* ouvrir_fichier_lecture(const char*);
void charger_unites(FILE*);
void charger_partie_function(GtkWidget*,gpointer);



FILE* ouvrir_fichier(const char* nom_fichier)
{
    FILE* f = fopen(nom_fichier, "w");
    if(f == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    return f;
}

FILE* sauvegarde_partie(FILE* f)
{
    if(PLAY == 1) return f;
    fprintf(f,"type_field: %d\n",type_field);
    fprintf(f,"type_player: %d\n",type_player);
    for(int i=0;i<5;i++)
    {
        if((groupe[i]->nbrGuerier) != 0)
        {
            for(int j=0;j<groupe[i]->nbrGuerier;j++)
            {
                fprintf(f,"type: %d ",groupe[i]->guerrier[j]->type);
                fprintf(f,"id: %d ",groupe[i]->guerrier[j]->id);
                fprintf(f,"pos_x: %d ",groupe[i]->guerrier[j]->pos_x);
                fprintf(f,"pos_y: %d ",groupe[i]->guerrier[j]->pos_y);
                fprintf(f,"lignevie: %d",groupe[i]->guerrier[j]->lignevie);
                fprintf(f,"\n");
            }
        }
    }
    return f;
}

void declencher_sauvegarde(GtkWidget* widget,gpointer data)
{
    FILE* f = NULL;
    f=ouvrir_fichier("sauvegarde.txt");
    f = sauvegarde_partie(f);
    fclose(f);
}

FILE* ouvrir_fichier_lecture(const char* nom_fichier)
{
    FILE* f = fopen(nom_fichier, "r");
    if(f == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
    return f;
}

void charger_unites(FILE* f)
{
    char c;
    char propriete[15];
    char field[11],player[11];
    int type,id,pos_x,pos_y,lignevie;
    fscanf(f,"%s",field);
    c=fgetc(f);
    fscanf(f,"%d",&type_field);
    c=fgetc(f);
    fscanf(f,"%s",player);
    c=fgetc(f);
    fscanf(f,"%d",&type_player);
    c=fgetc(f);
    c=fgetc(f);
    if(c==EOF)
    {
        fclose(f);
        return;
    }
    else ungetc(c,f);
    while(c != EOF)
    {
        fscanf(f,"%s",propriete);
        c=fgetc(f);
        fscanf(f,"%d",&type);
        c=fgetc(f);
        fscanf(f,"%s",propriete);
        c=fgetc(f);
        fscanf(f,"%d",&id);
        c=fgetc(f);
        fscanf(f,"%s",propriete);
        c=fgetc(f);
        fscanf(f,"%d",&pos_x);
        c=fgetc(f);
        fscanf(f,"%s",propriete);
        c=fgetc(f);
        fscanf(f,"%d",&pos_y);
        c=fgetc(f);
        fscanf(f,"%s",propriete);
        c=fgetc(f);
        fscanf(f,"%d",&lignevie);
        c = fgetc(f);
        c=fgetc(f);
        groupe[type]->guerrier[id]=(Guerier*)g_malloc(sizeof(Guerier));
        groupe[type]->guerrier[id]->lignevie=lignevie;
        groupe[type]->guerrier[id]->index_img=0;
        groupe[type]->guerrier[id]->frame_img=7;
        groupe[type]->guerrier[id]->etat=0;
        groupe[type]->guerrier[id]->P=(Lst_Proches*)malloc(sizeof(Lst_Proches));
        groupe[type]->guerrier[id]->P->nbproche=0;
        groupe[type]->guerrier[id]->id = id;
        groupe[type]->guerrier[id]->type=type;
        groupe[type]->guerrier[id]->attaque=carac[type][0];
        groupe[type]->guerrier[id]->defense=carac[type][1];
        groupe[type]->guerrier[id]->endurance=carac[type][2];
        groupe[type]->guerrier[id]->vitesse=carac[type][3];
        groupe[type]->guerrier[id]->pos_x=pos_x;
        groupe[type]->guerrier[id]->pos_y=pos_y;
        force_dans_sa_place(groupe[type]->guerrier[id]);
        groupe[type]->guerrier[id]->power=(groupe[type]->guerrier[id]->attaque + groupe[type]->guerrier[id]->defense)*0.35 + groupe[type]->guerrier[id]->endurance*0.2 +groupe[type]->guerrier[id]->vitesse*0.1;
        groupe[type]->guerrier[id]->rayon=carac[type][4];
        ajouter_img(groupe[type]->guerrier[id],type);
        groupe[type]->guerrier[id]->combat=-1;
        groupe[type]->guerrier[id]->mat=0;
        groupe[type]->guerrier[id]->animation_en_cours=FALSE;
        if(groupe[type]->nbrGuerier==0) NB++;
        groupe[type]->nbrGuerier++;
        if(c==EOF) break;
        else ungetc(c,f);
    }
    fclose(f);

}

void charger_partie_function(GtkWidget *widget,gpointer data)
{
    FILE *f=ouvrir_fichier_lecture("sauvegarde.txt");
    initialiser();
    charger_unites(f);
    charger_partie=1;
    startGame();
}


#endif // SAVING_H_INCLUDED
