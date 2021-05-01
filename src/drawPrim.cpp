// DrawPrim->cpp
// Classe responsable d'importer une image sur la scène

#include "drawPrim.h"

namespace objects_in_scene
{

  /**
 * \brief Constructeur par défaut.
*/

  DrawPrim::DrawPrim(int type, float p_posx, float p_posy, float p_width, float p_height, ofVec3f p_line_color, ofVec3f p_fill_color) : Instance_Imported()
  {
    m_width_img = p_width; //on enregistre la taille en widht et height + on copie un original qui sert à la redimension.
    m_height_img = p_height;
    m_posx = p_posx; //On affiche la nouvelle image au milieu de la scène,
    m_posy = p_posy; //On alligne l'image à 400 pixels de hauteur.
    m_choi_prim = type;
    m_line_color = p_line_color;
    m_fill_color = p_fill_color;
    m_line_colorN = p_line_color.normalize();
    m_fill_colorN = p_fill_color.normalize();
  }
  /**
 * \brief Mets toutes les valeurs par défaut de l'image et importe une image en proposant un path selector.
 */
  void DrawPrim::setup(string p_path, bool p_obj_du_menu)
  {
    m_rotx = 0;
    m_roty = 0;
    m_rotz = 0;
    m_close_true = false;       //Est-ce que on doit detruire l'objet ?
    m_mouse_move_image = false; //Bool qui vérifie si on doit bouger l'image.
    m_image_redim_selected = false;
    m_line_width = outil_dessin.req_LineWidth();

    m_image_selected = true; //Bool : Par défaut la sélection est à true donc on affiche
    m_redim_box_height = 10; //Hauteur de la zone de redimensionnage de l'image.
    m_redim_box_width = 10;  //Largeur de la zone de redimensionnage de l'image.
    m_close_box_height = 13; //Hauteur de la zone de destruction de l'image.
    m_close_box_width = 13;  //Largeur de la zone de destruction de l'image.
    m_enable_texture = true;
    
  // charger, compiler et linker les sources des shaders
  m_shaders_illum[0].load(
    "shaderillum/color_fill_330_vs.glsl",
    "shaderillum/color_fill_330_fs.glsl");

  m_shaders_illum[1].load(
    "shaderillum/lambert_330_vs.glsl",
    "shaderillum/lambert_330_fs.glsl");

  m_shaders_illum[2].load(
    "shaderillum/gouraud_330_vs.glsl",
    "shaderillum/gouraud_330_fs.glsl");

  m_shaders_illum[3].load(
    "shaderillum/phong_330_vs.glsl",
    "shaderillum/phong_330_fs.glsl");

  m_shaders_illum[4].load(
    "shaderillum/blinn_phong_330_vs.glsl",
    "shaderillum/blinn_phong_330_fs.glsl");

  m_shaders_illum[5].load(
    "shaderillum/phongNMap_330_vs.glsl",
    "shaderillum/phongNmap_330_fs.glsl");

  // shader actif au lancement de la scène
  m_index_shader_select = -1;
  m_index_texture_select = 0;
  ofLoadImage(m_texture,"../../data/bloc-life.png");
  ofLoadImage(m_normal_map,"../../data/briqueNMAP.jpg");


  // configurer le matériau Shiny
  m_materiel_lego[0].setAmbientColor(ofColor(80, 80, 80));
  m_materiel_lego[0].setDiffuseColor(ofColor(120, 120, 120));
  m_materiel_lego[0].setEmissiveColor(ofColor(10, 10, 10));
  m_materiel_lego[0].setSpecularColor(ofColor(150, 150, 150));
  m_materiel_lego[0].setShininess(1000.0f);

  // configurer le matériau Poreux
  m_materiel_lego[1].setAmbientColor(ofColor(110, 110, 110));
  m_materiel_lego[1].setDiffuseColor(ofColor(80, 80, 80));
  m_materiel_lego[1].setEmissiveColor(ofColor(10, 10, 10));
  m_materiel_lego[1].setSpecularColor(ofColor(10, 10, 10));
  m_materiel_lego[1].setShininess(0.0f);

  // configurer le matériau Metalique
  m_materiel_lego[2].setAmbientColor(ofColor(25, 25, 25));
  m_materiel_lego[2].setDiffuseColor(ofColor(200, 200, 200));
  m_materiel_lego[2].setEmissiveColor(ofColor(10, 10, 10));
  m_materiel_lego[2].setSpecularColor(ofColor(120, 120, 120));
  m_materiel_lego[2].setShininess(50.0f);

  // configurer le matériau Caoutchou
  m_materiel_lego[3].setAmbientColor(ofColor(180, 150, 150));
  m_materiel_lego[3].setDiffuseColor(ofColor(120, 120, 150));
  m_materiel_lego[3].setEmissiveColor(ofColor(100, 100, 100));
  m_materiel_lego[3].setSpecularColor(ofColor(200, 200, 200));
  m_materiel_lego[3].setShininess(20.0f);

  m_choi_materiau = 1;
  m__nb_light_dynamic = 2;
  m_light.setPosition(0, 0, 0);
  m_light.setOrientation(ofVec3f(0,0,0));



 


  }

