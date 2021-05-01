// cursor.cpp
// Classe responsable du rendu du curseur

#include "cursor.h"

void Cursor::setup()
{
  mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = 0;
  is_mouse_button_pressed = false;
  //Inclusion des différentes images curseur
  for (int i = 0; i < 10; i++)
    _cursors[i].load("../../data/cur" + std::to_string(i + 1) + ".png");
  switchCursor.load("../../data/switchcur.png");
  indexCursor = 0;
}

void Cursor::draw()
{
  // épaisseur du trait
  ofSetLineWidth(2);
  // afficher le curseur
  draw_cursor(mouse_current_x, mouse_current_y);
}

// fonction qui dessine un curseur
void Cursor::draw_cursor(float x, float y) const
{
  ofHideCursor(); //Cacher le cursor du OS

  //Affiche le bon image en fonctione de l'index recu.
  // switchCursor.draw(ofGetWindowWidth() / 2 - switchCursor.getWidth() / 2, 300);
  _cursors[indexCursor].draw(x, y);
}