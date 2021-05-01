// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "Instance_Imported.h"

namespace objects_in_scene
{

    /**
 * \brief Constructeur par défaut.
*/

    Instance_Imported::Instance_Imported()
    {
    }
    void Instance_Imported::asg_toggle_rotation_x()
    {
    }
    void Instance_Imported::asg_toggle_rotation_y()
    {
    }
    void Instance_Imported::asg_toggle_rotation_z()
    {
    }
    void Instance_Imported::asg_toggle_lego_lock(bool p_cond)
    {
    }
    void Instance_Imported::asg_vitesse_rotation(float speed)
    {
    }
    void Instance_Imported::asg_toggle_mode_lego(bool p_condition)
    {
    }
    void Instance_Imported::asg_scale(float p_scale)
    {
    }
    void Instance_Imported::asg_position(float p_x, float p_y, float p_z)
    {
    }
    void Instance_Imported::asg_bounding_size(int p_x, int p_y)
    {
    }
    void Instance_Imported::select_obj(int p_x, int p_y, int p_button)
    {
    }
    void Instance_Imported::move_obj(int p_x, int p_y, int p_z, int p_button)
    {
    }
    void Instance_Imported::redim_obj(int p_x, int p_y, int p_button)
    {
    }
    void Instance_Imported::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
    {
    }
    void Instance_Imported::asg_image_selected(bool p_selected)
    {
    }
    void Instance_Imported::asg_choix_filtre()
    {
    }
    void Instance_Imported::set_close_true()
    {
    }
    void Instance_Imported::resetMouse(int p_x, int p_y, int p_button)
    {
    }
    const string Instance_Imported::getPathName() const 
    {
        return "";
    }
    bool Instance_Imported::req_close_true() const
    {
        return false;
    }
    bool Instance_Imported::req_image_selected() const
    {
        return false;
    }
    int Instance_Imported::req_pos_z() const
    {
        return 0;
    }
    ofTexture Instance_Imported::req_texture() const 
    {
        return ofTexture();
    }
    void Instance_Imported::set_shader(int p_shader)
    {
    }
    void Instance_Imported::set_filling_color(ofVec3f p_fill_color)
    {
    }
    void Instance_Imported::set_enable_materiel()
    {
    }
    void Instance_Imported::set_texture(int p_texture)
    {
    }
    void Instance_Imported::set_choix_material(int p_choi)
    {
    }
    void Instance_Imported::set_nb_dynamic_light(int p_nbLight)
    {
    }
    void Instance_Imported::set_pos_dynamic_light(ofVec3f p_pos)
    {
    }

} /*namespace objects_in_scene*/