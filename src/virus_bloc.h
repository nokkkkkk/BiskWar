
#pragma once

#include "ofMain.h"
#include "blocs.h"
#include "ofxAssimpModelLoader.h"

    class Virus_bloc : public Blocs
    {
    public: //FONCTIONS PUBLIQUES
        Virus_bloc();
        void setup(bool p_block_depart = true);
        void show_obj();
        virtual const ofVec2f get_pos_on_grid() const;
        bool get_bloc_lock() const;
        virtual void set_bloc_lock(bool p_cond);
        virtual void move_obj(int p_x, int p_y, int p_z, int p_button);
        virtual char get_bloc_char() const;
        virtual void set_bloc_char(char p_char_type);
        virtual bool get_bloc_virus() const;
        virtual void set_bloc_virus(bool p_cond);

    private:
        //ATTRIBUTS PRIVÉS
        ofVec2f m_pos_on_grid;
        ofVec3f m_pos;
        ofxAssimpModelLoader m_virus;
        ofVec3f m_ambiant_color;
        ofColor m_fill_color;
        ofColor m_line_color;
        ofShader m_shader;
        ofTexture m_texture;
        ofLight virus_light;
        int m_speed_rotation;
        int m_line_size;
        int m_bloc_size;
        bool m_block_lock;
        bool m_block_is_virus;
        bool m_close_true;  //Detect si la destruction de l'image est effectuée.
        char m_bloc_char;
    };
