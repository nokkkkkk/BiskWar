// IFT3100H20_BackgroundColor/application.cpp
// Classe principale de l'application.
#include <iostream>
#include "application.h"

using namespace objects_in_scene;

void Application::setup()
{
  ofSetWindowTitle("BLOC LIFE - TP1 - INFOGRAPHIE 2021");
  ofSetFrameRate(60);
  ofDisableArbTex();

  bgcolor = ofColor(0,0,0);
  message_edition = "---MODE EDITION !---\n---Naviguer dans le menu ou avec les Racourcis---\nI --> Importer une image\nJ --> Importer un modele 3d(.obj)\nT --> Changer de curseur\nG --> CAPTURE ECRAN DE LA VUE\nH --> 30 CAPTURES D'ECRAN SUR 2MIN DE LA VUE\nW --> ACTIVER LE MODE CAMERA !\n0 --> CANVAS ALeRATOIRE";
  message_camera = "---MODE CAMERA !--- Selection sur clavier(1,2,3,4)\nW --> AVANCER\nS --> RECULER\nA --> ROTATION GAUCHE\nD --> ROTATION DROITE\nQ --> GAUCHE\nE --> DROITE\nO --> ROTATION HAUT\nK --> ROTATION BAS\nC --> RESET TOUS LES CAMS\n---CLIQUEZ POUR RETOURNER EN MODE EDITION---";

  toggle_ortho = false;

  index_cubemap_vector = 9999;

  message = "";
  font1.loadFont("consolas.ttf", 13);
  

  //LES CAMeRAS ET LIGHTS
  cameras[0].setPosition(0, 0, 1000);
  cameras[0].lookAt(ofVec3f(0, 0, 0));
  cameras[1].setPosition(0, -750, 500);
  cameras[1].lookAt(ofVec3f(0, 0, 0));
  cameras[2].setPosition(0, -300, 0);
  cameras[2].lookAt(ofVec3f(0, 0, 0));
  cameras[3].setPosition(750, 0, 250);
  cameras[3].lookAt(ofVec3f(0, 0, 0));

   difuse_color_direc = ofColor(120,120,120);
   spec_color_direct = ofColor(50,50,50);
   difuse_color_ponctuel = ofColor(120,120,120);
   spec_color_ponctuel = ofColor(170,170,170);
   difuse_color_projecteur = ofColor(120,120,120);
   spec_color_projecteur = ofColor(170,170,170);
   difuse_color_projecteur2 = ofColor(120,120,120);
   spec_color_projecteur2 = ofColor(170,170,170);

  //Lumière Directionnelle
  light_position_directionnelle = ofVec3f(0, 0, -5000);
  lights[0].setDiffuseColor(difuse_color_direc);
  lights[0].setSpecularColor(spec_color_direct);
  lights[0].setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
  lights[0].setDirectional();
  lights[0].setPosition(light_position_directionnelle);
  lights[0].lookAt(ofVec3f(0,0,0));
  toggle_lumiere_directionnelle = true;

  //Lumière ponctuel
  light_position_ponctuel = ofVec3f(1000, 1000, 1000);
  lights[1].setDiffuseColor(difuse_color_ponctuel);
  lights[1].setSpecularColor(spec_color_ponctuel);
  lights[1].setPointLight();
  lights[1].setPosition(light_position_ponctuel);
  toggle_lumiere_ponctuel = true;

  //Lumière Projecteur 1

  light_position_projecteur = ofVec3f(250, 0, 3000);
  lights[2].setDiffuseColor(difuse_color_projecteur);
  lights[2].setSpecularColor(spec_color_projecteur);
  lights[2].setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
  lights[2].setSpotConcentration(2);
  lights[2].setSpotlightCutOff(30);
  lights[2].setSpotlight();
  lights[2].setPosition(light_position_projecteur);
  lights[2].lookAt(ofVec3f(0, 0, 0));
  toggle_lumiere_projecteur = true;

  //Lumière Projecteur 2

  light_position_projecteur2 = ofVec3f(0, 1000, 2000);
  lights[3].setDiffuseColor(difuse_color_projecteur2);
  lights[3].setSpecularColor(spec_color_projecteur2);
  lights[3].setOrientation(ofVec3f(0.0f, 0.0f, 0.0f));
  lights[3].setSpotConcentration(20);
  lights[3].setSpotlightCutOff(100);
  lights[3].setSpotlight();
  lights[3].setPosition(light_position_projecteur2);
  lights[3].lookAt(ofVec3f(0, 0, 0));
  toggle_lumiere_projecteur2 = true;


  //Camera pour les obj du menu
  camera_obj_menu.setPosition(0, 0, 1000);
  camera_obj_menu.lookAt(ofVec3f(0, 0, 0));
  light_obj_menu.setPosition(ofVec3f(800, 800, 1000));

  //objet du menu
  obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("bloc4X2X2red.obj", true);
  menu_obj.back()->asg_scale(0.03);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("bloc4X2X2jaune.obj", true);
  menu_obj.back()->asg_scale(0.03);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("bloc6X2X2rouge.obj", true);
  menu_obj.back()->asg_scale(0.04);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("roue2X2X2noir.obj", true);
  menu_obj.back()->asg_scale(0.025);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("bloc8X2X2jaune.obj", true);
  menu_obj.back()->asg_scale(0.05);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("bloc4X2X2croche-red.obj", true);
  menu_obj.back()->asg_scale(0.018);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("blocvitre.obj", true);
  menu_obj.back()->asg_scale(0.03);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("persodarth.obj", true);
  menu_obj.back()->asg_scale(0.03);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("plate4X4.obj", true);
  menu_obj.back()->asg_scale(0.028);

  obj_to_insert = new Import_obj;
  menu_obj.push_back(obj_to_insert);
  menu_obj.back()->setup("plate.obj", true);
  menu_obj.back()->asg_scale(0.028);




  for (int i = 0; i < 4; i++)	
      cameraBuffers[i].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
	

  camera_index_active = 0;

  camera_fov = 60;
  camera_vertigo_count = 0;

  pos_z = 0;
  pos_z_init = 0;

  toggle_cam_mode = false;

  toggle_dessin_prim_rect == false;
  toggle_dessin_prim_ellipse == false;
  toggle_dessin_prim_triangle == false;
  toggle_dessin_prim_polygone == false;
  toggle_dessin_prim_line == false;
  toggle_dessin_prim_box == false;
  toggle_dessin_prim_sphere == false;

  //Portail
	startHeight = 0;
	portailWidth =  ofGetWindowWidth() / 5.5;
	portailHeight = ofGetWindowHeight() / 5.5;

  //---Gestion du DatGui -->
 

  gui->setAssetPath("");
  gui = new ofxDatGui(0, 0);
  gui->addBreak(); //deux lignes

  gui->addButton("(I)mport image");
  gui->addButton("(J)Import 3D OBJ");
  gui->addButton("(G)rab screen");
  gui->addButton("(H)grab 30 screenshots(1 min)");
  gui->addButton("(T)switch Cursor");
  gui->addBreak();
  gui->addBreak();
  gui->addFooter();

  gui->setAutoDraw(false);

  gui->onColorPickerEvent(this, &Application::colorPickerEvent);
  gui->onButtonEvent(this, &Application::onButtonEvent); //Slider qui controle l'epaisseur de la ligne de dessin
  gui->onSliderEvent(this, &Application::onLineThicknessEvent);

  //---Gestion du DatGui --> end <--

  //---Gestion du gui_outils_dessins -->
  gui_outils_dessins->setAssetPath("");
  gui_outils_dessins = new ofxDatGui(0, 185);
  gui_outils_dessins->addBreak(); //deux lignes

  gui_outils_dessins->addColorPicker("Couleur Canvas", (255, 0, 0));
  gui_outils_dessins->addButton("Couleur remplissage aleatoire"); // Bouton donnant une couleur aleatoire au remplissage
  gui_outils_dessins->addBreak();
  gui_outils_dessins->addSlider("epaisseur ligne", 1, 50, 5); // L'evènement qui va gerer le slider
  gui_outils_dessins->addColorPicker("Couleur ligne");        // Bouton donnant une couleur aleatoire a la ligne
  gui_outils_dessins->addColorPicker("Couleur remplissage");
  gui_outils_dessins->addButton("Dessiner CARRE");
  gui_outils_dessins->addButton("Dessiner ELLIPSE");
  gui_outils_dessins->addButton("Dessiner TRIANGLE");
  gui_outils_dessins->addButton("Dessiner POLYGONE");
  gui_outils_dessins->addButton("Dessiner LINE");
  gui_outils_dessins->addButton("Dessiner CUBE");
  gui_outils_dessins->addButton("Dessiner SPHERE");
  gui_outils_dessins->addButton("switch FILTRE");
  gui_outils_dessins->addBreak();
  rot_x = gui_outils_dessins->addSlider("Rotation_x", 0, 360, 5); // L'evènement qui va gerer le slider
  gui_outils_dessins->addButton("De/Activer Rotation Auto (X)");
  rot_y = gui_outils_dessins->addSlider("Rotation_y", 0, 360, 5); // L'evènement qui va gerer le slider
  gui_outils_dessins->addButton("De/Activer Rotation Auto (Y)");
  rot_z = gui_outils_dessins->addSlider("Rotation_z", 0, 360, 5); // L'evènement qui va gerer le slider
  gui_outils_dessins->addButton("De/Activer Rotation Auto (Z)");
  gui_outils_dessins->addSlider("Vitesse de rotation", 0, 5, 0.01);
  gui_outils_dessins->addFooter();

  gui_outils_dessins->setAutoDraw(false);

  gui_outils_dessins->onColorPickerEvent(this, &Application::colorPickerEvent);
  gui_outils_dessins->onButtonEvent(this, &Application::onButtonEvent); //Slider qui controle l'epaisseur de la ligne de dessin
  gui_outils_dessins->onSliderEvent(this, &Application::onLineThicknessEvent);

  gui_cameras->setAssetPath("");
  gui_cameras = new ofxDatGui(0, 800);
  gui_cam1->setAssetPath("");
  gui_cam1 = new ofxDatGui(320, 0);
  gui_cam2->setAssetPath("");
  gui_cam2 = new ofxDatGui(320 + portailWidth + 2, 0);
  gui_cam3->setAssetPath("");
  gui_cam3 = new ofxDatGui(320 + portailWidth * 2 + 4, 0);
  gui_cam4->setAssetPath("");
  gui_cam4 = new ofxDatGui(320 + portailWidth * 3 + 6, 0);

  gui_cameras->addBreak();
  gui_cameras->addButton("MODE CAMERA");
  gui_cameras->addButton("MODE EDITION");
  gui_cameras->addButton("MODE ORTHOGONAL ON/OFF");
  gui_cam1->addButton("CAM1");
  gui_cam1->addButton("CAM1");
  gui_cam1->addButton("CAM1");
  gui_cam1->addButton("CAM1");
  gui_cam1->addButton("CAM1");
  gui_cam1->addButton("CAM1");
  gui_cam1->addButton("CAM1");
  gui_cam2->addButton("CAM2");
  gui_cam2->addButton("CAM2");
  gui_cam2->addButton("CAM2");
  gui_cam2->addButton("CAM2");
  gui_cam2->addButton("CAM2");
  gui_cam2->addButton("CAM2");
  gui_cam2->addButton("CAM2");
  gui_cam3->addButton("CAM3");
  gui_cam3->addButton("CAM3");
  gui_cam3->addButton("CAM3");
  gui_cam3->addButton("CAM3");
  gui_cam3->addButton("CAM3");
  gui_cam3->addButton("CAM3");
  gui_cam3->addButton("CAM3");
  gui_cam4->addButton("CAM4");
  gui_cam4->addButton("CAM4");
  gui_cam4->addButton("CAM4");
  gui_cam4->addButton("CAM4");
  gui_cam4->addButton("CAM4");
  gui_cam4->addButton("CAM4");
  gui_cam4->addButton("CAM4");
  gui_cameras->addButton("RESET ALL CAM");
  gui_cameras->addFooter();
  gui_cameras->setAutoDraw(false);
  gui_cam1->setAutoDraw(false);
  gui_cam2->setAutoDraw(false);
  gui_cam3->setAutoDraw(false);
  gui_cam4->setAutoDraw(false);


  gui_cameras->onButtonEvent(this, &Application::onButtonEvent);
  gui_cam1->onButtonEvent(this, &Application::onButtonEvent);
  gui_cam2->onButtonEvent(this, &Application::onButtonEvent);
  gui_cam3->onButtonEvent(this, &Application::onButtonEvent);
  gui_cam4->onButtonEvent(this, &Application::onButtonEvent);



  gui_bloc_lego->setAssetPath("");
  gui_bloc_lego = new ofxDatGui(ofGetWidth() - 200, 0);

  gui_bloc_lego->addBreak();
  gui_bloc_lego->addButton("Bloc 4 X 2 X 2 - Rouge");
  gui_bloc_lego->addButton("Bloc 4 X 2 X 2 - Jaune");
  gui_bloc_lego->addButton("Bloc 6 X 2 X 2 - Bourgogne");
  gui_bloc_lego->addButton("Roue 2 X 2 X 2- Noir");
  gui_bloc_lego->addButton("Bloc 8 X 2 X 2- Jaune");
  gui_bloc_lego->addButton("Bloc 4 X 4 X 2 - Oblique");
  gui_bloc_lego->addButton("Bloc vitre");
  gui_bloc_lego->addButton("Persone Darth");
  gui_bloc_lego->addButton("Plate 4 X 4");
  gui_bloc_lego->addButton("Plateau");
  gui_bloc_lego->addFooter();
  gui_bloc_lego->setAutoDraw(false);

  gui_bloc_lego->onButtonEvent(this, &Application::onButtonEvent);

  gui_cubemap->setAssetPath("");
  gui_cubemap = new ofxDatGui(ofGetWidth() - 200, 300);

  gui_cubemap->addBreak();
  gui_cubemap->addButton("Nebula");
  gui_cubemap->addButton("Mystere");
  gui_cubemap->addButton("Beach");
  gui_cubemap->addButton("Plaine");
  gui_cubemap->addButton("Smooth");
  gui_cubemap->setAutoDraw(false);

  gui_cubemap->onButtonEvent(this, &Application::onButtonEvent);


  gui_shader_illum->setAssetPath("");
  gui_shader_illum = new ofxDatGui(ofGetWidth() - 200, 450);

  gui_shader_illum->addBreak();
  gui_shader_illum->addButton("Materiel de base On/Off");
  gui_shader_illum->addButton("Aucun Shader illum");
  gui_shader_illum->addButton("shader Ambiance");
  gui_shader_illum->addButton("lambert");
  gui_shader_illum->addButton("gouraud");
  gui_shader_illum->addButton("phong");
  gui_shader_illum->addButton("blinn-phong");
  gui_shader_illum->addButton("Normal Mapping with Phong");
  gui_shader_illum->setAutoDraw(false);

  gui_shader_illum->onButtonEvent(this, &Application::onButtonEvent);

  gui_textures->setAssetPath("");
  gui_textures = new ofxDatGui(ofGetWidth() - 200, 670);

  gui_textures->addBreak();
  gui_textures->addButton("Textures Bloc-Life");
  gui_textures->addButton("Bois");
  gui_textures->addButton("brique");
  gui_textures->addButton("cailloux");
  gui_textures->addButton("gazon");
  gui_textures->addButton("marble");
  gui_textures->addButton("metal");
  gui_textures->addButton("peinture");
  gui_textures->addButton("planche");
  gui_textures->addButton("terre");
  gui_textures->addButton("textil");
  gui_textures->setAutoDraw(false);

  gui_textures->onButtonEvent(this, &Application::onButtonEvent);



  //---Gestion du DatGui --> end <--

  renderer.setup();
  show_message(message_edition);
  // tp1Ui.setup();
  toggle_grab_mode = false;
  count_grab_laps = 0;

  cursor.setup();

  is_verbose = false;
}

