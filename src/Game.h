


#pragma once

#include "ofMain.h"
#include "std_bloc.h"
#include "blocs.h"
#include "Factoblocs.h"


class Game
{
public: 
    Game();
    Game(int p_nb_blocs_to_load, int p_nb_joueurs);   
    void start_game();
    void add_bloc(int p_type);    
    std::vector<objects_in_scene::Blocs *> get_vecteur_blocs();

private:
   

  
  std::vector<objects_in_scene::Blocs *> m_blocs; // Déclaration d'un vecteur de pointeur pour Polymorphisme   
};


