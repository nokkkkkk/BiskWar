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
    game_bg_music.load("../../data/music/fast.mp3");
    game_clear_bloc[0].load("../../data/sound/clear1.mp3");
    game_clear_bloc[1].load("../../data/sound/clear2.mp3");
    game_clear_bloc[2].load("../../data/sound/clear3.mp3");
    indice_sound_clear = 0;
    m_bloc_lock_sound.load("../../data/sound/bloclock.mp3");
    m_bloc_lock_sound.setVolume(0.5);
    game_bg_music.play();

    ofLoadImage(m_tex_lvl_up,"../../data/images/levelup.png");
    m_toggle_level_up = false;

    

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
void Game::play_level_up()
{
    if (m_toggle_level_up == true)
    {
        ofFill();
        ofSetColor(200, 200, 200);
        m_tex_lvl_up.bind();
        ofPushMatrix();
            ofRotateYDeg(ofGetFrameNum() * 0.8f);
            ofDrawSphere(ofVec3f(600, 300, 1000),250);
        ofPopMatrix();
        m_tex_lvl_up.unbind();

    }
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
        if ((m_blocs.back()->get_pos_on_grid().x != 0 && p_x > 0) || (m_blocs.back()->get_pos_on_grid().x != (nb_col - 1) && p_x < 0))
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
        if (m_blocs.back()->get_pos_on_grid().y < (nb_lignes - 1) && get_block_from_pos_in_table(m_blocs.back()->get_pos_on_grid().x, m_blocs.back()->get_pos_on_grid().y + 1) == '.')
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
    // m_bloc_lock_sound.play();
    // ofVec2f pos_grid_last_block;
    // // if (m_blocs.size() < 0)
    // // {
    //         pos_grid_last_block = ofVec2f(m_blocs.back()->get_pos_on_grid().x , m_blocs.back()->get_pos_on_grid().y);
    // // }


    // int serie_count = 0;
    // vector<int> indice_to_clear{}; //Vector des position a supprimer

    //     for (unsigned int i = 0; i < m_blocs.size(); i++)
    //     {
    //         if (m_blocs[i]->get_pos_on_grid() == ofVec2f(pos_grid_last_block.x , pos_grid_last_block.y + 1) &&
    //             m_blocs[i]->get_bloc_char() == m_blocs.back()->get_bloc_char())
    //         {
    //             indice_to_clear.push_back(i);
    //         }
    //     }
    //     if (indice_to_clear.size() >= 1)
    //     {
    //         m_blocs.pop_back();
    //         set_block_from_pos_in_table(pos_grid_last_block.x, pos_grid_last_block.y, '.');
    //         for (unsigned int i = 0; i < indice_to_clear.size(); i++)
    //         {
    //             set_block_from_pos_in_table(pos_grid_last_block.x, pos_grid_last_block.y + i + 1, '.');
    //             m_blocs.erase(m_blocs.begin() + indice_to_clear[i]);
    //             game_clear_bloc[indice_sound_clear].play();
    //             if (indice_sound_clear == 2)
    //             {
    //                 indice_sound_clear = 0;
    //                 m_toggle_level_up = true;
    //             }
    //             else
    //             {
    //                 indice_sound_clear += 1;
    //                 m_toggle_level_up = false;
    //             }
    //         }
    //     }
        verify_all_grid_clear();


}
void Game::verify_all_grid_clear()
{  
    vector<ofVec2f> indice_to_clear{}; //Vector des position a supprimer 
    int nb_blocs_lign = 0;
    bool get_out = false;
    //Parcour du tableau d'état pour trouver les ligne horizontales de plus de 4 blocs
    for (unsigned int i = 0; i < nb_lignes; i++)
    {
        for (unsigned int y = 0; y < nb_col; y++)
        {
            if (m_etat_table[i][y] != '.')
            {
                while (get_out == false && ((y + nb_blocs_lign) <= (nb_col - 1))) //6 doit etre valider.
                {
                    if (m_etat_table[i][y] == m_etat_table[i][y + 1 + nb_blocs_lign])
                    {
                        nb_blocs_lign += 1;
                    }
                    else
                    {
                        get_out = true;
                        if(nb_blocs_lign >= 3)
                        {
                            for (unsigned int z = 0; z <= nb_blocs_lign; z++)
                            {
                                indice_to_clear.push_back(ofVec2f((y + z), i));
                                ofLog() << indice_to_clear.back(); 
                            }
                            ofLog() << "4 blocs ou plus en lignes Horizontale : " << "(" << y << "," << i << ") --> " <<"(" << (y + nb_blocs_lign) << "," << i << ")";
                            y = y + nb_blocs_lign; // ne pas vérifer les blocs déja tagués
                        }
                        nb_blocs_lign = 0;
                    }

                }
                get_out = false;
            }
        }
    }
    //Parcour du tableau d'état pour trouver les ligne verticales de plus de 4 blocs
    for (unsigned int i = 0; i < nb_lignes; i++)
    {
        for (unsigned int y = 0; y < nb_col; y++)
        {
            if (m_etat_table[i][y] != '.')
            {
                ofLog() << i + nb_blocs_lign << "<=" << nb_blocs_lign - 1;
                while (get_out == false && ((i + nb_blocs_lign) <= (nb_lignes - 1)))
                {
                    if (m_etat_table[i][y] == m_etat_table[i + 1 + nb_blocs_lign][y])
                    {
                        nb_blocs_lign += 1;
                    }
                    else
                    {
                        get_out = true;
                        if(nb_blocs_lign >= 3)
                        {
                            for (unsigned int z = 0; z <= nb_blocs_lign; z++)
                            {
                                indice_to_clear.push_back(ofVec2f(y, (i + z)));
                                ofLog() << indice_to_clear.back(); 
                            }
                            ofLog() << "4 blocs ou plus en lignes Verticales : " << "(" << y << "," << i << ") --> " <<"(" << (y + nb_blocs_lign) << "," << i << ")";
                            i = i + nb_blocs_lign; // ne pas vérifer les blocs déja tagués
                        }
                        nb_blocs_lign = 0;
                    }

                }
                get_out = false;
            }
        }
    }
    for (unsigned int i = 0; i < indice_to_clear.size(); i++) // Parcour de tous les indices à supprimer dans le tableau d'état et dans le vector d'objet 
    {
        ofLog() << i;
        ofLog() << indice_to_clear[i].x;
        ofLog() << indice_to_clear[i].y;
        set_block_from_pos_in_table(indice_to_clear[i].x, indice_to_clear[i].y, '.'); //On met le tableau d'état a jour.
        for (unsigned int y = 0; y < m_blocs.size(); y++)
        {
            if (m_blocs[y]->get_pos_on_grid() == indice_to_clear[i])
            {
                m_blocs.erase(m_blocs.begin() + y);
            }
        }


        game_clear_bloc[indice_sound_clear].play();
        if (indice_sound_clear == 2)
        {
            indice_sound_clear = 0;
            m_toggle_level_up = true;
        }
        else
        {
            indice_sound_clear += 1;
            m_toggle_level_up = false;
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