void Application::draw()
{

  //---Gestion du DatGui -->
  gui->update();
  //---Gestion du DatGui --> end <--

  //---Gestion du gui_outils_dessins -->
  gui_outils_dessins->update();
  //---Gestion du gui_outils_dessins --> end <--
  gui_cameras->update();
  gui_bloc_lego->update();
  gui_cubemap->update();
  gui_shader_illum->update();
  gui_textures->update();
  gui_cam1->update();
  gui_cam2->update();
  gui_cam3->update();
  gui_cam4->update();



  renderer.draw();


	portailWidth =  ofGetWindowWidth() / 5.5;
	portailHeight = ofGetWindowHeight() / 5.5;

  ofDisableAlphaBlending();
  ofEnableDepthTest();
  ofEnableSmoothing();
  ofEnableAntiAliasing();

    if(toggle_lumiere_directionnelle)
    {
      lights[0].setPosition(light_position_directionnelle);
      lights[0].setDiffuseColor(difuse_color_direc);
      lights[0].setSpecularColor(spec_color_direct);
      lights[0].enable();
    }
    if(toggle_lumiere_ponctuel)
    {
      lights[1].setPosition(light_position_ponctuel);
      lights[1].setDiffuseColor(difuse_color_ponctuel);
      lights[1].setSpecularColor(spec_color_ponctuel);
      lights[1].enable();
    }
    if(toggle_lumiere_projecteur)
    {
      lights[2].setPosition(light_position_projecteur);
      lights[2].setDiffuseColor(difuse_color_projecteur);
      lights[2].setSpecularColor(spec_color_projecteur);
      lights[2].enable();
    }
    if(toggle_lumiere_projecteur2)
    {
      lights[3].setPosition(light_position_projecteur2);
      lights[3].setDiffuseColor(difuse_color_projecteur2);
      lights[3].setSpecularColor(spec_color_projecteur2);
      lights[3].enable();
    }

  //Buffering des 4 portails
  for (int j = 0; j < 4; j++)
	{
		cameraBuffers[j].begin();
			ofBackground(bgcolor);
			ofNoFill();
          for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
          {

            cameras[j].begin();
            ofPushMatrix();
              ofTranslate(-ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0);
              ofScale(1, -1, 1);
          //  materiel_lego[choi_materiau].begin();
              m_instance_Imported[i]->show_obj();
          //  materiel_lego[choi_materiau].end();
            ofPopMatrix();
            cameras[j].end();
          }
			cameraBuffers[j].end();
	}

  if (toggle_dessin_prim_rect && anchorx > 250)
  {
    drawRectangle();
  }
  if (toggle_dessin_prim_ellipse && anchorx > 250)
  {
    drawEllipse();
  }
  if (toggle_dessin_prim_triangle && anchorx > 250)
  {
    drawTriangle();
  }
  if (toggle_dessin_prim_polygone && anchorx > 250)
  {
    drawPolygone();
  }
  if (toggle_dessin_prim_line && anchorx > 250)
  {
    drawLine();
  }
  if (toggle_dessin_prim_box && anchorx > 250)
  {
    drawBox();
  }
  if (toggle_dessin_prim_sphere && anchorx > 250)
  {
    drawSphere();
  }

  if (toggle_ortho == true)
  {
    cameras[camera_index_active].enableOrtho();
  }
  if (!toggle_cam_mode)
  {
    // ---m_instance_Imported --> parcour du vector d'images afin de l'afficher et d'afficher la zone de selection autour. en mode ORTHO<--
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      // materiel_lego[choi_materiau].begin();
      m_instance_Imported[i]->show_obj();
      // materiel_lego[choi_materiau].end();
      if (m_instance_Imported[i]->req_close_true() == 1)
      { //Si on doit ferme l'image on lenleve du vector
        m_instance_Imported.erase(m_instance_Imported.begin() + i);
      }
    }
  }
  if (toggle_cam_mode)
  {
    //---m_instance_Imported --> parcour du vector d'images afin de l'afficher et d'afficher la zone de selection autour.<--
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      cameras[camera_index_active].begin();
      // materiel_lego[choi_materiau].begin();
      ofPushMatrix();
        ofTranslate(-ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0);
        ofScale(1, -1, 1);
        m_instance_Imported[i]->show_obj();
      ofPopMatrix();
      cameras[camera_index_active].end();
      // materiel_lego[choi_materiau].end();
      if (m_instance_Imported[i]->req_close_true() == 1)
      { //Si on doit ferme l'image on lenleve du vector
        m_instance_Imported.erase(m_instance_Imported.begin() + i);
      }
    }
  }
  




  ofEnableAlphaBlending();
  ofDisableDepthTest();
  ofDisableSmoothing();
  ofDisableAntiAliasing();
  //---m_instance_Imported --> end <--

  if (toggle_grab_mode)
  {
    image_export_per_sec("SceneGrabPer2sec", "jpg");

    ofLog() << "<Grab Screen per 2 sec for 60 sec = 30 images>";
  }

  //---Gestion du DatGui -->
  gui->draw();
  //---Gestion du DatGui --> end <--

  //---Gestion du gui_outils_dessins -->
  gui_outils_dessins->draw();
  //---Gestion du gui_outils_dessins --> end <--
  gui_cameras->draw();
  gui_bloc_lego->draw();
  gui_cubemap->draw();
  gui_shader_illum->draw();
  gui_textures->draw();
  gui_cam1->draw();
  gui_cam2->draw();
  gui_cam3->draw();
  gui_cam4->draw();

  //Affichage des obj du menu

  ofEnableDepthTest();
  ofEnableSmoothing();
  ofEnableAntiAliasing();
  light_obj_menu.enable();
  camera_obj_menu.begin();

  camera_obj_menu.enableOrtho();
  font1.drawString(message, 400, -280);
   for (unsigned int i = 0; i < menu_obj.size(); i++)
    {
      menu_obj[i]->show_obj();
      menu_obj[i]->asg_position(ofGetWidth() / 2 + 75, 550 - i * 30, 0);
      menu_obj[i]->asg_toggle_rotation_x();
      menu_obj[i]->asg_toggle_rotation_y();
      menu_obj[i]->asg_toggle_rotation_z();
      
    }
  menu_obj[3]->asg_position(ofGetWidth() / 2 + 95, 550 - 100, 0); //correction
  menu_obj[5]->asg_position(ofGetWidth() / 2 + 95, 550 - 155, 0); //correction
  menu_obj[8]->asg_position(ofGetWidth() / 2 + 75, 550 - 250, 0); //correction
  menu_obj[9]->asg_position(ofGetWidth() / 2 + 75, 550 - 280, 0); //correction

  camera_obj_menu.disableOrtho();
  camera_obj_menu.end();
  light_obj_menu.disable();

  //Portail
	ofRectangle rectCam1 = ofRectangle(300, startHeight, portailWidth, portailHeight);
	ofRectangle rectCam2 = ofRectangle(300 + portailWidth + 2, startHeight, portailWidth, portailHeight);
	ofRectangle rectCam3 = ofRectangle(300 + portailWidth * 2 + 4, startHeight, portailWidth, portailHeight);
	ofRectangle rectCam4 = ofRectangle(300 + portailWidth * 3 + 6, startHeight, portailWidth, portailHeight);


	drawCamera(0, rectCam1);
	drawCamera(1, rectCam2);
	drawCamera(2, rectCam3);
	drawCamera(3, rectCam4);


    if(toggle_lumiere_directionnelle)
    {
      lights[0].disable();
    }
    if(toggle_lumiere_ponctuel)
    {
    lights[1].disable();
    }
    if(toggle_lumiere_projecteur)
    {
    lights[2].disable();
    }
    if(toggle_lumiere_projecteur2)
    {
    lights[3].disable();
    }

  ofDisableDepthTest();
  ofDisableSmoothing();
  ofDisableAntiAliasing();

  cursor.draw(); //Doit-être à la fin pour avoir le cursor au dessus des items.
}
void Application::update()
{
  if (toggle_vertigo_mode)
  {
    camera_vertigo_count = camera_vertigo_count + 1;
    if (camera_vertigo_count < 400)
    {
      cameras[camera_index_active].rollDeg(-0.1);
      cameras[camera_index_active].setFov(camera_fov += 0.3);
      cameras[camera_index_active].dolly(-4);
    }
    else
    {
      camera_vertigo_count = 0;
      camera_fov = 60;
      cameras[camera_index_active].setFov(camera_fov);
      cameras[camera_index_active].dolly(1600);
    }
  }
  gui->update();
  gui_outils_dessins->update();
  gui_cameras->update();
  gui_bloc_lego->update();
  gui_cubemap->update();
  gui_shader_illum->update();
  gui_textures->update();
  gui_cam1->update();
  gui_cam2->update();
  gui_cam3->update();
  gui_cam4->update();
}
void Application::keyPressed(int key)
{

  switch (key)
  {
  case 109: // touche m
    toggle_move_z = true;
    show_message("DÉPLACEMENT EN AXE Z ACTIF");
    break;
  case 101: // touche q
    if (cameras[camera_index_active].getPosition().z < 4500 && 
        cameras[camera_index_active].getPosition().z > -4500 && 
        cameras[camera_index_active].getPosition().x < 4500 && 
        cameras[camera_index_active].getPosition().x > -4500 && 
        cameras[camera_index_active].getPosition().y < 4500 && 
        cameras[camera_index_active].getPosition().y > -4500)
    {
      cameras[camera_index_active].truck(20);
      if (index_cubemap_vector != 9999){
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,0,20);
      }
    }
    else
    {
      cameras[camera_index_active].truck(-200);
      if (index_cubemap_vector != 9999){
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,0,-200);
      }
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;

  case 113: // touche e
    if (cameras[camera_index_active].getPosition().z < 4500 && 
        cameras[camera_index_active].getPosition().z > -4500 && 
        cameras[camera_index_active].getPosition().x < 4500 && 
        cameras[camera_index_active].getPosition().x > -4500 && 
        cameras[camera_index_active].getPosition().y < 4500 && 
        cameras[camera_index_active].getPosition().y > -4500)
    {
      cameras[camera_index_active].truck(-20);
      if (index_cubemap_vector != 9999){
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,0,-20);
      }
    }
    else
    {
      cameras[camera_index_active].truck(200);
      if (index_cubemap_vector != 9999){
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,0,200);
      }
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;

  case 115: // touche s
    toggle_cam_mode = true;
    if (cameras[camera_index_active].getPosition().z < 4500 && 
        cameras[camera_index_active].getPosition().z > -4500 && 
        cameras[camera_index_active].getPosition().x < 4500 && 
        cameras[camera_index_active].getPosition().x > -4500 && 
        cameras[camera_index_active].getPosition().y < 4500 && 
        cameras[camera_index_active].getPosition().y > -4500)
    {
      cameras[camera_index_active].dolly(20);
      if (index_cubemap_vector != 9999){
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,20,0);
      }
    }
    else
    {
      cameras[camera_index_active].dolly(-200);
      if (index_cubemap_vector != 9999){
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,-200,0);
      }
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;

  case 119: // touche w
    toggle_cam_mode = true;
    if (cameras[camera_index_active].getPosition().z < 4500 && 
        cameras[camera_index_active].getPosition().z > -4500 && 
        cameras[camera_index_active].getPosition().x < 4500 && 
        cameras[camera_index_active].getPosition().x > -4500 && 
        cameras[camera_index_active].getPosition().y < 4500 && 
        cameras[camera_index_active].getPosition().y > -4500)
    {
      cameras[camera_index_active].dolly(-20);
      if (index_cubemap_vector != 9999) //Si un cubemap existe.
      {
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,-20,0);
      }
    }
    else
    {
       cameras[camera_index_active].dolly(200);
      if (index_cubemap_vector != 9999) //Si un cubemap existe.
      {
        m_instance_Imported[index_cubemap_vector]->move_obj(0,0,200,0);
      }
    }

     
    
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));
    break;

  case 45: // touche -
    if(toggle_lumiere_directionnelle)
    {
      
      light_position_directionnelle.z -= 100;
    }
    if(toggle_lumiere_ponctuel)
    {
      light_position_ponctuel.z -= 100;
    }
    if(toggle_lumiere_projecteur)
    {
      
      light_position_projecteur.z -= 100;
    }
    if(toggle_lumiere_projecteur2)
    {
      
      light_position_projecteur2.z -= 100;
    }
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_pos_dynamic_light(ofVec3f(0,0,100));
        }
      }
    show_message("Déplacement des lumières scene ET Dynamique   active vers l'arriere !");
    break;

  case 43: // touche +
    if(toggle_lumiere_directionnelle)
    {
      light_position_directionnelle.z += 100;
    }
    if(toggle_lumiere_ponctuel)
    {
      light_position_ponctuel.z += 100;
    }
    if(toggle_lumiere_projecteur)
    {
      
      light_position_projecteur.z += 100;
    }
    if(toggle_lumiere_projecteur2)
    {
      
      light_position_projecteur2.z += 100;
    }
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_pos_dynamic_light(ofVec3f(0,0,-100));
        }
      }
    show_message("Déplacement des lumières scene ET Dynamique   active vers l'avant !");

    break;

    case ofKey::OF_KEY_RIGHT:

    if(toggle_lumiere_directionnelle)
    {
      
      light_position_directionnelle.x += 100;
    }
    if(toggle_lumiere_ponctuel)
    {
      light_position_ponctuel.x += 100;
    }
    if(toggle_lumiere_projecteur)
    {
      
      light_position_projecteur.x += 100;
    }
    if(toggle_lumiere_projecteur2)
    {
      
      light_position_projecteur2.x += 100;
    } 
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_pos_dynamic_light(ofVec3f(100,0,0));
        }
      }
      
    show_message("Déplacement des lumières de scene ET Dynamique  active vers la droite");
    break;


    case ofKey::OF_KEY_LEFT:

    if(toggle_lumiere_directionnelle)
    {
      
      light_position_directionnelle.x -= 100;
    }
    if(toggle_lumiere_ponctuel)
    {
      light_position_ponctuel.x -= 100;
    }
    if(toggle_lumiere_projecteur)
    {
      
      light_position_projecteur.x -= 100;
    }
    if(toggle_lumiere_projecteur2)
    {
      
      light_position_projecteur2.x -= 100;
    }
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_pos_dynamic_light(ofVec3f(-100,0,0));
        }
      }
      
    show_message("Déplacement des lumières de scene ET Dynamique  active vers la gauche");
    break;

    case ofKey::OF_KEY_UP:

    if(toggle_lumiere_directionnelle)
    {
      
      light_position_directionnelle.y -= 100;
    }
    if(toggle_lumiere_ponctuel)
    {
      light_position_ponctuel.y -= 100;
    }
    if(toggle_lumiere_projecteur)
    {
      
      light_position_projecteur.y -= 100;
    }
    if(toggle_lumiere_projecteur2)
    {
      
      light_position_projecteur2.y -= 100;
    }
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_pos_dynamic_light(ofVec3f(0,-100,0));
        }
      }


      
    show_message("Déplacement des lumières de scene ET Dynamique  active vers le haut");
    break;

    case ofKey::OF_KEY_DOWN:

    if(toggle_lumiere_directionnelle)
    {
      
      light_position_directionnelle.y = +100;
    }
    if(toggle_lumiere_ponctuel)
    {
      light_position_ponctuel.y += 100;
    }
    if(toggle_lumiere_projecteur)
    {
      
      light_position_projecteur.y += 100;
    }
    if(toggle_lumiere_projecteur2)
    {
      
      light_position_projecteur2.y += 100;
    }
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_pos_dynamic_light(ofVec3f(0,100,0));
        }
      }
      
    show_message("Déplacement des lumières de scene ET Dynamique active vers le bas");
    break;


    case ofKey::OF_KEY_CONTROL:

    if(toggle_lumiere_directionnelle)
    {
      difuse_color_direc = ofColor(line_color.x, line_color.y, line_color.z);
      spec_color_direct = ofColor(fill_color.x, fill_color.y, fill_color.z);
    }
    if(toggle_lumiere_ponctuel)
    {
      difuse_color_ponctuel = ofColor(line_color.x, line_color.y, line_color.z);
      spec_color_ponctuel = ofColor(fill_color.x, fill_color.y, fill_color.z);
    }
    if(toggle_lumiere_projecteur)
    {
      difuse_color_projecteur = ofColor(line_color.x, line_color.y, line_color.z);
      spec_color_projecteur = ofColor(fill_color.x, fill_color.y, fill_color.z);
    }
    if(toggle_lumiere_projecteur2)
    {
      difuse_color_projecteur2 = ofColor(line_color.x, line_color.y, line_color.z);
      spec_color_projecteur2 = ofColor(fill_color.x, fill_color.y, fill_color.z);
    }
    
      
    show_message("Couleurs du selecteur appliqués au Lumière active");
    break;


    case ofKey::OF_KEY_F5:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_choix_material(0);
        }
      }
      show_message("Vous avez choisi le MATERIAU ULTRA SHINY !");
    break;
    case ofKey::OF_KEY_F6:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_choix_material(1);
        }
      }
      show_message("Vous avez choisi le MATERIAU PORRRRREU !");
    break;
    case ofKey::OF_KEY_F7:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_choix_material(2);
        }
      }
      show_message("Vous avez choisi le MATERIAU METALIQUE !");
    break;
    case ofKey::OF_KEY_F8:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_choix_material(3);
        }
      }
      show_message("Vous avez choisi le MATERIAU CAOUTHCOU !");
    break;




    case ofKey::OF_KEY_F9:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_nb_dynamic_light(1);
        }
      }
      show_message("Vous avez choisi 1 seule lumière Dynamique");
    break;

    case ofKey::OF_KEY_F10:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_nb_dynamic_light(2);
        }
      }
      show_message("Vous avez choisi 2 lumières Dynamiques");
    break;

    case ofKey::OF_KEY_F11:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_nb_dynamic_light(3);
        }
      }
      show_message("Vous avez choisi 3 lumières Dynamiques");
    break;

    case ofKey::OF_KEY_F12:
      for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
      {
        if (m_instance_Imported[i]->req_image_selected() == true)
        {
          m_instance_Imported[i]->set_nb_dynamic_light(4);
        }
      }
      show_message("Vous avez choisi 4 lumières Dynamiques");
    break;





  case 111: // touche o
    cameras[camera_index_active].tiltDeg(2);
    if (index_cubemap_vector != 9999){
      m_instance_Imported[index_cubemap_vector]->move_obj(0,-2,0,0);
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;

  case 107: // touche k
    cameras[camera_index_active].tiltDeg(-2);
    if (index_cubemap_vector != 9999){
      m_instance_Imported[index_cubemap_vector]->move_obj(0,2,0,0);
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;

  case 97: // touche a
    cameras[camera_index_active].panDeg(3);
    if (index_cubemap_vector != 9999){
    m_instance_Imported[index_cubemap_vector]->move_obj(3,0,0,0);
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;

  case 100: // touche d
    cameras[camera_index_active].panDeg(-3);
    if (index_cubemap_vector != 9999){
      m_instance_Imported[index_cubemap_vector]->move_obj(-3,0,0,0);
    }
    show_message(message_camera + "\nCAMERA ACTIVE : " + to_string(camera_index_active + 1) + "\n - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z));

    break;


  
  default:
    break;
  }
}
void Application::keyReleased(int key)
{
  string message_tmp;
  switch (key)
  {
  case ofKey::OF_KEY_RETURN:
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
      {
        m_instance_Imported[i]->asg_toggle_lego_lock(true);
      }
    }
    show_message("Toggle LEGO Lock engagé");
    break;
  case ofKey::OF_KEY_RIGHT_SHIFT:
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
      {
        m_instance_Imported[i]->asg_toggle_lego_lock(false);
      }
    }
    show_message("Toggle LEGO Lock engagé");
    break;
  case 'f': // touche f
    ofToggleFullscreen();
    show_message("Toggle FullScreen");
    break;
  case 109: // touche m
    toggle_move_z = false;
    show_message(message_edition);
    break;
  case 48: // touche 0
    renderer.clear_mode = ClearMode::random;
    show_message("CANVAS ALEATOIRE - Vous pouvez aussi utiliser le selecteur de couleur dans le menu a gauche.");
    break;
  case 49: // touche 1
    camera_index_active = 0;
    message_tmp = "-CAMERA " + to_string(camera_index_active + 1) + " - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z);
    show_message(message_tmp);
    break;

  case 50: // touche 2
    camera_index_active = 1;
    message_tmp = "-CAMERA " + to_string(camera_index_active + 1) + " - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z);
    show_message(message_tmp);
    break;

  case 51: // touche 3
    camera_index_active = 2;
    message_tmp = "-CAMERA " + to_string(camera_index_active + 1) + " - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z);
    show_message(message_tmp);
    break;

  case 52: // touche 4
    camera_index_active = 3;
    message_tmp = "-CAMERA " + to_string(camera_index_active + 1) + " - 'W''S''Q''E' ++ Continuez la navigation :) !" + "\n Position de la Camera --> x : " + to_string(cameras[camera_index_active].getPosition().x) + " y : " + to_string(cameras[camera_index_active].getPosition().y) + " z : " + to_string(cameras[camera_index_active].getPosition().z);
    show_message(message_tmp);
    break;

  case 99: // touche c
    resetAllCam();
    show_message("RESET DE TOUS LES CAMERAS EFFECTUE !");
    break;

  case 103: // touche g
    image_export("SceneGrab", "jpg");
    show_message("Vous avez exporte une vue de votre projet en format JPG.");
    break;

  case 104: // touche h
    toggle_grab_mode = true;
    show_message("echantillonage de 30 images de la vue sur 1 minutes\n1 images / 2 secondes pour les 2 prochaines minutes.\nVous pouvez continuer à editer ou vous deplacer avec la camera(W) pendant l'operation.");
    break;

  case 105:                           // touche i
                                      //---m_instance_Imported --> Si la touche "i" est appuyee, push_back l'objet à ajouter dans le vector et imb_import.setup() pour parametrer<--
    image_to_insert = new Import_img; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(image_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup();
    show_message("Si votre fichier IMAGE est valide, vous pouvez manipuler votre image!\nUtiliser le 'X' et '/' sur le modele pour fermer ou redimensionner\nVous pouvez déplacer votre image en -Draging-.\nLes outils de dession sont utilisables pour les rotation entre-autre.\n AMUSEZ-VOUS!");
    //---m_instance_Imported --> end <--
    break;

  case 106:                         // touche j
                                    //---m_instance_Imported --> Si la touche "i" est appuyee, push_back l'objet à ajouter dans le vector et imb_import.setup() pour parametrer<--
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup();
    show_message("Si votre fichier OBJ est valide, vous pouvez manipuler votre Objet 3D! \nUtiliser le 'X' et '/' sur le modele pour fermer ou redimensionner\nVous pouvez déplacer votre image en -Draging-.\nLes outils de dession sont utilisables pour les rotation entre-autre.\n AMUSEZ-VOUS!");
    //---m_instance_Imported --> end <--
    break;

  case 116: // touche t
            //SI l'index m'Est pas le dernier... On  incremente sinon on revient a 0
    if (cursor.indexCursor < 9)
      cursor.indexCursor = cursor.indexCursor + 1;
    else
      cursor.indexCursor = 0;
    show_message("Curseur Mis à jour. ");
    break;

  case 117: // touche u
    if (toggle_ortho == true)
    {
      toggle_ortho = false;

      cameras[camera_index_active].disableOrtho();
      cameras[camera_index_active].setupPerspective(false, 60.0f, 50.0f, 1750.0f, ofVec2f(0, 0));
      resetAllCam();
    }
    else
    {
      toggle_ortho = true;
    }
    show_message("Mode Orthogonal (De)Active");
    break;
  case 118: // touche v
    if (toggle_vertigo_mode)
    {
      resetAllCam();
      toggle_vertigo_mode = false;
      toggle_cam_mode = false;
      show_message("Mode Vertigo STOP !");
    }
    else
    {
      toggle_vertigo_mode = true;
      toggle_cam_mode = true;
      show_message("Mode Vertigo START !");
    }
      

    break;

  case 120: // touche x
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_toggle_rotation_x();
    }
    show_message("Rotation X (De)Active");
    break;
  case 121: // touche y

    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_toggle_rotation_y();
    }
    show_message("Rotation Y (De)Active");
    break;
  case 122: // touche z

    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_toggle_rotation_z();
    }
    show_message("Rotation Z (De)Active");
    break;

  case 108: // touche l
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
        m_instance_Imported[i]->asg_toggle_mode_lego(true);
        show_message("MODE LEGO ! Active");
    }
    break;

  case 112: // touche l
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
        m_instance_Imported[i]->asg_toggle_mode_lego(false);
        show_message("MODE LEGO ! Deactive");
    }
    break;


  case ofKey::OF_KEY_F1: // touche f1
  {
    toggle_lumiere_directionnelle = !toggle_lumiere_directionnelle;
    show_message("Lumière Directionnelle ON/OFF");
  }
    break;

  case ofKey::OF_KEY_F2: // touche f2
  {
    toggle_lumiere_ponctuel = !toggle_lumiere_ponctuel;
    show_message("Lumière spotlight ON/OFF");
  }
    break;

  case ofKey::OF_KEY_F3: // touche f3
  {
    toggle_lumiere_projecteur = !toggle_lumiere_projecteur;
    show_message("Lumière projecteur 1 ON/OFF");
  }
    break;

  case ofKey::OF_KEY_F4: // touche f4
  {
    toggle_lumiere_projecteur2 = !toggle_lumiere_projecteur2;
    show_message("Lumière projecteur 2 ON/OFF");
  }
    break;


    break;


  default: // et autre
    // renderer.clear_mode = ClearMode::random;
    // ofLog() << "<mode: random>";
    break;
  }
  renderer.has_changed = true;
}

