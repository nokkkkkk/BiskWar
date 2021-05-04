/**
 * \file Cubemap->h
 * \brief Classe responsable d'importer une image sur la scène
 * \author Guillaume Vallerand
 * \version 2.0
 */

#ifndef CUBEMAP_H_
#define CUBEMAP_H_

#pragma once

#include "ofMain.h"
#include "Instance_Imported.h"

namespace objects_in_scene
{

    /**
 * \class Cubemap
 * \brief Cette classe permet d'importer un fichier image
 *
 *        On peut ensuite sélectionner, déplacer et redimentionner l'image.
 *        
 */

    class Cubemap : public Instance_Imported
    {
    public: //FONCTIONS PUBLIQUES
        Cubemap();
        virtual void setup(string p_path = "", bool p_obj_du_menu = false);

        virtual void show_obj();
        virtual void set_close_true();
        virtual bool req_close_true() const;
        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);   //UTILISER POUR DOLLY et autre
        virtual bool req_image_selected() const;         //UTILISER POUR DEFINIR QUE CEST UN CUBEMAP POUR DESACTVIER SOURISE

        virtual int req_pos_z() const;                                      //SAME

        virtual const bool get_if_cubemap() const ;

    private:
        //ATTRIBUTS PRIVÉS
        
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
        int m_select_cube;
        float m_cube_scale;
        ofPoint points[8];
        ofTexture imageTexture[6];
        ofCamera cube_map_cam;
        ofLight cube_map_light;

    };

} /*namespace objects_in_scene*/

#endif /* Cubemap_H_ */