// IFT3100H20_BackgroundColor/main.cpp
// Exemple de configuration de la couleur d'arrière-plan avec une couleur fixe ou aléatoire.

#include "ofMain.h"
#include "application.h"

int main()
{

  // paramètres du contexte de rendu OpenGL
  ofGLFWWindowSettings windowSettings;

  // option de redimentionnement de la fenêtre d'affichage
  windowSettings.resizable = true;
  // windowSettings.windowMode = OF_FULLSCREEN;
  windowSettings.setSize(1920,1024);

  // sélection de la version de OpenGL
  windowSettings.setGLVersion(4, 1);

  // création de la fenêtre
  ofCreateWindow(windowSettings);

  // démarrer l'exécution de l'application
  ofRunApp(new Application());

}
