// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "Game.h"
using namespace std;
using namespace objects_in_scene;

Game::Game()
{
}

Game::Game(int p_nb_blocs_to_load, int p_nb_joueurs)
{
  for (unsigned int i = 0; i < p_nb_blocs_to_load; i++)
    {
      m_blocs.push_back(new Std_bloc);
      m_blocs.back()->setup(true);
      ofLog() << i;
    }
    for (unsigned int i = 0; i < nb_lignes; i++)
    {
        for (unsigned int y = 0; y < nb_col; y++)
        {
            m_etat_table[y][i] = 'X';
        }
    }
    show_state_table();
}
void Game::start_game()
{
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
            ligne += m_etat_table[y][i];
        }
        ofLog() << ligne;
        ligne = "";
    }
}

