
#include "virus_bloc.h"
#include <math.h>
  Virus_bloc::Virus_bloc() : Blocs()
  {
  }
  void Virus_bloc::setup(bool p_block_depart)
  {

    m_close_true = false; //Est-ce que on doit detruire l'objet ?
    m_block_lock = p_block_depart;
    m_block_is_virus = p_block_depart;
    m_bloc_size = 25;
    m_line_size = 1;
    m_pos.x = -25;
    m_pos.y = 25;
    m_pos_on_grid.x = (int)(m_pos.x / -50);
    m_pos_on_grid.y = (int)(m_pos.y / 50);
    m_pos.z = 0;
    virus_light.setPosition(0, 0, -100);
    virus_light.lookAt(ofVec3f(0, 0, 0));
    // int tempo_int_char = 0;
    int tempo_int_char = ofRandom(6);
    switch (tempo_int_char)
    {
    case 0:
      m_bloc_char = 'R';
      m_fill_color = ofColor(255, 0, 0);
      m_line_color = ofColor(155, 0, 0);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      m_virus.loadModel("../../data/virus/v1.obj");
      break;
    case 1:
      m_bloc_char = 'G';
      m_fill_color = ofColor(0, 255, 0);
      m_line_color = ofColor(0, 155, 0);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      m_virus.loadModel("../../data/virus/v2.obj");
      break;
    case 2:
      m_bloc_char = 'B';
      m_fill_color = ofColor(0, 0, 255);
      m_line_color = ofColor(0, 0, 150);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      m_virus.loadModel("../../data/virus/v3.obj");
      break;
    case 3:
      m_bloc_char = 'Y';
      m_fill_color = ofColor(100, 100, 100);
      m_line_color = ofColor(50, 50, 50);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      m_virus.loadModel("../../data/virus/v4.obj");
      break;
    case 4:
      m_bloc_char = 'V';
      m_fill_color = ofColor(0, 0, 0);
      m_line_color = ofColor(50, 155, 50);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      m_virus.loadModel("../../data/virus/v5.obj");
      break;
    case 5:
      m_bloc_char = 'P';
      m_fill_color = ofColor(0, 0, 0);
      m_line_color = ofColor(50, 155, 50);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      m_virus.loadModel("../../data/virus/v6.obj");
      break;
    
    default: //Faut pas que ca arrive :)
      m_bloc_char = '.';
      break;
    }
    if (m_block_lock) //Si le block est lock au setup, on le place dans le tableau.
    {
      m_pos.x = (int)ofRandom(7) * -50 - 25; //On affiche la nouvelle image aleatoire sur X
      m_pos.y = ((int)ofRandom(12) + 4) * 50 + 25;
      m_pos_on_grid.x = (int)(m_pos.x / -50);
      m_pos_on_grid.y = (int)(m_pos.y / 50);
    }


      

  }

  void Virus_bloc::show_obj()
  {

    ofEnableLighting();
    
    m_virus.setRotation(1, ofGetFrameNum() * 1, 0.0f, 1.0f, 0.0f);
    m_virus.setPosition(
      m_pos.x,
      m_pos.y,
      m_pos.z);
    m_virus.setScale(0.0800, 0.0800, 0.0800);
    
    virus_light.setPosition( // repositionnement de la lumière en fonction de la postion du virus pour un meilleur éclairage.
      m_pos.x,
      m_pos.y,
      m_pos.z - 900);

    virus_light.lookAt(ofVec3f(m_pos.x,
      m_pos.y,
      m_pos.z));

    virus_light.enable();
    m_virus.drawFaces();
    virus_light.disable();

    ofDisableLighting();


  }

 void Virus_bloc::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
    m_pos.y += p_y;
    m_pos.x += p_x;
    m_pos_on_grid.x = (int)(m_pos.x / -50);
    m_pos_on_grid.y = (int)(m_pos.y / 50);

  }
  ofVec2f const Virus_bloc::get_pos_on_grid() const 
  {
      return m_pos_on_grid;
  }
  void Virus_bloc::set_bloc_lock(bool p_cond) 
  {
    m_block_lock = p_cond;
  }
  bool Virus_bloc::get_bloc_lock() const
  {
    return m_block_lock;
  }
  char Virus_bloc::get_bloc_char() const
  {
      return m_bloc_char;
  }
  void Virus_bloc::set_bloc_char(char p_char_type) 
  {
    m_bloc_char = p_char_type;
  }
    bool Virus_bloc::get_bloc_virus() const 
    {
        return m_block_is_virus;
    }
    void Virus_bloc::set_bloc_virus(bool p_cond) 
    {
      m_block_is_virus = p_cond;
    }
