
#pragma once

#include "ofMain.h"
#include "blocs.h"
#include "ofxAssimpModelLoader.h"

namespace objects_in_scene
{

    class Std_bloc : public Blocs
    {
    public: //FONCTIONS PUBLIQUES
        Std_bloc();
        void setup(bool p_block_depart = false);
        void show_obj();
        bool get_bloc_lock() const;

        virtual void select_obj(int p_x, int p_y, int p_button);
        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void redim_obj(int p_x, int p_y, int p_button);
        virtual bool req_close_true() const;
        virtual bool req_image_selected() const;
        virtual int req_pos_z() const;
        virtual void asg_image_selected(bool p_selected);
        virtual void asg_toggle_rotation_x();
        virtual void asg_toggle_rotation_y();
        virtual void asg_toggle_rotation_z();
        virtual void resetMouse(int p_x, int p_y, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);
        virtual const string getPathName() const;
        virtual void asg_vitesse_rotation(float speed);
        virtual void asg_toggle_mode_lego(bool p_condition);
        virtual void asg_scale(float p_scale);
        virtual void asg_position(float p_x, float p_y, float p_z);
        virtual void asg_bounding_size(int p_x, int p_y);
        virtual void asg_toggle_lego_lock(bool p_cond);
        virtual const bool get_if_cubemap() const ;
        virtual void set_filling_color(ofVec3f p_fill_color);
        virtual void set_enable_materiel();
        virtual void set_texture(int p_texture);
        virtual void set_choix_material(int p_choi);
        virtual void set_nb_dynamic_light(int p_nbLight);
        virtual void set_pos_dynamic_light(ofVec3f p_pos);

    private:
        //ATTRIBUTS PRIVÉS
        ofxAssimpModelLoader m_objectImport;   //objet qui sera chargée.
        bool m_block_lock;





        string m_path_name;                    //Nom du pathName en string.
        bool m_image_selected;
        bool m_toggle_x_rotation;
        bool m_toggle_y_rotation;
        bool m_toggle_z_rotation;
        float vitesse_rotation;
        int m_posx;       //Conserve la position X de l'image
        int m_posy;       //Conserve la position Y  de l'image
        int m_posz;       //Conserve la position Y  de l'image

        float m_x_scale;             //La x de l'image en tout temps
        float m_y_scale;             //La y de l'image en tout temps
        float m_z_scale;             //La z de l'image en tout temps
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
        bool m_mode_lego;  
        bool m_enable_materiel;

        void m_show_select(); //Dessine la boite de sélection

        int m_bloc_angle;


    };

} /*namespace objects_in_scene*/