// fonction appelee quand la position du curseur change
void Application::mouseMoved(int x, int y)
{
  if (toggle_cam_mode)
  {
    if(cursor.mouse_current_x > x )
    {
      // cameras[camera_index_active].panDeg(2);
    if (index_cubemap_vector != 9999){
      // m_instance_Imported[index_cubemap_vector]->move_obj(2,0,0,0);
    }
    }
    if(cursor.mouse_current_x < x )
    {
      // cameras[camera_index_active].panDeg(-2);
    if (index_cubemap_vector != 9999){
      // m_instance_Imported[index_cubemap_vector]->move_obj(-2,0,0,0);
    }

    }
    // if(cursor.mouse_current_y > y )
    //   cameras[camera_index_active].tiltDeg(2);
    // if(cursor.mouse_current_y < y )
    //   cameras[camera_index_active].tiltDeg(-2);
  }

  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

}

void Application::exit()
{
}

// fonction appelee quand la position du curseur change pendant qu'un bouton d'un peripherique de pointage est appuye
void Application::mouseDragged(int x, int y, int button)
{
  
  prim_heigth = y - anchory;
  prim_width = x - anchorx;

  //---m_instance_Imported --> afin de ne pas perde l'image en drag si on deplace l'image rapidement, on creer un bool qui sais si l'image à ete clique dans sa zone.
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
    if (m_instance_Imported[i]->get_if_cubemap() == false)
    {
      
    prim_z = m_instance_Imported[i]->req_pos_z();
    //Si lancien y est plus grand que le nouveau, on augmente ou diminue le z
    if (cursor.mouse_current_y > y) // On bouge de signe_move_z quand m est enfoncer
    {
      signe_move_z = -4;
    }
    else{
      signe_move_z = 4;
    }

    if (toggle_move_z)
    {
        // pos_z = pos_z_init + prim_heigth / 2;
        m_instance_Imported[i]->move_obj(x - prim_width, y - prim_heigth, prim_z + signe_move_z, button);
    }
    else  //Petit bug - Quand on déplace et ensuite on appuie sur M sur le meme clic, on voit appraitre le model au centre momentanément
    {
      m_instance_Imported[i]->move_obj(x, y, m_instance_Imported[i]->req_pos_z(), button);
    }
    m_instance_Imported[i]->redim_obj(x, y, button);
  }
  //---m_instance_Imported --> end <--

    }

  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

}

