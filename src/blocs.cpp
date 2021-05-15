// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "blocs.h"



    /**
 * \brief Constructeur par défaut.
*/

    Blocs::Blocs()
    {
    }
    void Blocs::move_obj(int p_x, int p_y, int p_z, int p_button)
    {
    }
    void Blocs::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
    {
    }
    bool Blocs::get_bloc_lock() const 
    {
        return false;
    }
    void Blocs::set_bloc_lock(bool p_cond) 
    {
    }
    bool Blocs::get_bloc_virus() const 
    {
        return false;
    }
    void Blocs::set_bloc_virus(bool p_cond) 
    {
    }
    char Blocs::get_bloc_char() const
    {
        return '.';
    }
    void Blocs::set_bloc_char(char p_char_type) 
    {
    }
    ofVec2f const Blocs::get_pos_on_grid() const 
    {
        return ofVec2f(0,0);
    }
