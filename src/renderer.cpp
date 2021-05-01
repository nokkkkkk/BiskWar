// IFT3100H20_BackgroundColor/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

using namespace objects_in_scene;

void Renderer::setup()
{

  cameras.setPosition(0, 0, 1000);
  cameras.lookAt(ofVec3f(0, 0, 0));
  // lights.setPosition(ofVec3f(0, 0, 1100));
  // lights.lookAt(ofVec3f(0, 0, 0));


  // mode initial
  clear_mode = ClearMode::none;

  // couleur initiale
  clear_color_r = 0;
  clear_color_g = 0;
  clear_color_b = 0;

  // changement d'état
  has_changed = true;

  blocLife.load("../../data/bloc-life.png");


  // 1. couleur d'arrière-plan fixe et automatique

  // efface automatiquement le framebuffer et le rempli avec la couleur d'arrière-plan courante au début de chaque appel de la fonction draw (actif par défaut)
  ofSetBackgroundAuto(true);

  // si la couleur d'arrière-plan de ne change pas et est en mode automatique, elle peut être configurée et appliquée en une seule étape dans la fonction d'initialisation
  ofSetBackgroundColor(clear_color_r, clear_color_g, clear_color_b);

  // 2. couleur d'arrière-plan variable et/ou changée explicitement

  // désactiver l'application automatique de la couleur d'arrière-plan à chaque appel de la fonction draw
  ofSetBackgroundAuto(false);

  // 2.1 sélectionne la couleur d'arrière-plan courante, mais ne l'applique pas immédiatement
  ofSetBackgroundColor(clear_color_r, clear_color_g, clear_color_b);

  // 2.2 sélectionne la couleur d'arrière-plan courante et l'applique immédiatement
  ofBackground(clear_color_r, clear_color_g, clear_color_b);
}

void Renderer::draw()
{
  // lights.enable();
  cameras.begin();
  cameras.enableOrtho();

  // 3. appliquer la couleur d'arrière-plan selon le mode courant
  switch (clear_mode)
  {
  default:
    ofBackground(0 , 0, 0, 255);
    break;
  }
  ofPushMatrix();
  // ofTranslate(-ofGetWidth() / 2 , -ofGetHeight() / 2);
  blocLife.draw(-blocLife.getWidth() / 2, -ofGetWindowHeight()  + blocLife.getHeight()*2);
  
   
  ofPopMatrix();

  cameras.disableOrtho();
    cameras.end();
    // lights.disable();
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur par défaut
void Renderer::clear() const
{
  ofBackground(0, 0, 0, 0);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par la couleur noir
void Renderer::clear_to_black() const
{
  ofBackground(0);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par la couleur blanc
void Renderer::clear_to_white() const
{
  ofBackground(255);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par un ton de gris passé en paramètre
void Renderer::clear_to_gray(int g)
{
  if (has_changed)
  {
    has_changed = false;
    clear_color_gray = g;
  }

  ofBackground(clear_color_gray);
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur RGB passée en paramètre
void Renderer::clear_to_color(int r, int g, int b)
{

  clear_color_r = r;
  clear_color_g = g;
  clear_color_b = b;

  clear();
}

// fonction qui efface le contenu du framebuffer actif et le remplace par une couleur RGB aléatoire
void Renderer::clear_to_random()
{
  if (has_changed)
  {
    has_changed = false;

    clear_color_r = (int)ofRandom(0, 256);
    clear_color_g = (int)ofRandom(0, 256);
    clear_color_b = (int)ofRandom(0, 256);
  }

  clear();
}