// fonction appelee quand un bouton d'un peripherique de pointage est appuye
void Application::mousePressed(int x, int y, int button)
{
  anchorx = x;
  anchory = y;
  // resetAllCam();

  cursor.is_mouse_button_pressed = true;

  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

  cursor.mouse_press_x = x;
  cursor.mouse_press_y = y;

  // if (toggle_ortho == true)
  // {
  //   toggle_ortho = false;
  // }

  //Condition qui verifie la zone cliquee = SWITCH BOUTON pour celle ci.
  // if (x > 462 && y > 300 && x < 561 && y < 338)
  // {
  //   //Sinon l'index m'Est pas le dernier... On  incremente sinon on revient a 0
  //   if (cursor.indexCursor < 9)
  //     cursor.indexCursor = cursor.indexCursor + 1;
  //   else
  //     cursor.indexCursor = 0;
  // }

  //---m_instance_Imported --> On parcour le vecteur pour gerer tous les evenements mousePressed sur chaques image importees dans le vecteur<--
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
    ofLog() << startHeight + portailWidth;
    if (x > 270 && y > startHeight + portailWidth -200 && x < ofGetWidth() - 200)
    { //permet de protege la zone du gui contre les les clics de selections.

      show_message(message_edition);
      toggle_cam_mode = false;
      m_instance_Imported[i]->select_obj(x, y, button);
      if (m_instance_Imported[i]->req_close_true() == 1)
      { //Si la zone de destruction de l'objet dans le vesteur est cliquee, on le supprime du vector.
        m_instance_Imported.erase(m_instance_Imported.begin() + i);
      }
    }
  }
  //---m_instance_Imported --> end <--

}

