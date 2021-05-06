
#include "std_bloc.h"
#include <math.h> 
namespace objects_in_scene
{
  Std_bloc::Std_bloc() : Blocs()
  {
  }
  void Std_bloc::setup(bool p_block_depart)
  {
    m_bloc_angle = 0;
    m_close_true = false;       //Est-ce que on doit detruire l'objet ?
    vitesse_rotation = 0.5;
    m_image_selected = false;
    m_toggle_x_rotation = false;
    m_toggle_y_rotation = false;
    m_toggle_z_rotation = false;
    m_objectImport.loadModel("../../data/blocs/BW.obj");      
    m_x_scale = 0.09;
    m_y_scale = 0.15;
    m_z_scale = 0.15;
    m_block_lock = p_block_depart;
    m_posx = ofRandom(0) - ofRandom(400); //On affiche la nouvelle image aleatoire sur X
    m_posy = 0;   
    m_posz = 0;
    if (m_block_lock)
    {
      m_posy = ofRandom(100) + ofRandom(400); 
    }            
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

  void Std_bloc::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
    if(m_posy < 550){
      m_posy += p_y;
    }
    else{
      m_block_lock = true;
    }
    m_posx += p_x;
    m_posz = p_z;
  }
  bool Std_bloc::get_bloc_lock() const
  {
    return m_block_lock;
  }

  void Std_bloc::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
  {
      m_bloc_angle += angle;
      m_objectImport.setRotation(which, m_bloc_angle, rot_x, rot_y, r_z);
  }


} /*namespace objects_in_scene*/