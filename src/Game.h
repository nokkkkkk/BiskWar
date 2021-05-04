


#pragma once

#include "ofMain.h"
#include "import_obj.h"
#include "Instance_Imported.h"



class Game
{
public: 
    Game();
    Game(int p_nb_blocs_to_load);   
private:

  std::vector<objects_in_scene::Instance_Imported *> m_instance_Imported; // Déclaration d'un vecteur de pointeur pour Polymorphisme
  objects_in_scene::Import_obj *obj_to_insert;          
};


