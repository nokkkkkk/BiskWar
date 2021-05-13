
#include "std_bloc.h"
#include <math.h>
  Std_bloc::Std_bloc() : Blocs()
  {
  }
  void Std_bloc::setup(bool p_block_depart)
  {
    m_close_true = false; //Est-ce que on doit detruire l'objet ?
    m_block_lock = p_block_depart;
    m_bloc_size = 25;
    m_line_size = 1;
    m_pos.x = -25;
    m_pos.y = 25;
    m_pos_on_grid.x = (int)(m_pos.x / -50);
    m_pos_on_grid.y = (int)(m_pos.y / 50);
    m_pos.z = 0;
    int tempo_int_char = ofRandom(5);
    switch (tempo_int_char)
    {
    case 0:
      m_bloc_char = 'R';
      m_fill_color = ofColor(255, 0, 0);
      m_line_color = ofColor(155, 0, 0);
      break;
    case 1:
      m_bloc_char = 'G';
      m_fill_color = ofColor(0, 255, 0);
      m_line_color = ofColor(0, 155, 0);
      break;
    case 2:
      m_bloc_char = 'B';
      m_fill_color = ofColor(0, 0, 255);
      m_line_color = ofColor(0, 0, 150);
      break;
    case 3:
      m_bloc_char = 'Y';
      m_fill_color = ofColor(100, 100, 100);
      m_line_color = ofColor(50, 50, 50);
      break;
    case 4:
      m_bloc_char = 'V';
      m_fill_color = ofColor(0, 0, 0);
      m_line_color = ofColor(50, 155, 50);
      break;
    
    default: //Faut pas que ca arrive :)
      m_bloc_char = '.';
      break;
    }
    if (m_block_lock) //Si le block est lock au setup, on le place dans le tableau.
    {
      m_pos.x = (int)ofRandom(7) * -50 - 25; //On affiche la nouvelle image aleatoire sur X
      m_pos.y = (int)ofRandom(16) * 50 + 25;
      m_pos_on_grid.x = (int)(m_pos.x / -50);
      m_pos_on_grid.y = (int)(m_pos.y / 50);

    }
  }

  void Std_bloc::show_obj()
  {
    ofFill();
    ofSetColor(m_fill_color);
    ofSetLineWidth(m_line_size);
    ofDrawSphere(m_pos,m_bloc_size);
    ofNoFill();
    ofSetColor(m_line_color);
    ofSetLineWidth(m_line_size);
    ofDrawSphere(m_pos,m_bloc_size);

  }

 void Std_bloc::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
    m_pos.y += p_y;
    m_pos.x += p_x;
    m_pos_on_grid.x = (int)(m_pos.x / -50);
    m_pos_on_grid.y = (int)(m_pos.y / 50);

  }
  ofVec2f const Std_bloc::get_pos_on_grid() const 
  {
      return m_pos_on_grid;
  }
  void Std_bloc::set_bloc_lock(bool p_cond) 
  {
    m_block_lock = p_cond;
  }
  bool Std_bloc::get_bloc_lock() const
  {
    return m_block_lock;
  }
  char Std_bloc::get_bloc_char() const
  {
      return m_bloc_char;
  }
  void Std_bloc::set_bloc_char(char p_char_type) 
  {
    m_bloc_char = p_char_type;
  }
