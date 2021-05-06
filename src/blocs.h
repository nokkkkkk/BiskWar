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

        virtual bool get_bloc_lock() const;




        virtual void select_obj(int p_x, int p_y, int p_button) ;
        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void redim_obj(int p_x, int p_y, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);
        virtual bool req_close_true() const;
        virtual bool req_image_selected() const;
        virtual int req_pos_z() const;
        virtual ofTexture req_texture() const;
        virtual void asg_image_selected(bool p_selected);
        virtual void asg_toggle_rotation_x();
        virtual void asg_toggle_rotation_y();
        virtual void asg_toggle_rotation_z();
        virtual void asg_toggle_lego_lock(bool p_cond);
        virtual void asg_vitesse_rotation(float speed);
        virtual void asg_choix_filtre();
        virtual void asg_toggle_mode_lego(bool p_condition);
        virtual void asg_scale(float p_scale);
        virtual void asg_position(float p_x, float p_y, float p_z);
        virtual void asg_bounding_size(int p_x, int p_y);
        virtual void set_close_true();
        virtual void resetMouse(int p_x, int p_y, int p_button);
        virtual const string getPathName() const ;
        virtual const bool get_if_cubemap() const = 0 ;
        virtual void set_shader(int p_shader);
        virtual void set_filling_color(ofVec3f p_fill_color);
        virtual void set_enable_materiel();
        virtual void set_texture(int p_texture);
        virtual void set_choix_material(int p_choi);
        virtual void set_nb_dynamic_light(int p_nbLight);
        virtual void set_pos_dynamic_light(ofVec3f p_pos);

    private:
    };

} /*namespace objects_in_scene*/

