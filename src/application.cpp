// IFT3100H20_BackgroundColor/application.cpp
// Classe principale de l'application.
#include <iostream>
#include "application.h"

using namespace objects_in_scene;

void Application::setup()
{
  ofSetWindowTitle("BISK WAR 1.0");
  ofSetFrameRate(60);
  renderer.setup();
}

void Application::draw()
{
  
  ofDisableAlphaBlending();
  ofEnableDepthTest();
  ofEnableSmoothing();
  ofEnableAntiAliasing();

  renderer.draw();
  //---m_instance_Imported --> parcour du vector d'images afin de l'afficher et d'afficher la zone de selection autour.<--
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
     
        m_instance_Imported[i]->show_obj();
      // materiel_lego[choi_materiau].end();
      if (m_instance_Imported[i]->req_close_true() == 1)
      { //Si on doit ferme l'image on lenleve du vector
        m_instance_Imported.erase(m_instance_Imported.begin() + i);
      }
    }

  renderer.draw();

  ofEnableAlphaBlending();
  ofDisableDepthTest();
  ofDisableSmoothing();
  ofDisableAntiAliasing();

}
void Application::update()
{
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      m_instance_Imported[i]->move_obj(0,1,0,0);
    }
}
void Application::keyPressed(int key)
{
  switch(key)
  {
    case ofKey::OF_KEY_LEFT:
      m_instance_Imported.back()->move_obj(-25,0,0,0);
      break;
    case ofKey::OF_KEY_RIGHT:
      m_instance_Imported.back()->move_obj(25,0,0,0);
      break;
    case ofKey::OF_KEY_UP:
      m_instance_Imported.back()->rotate_obj(2, 90, 0.0f, 0.0f, 1.0f);
      break;
    case ofKey::OF_KEY_DOWN:
      m_instance_Imported.back()->move_obj(0,25,0,0);
      break;
  }

}
void Application::keyReleased(int key)
{
  switch(key)
  {
  case 106:                         // touche j
                                     
      obj_to_insert = new Import_obj;
      m_instance_Imported.push_back(obj_to_insert);
      m_instance_Imported.back()->setup("/home/guillaume/ULAVAL/Info/OF/apps/myApps/BiskWar/data/blocs/BW.obj");
      break;
  }
}

// fonction appelee quand la position du curseur change
void Application::mouseMoved(int x, int y)
{
  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;
}

void Application::exit()
{
}
// fonction appelee quand la position du curseur change pendant qu'un bouton d'un peripherique de pointage est appuye
void Application::mouseDragged(int x, int y, int button)
{
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
   m_instance_Imported[i]->move_obj(x, y, m_instance_Imported[i]->req_pos_z(), button);
   m_instance_Imported[i]->redim_obj(x, y, button);
  }
  

}
// fonction appelee quand un bouton d'un peripherique de pointage est appuye
void Application::mousePressed(int x, int y, int button)
{

  anchorx = x;
  anchory = y;

  cursor.is_mouse_button_pressed = true;

  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

  cursor.mouse_press_x = x;
  cursor.mouse_press_y = y;
 for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
      m_instance_Imported[i]->select_obj(x, y, button);
      if (m_instance_Imported[i]->req_close_true() == 1)
      { //Si la zone de destruction de l'objet dans le vesteur est cliquee, on le supprime du vector.
        m_instance_Imported.erase(m_instance_Imported.begin() + i);
      }
    
  }
}

// fonction appelee quand un bouton d'un peripherique de pointage est relâche
void Application::mouseReleased(int x, int y, int button)
{ 
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
    m_instance_Imported[i]->resetMouse(x, y, button);
  }

}

// fonction appelee quand le curseur entre dans la fenêtre d'affichage
void Application::mouseEntered(int x, int y)
{

}

// fonction appelee quand le curseur sort de la fenêtre d'affichage
void Application::mouseExited(int x, int y)
{
}

// fonction appelée pour reset tous les caméra à leur position init.
void Application::show_message(string new_message)
{
  message = new_message;
  ofLog() << message;
}
