// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "std_bloc.h"
#include "blocs.h"
#include "Factogame.h"
#include "Factoblocs.h"
#include "Game.h"

class Application : public ofBaseApp
{
private:
  std::vector<Blocs *> m_blocs; // Déclaration d'un vecteur de pointeur pour Polymorphisme
  Std_bloc *obj_to_insert;      //Déclaration d'un pointeur d'objet pour creer des nouveau objet a envoyer au PUSHBACK du vecteur

  Game game_on;
  ofLight lights;
  ofCamera cameras;
  bool all_blocs_are_lock;

public:
  Renderer renderer;
  string message;

  void setup();
  void draw();
  void update();

  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void show_message(string new_message);
  void keyReleased(int key);
  void keyPressed(int key);

  void exit();
};
