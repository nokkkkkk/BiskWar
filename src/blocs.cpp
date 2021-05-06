// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "blocs.h"

namespace objects_in_scene
{

    /**
 * \brief Constructeur par défaut.
*/

    Blocs::Blocs()
    {
    }
    void Blocs::asg_toggle_rotation_x()
    {
    }
    void Blocs::asg_toggle_rotation_y()
    {
    }
    void Blocs::asg_toggle_rotation_z()
    {
    }
    void Blocs::asg_toggle_lego_lock(bool p_cond)
    {
    }
    void Blocs::asg_vitesse_rotation(float speed)
    {
    }
    void Blocs::asg_toggle_mode_lego(bool p_condition)
    {
    }
    void Blocs::asg_scale(float p_scale)
    {
    }
    void Blocs::asg_position(float p_x, float p_y, float p_z)
    {
    }
    void Blocs::asg_bounding_size(int p_x, int p_y)
    {
    }
    void Blocs::select_obj(int p_x, int p_y, int p_button)
    {
    }
    void Blocs::move_obj(int p_x, int p_y, int p_z, int p_button)
    {
    }
    void Blocs::redim_obj(int p_x, int p_y, int p_button)
    {
    }
    void Blocs::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
    {
    }
    void Blocs::asg_image_selected(bool p_selected)
    {
    }
    void Blocs::asg_choix_filtre()
    {
    }
    void Blocs::set_close_true()
    {
    }
    void Blocs::resetMouse(int p_x, int p_y, int p_button)
    {
    }
    const string Blocs::getPathName() const 
    {
        return "";
    }
    bool Blocs::req_close_true() const
    {
        return false;
    }
    bool Blocs::req_image_selected() const
    {
        return false;
    }
    int Blocs::req_pos_z() const
    {
        return 0;
    }
    ofTexture Blocs::req_texture() const 
    {
        return ofTexture();
    }
    void Blocs::set_shader(int p_shader)
    {
    }
    void Blocs::set_filling_color(ofVec3f p_fill_color)
    {
    }
    void Blocs::set_enable_materiel()
    {
    }
    void Blocs::set_texture(int p_texture)
    {
    }
    void Blocs::set_choix_material(int p_choi)
    {
    }
    void Blocs::set_nb_dynamic_light(int p_nbLight)
    {
    }
    void Blocs::set_pos_dynamic_light(ofVec3f p_pos)
    {
    }

} /*namespace objects_in_scene*/