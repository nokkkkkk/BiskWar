/**
 * \file import_img->h
 * \brief Classe responsable d'importer une image sur la scène
 * \author Guillaume Vallerand
 * \version 2.0
 */

#ifndef IMPORT_IMG_H_
#define IMPORT_IMG_H_

#pragma once

#include "ofMain.h"
#include "Outil_dessin.h"
#include "Instance_Imported.h"

namespace objects_in_scene
{

    /**
 * \class Import_img
 * \brief Cette classe permet d'importer un fichier image
 *
 *        On peut ensuite sélectionner, déplacer et redimentionner l'image.
 *        
 */

    class Import_img : public Instance_Imported
    {
    public: //FONCTIONS PUBLIQUES
        Import_img();
        void setup(string p_path = "", bool p_obj_du_menu = false);

        void show_obj();

        virtual void select_obj(int p_x, int p_y, int p_button);
        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void redim_obj(int p_x, int p_y, int p_button);
        virtual bool req_close_true() const;
        virtual ofTexture req_texture() const;
        virtual bool req_image_selected() const;
        virtual int req_pos_z() const;
        virtual void asg_image_selected(bool p_selected);
        virtual void resetMouse(int p_x, int p_y, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);
        virtual const string getPathName() const;
        virtual void asg_choix_filtre();
        virtual const bool get_if_cubemap() const ;

    private:
        //ATTRIBUTS PRIVÉS
        ofImage m_imageImport;                 //image qui sera chargée.
        ofFileDialogResult m_path_fichier_img; //Boite de sélection de fichier qui demande un path.
        ofShader shader;
        ofShader shader_passthrough;
        ofShader shader_off_red;
        ofShader shader_grayscale;
        ofShader shader_off_blue;
        ofShader shader_off_green;

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
        int m_choix_filtre;       
        int m_nb_choix_filtre;           

        int m_clicked_x;    //Conserve un clic X
        int m_clicked_y;    //Conserve un clic Y
        int m_x_correction; //Conserve la correction X à appliquer pour un déplacement serin :)
        int m_y_correction; //Conserve la correction Y  à apliquer pour un déplacement serin :)
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
                            //FONCTIONS PRIVÉS


        void m_show_select(); //Dessine la boite de sélection
    };

} /*namespace objects_in_scene*/

#endif /* IMPORT_IMG_H_ */