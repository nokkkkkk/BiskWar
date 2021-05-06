// IFT3100H20_BackgroundColor/application.cpp
// Classe principale de l'application.
#include <iostream>
#include "application.h"

using namespace objects_in_scene;

void Application::setup()
{
  ofSetWindowTitle("BISK WAR 1.0");
  ofSetFrameRate(60);
  game_on = Factogame::get_game();
  cameras.setPosition(0, 0, -1000);
  cameras.lookAt(ofVec3f(0, 0, 0));
  lights.setPosition(0, 0, -1000);
  lights.lookAt(ofVec3f(0, 0, 0));
  cameras.enableOrtho();
}

void Application::draw()
{
 
 ofDisableAlphaBlending();
  ofEnableDepthTest();
  ofEnableSmoothing();
  ofEnableAntiAliasing();
  cameras.setVFlip(true);
  cameras.begin();
  lights.enable();

  for (unsigned int i = 0; i < m_blocs.size(); i++)
  {
      m_blocs[i]->show_obj();
  }

  cameras.disableOrtho();
  lights.disable();
  cameras.end();
  ofEnableAlphaBlending();
  ofDisableDepthTest();
  ofDisableSmoothing();
  ofDisableAntiAliasing();

}
void Application::update()
{
  for (unsigned int i = 0; i < m_blocs.size(); i++)
    {
      if(ofGetFrameNum() % 60 == 0)
        m_blocs[i]->move_obj(0,25,0,0);
    }
}
void Application::keyPressed(int key)
{
  switch(key)
  {
    case ofKey::OF_KEY_LEFT:
      m_blocs.back()->move_obj(25,0,0,0);
      break;
    case ofKey::OF_KEY_RIGHT:
      m_blocs.back()->move_obj(-25,0,0,0);
      break;
    case ofKey::OF_KEY_UP:
      m_blocs.back()->rotate_obj(2, 90, 0.0f, 0.0f, 1.0f);
      break;
    case ofKey::OF_KEY_DOWN:
      m_blocs.back()->move_obj(0,25,0,0);
      break;
  }

}
void Application::keyReleased(int key)
{
  switch(key)
  {
  case 106:                         // touche j
                                     
      obj_to_insert = new Import_obj;
      m_blocs.push_back(obj_to_insert);
      m_blocs.back()->setup("../../data/blocs/BW.obj");
      break;
  }
}

// fonction appelee quand la position du curseur change
void Application::mouseMoved(int x, int y)
{
}

void Application::exit()
{
}
// fonction appelee quand la position du curseur change pendant qu'un bouton d'un peripherique de pointage est appuye
void Application::mouseDragged(int x, int y, int button)
{
}
// fonction appelee quand un bouton d'un peripherique de pointage est appuye
void Application::mousePressed(int x, int y, int button)
{
}

// fonction appelee quand un bouton d'un peripherique de pointage est relâche
void Application::mouseReleased(int x, int y, int button)
{ 

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
}
