
#pragma once

#include "ofMain.h"
#include "blocs.h"

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

    private:
        //ATTRIBUTS PRIVÉS
        ofVec3f m_pos;
        ofColor m_fill_color;
        ofColor m_line_color;
        int m_line_size;
        int m_bloc_size;
        bool m_block_lock;
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
    };

} /*namespace objects_in_scene*/
