
#include "std_bloc.h"
#include <math.h>
namespace objects_in_scene
{
  Std_bloc::Std_bloc() : Blocs()
  {
  }
  void Std_bloc::setup(bool p_block_depart)
  {
    m_close_true = false; //Est-ce que on doit detruire l'objet ?
    m_block_lock = p_block_depart;
    m_bloc_size = 20;
    m_fill_color = ofColor(255, 50, 0);
    m_line_color = ofColor(50, 155, 50);
    m_line_size = 1;
    m_pos.x = ofRandom(0) - ofRandom(400); //On affiche la nouvelle image aleatoire sur X
    m_pos.y = 0;
    m_pos.z = 0;
    if (m_block_lock) //Si le block est lock au setup, on le place dans le tableau.
    {
      m_pos.y = ofRandom(100) + ofRandom(400);
    }
  }

  void Std_bloc::show_obj()
  {
    ofFill();
    ofSetColor(m_fill_color);
    ofSetLineWidth(1);
    ofDrawSphere(m_pos,m_bloc_size);
    ofNoFill();
    ofSetColor(m_line_color);
    ofSetLineWidth(m_line_size);
    ofDrawSphere(m_pos,m_bloc_size);
  }

  void Std_bloc::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
    if (m_pos.y < 550)
    {
      m_pos.y += p_y;
    }
    else
    {
      m_block_lock = true;
    }
    m_pos.x += p_x;
    m_pos.z = p_z;
  }
  bool Std_bloc::get_bloc_lock() const
  {
    return m_block_lock;
  }

} /*namespace objects_in_scene*/