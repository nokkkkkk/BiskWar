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

        set_block_from_pos_in_table(2,2,'W');
        
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

