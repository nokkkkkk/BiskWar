// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "Factoblocs.h"

using namespace objects_in_scene;

Blocs* Factoblocs::get_bloc(int p_type_bloc)
{
    // switch(p_type_bloc)
    // {
    //     case 1:
            Std_bloc *bloc_std = new Std_bloc;
            // bloc_std->setup();                     
            return bloc_std;           
    //     break;
        
    // }
}