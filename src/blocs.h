/**
 * \file Instance_Imported.h
 * \brief Classe responsable d'importer une image sur la scène
 * \author Guillaume Vallerand
 * \version 2.0
 */

#pragma once

#include "ofMain.h"




    class Blocs
    {
    public: //FONCTIONS PUBLIQUES
        Blocs();
        virtual ~Blocs(){};

        virtual void setup(bool p_block_depart = false) = 0;
        virtual void show_obj() = 0;

        virtual const ofVec2f get_pos_on_grid() const;
        virtual bool get_bloc_lock() const;
        virtual void set_bloc_lock(bool p_cond);
        virtual bool get_bloc_virus() const;
        virtual void set_bloc_virus(bool p_cond);
        virtual char get_bloc_char() const;
        virtual void set_bloc_char(char p_char_type);

        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);



    private:
    };
