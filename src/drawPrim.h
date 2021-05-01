/**
 * \file drawPrim->h
 * \brief Classe responsable d'importer une image sur la scène
 * \author Guillaume Vallerand
 * \version 2.0
 */

#ifndef DRAWPRIM_H_
#define DRAWPRIM_H_

#pragma once

#include "ofMain.h"
#include "Outil_dessin.h"
#include "Instance_Imported.h"

namespace objects_in_scene
{

    /**
 * \class DrawPrim
 * \brief Cette classe permet d'importer un fichier image
 *
 *        On peut ensuite sélectionner, déplacer et redimentionner l'image.
 *        
 */

    class DrawPrim : public Instance_Imported
    {
    public: //FONCTIONS PUBLIQUES
        DrawPrim(int type, float p_posx, float p_posy, float p_width, float p_height, ofVec3f p_line_color, ofVec3f p_fill_color);
        void setup(string p_path = "", bool p_obj_du_menu = false);

        void show_obj();

        virtual void select_obj(int p_x, int p_y, int p_button);
        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void redim_obj(int p_x, int p_y, int p_button);
        virtual bool req_close_true() const;
        virtual bool req_image_selected() const;
        virtual int req_pos_z() const;
        virtual ofTexture req_texture() const;
        virtual void asg_image_selected(bool p_selected);
        virtual void resetMouse(int p_x, int p_y, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);
        virtual const string getPathName() const;
        void drawRectangle();
        void drawCircle();
        void drawTriangle();
        void drawPolygone();
        void drawLine();
        void drawBox();
        void drawShere();
        virtual void asg_choix_filtre();
        virtual const bool get_if_cubemap() const ;
        virtual void set_shader(int p_shader);
        virtual void set_texture(int p_texture);
        virtual void set_choix_material(int p_choi);
        virtual void set_nb_dynamic_light(int p_nbLight);
        virtual void set_pos_dynamic_light(ofVec3f p_pos);

    private:
        //ATTRIBUTS PRIVÉS
        ofImage m_imageImport;                 //image qui sera chargée.
        ofFileDialogResult m_path_fichier_img; //Boite de sélection de fichier qui demande un path.
        Outil_dessin outil_dessin;             //Instance pour acceger au valeur de l'outil du GUI
        string m_path_name;                    //Nom du pathName en string.
        bool m_image_selected;                 //détermine si l'image est sélectionnée
        bool m_image_redim_selected;           //détermine si l'image est sélectionnée et la zone de redim
        bool m_mouse_move_image;               // Si le clic est dans l'image, on active mouse mouseDragged()
        int m_posx;                            //Conserve la position X de l'image
        int m_posy;                            //Conserve la position Y  de l'image
        float m_rotx;                          //Conserve la rotation X  de l'image
        float m_roty;                          //Conserve la rotationY  de l'image
        float m_rotz;                          //Conserve la rotation Z  de l'image
        int m_width_img;                       //La largeur de l'image en tout temps
        int m_height_img;                      //La hauteur de l'image en tout temps
        int m_original_m_width_img;            //La largeur original avant redimension à des fins de calculs
        int m_original_m_height_img;           //La largeur hauteur avant redimension à des fins de calculs
        int m_redim_box_height;                //La hauteur de la boite de redimension
        int m_redim_box_width;                 //La largeur de la boite de redimension
        int m_close_box_height;                //La hauteur de la boite de destruction
        int m_close_box_width;                 //La largeur de la boite de destruction

        int m_clicked_x;    //Conserve un clic X
        int m_clicked_y;    //Conserve un clic Y
        int m_x_correction; //Conserve la correction X à appliquer pour un déplacement serin :)
        int m_y_correction; //Conserve la correction Y  à apliquer pour un déplacement serin :)
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
        ofVec3f m_line_color;
        ofVec3f m_fill_color;
        ofVec3f m_line_colorN;
        ofVec3f m_fill_colorN;
        int m_line_width;
        int m_choi_prim;
        int m_choi_text;

        ofShader m_shaders_illum[6];;
        ofShader* m_shader;
        // ofLight* shader_light;
        ofLight m_light;
        string m_shader_name;
        int m_index_shader_select;


        ofMaterial m_materiel_lego[4];
        int m_choi_materiau;

        ofTexture m_texture;
        ofTexture m_normal_map;
        bool m_enable_texture;
        int m_index_texture_select;

        int m__nb_light_dynamic;




        
        //FONCTIONS PRIVÉS

        void m_show_select(); //Dessine la boite de sélection
    };

} /*namespace objects_in_scene*/

#endif /* IMPORT_IMG_H_ */