// fonction appelee quand un bouton d'un peripherique de pointage est relâche
void Application::mouseReleased(int x, int y, int button)
{
  if (x > 250)
  {
    if (toggle_dessin_prim_rect)
    {
      prim_to_insert = new DrawPrim(0, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_rect = false;
    }
    if (toggle_dessin_prim_ellipse)
    {
      prim_to_insert = new DrawPrim(1, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_ellipse = false;
    }
    if (toggle_dessin_prim_triangle)
    {
      prim_to_insert = new DrawPrim(2, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_triangle = false;
    }
    if (toggle_dessin_prim_polygone)
    {
      prim_to_insert = new DrawPrim(3, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_polygone = false;
    }
    if (toggle_dessin_prim_line)
    {
      prim_to_insert = new DrawPrim(4, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_line = false;
    }
    if (toggle_dessin_prim_box)
    {
      prim_to_insert = new DrawPrim(5, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_box = false;
    }
    if (toggle_dessin_prim_sphere)
    {
      prim_to_insert = new DrawPrim(6, anchorx, anchory, prim_width, prim_heigth, line_color, fill_color); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
      m_instance_Imported.push_back(prim_to_insert);
      resetSliders();
      m_instance_Imported.back()->setup();
      toggle_dessin_prim_sphere = false;
    }
  }
  cursor.is_mouse_button_pressed = false;

  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

  //---m_instance_Imported --> On parcour le vecteur pour gerer tous les evenements mouseReleased<--
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
    m_instance_Imported[i]->resetMouse(x, y, button);
  }
  //---m_instance_Imported --> end <--

}

// fonction appelee quand le curseur entre dans la fenêtre d'affichage
void Application::mouseEntered(int x, int y)
{
  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

}

// fonction appelee quand le curseur sort de la fenêtre d'affichage
void Application::mouseExited(int x, int y)
{
  cursor.mouse_current_x = x;
  cursor.mouse_current_y = y;

}

// fonction appelee pour reset sliders et unselect all instance
void Application::resetSliders()
{
  for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
  {
    m_instance_Imported[i]->asg_image_selected(false);
  }
  rot_x->setValue(0); // Reset des slider de rotation
  rot_y->setValue(0);
  rot_z->setValue(0);
}

// fonction appelee pour reset tous les camera à leur position init.
void Application::resetAllCam()
{
  //Lumière Directionnelle
  camera_fov =  60;
  toggle_vertigo_mode = false;
  cameras[0].setPosition(0, 0, 1000);
  cameras[0].lookAt(ofVec3f(0, 0, 0));
  cameras[0].setFov(camera_fov);
  cameras[0].roll(0);

  cameras[1].setPosition(0, 0, -1000);
  cameras[1].lookAt(ofVec3f(0, 0, 0));
  cameras[1].setFov(camera_fov);
  cameras[1].roll(0);

  cameras[2].setPosition(-1000, 0, 0);
  cameras[2].lookAt(ofVec3f(0, 0, 0));
  cameras[2].setFov(camera_fov);
  cameras[2].roll(0);

  cameras[3].setPosition(1000, 0, 0);
  cameras[3].lookAt(ofVec3f(0, 0, 0));
  cameras[3].setFov(camera_fov);
  cameras[3].roll(0);

  camera_index_active = 0;




  //Lumière Directionnelle
  light_position_directionnelle = ofVec3f(0, 0, -5000);

  //Lumière ponctuel
  light_position_ponctuel = ofVec3f(1000, 1000, 1000);

  //Lumière Projecteur 1

  light_position_projecteur = ofVec3f(250, 0, 3000);

  //Lumière Projecteur 2

  light_position_projecteur2 = ofVec3f(0, 1000, 2000);



}

void Application::onButtonEvent(ofxDatGuiButtonEvent e)
{

  // gui->addButton("");
  // gui->addButton("(G)rab screen");
  // gui->addButton("(H)grab 30 screenshots(1 min)");
  // gui->addButton("");
  if (e.target->getLabel() == "(I)mport image")
  {
    //---m_instance_Imported --> Si la touche "i" est appuyee, push_back l'objet à ajouter dans le vector et imb_import.setup() pour parametrer<--
    image_to_insert = new Import_img(); //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(image_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup();
    show_message("Si votre fichier IMAGE est valide, vous pouvez manipuler votre image! \nUtiliser le 'X' et '/' sur le modele pour fermer ou redimensionner\nVous pouvez déplacer votre image en -Draging-.\nLes outils de dession sont utilisables pour les rotations entre-autre.\n AMUSEZ-VOUS!");
    //---m_instance_Imported --> end <--
  }
  if (e.target->getLabel() == "(J)Import 3D OBJ")
  {
    //---m_instance_Imported --> Si la touche "i" est appuyee, push_back l'objet à ajouter dans le vector et imb_import.setup() pour parametrer<--
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup();
    show_message("Si votre fichier OBJ est valide, vous pouvez manipuler votre objet 3D! \nUtiliser le 'X' et '/' sur le modele pour fermer ou redimensionner\nVous pouvez déplacer votre image en -Draging-.\nLes outils de dession sont utilisables pour les rotations entre-autre.\n AMUSEZ-VOUS!");
    //---m_instance_Imported --> end <--
  }
  if (e.target->getLabel() == "(G)rab screen")
  {
    image_export("SceneGrab", "jpg");
    show_message("Vous avez exporte la vue !");
  }
  if (e.target->getLabel() == "(H)grab 30 screenshots(1 min)")
  {
    toggle_grab_mode = true;
    show_message("echantillonage de 30 images de la vue sur 1 minutes\n1 images / 2 secondes pour les 2 prochaines minutes.\nVous pouvez continuer à editer ou vous deplacer avec la camera(W) pendant l'operation.");
  }
  if (e.target->getLabel() == "(T)switch Cursor")
  {
    //SI l'index m'Est pas le dernier... On  incremente sinon on revient a 0
    if (cursor.indexCursor < 9)
      cursor.indexCursor = cursor.indexCursor + 1;
    else
      cursor.indexCursor = 0;
  }

  else if (e.target->getName() == "Couleur remplissage aleatoire") // Le bouton genère une couleur aleatoire pour le remplissage
  {
    outil_dessin.set_colorFilling(0, (int)ofRandom(0, 255));
    outil_dessin.set_colorFilling(1, (int)ofRandom(0, 255));
    outil_dessin.set_colorFilling(2, (int)ofRandom(0, 255));

    cout << "R = " << outil_dessin.req_colorFilling(0) << endl;
    cout << "G = " << outil_dessin.req_colorFilling(1) << endl;
    cout << "B = " << outil_dessin.req_colorFilling(2) << endl;
  }

  if (e.target->getName() == "Dessiner CARRE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_rect = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'epaisseur de la ligne\nEnsuite Dessinez votre Rectangle/Carre");
  }
  if (e.target->getName() == "Dessiner ELLIPSE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_ellipse = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Ellipse");
  }
  if (e.target->getName() == "Dessiner TRIANGLE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_triangle = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Triangle");
  }
  if (e.target->getName() == "Dessiner LINE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_line = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Ligne");
  }
  if (e.target->getName() == "Dessiner POLYGONE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_polygone = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Polygone");
  }
  if (e.target->getName() == "Dessiner CUBE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_box = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Cube");
  }
  if (e.target->getName() == "Dessiner SPHERE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    anchorx = 0;
    anchory = 0;
    prim_width = 0;
    prim_heigth = 0;
    toggle_dessin_prim_sphere = true;
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Sphere");
  }
  if (e.target->getName() == "switch FILTRE") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_choix_filtre();
    }
    show_message("Selectionnez : \nCouleur de remplissage, Couleur de ligne et l'épaisseur de la ligne\nEnsuite Dessinez votre Sphere");
  }
  if (e.target->getName() == "Nebula") // Le bouton genère une couleur aleatoire pour la ligne
  {
    if (index_cubemap_vector != 9999)
    {
      m_instance_Imported.erase(m_instance_Imported.begin() + index_cubemap_vector);
    }
    cubemap_to_insert = new Cubemap; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(cubemap_to_insert);
    m_instance_Imported.back()->setup("1");
    index_cubemap_vector = m_instance_Imported.size() - 1;
    show_message("Votre CubeMap est apparru !");
  }
  if (e.target->getName() == "Mystere") // Le bouton genère une couleur aleatoire pour la ligne
  {
    if (index_cubemap_vector != 9999)
    {
      m_instance_Imported.erase(m_instance_Imported.begin() + index_cubemap_vector);
    }
    cubemap_to_insert = new Cubemap; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(cubemap_to_insert);
    m_instance_Imported.back()->setup("2");
    index_cubemap_vector = m_instance_Imported.size() - 1;
    show_message("Votre CubeMap est apparru !");
  }
  if (e.target->getName() == "Beach") // Le bouton genère une couleur aleatoire pour la ligne
  {
    if (index_cubemap_vector != 9999)
    {
      m_instance_Imported.erase(m_instance_Imported.begin() + index_cubemap_vector);
    }
    cubemap_to_insert = new Cubemap; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(cubemap_to_insert);
    m_instance_Imported.back()->setup("0");
    index_cubemap_vector = m_instance_Imported.size() - 1;
    show_message("Votre CubeMap est apparru !");
  }
  if (e.target->getName() == "Plaine") // Le bouton genère une couleur aleatoire pour la ligne
  {
    if (index_cubemap_vector != 9999)
    {
      m_instance_Imported.erase(m_instance_Imported.begin() + index_cubemap_vector);
    }
    cubemap_to_insert = new Cubemap; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(cubemap_to_insert);
    m_instance_Imported.back()->setup("3");
    index_cubemap_vector = m_instance_Imported.size() - 1;
    show_message("Votre CubeMap est apparru !");
  }
  if (e.target->getName() == "Smooth") // Le bouton genère une couleur aleatoire pour la ligne
  {
    if (index_cubemap_vector != 9999)
    {
      m_instance_Imported.erase(m_instance_Imported.begin() + index_cubemap_vector);
    }
    cubemap_to_insert = new Cubemap; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(cubemap_to_insert);
    m_instance_Imported.back()->setup("4");
    index_cubemap_vector = m_instance_Imported.size() - 1;
    show_message("Votre CubeMap est apparru !");
  }

  if (e.target->getName() == "Materiel de base On/Off") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_enable_materiel();
        show_message("Materiau de base On/Off");
      }
    }
  }

  if (e.target->getName() == "Aucun Shader illum") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(-1);
        show_message("Shader Off");
      }
    }
  }
  if (e.target->getName() == "shader Ambiance") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(0);
        show_message("Shader Ambiance selectionne");
      }
    }
  }
  if (e.target->getName() == "lambert") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(1);
        show_message("Shader lambert selectionne");
      }
    }
  }
  if (e.target->getName() == "gouraud") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(2);
        show_message("shader gouraud selectionne");
      }
    }
  }
  if (e.target->getName() == "phong") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(3);
        show_message(" phong selectionne");
      }
    }
  }
  if (e.target->getName() == "blinn-phong") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(4);
        show_message("gouraud blinn-phong selectionne");
      }
    }
  }
  if (e.target->getName() == "Normal Mapping with Phong") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_shader(5);
        show_message("gouraud blinn-phong selectionne");
      }
    }
  }

  if (e.target->getName() == "Textures Bloc-Life") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(0);
        show_message("Bloc-Life selectionne");
      }
    }
  }
  if (e.target->getName() == "Bois") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(1);
        show_message("Bois selectionne");
      }
    }
  }
  if (e.target->getName() == "brique") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(2);
        show_message("brique selectionne");
      }
    }
  }
  if (e.target->getName() == "cailloux") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(3);
        show_message("cailloux selectionne");
      }
    }
  }
  if (e.target->getName() == "gazon") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(4);
        show_message("gazon selectionne");
      }
    }
  }
  if (e.target->getName() == "marble") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(5);
        show_message("marble selectionne");
      }
    }
  }
  if (e.target->getName() == "metal") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(6);
        show_message("metal selectionne");
      }
    }
  }
  if (e.target->getName() == "peinture") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(7);
        show_message("peinture selectionne");
      }
    }
  }
  if (e.target->getName() == "planche") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(8);
        show_message("planche selectionne");
      }
    }
  }
  if (e.target->getName() == "terre") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(9);
        show_message("terre selectionne");
      }
    }
  }
  if (e.target->getName() == "textil") // Le bouton genère une couleur aleatoire pour la ligne
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected())
      {
        m_instance_Imported[i]->set_texture(10);
        show_message("textil selectionne");
      }
    }
  }
    
   

  if (e.target->getLabel() == "De/Activer Rotation Auto (X)")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_toggle_rotation_x();
    }
    show_message("Rotation X (De)Active");
  }

  if (e.target->getLabel() == "De/Activer Rotation Auto (Y)")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_toggle_rotation_y();
    }
    show_message("Rotation Y (De)Active");
  }

  if (e.target->getLabel() == "De/Activer Rotation Auto (Z)")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->asg_toggle_rotation_z();
    }
    show_message("Rotation Z (De)Active");
  }

  if (e.target->getLabel() == "MODE CAMERA")
  {
    toggle_cam_mode = true;
    cameras[camera_index_active].dolly(-20);
    show_message(message_camera);
  }
  if (e.target->getLabel() == "MODE EDITION")
  {
    toggle_cam_mode = false;
  }
  if (e.target->getLabel() == "MODE ORTHOGONAL ON/OFF")
  {
    if (toggle_ortho)
      toggle_ortho = false;
    else
      toggle_ortho = true;
    cameras[camera_index_active].disableOrtho();
    cameras[camera_index_active].setupPerspective(false, 60.0f, 50.0f, 1750.0f, ofVec2f(0, 0));
    resetAllCam();
  }
  if (e.target->getLabel() == "CAM1")
  {
    camera_index_active = 0;
    show_message("-CAMERA 1- 'W''S''Q''E' ++ Continuez la navigation :) !");
  }
  if (e.target->getLabel() == "CAM2")
  {
    camera_index_active = 1;
    show_message("-CAMERA 2- 'W''S''Q''E' ++ Continuez la navigation :) !");
  }
  if (e.target->getLabel() == "CAM3")
  {
    camera_index_active = 2;
    show_message("-CAMERA 3- 'W''S''Q''E' ++ Continuez la navigation :) !");
  }
  if (e.target->getLabel() == "CAM4")
  {
    camera_index_active = 3;
    show_message("-CAMERA 4- 'W''S''Q''E' ++ Continuez la navigation :) !");
  }
  if (e.target->getLabel() == "RESET ALL CAM")
  {
    resetAllCam();
    show_message("RESET DE TOUS LES CAMERAS EFFECTUE !");
  }


  if (e.target->getLabel() == "Bloc 4 X 2 X 2 - Rouge")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("bloc4X2X2red.obj");
    m_instance_Imported.back()->asg_scale(0.1);
    show_message("Une nouveau Bloc est apparru ! - 4 X 4 X 2 -Rouge");
  }

  if (e.target->getLabel() == "Bloc 4 X 2 X 2 - Jaune")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("bloc4X2X2jaune.obj");
    m_instance_Imported.back()->asg_scale(0.1);
    show_message("Une nouveau Bloc est apparru ! - 4 X 4 X 2 -Jaune");
  }

  if (e.target->getLabel() == "Bloc 6 X 2 X 2 - Bourgogne")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("bloc6X2X2rouge.obj");
    m_instance_Imported.back()->asg_scale(0.24);
    show_message("Une nouveau Bloc est apparru ! - 6 X 4 X 2 -Bourgogne");
  }

  if (e.target->getLabel() == "Roue 2 X 2 X 2- Noir")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("roue2X2X2noir.obj");
    m_instance_Imported.back()->asg_scale(0.1);
    show_message("Une nouveau Bloc est apparru ! - Roue 2 X 2 X 2 -Noir");
  }

  if (e.target->getLabel() == "Bloc 8 X 2 X 2- Jaune")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("bloc8X2X2jaune.obj");
    m_instance_Imported.back()->asg_scale(0.32);
    show_message("Un nouveau Bloc est apparru ! - 8 X 2 X 2 -Jaune");
  }
  if (e.target->getLabel() == "Bloc 4 X 4 X 2 - Oblique")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("bloc4X2X2croche-red.obj");
    m_instance_Imported.back()->asg_scale(0.051);
    show_message("Un nouveau Bloc est apparru ! - Bloc 4 X 4 X 2 - Oblique");
  }
  if (e.target->getLabel() == "Bloc vitre")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("blocvitre.obj");
    m_instance_Imported.back()->asg_scale(0.18);
    show_message("Un nouveau Bloc est apparru ! - Bloc vitre");
  }
  if (e.target->getLabel() == "Persone Darth")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("persodarth.obj");
    m_instance_Imported.back()->asg_scale(0.13);
    show_message("Un nouveau Bloc est apparru ! - Personnage Darth");
  }
  if (e.target->getLabel() == "Plate 4 X 4")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("plate4X4.obj");
    m_instance_Imported.back()->asg_scale(0.08);
    show_message("Un nouveau Bloc est apparru ! - Plate 4 X 4");
  }
  if (e.target->getLabel() == "Plateau")
  {
    obj_to_insert = new Import_obj; //On cree un nouvel objet en memoire par l'entremise du pointeur d'objet m_instance_Imported
    m_instance_Imported.push_back(obj_to_insert);
    resetSliders();
    m_instance_Imported.back()->setup("plate.obj");
    m_instance_Imported.back()->asg_scale(0.85);
    m_instance_Imported.back()->asg_position(ofGetWidth() / 2, ofGetHeight() / 2 - 180, -48);
    m_instance_Imported.back()->asg_bounding_size(200, 200);
    show_message("Un nouveau Bloc est apparru ! - Plateau principal");
  }
}

