// IFT3100H20_BackgroundColor/application.cpp
// Classe principale de l'application.
#include <iostream>
#include "application.h"

void Application::setup()
{
  ofSetWindowTitle("BISK WAR 1.0");
  ofSetFrameRate(60);

  game_on = *Factogame::get_game(1);
  all_blocs_are_lock = false;

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

  ofPushMatrix();//matrice de la partie joueur 1
  ofTranslate(700, -500, 0); // Décalage de la matrice du joueur 1

    for (unsigned int i = 0; i < game_on.get_vecteur_blocs().size(); i++)
    {
      game_on.get_vecteur_blocs()[i]->show_obj();
    }
    game_on.show_grid();

  ofPopMatrix();


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
  all_blocs_are_lock = true;
  for (unsigned int i = 0; i < game_on.get_vecteur_blocs().size(); i++)
  {
    if (game_on.get_vecteur_blocs()[i]->get_bloc_lock() == false)
    {
      all_blocs_are_lock = false;
    }
    else
    {
      game_on.set_block_from_pos_in_table(game_on.get_vecteur_blocs()[i]->get_pos_on_grid().x, game_on.get_vecteur_blocs()[i]->get_pos_on_grid().y, 'G');
    }
  }
  if (all_blocs_are_lock)
  {
    game_on.add_bloc(1);
  }
  if (ofGetFrameNum() % 60 == 0)
    game_on.get_vecteur_blocs().back()->move_obj(0, 50, 0, 0, game_on);
}
void Application::keyPressed(int key)
{
  switch (key)
  {
  case ofKey::OF_KEY_LEFT:
    game_on.get_vecteur_blocs().back()->move_obj(50, 0, 0, 0, game_on);
      game_on.show_state_table();
    break;
  case ofKey::OF_KEY_RIGHT:
    game_on.get_vecteur_blocs().back()->move_obj(-50, 0, 0, 0, game_on);
    break;
  case ofKey::OF_KEY_UP:
    game_on.get_vecteur_blocs().back()->rotate_obj(2, 90, 0.0f, 0.0f, 1.0f);
    break;
  case ofKey::OF_KEY_DOWN:
    game_on.get_vecteur_blocs().back()->move_obj(0, 50, 0, 0, game_on);
    break;
  }
}
void Application::keyReleased(int key)
{
  switch (key)
  {
  case 106: // touche j
    game_on.add_bloc(1);
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
