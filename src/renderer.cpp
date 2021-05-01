// IFT3100H20_BackgroundColor/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

using namespace objects_in_scene;

void Renderer::setup()
{

  cameras.setPosition(0, 0, 1000);
  cameras.lookAt(ofVec3f(0, 0, 0));
}

void Renderer::draw()
{
  cameras.begin();
  cameras.enableOrtho();


  cameras.disableOrtho();
    cameras.end();
    // lights.disable();
}