  /**
 * \brief On rends l'image au (milieu, 400), on tace un contour sélectif, on affiche un X au coin supérieur gauche
 * et une option de redimension au bas droite de la barre contour de sélection.
 */
  void DrawPrim::show_obj()
  {

     // passer les attributs uniformes au shader de sommets
  switch (m_index_shader_select)
  {
    case -1:
      break;
    case 0:
      m_shader = &m_shaders_illum[0];
      m_shader->begin();
      m_shader->setUniform3f("color", m_fill_colorN.x, m_fill_colorN.y, m_fill_colorN.z);
      m_shader->end();
      break;

    case 1:
      m_shader = &m_shaders_illum[1];
      m_shader->begin();
      m_shader->setUniform3f("color_ambient", m_fill_colorN.x, m_fill_colorN.y, m_fill_colorN.z);
      m_shader->setUniform3f("color_diffuse",  0.4f, 0.4f, 0.4f);
      m_shader->setUniform3f("light_position", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->end();
      break;

    case 2:
      m_shader = &m_shaders_illum[2];
      m_shader->begin();
      m_shader->setUniform3f("color_ambient", m_fill_colorN.x, m_fill_colorN.y, m_fill_colorN.z);
      m_shader->setUniform3f("color_diffuse",  0.4f, 0.4f, 0.4f);
      m_shader->setUniform3f("color_specular", 0.3f, 0.3f, 0.1f);
      m_shader->setUniform1f("brightness", 1.0f);
      m_shader->setUniform3f("light_position", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->end();
      break;

//PHONG
    case 3:
      m_shader = &m_shaders_illum[3];
      m_shader->begin();
      m_shader->setUniform3f("color_ambient", m_fill_colorN.x, m_fill_colorN.y, m_fill_colorN.z);
      m_shader->setUniform3f("color_diffuse",  0.2f, 0.2f, 0.4f);
      m_shader->setUniform3f("color_specular", 0.3f, 0.3f, 0.3f);
      m_shader->setUniform1f("brightness", 1.0f);
      m_shader->setUniform1i("nb_light", m__nb_light_dynamic);
      m_shader->setUniform3f("light_position", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->end();
      break;
    case 4:
      m_shader = &m_shaders_illum[4];
      m_shader->begin();
      m_shader->setUniform3f("color_ambient", m_fill_colorN.x, m_fill_colorN.y, m_fill_colorN.z);
      m_shader->setUniform3f("color_diffuse",  0.4f, 0.4f, 0.4f);
      m_shader->setUniform3f("color_specular", 0.3f, 0.3f, 0.1f);
      m_shader->setUniform1f("brightness", 1.0f);
      m_shader->setUniform3f("light_position", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->end();
      break;

    case 5://Phong with normal mapping essaie
      m_shader = &m_shaders_illum[5];
      m_shader->begin();
      m_shader->setUniform3f("color_ambient", m_fill_colorN.x, m_fill_colorN.y, m_fill_colorN.z);
      m_shader->setUniform3f("color_diffuse", 0.2f, 0.2f, 0.2f);
      m_shader->setUniform3f("color_specular", 0.3f, 0.3f, 0.1f);
      m_shader->setUniform1f("brightness", 0.5f);
      m_shader->setUniformTexture("textureBase", (m_texture), 1);
      m_shader->setUniformTexture("normalMapTex", (m_normal_map), 2);
      m_shader->setUniform3f("light_position", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->setUniform3f("lightDirections", glm::vec4(m_light.getOrientationEuler(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->setUniform3f("light_position_vertex_shader", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->end();
      break;


    default:
      break;
  }




    // activer la lumière dynamique
    if (m_index_shader_select != -1)
    {
     // activer l'éclairage dynamique
    ofEnableLighting();
      // m_light.enable();
    }
    
    m_show_select();
    ofPushMatrix();
    ofTranslate(m_posx + m_width_img / 2, m_posy + m_height_img / 2); //move pivot to centre
    ofRotateXDeg(m_rotx);
    ofRotateYDeg(m_roty);
    ofRotateZDeg(m_rotz);
    ofPushMatrix();
    ofTranslate(-m_width_img / 2, -m_height_img / 2); //move back by the centre offset
    // offil(outil_dessin.req_lineColor(0), outil_dessin.req_lineColor(1), outil_dessin.req_lineColor(2));
    


    // activer le shader
    if (m_index_shader_select != -1)
    {
      m_shader->begin();
    }

    //activer la texture
    if (m_enable_texture)
    {
      m_texture.bind();
    }
    if(m_choi_materiau != -1)
      {
        m_materiel_lego[m_choi_materiau].begin();
      }
    switch (m_choi_prim)
    {
    case 0: // Rectangle
      drawRectangle();
      break;
    case 1: // ellipse
      drawCircle();
      break;
    case 2: // triangle
      drawTriangle();
      break;
    case 3: // polygone
      drawPolygone();
      break;
    case 4: // ligne
      drawLine();
      break;
    case 5: // cube
      drawBox();
      break;
    case 6: // sphere
      drawShere();
      break;
    }
    if(m_choi_materiau != -1)
      {
        m_materiel_lego[m_choi_materiau].end();
      }
    ofPopMatrix();
    ofPopMatrix(); //on affiche la zone de sélection autour de l'image importée.
        // m_imageImport.draw(m_posx, m_posy, m_width_img, m_height_img);        //on affiche l'image en (milieu,400) de grosseur native.
  
    // désactiver le shader
    if (m_index_shader_select != -1)
    {
      m_shader->end();
    // désactiver la lumière
      // m_light.disable();
    }

    //deactiver la texture
    if (m_enable_texture)
    {
      m_texture.unbind();
    }

    // désactiver l'éclairage dynamique
    ofDisableLighting();
  }
  void DrawPrim::m_show_select()
  {
    if (m_image_selected) //Si l'image est sélectionnée.
    {
      ofNoFill(); //On dessine la sélection autour de l'image.
      ofSetLineWidth(1);
      ofSetColor(0, 100, 20);
      ofDrawRectangle(m_posx - 3, m_posy - 3, //On décale les x,y de -1 et on agrandit la zone de 2 pour qu'elle soit visible AUTOUR de
                      m_width_img + 6, m_height_img + 6);
      ofSetColor(255, 255, 255); //remise à 0 des couleurs pour les autres images du programme.

      ofNoFill(); //On dessine la zone d'agrandissement en bas à droite la zone de sélection.
      ofSetLineWidth(1);
      ofSetColor(0, 200, 200);
      ofDrawRectangle(m_posx + m_width_img - m_redim_box_width + 1, //affichage la zone de redimensionnage de la zone de sélection.
                      m_posy + m_height_img - m_redim_box_height + 1,
                      m_redim_box_width, m_redim_box_height);
      ofDrawLine(m_posx + m_width_img - m_redim_box_width + 3, //affichagedu \ de la zone de redimensionnage de la zone de sélection.
                 m_posy + m_height_img - m_redim_box_height + 3,
                 m_posx + m_width_img - m_redim_box_width + m_redim_box_width - 1,
                 m_posy + m_height_img - m_redim_box_height + m_redim_box_height - 1);
      ofSetColor(255, 255, 255);

      ofNoFill(); //On dessine la zone de destruction de l'objet en haut à gauche de la zone de sélection.
      ofSetLineWidth(1);
      ofSetColor(200, 0, 0);
      ofDrawRectangle(m_posx, //affichage la zone de destruction de la zone de sélection.
                      m_posy,
                      m_close_box_width, m_close_box_height);
      ofDrawLine(m_posx + 3, m_posy + 3, m_posx + m_close_box_width - 3, //affichagedu X de  la zone de destruction de la zone de sélection.
                 m_posy + m_close_box_height - 3);
      ofDrawLine(m_posx + m_close_box_width - 3, m_posy + 3, m_posx + 3,
                 m_posy + m_close_box_height - 3);
      ofSetColor(255, 255, 255);
    }
  }

  /**
 * \brief Sélectionne l'objet et enregistre les coordo du clic. Les bool redim, move, close sont ajuster en conséquence de la zone du clic
 */
  void DrawPrim::select_obj(int p_x, int p_y, int p_button)
  {
    m_clicked_x = p_x; //Sauvegarde de la coordonnée du clic pour calcul de déplacement et d'agrandissement
    m_clicked_y = p_y;
    if (p_x > m_posx && p_x < m_posx + m_width_img && //Si le clic est dans la zone de sélection, on active m_mouse_move_image == true pour si mouse_drag =  déplacement d'image.
        p_y > m_posy && p_y < m_posy + m_height_img)
    {
      m_mouse_move_image = true;
      m_x_correction = p_x - m_posx; //On applique la correction pour que le déplacement soit fluide et synchro avec mouse (x,y)
      m_y_correction = p_y - m_posy;
      if (p_x > m_posx + m_width_img - m_redim_box_width + 1 && //Si en plus nous somme dans la zone de redimensionnage... on m_image_redim_selected = true
          p_x < m_posx + m_width_img - m_redim_box_width + 1 +
                    m_redim_box_width &&
          p_y > m_posy + m_height_img - m_redim_box_height + 1 &&
          p_y < m_posy + m_height_img - m_redim_box_height + 1 +
                    m_redim_box_height)
      {
        m_image_redim_selected = true; //on m_image_redim_selected = true;
        ofLog() << m_image_redim_selected;
      }
      else
      {
        if (p_x > m_posx && //Si en plus nous somme dans la zone de destruction d'image... on m_close_true = true.
            p_x < m_posx + m_close_box_width &&
            p_y > m_posy &&
            p_y < m_posy + m_close_box_height)
        {
          m_close_true = true;
        }
        else //Sinon on met m_close_true = false.
          m_close_true = false;
      }

      m_image_selected = true; //SI nous ne sommes pas dans la zone REDIM, m_image_selected = true quand même car nous sommes dans m_image_selected
    }
    else //MAIS SINON, nous somme complètement hors zone donc tout reste faux.
    {
      m_image_selected = false;
      m_image_redim_selected = false;
      m_close_true = false;
    }
  }

  /**
 * \brief Bouge l'objet si m_mouse_move_image.Sur un drag mouse, si le déplacement ET la redimension sont activés, on calculla nouvelle grosseur
 * de l'image en fonction du déplacement (x, y) de la souris.
 * SINON, Nous effectuons le déplacement avec un facteur de correction qui rend le tout fluide.
 * Sans la correction l'image serait repositionné sur la souris en sa position...et c'est très laid ! :)
 */
  void DrawPrim::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
    if (m_mouse_move_image == true && m_image_redim_selected == false) //SI nous avons activé le déplacement d'image....
    {
      m_posx = p_x - m_x_correction; //Déplacement de l'image importée avec l'attribution de la position
      m_posy = p_y - m_y_correction; //corrigée en fonction de l'endroit cliqué dans l'image ! :)
    }
  }
  /**
 * \brief Sélectionne l'objet et enregistre les coordo du clic.
 */
  void DrawPrim::redim_obj(int p_x, int p_y, int p_button)
  {
    if (m_image_redim_selected) //Et SI la redimension est aussi activée....
    {
      m_width_img = m_original_m_width_img + p_x - m_clicked_x; //On recalcul la grosseur de l'image en fonction du déplacement de la souris en (x, y).
      m_height_img = m_original_m_height_img + p_y - m_clicked_y;
    }
  }

  /**
 * \brief retourne si l'objet doit être fermé
 * \return string de l'electeur formaté
 */
  bool DrawPrim::req_close_true() const
  {
    return m_close_true;
  }
  /**
 * \brief retourne si l'image est sélectionnée
 * \return string de l'electeur formaté
 */
  bool DrawPrim::req_image_selected() const
  {
    return m_image_selected;
  }
  /**
 * \brief retourne la textu tempo unable
 * \return exture de l'imaget
 */
  ofTexture DrawPrim::req_texture() const 
  {
    ofTexture temp;
    return temp;
  }
  /**
 * \brief retourne si l'image est sélectionnée
 * \param selected Définit l'attribut à true ou false.
 */
  void DrawPrim::asg_image_selected(bool p_selected)
  {
    m_image_selected = p_selected;
  }
  /**
 * \brief change le filtre
 */
  void DrawPrim::asg_choix_filtre()
  {

  }

  /**
 * \brief rotation de l'objet
 */
  void DrawPrim::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
  {
    if (rot_x == 1)
      m_rotx = angle;
    if (rot_y == 1)
      m_roty = angle;
    if (r_z == 1)
      m_rotz = angle;
  }

  /**
 * \brief Action sur le relachement de souris, On désactive le déplacement, la redimension et la sélection de l'image
 */
  void DrawPrim::resetMouse(int p_x, int p_y, int p_button)
  {
    m_mouse_move_image = false; //Quand on relâche le bouton de la souris, on désactive le déplacement et la redimension.
    m_image_redim_selected = false;

    m_original_m_width_img = m_width_img;   //Réafectation de la nouvelle grosseur de l'image(Originale avant transfo) pour la prochaine transformation
    m_original_m_height_img = m_height_img; //Cet attribut est nécessaire pour le calcul de la grosseur en fonction de la souris dans mouseDragged(...).
  }
  /**
 * \brief Retourn le pathName de l'image.
 */
  const string DrawPrim::getPathName() const
  {
    return m_path_name;
  }
  /**
 * \brief dessine un rectangle
 */
  void DrawPrim::drawRectangle()
  {
    // ofNoFill();
    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawRectangle(0, 0, m_width_img, m_height_img);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawRectangle(0, 0, m_width_img, m_height_img);
    ofSetColor(255, 255, 255);
  }

  void DrawPrim::drawCircle()
  {

    // ofNoFill();

    ofSetCircleResolution(100);
    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawEllipse(ofVec2f(m_width_img / 2, m_height_img / 2), m_width_img, m_height_img);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawEllipse(ofVec2f(m_width_img / 2, m_height_img / 2), m_width_img, m_height_img);
    ofSetColor(255, 255, 255);
  }

  void DrawPrim::drawTriangle()
  {

    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawTriangle(0, 0, 0, m_width_img / 2, m_height_img, 0, m_width_img, 0, 0);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawTriangle(0, 0, 0, m_width_img / 2, m_height_img, 0, m_width_img, 0, 0);
    ofSetColor(255, 255, 255);
  }

  void DrawPrim::drawPolygone()
  {
    ofSetCircleResolution(5);
    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawEllipse(ofVec2f(m_width_img / 2, m_height_img / 2), m_width_img, m_height_img);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawEllipse(ofVec2f(m_width_img / 2, m_height_img / 2), m_width_img, m_height_img);
    ofSetColor(255, 255, 255);
  }

  void DrawPrim::drawLine()
  {
    // ofNoFill();
    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawLine(0, 0, m_width_img, m_height_img);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawLine(0, 0, m_width_img, m_height_img);
    ofSetColor(255, 255, 255);
  }

  void DrawPrim::drawBox()
  {
    ofPushMatrix();
    ofTranslate(m_width_img / 2, m_height_img / 2);
    ofScale(0.5, 0.5, 0.5);
    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawBox(m_width_img);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawBox(m_width_img);
    ofSetColor(255, 255, 255);
    ofPopMatrix();
  }

  void DrawPrim::drawShere()
  {
    ofPushMatrix();
    ofTranslate(m_width_img / 2, m_height_img / 2);
    ofScale(0.5, 0.5, 0.5);
    ofFill();
    ofSetColor(m_fill_color.x, m_fill_color.y, m_fill_color.z);
    ofSetLineWidth(0);
    ofDrawSphere(m_width_img / 2);

    ofNoFill();
    ofSetColor(m_line_color.x, m_line_color.y, m_line_color.z);
    ofSetLineWidth(m_line_width);
    ofDrawSphere(m_width_img / 2);
    ofSetColor(255, 255, 255);
    ofPopMatrix();
  }
  /**
 * \brief req la poz_z
 */
  int DrawPrim::req_pos_z() const
  {
    return 0;
  }
  const bool DrawPrim::get_if_cubemap() const 
  {
      return false;
  }
  void DrawPrim::set_shader(int p_shader)
  {
    m_index_shader_select = p_shader;
      m_choi_materiau = -1;
  }
  void DrawPrim::set_texture(int p_texture)
  {
    m_index_texture_select = p_texture;
    switch(p_texture)
    {
      case 0: 
        ofLoadImage(m_texture,"../../data/bloc-life.png");
      break;
      case 1: 
        ofLoadImage(m_texture,"../../data/bois.jpg");
      break;
      case 2: 
        ofLoadImage(m_texture,"../../data/brique.jpg");
        ofLoadImage(m_normal_map,"../../data/briqueNMAP.jpg");
      break;
      case 3: 
        ofLoadImage(m_normal_map,"../../data/caillouxNMAP.jpg");
        ofLoadImage(m_texture,"../../data/cailloux.jpg");
      break;
      case 4: 
        ofLoadImage(m_texture,"../../data/gazon.png");
      break;
      case 5: 
        ofLoadImage(m_texture,"../../data/marble.jpg");
      break;
      case 6: 
        ofLoadImage(m_texture,"../../data/metal.jpg");
      break;
      case 7: 
        ofLoadImage(m_texture,"../../data/peinture.jpg");
      break;
      case 8: 
        ofLoadImage(m_texture,"../../data/planche.jpg");
      break;
      case 9: 
        ofLoadImage(m_texture,"../../data/terre.jpg");
      break;
      case 10: 
        ofLoadImage(m_texture,"../../data/textil.jpg");
      break;
    }
      
  }

  void DrawPrim::set_choix_material(int p_choi)
  {
    m_choi_materiau = p_choi;
  }

  void DrawPrim::set_nb_dynamic_light(int p_nbLight)
  {
    m__nb_light_dynamic = p_nbLight;
  }
  void DrawPrim::set_pos_dynamic_light(ofVec3f p_pos)
  {
    ofVec3f postmp = m_light.getGlobalPosition();
    postmp += p_pos;
    m_light.setPosition(postmp);
    ofLog() << m_light.getGlobalPosition();
  }
} /*namespace objects_in_scene*/