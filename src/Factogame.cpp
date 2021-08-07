// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "Factogame.h"

Game* Factogame::get_game(int p_nb_joueurs)
{
    switch(p_nb_joueurs)
    {
        case 1:                     
            return new Game(15, 1);           
        break;
        default:
            return new Game(0, 0);
        break;
    }
}