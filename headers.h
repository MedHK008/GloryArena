#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

///bibliotheque predefinis
#include<gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#include <pthread.h>

///nos macros (widgets)
#include "fenetre.h"
#include "fenetreDeroulante.h"
#include "bouton.h"
#include "combobox.h"
#include "fixed.h"
#include "label.h"
#include "image.h"
#include "frame.h"

///nos macros (constantes)
#define NUM_DIRECTIONS 8
#define STEPS_BEFORE_DIRECTION_CHANGE 10
#define Max 5
#define NBC 100

///le fichier des structures
#include "structures.h"

///definition des fonctions globales;
void load_css();
void debut_programme(int ,char**);
void fin_programme(Fenetre*);
void on_escape_clicked(GtkWidget*, gpointer);
gboolean on_key_press(GtkWidget*, GdkEventKey*, gpointer);
void on_quit_program(GtkWidget*, gpointer);
void fermer(GtkWidget*,GtkWidget*);
void on_window_closed(GtkWidget*, gpointer);
void on_destroy_parent_window(GtkWidget*, gpointer);
void quit_app(GtkWidget*, gpointer);
void initialiser();

///les fonctions du fichier saving
FILE* ouvrir_fichier(const char*);
FILE* sauvegarde_partie(FILE*);
void declencher_sauvegarde(GtkWidget*,gpointer);
FILE* ouvrir_fichier_lecture(const char*);
void charger_unites(FILE*);
void charger_partie_function(GtkWidget*,gpointer);
void startGame();

///les fonctions du fichier page d'accueil
void show_units_description(GtkWidget*,gpointer);
void show_tutoriel(GtkWidget*,gpointer);
void debut_jeu(Fenetre*);

///les fonctions du fichier traitement
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

///les fonctions du fichier simulation
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

///les fonctions du fichier mouvement
gboolean attack_vs_player(gpointer);
void mouvement_player(gpointer);
void attaque_player(GtkWidget*,gpointer);
void run_inv_player(GtkWidget*,gpointer);
void run_player(GtkWidget*,gpointer);
void haut_player(GtkWidget*,gpointer);
void bas_player(GtkWidget*,gpointer);

///les fonctions du fichier pageFinale
void Replay(GtkWidget*,gpointer);
void winners(int);

///nos fichier du jeu
#include "traitementJeu.h"
#include "pageFinale.h"
#include "simulation.h"
#include "mouvement.h"
#include "pageJeu.h"
#include "saving.h"
#include "pageAccueil.h"


///fonction globales

void load_css()
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    GError *error = NULL;
    if (!gtk_css_provider_load_from_path(provider, "assets/css/style.css", &error))
    {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        return;
    }
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

void debut_programme(int argc,char*argv[])
{
    gtk_init(&argc,&argv);
}

void fin_programme(Fenetre* ma_fenetre)
{
    g_signal_connect(G_OBJECT(ma_fenetre->window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void on_escape_clicked(GtkWidget *button, gpointer data)
{
    GtkWindow *window = GTK_WINDOW(data);
    gtk_window_unfullscreen(window);
}
// Fonction pour quitter le plein �cran lorsque la touche �chappement est press�e
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    if (event->keyval == GDK_KEY_Escape) {
        on_escape_clicked(NULL, data);
    }
    return FALSE;
}
// Fonction de rappel pour quitter le programme
void on_quit_program(GtkWidget *widget, gpointer data)
{
    gtk_main_quit(); // Quitter la boucle principale GTK
}

void fermer(GtkWidget *bm,GtkWidget *button)
{
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), bm);
}

void on_window_closed(GtkWidget *widget, gpointer data)
{
    NB=0;
    gtk_main_quit();

}

void on_destroy_parent_window(GtkWidget *widget, gpointer data)
{
    gtk_widget_hide(GTK_WIDGET(data));
    NB=0;/// nb des guerriers retourne a 0
    PLAY=0;/// le jeu est arreter
    type_player = -1;/// pour liberer le choix de comcobox
    GtkWidget* fenetre=(GtkWidget*)data;
    gtk_widget_destroy(fenetre);/// pour quiter la fenetre du jeu
}

void quit_app(GtkWidget *widget, gpointer data)
{
    GtkWidget* window=(GtkWidget*)data;
    gtk_window_close(GTK_WINDOW(window));
    gtk_main_quit();
}

void initialiser()
{
   for(int i=0;i<5;i++)
   {
       groupe[i]=(Gueriers*)g_malloc(sizeof(Gueriers));
       groupe[i]->nbrGuerier=0;
   }
}
#endif // HEADERS_H_INCLUDED
