// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "Game.h"
using namespace std;

Game::Game()
{
}

Game::Game(int p_nb_blocs_to_load, int p_nb_joueurs) // coplien Copy and swap -- DEsgin 
{
    m_size_grid_slot = 50;
    for (unsigned int i = 0; i < p_nb_blocs_to_load; i++)
        {
        m_blocs.push_back(new Std_bloc);
        m_blocs.back()->setup(true);
        }
    for (unsigned int i = 0; i < nb_lignes; i++)
    {
        for (unsigned int y = 0; y < nb_col; y++)
        {
            m_etat_table[i][y] = '.';
        }
    }

        // set_block_from_pos_in_table(2,2,'W');
        
}
void Game::show_grid()
{
    int x_pos = 0;
    int y_pos = 0;
    for (unsigned int i = 0; i < nb_lignes; i++)
    {
        y_pos = i * m_size_grid_slot;
        for (unsigned int y = 0; y < nb_col; y++)
        {
            x_pos = -(y * m_size_grid_slot);
            ofSetColor(20,20,250);
            ofSetLineWidth(1);
            ofDrawRectangle(x_pos, y_pos, -m_size_grid_slot,m_size_grid_slot);
        }
    }

}
void Game::start_game()
{
}

void Game::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
      if (p_x != 0) //Si on bouge de gauche a droite
      {
        if ((m_blocs.back()->get_pos_on_grid().x != 0 && p_x > 0) || (m_blocs.back()->get_pos_on_grid().x != 7 && p_x < 0))
        {
            m_blocs.back()->move_obj(p_x, p_y, p_z, p_button);
        }
      }

      if (p_y != 0) // si on bouge vers le bas
      {
        if (m_blocs.back()->get_pos_on_grid().y < 16 && get_block_from_pos_in_table(m_blocs.back()->get_pos_on_grid().x, m_blocs.back()->get_pos_on_grid().y + 1) == '.')
        {
            m_blocs.back()->move_obj(p_x, p_y, p_z, p_button);
            ofLog() << get_block_from_pos_in_table(m_blocs.back()->get_pos_on_grid().x, m_blocs.back()->get_pos_on_grid().y + 1) ;
        }
        else
        {
            m_blocs.back()->set_bloc_lock(true);
        }
      }

    


    

  }
vector<Blocs *> Game::get_vecteur_blocs()
{
    return m_blocs;
}
void Game::add_bloc(int p_type)
{
    m_blocs.push_back(Factoblocs::get_bloc(1));
    m_blocs.back()->setup(false);
    m_blocs.size();
}

void Game::show_state_table()
{
    string ligne = "";
    for (unsigned int i = 0; i < nb_lignes; i++)
    {
        for (unsigned int y = 0; y < nb_col; y++)
        {
            ligne += m_etat_table[i][y];
        }
        ofLog() << ligne;
        ligne = "";
    }
}
char Game::get_block_from_pos_in_table(int p_x, int p_y){
    return m_etat_table[p_y][p_x];
}
void Game::set_block_from_pos_in_table(int p_x, int p_y, char p_char_bloc){
    m_etat_table[p_y][p_x] = p_char_bloc;
}

