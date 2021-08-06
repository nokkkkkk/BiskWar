
#include "std_bloc.h"
#include <math.h>
  Std_bloc::Std_bloc() : Blocs()
  {
  }
  void Std_bloc::setup(bool p_block_depart)
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
    // int tempo_int_char = 0;
    int tempo_int_char = ofRandom(6);
    switch (tempo_int_char)
    {
    case 0:
      m_bloc_char = 'R';
      m_fill_color = ofColor(255, 0, 0);
      m_line_color = ofColor(155, 0, 0);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      ofLoadImage(m_texture,"../../data/textures/cailloux.jpg");
      break;
    case 1:
      m_bloc_char = 'G';
      m_fill_color = ofColor(0, 255, 0);
      m_line_color = ofColor(0, 155, 0);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      ofLoadImage(m_texture,"../../data/textures/brique.jpg");
      break;
    case 2:
      m_bloc_char = 'B';
      m_fill_color = ofColor(0, 0, 255);
      m_line_color = ofColor(0, 0, 150);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      ofLoadImage(m_texture,"../../data/textures/bois.jpg");
      break;
    case 3:
      m_bloc_char = 'Y';
      m_fill_color = ofColor(100, 100, 100);
      m_line_color = ofColor(50, 50, 50);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      ofLoadImage(m_texture,"../../data/textures/planche.jpg");
      break;
    case 4:
      m_bloc_char = 'V';
      m_fill_color = ofColor(0, 0, 0);
      m_line_color = ofColor(50, 155, 50);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      ofLoadImage(m_texture,"../../data/textures/bleu.jpg");
      break;
    case 5:
      m_bloc_char = 'P';
      m_fill_color = ofColor(0, 0, 0);
      m_line_color = ofColor(50, 155, 50);
      m_ambiant_color = ofVec3f(0.0f, 0.0f, 0.0f);
      ofLoadImage(m_texture,"../../data/textures/terre.jpg");
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

    //La lumières de chaque blocs
      m_shader.load(
    "shaderillum/phong_330_vs.glsl",
    "shaderillum/phong_330_fs.glsl");
      

  }

  void Std_bloc::show_obj()
  {

    ofEnableLighting();
    m_shader.begin();
    m_shader.setUniform3f("color_ambient", m_ambiant_color);
    m_shader.setUniform3f("color_diffuse",  0.1f, 0.2f, 0.4f);
    m_shader.setUniform3f("color_specular", 0.2f, 0.2f, 0.4f);
    m_shader.setUniform1f("brightness", 1.0f);
    m_shader.setUniform1i("nb_light", 2);
    m_shader.setUniform3f("light_position", glm::vec4(-2000.0f, -2000.0f, -1000.0f, 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
    m_shader.end();

    m_shader.begin();

    m_texture.bind();

    ofFill();
    ofDrawSphere(m_pos,m_bloc_size);

    m_texture.unbind();
    m_shader.end();
    ofDisableLighting();



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
    bool Std_bloc::get_bloc_virus() const 
    {
        return m_block_is_virus;
    }
    void Std_bloc::set_bloc_virus(bool p_cond) 
    {
      m_block_is_virus = p_cond;
    }
