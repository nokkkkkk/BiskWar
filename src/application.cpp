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
}
void Application::keyPressed(int key)
{

}
void Application::keyReleased(int key)
{
  switch(key)
  {
  case 106:                         // touche j
                                      //---m_instance_Imported --> Si la touche "i" est appuyee, push_back l'objet à ajouter dans le vector et imb_import.setup() pour parametrer<--
      obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(obj_to_insert);
      m_instance_Imported.back()->setup();
      show_message("Si votre fichier OBJ est valide, vous pouvez manipuler votre Objet 3D! \nUtiliser le 'X' et '/' sur le modele pour fermer ou redimensionner\nVous pouvez déplacer votre image en -Draging-.\nLes outils de dession sont utilisables pour les rotation entre-autre.\n AMUSEZ-VOUS!");
      //---m_instance_Imported --> end <--
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
