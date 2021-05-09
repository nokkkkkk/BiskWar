


#pragma once

#include "ofMain.h"
#include "std_bloc.h"
#include "blocs.h"
#include "Factoblocs.h"


const int nb_lignes = 17;
const int nb_col = 8;
class Game
{
public: 
    Game();
    Game(int p_nb_blocs_to_load, int p_nb_joueurs);   
    void start_game(); 
    void show_grid(); 
    void show_state_table();
    char get_block_from_pos_in_table(int p_x, int p_y);
    void set_block_from_pos_in_table(int p_x, int p_y, char p_char_bloc);
    void add_bloc(int p_type);    
    std::vector<objects_in_scene::Blocs *> get_vecteur_blocs();
    char m_etat_table[nb_lignes][nb_col];

private:
   ofColor m_grid_color = (25,25,255);
   int m_size_grid_slot;

  
  std::vector<objects_in_scene::Blocs *> m_blocs; // Déclaration d'un vecteur de pointeur pour Polymorphisme   
};


