/**
 * \file Instance_Imported.h
 * \brief Classe responsable d'importer une image sur la scène
 * \author Guillaume Vallerand
 * \version 2.0
 */

#pragma once

#include "ofMain.h"

namespace objects_in_scene
{


    class Blocs
    {
    public: //FONCTIONS PUBLIQUES
        Blocs();
        virtual ~Blocs(){};

        virtual void setup(bool p_block_depart = false) = 0;
        virtual void show_obj() = 0;

        virtual const ofVec2f get_pos_on_grid() const;
        virtual bool get_bloc_lock() const;

        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);



    private:
    };

} /*namespace objects_in_scene*/