void Application::colorPickerEvent(ofxDatGuiColorPickerEvent e)
{
  int r = e.color.r;
  int g = e.color.g;
  int b = e.color.b;
  if (e.target->getName() == "Couleur Canvas")
  {

    cout << "colorPickerEvent"
         << " color: " << e.color << " target: " << e.target->getName() << endl;
         bgcolor = ofColor(r,g,b);
    renderer.clear_to_color(r, g, b);
  }
  if (e.target->getName() == "Couleur ligne")
  {
    line_color.x = r;
    line_color.y = g;
    line_color.z = b;
  }
  if (e.target->getName() == "Couleur remplissage")
  {
    fill_color.x = r;
    fill_color.y = g;
    fill_color.z = b;
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->set_filling_color(fill_color);
    }
  }
}

/************Debut des evènements pour outils de dessin ********************/

void Application::onLineThicknessEvent(ofxDatGuiSliderEvent e) // Evenement qui gere l,epaisseur de la ligne
{
  if (e.target->getName() == "epaisseur ligne")
  {

    outil_dessin.set_LineWidth((int)e.value);

    cout << "onLineThicknessEvent"
         << " value: " << e.value << " target: " << e.target->getName() << endl;
  }
  if (e.target->getName() == "Rotation_x")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->rotate_obj(0, (int)e.value, 1.0f, 0.0f, 0.0f);
    }
  }
  if (e.target->getName() == "Rotation_y")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->rotate_obj(1, (int)e.value, 0.0f, 1.0f, 0.0f);
    }
  }
  if (e.target->getName() == "Rotation_z")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
        m_instance_Imported[i]->rotate_obj(2, (int)e.value, 0.0f, 0.0f, 1.0f);
    }
  }
  if (e.target->getName() == "Vitesse de rotation")
  {
    for (unsigned int i = 0; i < m_instance_Imported.size(); i++)
    {
      if (m_instance_Imported[i]->req_image_selected() == true)
      {
        m_instance_Imported[i]->asg_vitesse_rotation((float)e.value);
      }
    }
  }
}

