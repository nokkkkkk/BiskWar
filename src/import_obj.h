/**
 * \file Import_obj->h
 * \brief Classe responsable d'importer une image sur la scène
 * \author Guillaume Vallerand
 * \version 2.0
 */

#ifndef Import_obj_H_
#define Import_obj_H_

#pragma once

#include "ofMain.h"
#include "Outil_dessin.h"
#include "Instance_Imported.h"
#include "ofxAssimpModelLoader.h"

namespace objects_in_scene
{

    /**
 * \class Import_obj
 * \brief Cette classe permet d'importer un fichier image
 *
 *        On peut ensuite sélectionner, déplacer et redimentionner l'image.
 *        
 */

    class Import_obj : public Instance_Imported
    {
    public: //FONCTIONS PUBLIQUES
        Import_obj();
        void setup(string p_path = "", bool p_obj_du_menu = false);

        void show_obj();

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
        ofFileDialogResult m_path_fichier_img; //Boite de sélection de fichier qui demande un path.
        Outil_dessin outil_dessin;             //Instance pour acceger au valeur de l'outil du GUI
        string m_path_name;                    //Nom du pathName en string.
        bool m_image_selected;                 //détermine si l'image est sélectionnée
        bool m_image_redim_selected;           //détermine si l'image est sélectionnée et la zone de redim
        bool m_mouse_move_image;               // Si le clic est dans l'image, on active mouse mouseDragged()
        bool m_toggle_x_rotation;
        bool m_toggle_y_rotation;
        bool m_toggle_z_rotation;
        bool m_hard_coded_obj;
        bool m_obj_du_menu;
        bool m_lego_lock;
        float vitesse_rotation;
        int m_posx;       //Conserve la position X de l'image
        int m_posy;       //Conserve la position Y  de l'image
        int m_posz;       //Conserve la position Y  de l'image
        int m_posx_lego; //Conserve la position X de la box
        int m_posy_lego; //Conserve la position Y  de la box
        int m_posz_lego; //Conserve la position Y  de la box
        int m_width_img;  //La largeur de l'image en tout temps
        int m_height_img; //La hauteur de l'image en tout temps
        int m_random_rotation; //Valeur pour que les objet ne tourne pas en meme temps.

        std::vector<ofVec3f> m_model_vertices; //Vecteur pour contenir la liste des sommets du model.
        ofMesh m_model_mesh;
        float m_model_max_x;                     //sommet le max en x
        float m_model_min_x;                     //sommet le min en x
        float m_model_max_y;                     //sommet le max en y
        float m_model_min_y;                     //sommet le min en y

        float new_scale_x;           //scale Calculer avec la box de selection ********METTRE DANS DES VECTEUR DANS LE FUTUR !!!!*******
        float new_scale_y;           //scale Calculer avec la box de selection
        float new_scale_z;           //scale Calculer avec la box de selection
        float m_x_scale;             //La x de l'image en tout temps
        float m_y_scale;             //La y de l'image en tout temps
        float m_z_scale;             //La z de l'image en tout temps
        int m_original_m_width_img;  //La largeur original avant redimension à des fins de calculs
        int m_original_m_height_img; //La largeur hauteur avant redimension à des fins de calculs
        int m_redim_box_height;      //La hauteur de la boite de redimension
        int m_redim_box_width;       //La largeur de la boite de redimension
        int m_close_box_height;      //La hauteur de la boite de destruction
        int m_close_box_width;       //La largeur de la boite de destruction

        int m_clicked_x;    //Conserve un clic X
        int m_clicked_y;    //Conserve un clic Y
        int m_x_correction; //Conserve la correction X à appliquer pour un déplacement serin :)
        int m_y_correction; //Conserve la correction Y  à apliquer pour un déplacement serin :)
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
        bool m_mode_lego;  
        bool m_enable_materiel;
        ofMatrix4x4 m_model_matrix;
        ofVec3f m_scaling;
                          

        ofShader m_shaders_illum[5];;
        ofShader* m_shader;
        ofLight m_light;
        string m_shader_name;
        int m_index_shader_select;

        ofMaterial m_materiel_lego[4];
        int m_choi_materiau;

        ofVec3f m_fill_color;
        ofVec3f m_fill_colorN;

        ofTexture m_texture;
        ofTexture m_normal_map;
        bool m_enable_texture;
        int m_index_texture_select;

        int m__nb_light_dynamic;

        void m_show_select(); //Dessine la boite de sélection


        int m_bloc_angle;


    };

} /*namespace objects_in_scene*/

#endif /* Import_obj_H_ */