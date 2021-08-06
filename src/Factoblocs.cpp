// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "Factoblocs.h"

Blocs* Factoblocs::get_bloc(int p_type_bloc)
{
    switch(p_type_bloc)
    {
        case 1:
        {
            Std_bloc *bloc_std = new Std_bloc;                  
            return bloc_std;           
        }
        break;
        case 2:
        {
            Virus_bloc *bloc_virus = new Virus_bloc;                  
            return bloc_virus;           
        }
        break;
        default:
        {
            Std_bloc *bloc_std = new Std_bloc;                  
            return bloc_std;           
        }
        break;
        
    }
}