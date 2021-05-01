// cursor.h
// Classe responsable du rendu du cursor

#pragma once

#include "ofMain.h"
#include "renderer.h"

// // énumération de différents modes pour changer la couleur d'arrière-plan
// enum class ClearMode {none, black, white, gray, color, random};

class Cursor
{
public:
    int mouse_press_x;
    int mouse_press_y;

    int mouse_current_x;
    int mouse_current_y;

    bool is_mouse_button_pressed;

    //Ajout du cursor png
    ofImage _cursors[10];
    ofImage switchCursor;

    int indexCursor;

    void setup();
    void draw();
    void mousePressed(int x, int y, int button);
    void nextCursor();

    void draw_cursor(float x, float y) const;
};
