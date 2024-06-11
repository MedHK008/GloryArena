#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

struct {
    const char *image_path;
    const char *description;
} tutorial[6] = {
    {"assets/sprites/tutorialIdle/left.gif", "- Left arrow: move left\n"},
    {"assets/sprites/tutorialIdle/right.gif", "- Right arrow: move right\n"},
    {"assets/sprites/tutorialIdle/up.gif", "- Up arrow: move up\n"},
    {"assets/sprites/tutorialIdle/down.gif", "- Down arrow: move down\n"},
    {"assets/sprites/tutorialIdle/pause.gif", "Press the 'p' key to pause the game.\n"},
    {"assets/sprites/tutorialIdle/atk.gif", "Press the 'a' key to attack.\n"}
};

/// unit description
struct {
    const char *image_path;
    const char *description;
} characters[5] = {
    {"assets/sprites/descriptionIdle//ARAB.gif", "Name: Kael'Thas Sunstrider\nClass: Arab\nBackground: A master of dual-wielding scimitars from the Sunriders, Kael'Thas is an agile warrior and expert tactician of the desert.\n\nHealth: 100\nAttack: 20\nDefense: 15\nSpeed: 18\n"},
    {"assets/sprites/descriptionIdle//AZTEC.gif", "Name: Citlali Chimali\nClass: Aztec\nBackground: Trained as an Eagle and Jaguar warrior, Citlali is a fierce combatant and protector of the Aztec people.\n\nHealth: 120\nAttack: 25\nDefense: 20\nSpeed: 15\n"},
    {"assets/sprites/descriptionIdle//ROMAN.gif", "Name: Lucius Decimus Meridius\nClass: Roman\nBackground: A disciplined centurion of the Roman legion, Lucius commands with tactical expertise and combat prowess.\n\nHealth: 150\nAttack: 30\nDefense: 25\nSpeed: 12\n"},
    {"assets/sprites/descriptionIdle//PERSIAN.gif", "Name: Darius Arash Tir\nClass: Persian\nBackground: An elite archer of the Persian Immortals, Darius is a tactical genius and skilled diplomat.\n\nHealth: 130\nAttack: 22\nDefense: 24\nSpeed: 14\n"},
    {"assets/sprites/descriptionIdle//viking.gif", "Name: Batu Erdeni\nClass: Viking\nBackground: Batu, a master of horseback archery from the steppes, is a cunning tactician and fierce warrior of the Viking Empire.\n\nHealth: 110\nAttack: 28\nDefense: 18\nSpeed: 20\n"}
};
//il faut stocker le type de la reine
typedef struct{
    int largeur ;
    int min_hauteur ;
    int max_hauteur ;
}Surface;

typedef struct{
    gfloat norme ;
    int type ;
    int rang ;
}Proche ;

typedef struct {
    Proche proches[20];
    int nbproche;
    int ind_proche;
}Lst_Proches;

typedef struct {
    gint id;
    gint type; // Arabs : 0 , Aztech : 1, persian : 2, roman : 3, mongol : 4 ;
    gint attaque;
    gint defense;
    gint endurance;
    gint vitesse;
    gint lignevie;
    gint pos_x;
    gint pos_y;
    gfloat power ;
    gint rayon;
    Lst_Proches* P;
    int combat;
    gboolean animation_en_cours;
    int index_img;
    int etat;// 0:stop 1:run 2:atk 3:dead 4:run_inv 5:atk_inv
    GdkPixbuf *img[6][7];
    int frame_img;
    GtkWidget * area;
    int mat;

} Guerier;

typedef struct {
    Guerier *guerrier[Max];
    int nbrGuerier;
} Gueriers;

typedef struct {
    int direction;
    int steps_remaining;
} MovementState;

///variable globale
int charger_partie=0;
Gueriers *groupe[5];
int place[5] ={0,1,1,0,0}; //    0:sahara ; 1:forest
int carac[5][5]={{40,50,60,10,120},{65,30,40,20,120},{53,40,30,10,120},{55,40,60,10,120},{50,40,50,10,120}};
Surface bord[2] =
{
    {900, 180, 450},
    {900, 200, 480}
};
int NB=0;
int PLAY=0;
int type_player = -1;
int type_field=0;
int all=0;
int deja_visit;
//Tableau represantant la direction et les pas restants pour chaque guerier
MovementState movement_states[5][5];
Fenetre* F1;
Fixed *fixed1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif // STRUCTURES_H_INCLUDED