// fonction qui exporte une image à partir de son nom et de son extension, à partir du repertoire ./bin/data ou d'un chemin absolue
void Application::image_export(const string name, const string extension) const
{
  ofImage image;

  // extraire des donnees temporelles formatees
  string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

  // generer un nom de fichier unique et ordonne
  string file_name = name + time_stamp + "." + extension;

  // capturer le contenu du framebuffer actif
  image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

  ofPixels &pixels = image.getPixels();
  pixels.swapRgb(); // fix inverted R and B channels

  // sauvegarder le fichier image
  image.save(file_name);
  image.clear();
  pixels.clear();

  ofLog() << "<export image: " << file_name << ">";
}

// fonction qui dessine un rectanlge
void Application::drawRectangle()
{
  ofDrawRectangle(anchorx, anchory, prim_width, prim_heigth);
}
// fonction qui dessine un ellipse
void Application::drawEllipse()
{
  ofDrawEllipse(ofVec2f(anchorx + prim_width / 2, anchory + prim_heigth / 2), prim_width, prim_heigth);
}
// fonction qui dessine un rectanlge
void Application::drawTriangle()
{

  ofDrawRectangle(anchorx, anchory, prim_width, prim_heigth);
}
// fonction qui dessine un rectanlge
void Application::drawLine()
{

  ofDrawRectangle(anchorx, anchory, prim_width, prim_heigth);
}
// fonction qui dessine un rectanlge
void Application::drawPolygone()
{

  ofDrawRectangle(anchorx, anchory, prim_width, prim_heigth);
}
// fonction qui dessine un rectanlge
void Application::drawBox()
{

  ofDrawRectangle(anchorx, anchory, prim_width, prim_heigth);
}
// fonction qui dessine un rectanlge
void Application::drawSphere()
{

  ofDrawRectangle(anchorx, anchory, prim_width, prim_heigth);
}

