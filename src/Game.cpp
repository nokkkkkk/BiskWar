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
            ofNoFill();
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
    bool bloc_side_can_move = false; //on part avec l'idée qu'on ne peut pas bouger...
    if (p_x < 0) // Si on bouge vers la droite...
    {
        //Si aucun bloc ne se trouve à droite, on peut bouger. 
        if (get_block_from_pos_in_table(m_blocs.back()->get_pos_on_grid().x + 1, m_blocs.back()->get_pos_on_grid().y) == '.')
        {
            bloc_side_can_move = true;
        }
    }
    if (p_x > 0) // Si on bouge vers la gauche...
    {
        //Si aucun bloc ne se trouve à gauche, on peut bouger. 
        if (get_block_from_pos_in_table(m_blocs.back()->get_pos_on_grid().x - 1, m_blocs.back()->get_pos_on_grid().y) == '.')
        {
            bloc_side_can_move = true;
        }
    }

    if (p_x != 0) //Si on bouge de gauche a droite
    {
        //Si nous ne sommes pas au bord du tableau
        if ((m_blocs.back()->get_pos_on_grid().x != 0 && p_x > 0) || (m_blocs.back()->get_pos_on_grid().x != 7 && p_x < 0))
        {
            if(bloc_side_can_move)
            {
                m_blocs.back()->move_obj(p_x, p_y, p_z, p_button);
            }
        }
    }

    if (p_y != 0) // si on bouge vers le bas
    {
        //Si nous ne sommes pas au fond ou en colision avec un autre bloc en dessous : On bouge
        if (m_blocs.back()->get_pos_on_grid().y < 16 && get_block_from_pos_in_table(m_blocs.back()->get_pos_on_grid().x, m_blocs.back()->get_pos_on_grid().y + 1) == '.')
        {
            m_blocs.back()->move_obj(p_x, p_y, p_z, p_button);
        }
        //SINON on lock le bloc
        else
        {
            m_blocs.back()->set_bloc_lock(true);
        }
    }
  }


void Game::verify_last_move_to_clear()
{   
    ofVec2f pos_grid_last_block = ofVec2f(m_blocs.back()->get_pos_on_grid().x , m_blocs.back()->get_pos_on_grid().y);
    int serie_count = 0;
    vector<int> indice_to_clear{}; //Vector des position a supprimer

        for (unsigned int i = 0; i < m_blocs.size(); i++)
        {
            if (m_blocs[i]->get_pos_on_grid() == ofVec2f(pos_grid_last_block.x , pos_grid_last_block.y + 1) &&
                m_blocs[i]->get_bloc_char() == m_blocs.back()->get_bloc_char())
            {
                indice_to_clear.push_back(i);
            }
        }
        if (indice_to_clear.size() >= 1)
        {
            m_blocs.pop_back();
            set_block_from_pos_in_table(pos_grid_last_block.x, pos_grid_last_block.y, '.');
            for (unsigned int i = 0; i < indice_to_clear.size(); i++)
            {
                set_block_from_pos_in_table(pos_grid_last_block.x, pos_grid_last_block.y + i + 1, '.');
                m_blocs.erase(m_blocs.begin() + indice_to_clear[i]);
            }
        }


}
void Game::verify_all_grid_clear()
{   
//    int nb_blocs_lign = 0;
//    bool get_out = false;

//     for (unsigned int i = 0; i < nb_lignes; i++)
//     {
//     for (unsigned int y = 0; y < nb_col; y++)
//     {
//         while (get_out == false || ((i + nb_blocs_lign) >= (nb_col - 1))) //6 doit etre valider.
//         {
//             /* code */
//         }
        
//     }


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

