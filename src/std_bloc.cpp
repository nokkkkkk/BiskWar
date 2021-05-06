
#include "std_bloc.h"
#include <math.h> 
namespace objects_in_scene
{
  Std_bloc::Std_bloc() : Blocs()
  {
  }
  void Std_bloc::setup(string p_path, bool p_obj_du_menu)
  {
    m_bloc_angle = 0;
    m_close_true = false;       //Est-ce que on doit detruire l'objet ?
    vitesse_rotation = 0.5;
    m_image_selected = false;
    m_toggle_x_rotation = false;
    m_toggle_y_rotation = false;
    m_toggle_z_rotation = false;
    string path;
    path = m_path_name = p_path;
    m_objectImport.loadModel(path);      
    m_x_scale = 0.09;
    m_y_scale = 0.15;
    m_z_scale = 0.15;
    m_posx = 0; //On affiche la nouvelle image aleatoire sur X
    m_posy = 0;               
    m_posz = 0;
  }

  void Std_bloc::show_obj()
  {
    m_objectImport.enableMaterials();
    m_objectImport.setPosition(m_posx, m_posy, m_posz);
    m_objectImport.setScale(m_x_scale, m_y_scale, m_z_scale);
    m_objectImport.drawFaces(); 
    if (m_toggle_x_rotation == true)
      m_objectImport.setRotation(0, ofGetFrameNum() * vitesse_rotation, 1.0f, 0.0f, 0.0f);
    if (m_toggle_y_rotation == true)
      m_objectImport.setRotation(1, ofGetFrameNum() * vitesse_rotation, 0.0f, 1.0f, 0.0f);
    if (m_toggle_z_rotation == true)
      m_objectImport.setRotation(2, ofGetFrameNum() * vitesse_rotation, 0.0f, 0.0f, 1.0f);
    m_objectImport.disableMaterials();
  }
  void Std_bloc::m_show_select()
  {
  }

  /**
 * \brief 
 */
  void Std_bloc::select_obj(int p_x, int p_y, int p_button)
  {
  }

  /**
 * \brief 
 */
  void Std_bloc::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
      m_posx += p_x;
      m_posy += p_y;
      m_posz = p_z;
  }
  /**
 * \brief Sélectionne l'objet et enregistre les coordo du clic.
 */
  void Std_bloc::redim_obj(int p_x, int p_y, int p_button)
  {
  }

  void Std_bloc::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
  {
      m_bloc_angle += angle;
      m_objectImport.setRotation(which, m_bloc_angle, rot_x, rot_y, r_z);
  }

  bool Std_bloc::req_close_true() const
  {
    return m_close_true;
  }
  bool Std_bloc::req_image_selected() const
  {
    return m_image_selected;
  }
  void Std_bloc::asg_image_selected(bool p_selected)
  {
    m_image_selected = p_selected;
  }
  void Std_bloc::resetMouse(int p_x, int p_y, int p_button)
  {
  }
  const string Std_bloc::getPathName() const
  {
    return m_path_name;
  }
  void Std_bloc::asg_toggle_rotation_x()
  {
    m_toggle_x_rotation = !m_toggle_x_rotation;
  }
  void Std_bloc::asg_toggle_rotation_y()
  {
    m_toggle_y_rotation = !m_toggle_y_rotation;
  }
  void Std_bloc::asg_toggle_rotation_z()
  {
    m_toggle_z_rotation = !m_toggle_z_rotation;
  }
  void Std_bloc::asg_vitesse_rotation(float speed)
  {
    vitesse_rotation = speed;
  }
  void Std_bloc::asg_toggle_mode_lego(bool p_condition)
  {
  }
  int Std_bloc::req_pos_z() const
  {
    return m_posz;
  }
  void Std_bloc::asg_scale(float p_scale)
  {
   m_objectImport.setScale(p_scale, p_scale, p_scale);
  }
  void Std_bloc::asg_position(float p_x, float p_y, float p_z)
  {
  }
  void Std_bloc::asg_bounding_size(int p_x, int p_y)
  {
  }
  void Std_bloc::asg_toggle_lego_lock(bool p_cond)
  {
  }
  const bool Std_bloc::get_if_cubemap() const 
  {
      return false;
  }
  void Std_bloc::set_filling_color(ofVec3f p_fill_color)
  {
  }
  void Std_bloc::set_enable_materiel()
  {
  }
  void Std_bloc::set_texture(int p_texture)
  {
  }

  void Std_bloc::set_choix_material(int p_choi)
  {
  }
  void Std_bloc::set_nb_dynamic_light(int p_nbLight)
  {
  }
  void Std_bloc::set_pos_dynamic_light(ofVec3f p_pos)
  {
  }

} /*namespace objects_in_scene*/