// fonction qui exporte une image à partir de son nom et de son extension A CHAQUE 120 frame pôur 30 images donc 60 seconde., à partir du repertoire ./bin/data ou d'un chemin absolue
void Application::image_export_per_sec(const string name, const string extension)
{
  if (ofGetFrameNum() % 120 == 0)
  {
    ofImage image;

    // extraire des donnees temporelles formatees
    string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

    // generer un nom de fichier unique et ordonne
    string file_name = name + time_stamp + "." + extension;

    // capturer le contenu du framebuffer actif
    image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

    ofPixels &pixels = image.getPixels();
    pixels.swapRgb(); // fix inverted R and B channels

    // sauvegarder le fichier image
    image.save(file_name);
    image.clear();
    pixels.clear();
    count_grab_laps += 1;

    ofLog() << "<export image: " << file_name << ">";
  }
  if (count_grab_laps > 29)
  {
    toggle_grab_mode = false;
    count_grab_laps = 0;
  }
}
void Application::drawCamera(int cameraIndex, ofRectangle rect)
{
  ofNoFill();
  
  if (cameraIndex == camera_index_active)
  {
    
    // ofSetLineWidth(20);
	  cameraBuffers[cameraIndex].draw(rect);
    ofSetColor(255,0,0,255);
	  ofDrawRectangle(rect);
    ofSetColor(255,255,255,255);
  }
  else{
	  cameraBuffers[cameraIndex].draw(rect);
	  ofDrawRectangle(rect);
  }
}

// fonction appelée pour reset tous les caméra à leur position init.
void Application::show_message(string new_message)
{
  message = new_message;
  ofLog() << message;
}

//UN SEUL BUTTONEVENT
// void Application::onColorEvent(ofxDatGuiButtonEvent e)   // Evenement qui gere les couleurs
// {

// }

/************Fin des evènements pour outils de dessin ********************/