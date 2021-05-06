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
      m_blocs.back()->setup();
      ofLog() << i;
    }
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
    m_blocs.back()->setup();
    m_blocs.size();
}


