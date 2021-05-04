// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "cursor.h"
#include "import_obj.h"
#include "cubeMap.h"
#include "Instance_Imported.h"
#include "Factogame.h"
#include "Game.h"

class Application : public ofBaseApp
{
  private :

  std::vector<objects_in_scene::Instance_Imported *> m_instance_Imported; // Déclaration d'un vecteur de pointeur pour Polymorphisme
  objects_in_scene::Import_obj *obj_to_insert;                            //Déclaration d'un pointeur d'objet pour creer des nouveau objet a envoyer au PUSHBACK du vecteur

  Game game_online;
  ofLight lights;
  ofCamera cameras;
public:
  Renderer renderer;
  Cursor cursor;
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
