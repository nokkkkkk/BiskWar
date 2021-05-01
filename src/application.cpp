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

  renderer.draw();

}
void Application::update()
{
}
void Application::keyPressed(int key)
{

}
void Application::keyReleased(int key)
{
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
  message = new_message;
  ofLog() << message;
}
