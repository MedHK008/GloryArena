#include "headers.h"

int main(int argc,char*argv[])
{
    debut_programme(argc,argv);
    initialiser();
    Fenetre *F=add_window("GLORY ARENA","assets/backgrounds/gamelogo.png","LandingPage",NULL,1280,720,GTK_WIN_POS_CENTER,0,0,1,FALSE);
    debut_jeu(F);
    fin_programme(F);
    free_window(F);
    return 0;
}
