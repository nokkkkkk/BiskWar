// Classe principale de l'application.

#pragma once

#include "ofMain.h"
#include "renderer.h"
#include "cursor.h"
#include "import_img.h"
#include "import_obj.h"
#include "drawPrim.h"
#include "cubeMap.h"
#include "ofxDatGui.h"
#include "Outil_dessin.h"
#include "Instance_Imported.h"

class Application : public ofBaseApp
{
public:
  Renderer renderer;
  Cursor cursor;
  Outil_dessin outil_dessin;

  ofLight lights[4];
  ofCamera cameras[4];
  ofFbo cameraBuffers[4];	


  ofLight light_obj_menu;
  ofCamera camera_obj_menu;


    ofImage image;

  int camera_index_active;

  bool toggle_cam_mode;
  bool toggle_grab_mode;
  bool toggle_move_z;
  bool toggle_vertigo_mode;
  int count_grab_laps;
  float camera_fov;
  float camera_vertigo_count; 

  int prim_z;
  int signe_move_z;

  bool toggle_ortho;

  bool toggle_dessin_prim_rect;
  bool toggle_dessin_prim_ellipse;
  bool toggle_dessin_prim_triangle;
  bool toggle_dessin_prim_polygone;
  bool toggle_dessin_prim_line;
  bool toggle_dessin_prim_box;
  bool toggle_dessin_prim_sphere;


  bool toggle_lumiere_directionnelle;
  bool toggle_lumiere_ponctuel;
  bool toggle_lumiere_projecteur;
  bool toggle_lumiere_projecteur2;
  ofVec3f light_position_directionnelle;
  ofVec3f light_position_ponctuel;
  ofVec3f light_position_projecteur;
  ofVec3f light_position_projecteur2;
  ofColor difuse_color_direc;
  ofColor spec_color_direct;
  ofColor difuse_color_ponctuel;
  ofColor spec_color_ponctuel;
  ofColor difuse_color_projecteur;
  ofColor spec_color_projecteur;
  ofColor difuse_color_projecteur2;
  ofColor spec_color_projecteur2;



  int anchorx;
  int anchory;
  int prim_width;
  int prim_heigth;


  ofVec3f line_color;
  ofVec3f fill_color;


  int pos_z;
  int pos_z_init;

  string message_edition;
  string message_camera;

  ofTrueTypeFont font1;

  ofxDatGui *gui;
  ofxDatGui *gui_outils_dessins;
  ofxDatGui *gui_cameras;
  ofxDatGui *gui_cam1;
  ofxDatGui *gui_cam2;
  ofxDatGui *gui_cam3;
  ofxDatGui *gui_cam4;
  ofxDatGui *gui_bloc_lego;
  ofxDatGui *gui_cubemap;
  ofxDatGui *gui_shader_illum;
  ofxDatGui *gui_textures;
  ofxDatGuiSlider *rot_x;
  ofxDatGuiSlider *rot_y;
  ofxDatGuiSlider *rot_z;
  void onButtonEvent(ofxDatGuiButtonEvent e);
  void colorPickerEvent(ofxDatGuiColorPickerEvent e);
  // Outil de Dessin
  void onLineThicknessEvent(ofxDatGuiSliderEvent e);
  //void onColorEvent(ofxDatGuiButtonEvent e);// UN SEUL BUTTON EVENT

  // Import_img import_img[20];
  std::vector<objects_in_scene::Instance_Imported *> m_instance_Imported; // Déclaration d'un vecteur de pointeur pour future Polymorphisme
  objects_in_scene::Import_img *image_to_insert;                          //Déclaration d'un pointeur d'objet pour creer des nouveau objet a envoyer au PUSHBACK du vecteur
  objects_in_scene::Import_obj *obj_to_insert;                            //Déclaration d'un pointeur d'objet pour creer des nouveau objet a envoyer au PUSHBACK du vecteur
  objects_in_scene::DrawPrim *prim_to_insert;                         //Déclaration d'un pointeur d'objet pour creer des nouveau objet a envoyer au PUSHBACK du vecteur
  objects_in_scene::Cubemap *cubemap_to_insert;  

  
  std::vector<objects_in_scene::Instance_Imported *> menu_obj;   

  int index_cubemap_vector;

  string message;
  
  
  //Portails
	int startHeight;
	int portailWidth;
	int portailHeight;                          //Déclaration d'un pointeur d'objet pour creer des nouveau objet a envoyer au PUSHBACK du vecteur
  ofColor bgcolor;
  bool is_verbose;

  void setup();
  void draw();
  void update();

  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void resetSliders();
  void resetAllCam();
  void image_export(const string name, const string extension) const;
  void image_export_per_sec(const string name, const string extension);
  void drawRectangle();
  void drawEllipse();
  void drawTriangle();
  void drawPolygone();
  void drawLine();
  void drawBox();
  void drawSphere();
	void drawCamera(int cameraIndex, ofRectangle rect);
  void show_message(string new_message);

  void keyReleased(int key);
  void keyPressed(int key);

  void exit();
};
