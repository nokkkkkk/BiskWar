
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

        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual void rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z);


    private:
        //ATTRIBUTS PRIVÉS
        ofxAssimpModelLoader m_objectImport;   //objet qui sera chargée.
        bool m_block_lock;





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
        int m_bloc_angle;


    };

} /*namespace objects_in_scene*/
