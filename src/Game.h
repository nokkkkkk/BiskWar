


#pragma once

#include "ofMain.h"
#include "Factoblocs.h"


const int nb_lignes = 17;
const int nb_col = 15;
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
    void move_obj(int p_x, int p_y, int p_z, int p_button);
    std::vector<Blocs *> get_vecteur_blocs();
    char m_etat_table[nb_lignes][nb_col];
    void verify_who_fall();  
    void verify_all_grid_clear();  
    void play_level_up();  

private:  

   ofColor m_grid_color = (25,25,255);
   int m_size_grid_slot;
  std::vector<Blocs *> m_blocs; // Déclaration d'un vecteur de pointeur pour Polymorphisme   
  ofSoundPlayer  game_bg_music;
  ofSoundPlayer  game_clear_bloc[3];
  int indice_sound_clear;
  ofSoundPlayer  m_bloc_lock_sound;


  ofTexture m_tex_lvl_up;
  bool m_toggle_level_up;
};


