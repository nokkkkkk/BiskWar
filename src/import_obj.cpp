// Import_obj->cpp
// Classe responsable d'importer une image sur la scène

#include "import_obj.h"
#include <math.h> 

namespace objects_in_scene
{

  /**
 * \brief Constructeur par défaut.
*/

  Import_obj::Import_obj() : Instance_Imported()
  {
  }
  /**
 * \brief Mets toutes les valeurs par défaut de l'image et importe une image en proposant un path selector.
 */
  void Import_obj::setup(string p_path, bool p_obj_du_menu)
  {
    m_close_true = false;       //Est-ce que on doit detruire l'objet ?
    m_mouse_move_image = false; //Bool qui vérifie si on doit bouger l'image.

    m_mode_lego = false;
    vitesse_rotation = 0.5;

    m_image_selected = false;
    m_image_redim_selected = false;
    m_toggle_x_rotation = false;
    m_toggle_y_rotation = false;
    m_toggle_z_rotation = false;
    m_obj_du_menu = p_obj_du_menu;
    m_random_rotation = ofRandom(3000);
    m_lego_lock = false;
    m_enable_materiel = true;
    m_enable_texture = true;


    string path;
    
    if (p_path == "") //Affiche et prélève le path de l'image à importer ou hardcodé selon le cas.
      {
        m_path_fichier_img = ofSystemLoadDialog("Load file");
        path = m_path_fichier_img.getPath(); //On récupère le path
        m_path_name = path;
        m_hard_coded_obj = false;
        ofLog() << path;

      }
    else{ //Soi le path est hardcodé
        path = m_path_name = p_path;
        m_hard_coded_obj = true;
    }

    if (m_path_fichier_img.bSuccess || m_path_name != "") //Si l'ouverture du fichier est un succès:
    {
      m_objectImport.loadModel(path);
      int n = path.length();
      char path_char[n + 1];
      strcpy(path_char, path.c_str());

      if ((int)path_char[n - 1] == (int)'j')
      {      
        m_model_mesh = m_objectImport.getMesh(0);

        for(int i=0; i < m_model_mesh.getNumVertices();i++){
          m_model_vertices.push_back(m_model_mesh.getVertex(i));
        }

        //Parcour du vecteur des sommets pour les affichers dans la console.
        m_model_max_x = -9999999;
        m_model_min_x = 9999999;
        m_model_max_y = -9999999;
        m_model_min_y = 9999999;
        for (unsigned int i = 0; i < m_model_vertices.size(); i++)
        {
          if (m_model_vertices[i].x > m_model_max_x)
            m_model_max_x = m_model_vertices[i].x;
          if (m_model_vertices[i].y > m_model_max_y)
            m_model_max_y = m_model_vertices[i].y;
          if (m_model_vertices[i].x < m_model_min_x)
            m_model_min_x = m_model_vertices[i].x;
          if (m_model_vertices[i].y < m_model_min_y)
             m_model_min_y = m_model_vertices[i].y;
        }
        // ofLog() << "maxX :" << m_model_max_x << "maxY :" << m_model_max_y << "minX :" << m_model_min_x << "minY :" << m_model_min_y;

        m_model_matrix = m_objectImport.getModelMatrix();
        m_scaling = m_model_matrix.getScale();
        //On laod l'image avec le path
        m_width_img = m_original_m_width_img = (m_model_max_x - m_model_min_x) * m_scaling.x * 0.25; //on enregistre la taille en widht et height + on copie un original qui sert à la redimension.
        m_height_img = m_original_m_height_img = (m_model_max_y - m_model_min_y) * m_scaling.y * 0.25;

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

        // shader actif au lancement de la scène
        m_index_shader_select = 3;
        m_index_texture_select = 0;
        ofLoadImage(m_texture,"../../data/textures/bloc-life.png");


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

  m_choi_materiau = -1;
  m__nb_light_dynamic = 2;
  m_light.setPosition(0, 0, 0);
  m_light.setOrientation(ofVec3f(0,0,0));




      }
      else
      {
        m_close_true = true;
      }

      m_x_scale = 1;
      m_y_scale = 1;
      m_z_scale = 1;
      m_posx = ofGetWindowWidth() / 2 - 250 / 2 + ofRandom(300) - ofRandom(400); //On affiche la nouvelle image aleatoire
      m_posy = 400 + ofRandom(300) - ofRandom(300);                              //On alligne l'image à 400 pixels de hauteur.
      m_posz = 0;
      m_image_selected = true;                   //Bool : Par défaut la sélection est à true donc on affiche
      m_redim_box_height = 10;                   //Hauteur de la zone de redimensionnage de l'image.
      m_redim_box_width = 10;                    //Largeur de la zone de redimensionnage de l'image.
      m_close_box_height = 13;                   //Hauteur de la zone de destruction de l'image.
      m_close_box_width = 13;                    //Largeur de la zone de destruction de l'image.
    }
    else
    {
      m_close_true = true;
    }
  }

  /**
 * \brief On rends l'image au (milieu, 400), on tace un contour sélectif, on affiche un X au coin supérieur gauche
 * et une option de redimension au bas droite de la barre contour de sélection.
 */
  void Import_obj::show_obj()
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
      m_shader->setUniform3f("color_diffuse",  0.2f, 0.2f, 0.2f);
      m_shader->setUniform3f("color_specular", 0.4f, 0.3f, 0.4f);
      m_shader->setUniform1f("brightness", 1.0f);
      m_shader->setUniform3f("light_position", glm::vec4(m_light.getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));
      m_shader->setUniformTexture("NormalMaptex", (m_normal_map), 2);
      m_shader->end();
      break;

    default:
      break;
  }

    

    if (m_index_shader_select != -1)
    {
     // activer l'éclairage dynamique

      ofEnableLighting();

    // activer la lumière dynamique
      // m_light.enable();
    }

    if (!m_enable_materiel)
    {
      m_objectImport.disableMaterials();
    }
    if (m_enable_materiel)
    {
      m_objectImport.enableMaterials();
    }
      
    

      m_posx_lego = round(m_posx / 24) * 24;
      m_posy_lego = round(m_posy / 24) * 24;
      m_posz_lego = round(m_posz / 24) * 24;
      if(m_posz < 50 && m_posz > 10)
      {
        m_posz_lego = 24;
      }
      if(m_posz > -24 && m_posz < -10)
      {
        m_posz_lego = -24;
      }
      if (m_posz > 250)
      {
        m_posz_lego = 250;
        m_posz = 250;
      }
      if (m_posz < -250)
      {
        m_posz_lego = -250; 
        m_posz = -250; 
      }
      
    if (!m_mode_lego)
    {
      m_objectImport.setPosition(m_posx + m_width_img / 2, m_posy + m_height_img / 2, m_posz);
    }
    else
    {
      m_posx = m_posx_lego;
      m_posy = m_posy_lego;
      m_objectImport.setPosition(m_posx_lego + m_width_img / 2, m_posy_lego + m_height_img / 2, m_posz_lego);
    }
    
    if (!m_hard_coded_obj)
      m_objectImport.setScale(m_x_scale * 0.2, m_y_scale * 0.2, m_z_scale * 0.2);
    
    if (m_index_shader_select != -1)
    {
      m_shader->begin();
    }

    //activer la texture
    if (m_enable_texture)
    {
      m_objectImport.disableColors();
      m_objectImport.disableTextures();
      m_texture.bind();
    }

    if (!m_image_redim_selected)
    {
      if(m_choi_materiau != -1)
      {
        m_materiel_lego[m_choi_materiau].begin();
      }
      m_objectImport.drawFaces(); //on affiche l'image en (milieu,400) de grosseur native.
      // ofLog() << m_posx + m_width_img / 2 << "YYYYYYYYYYYYYYYYYY : " <<  m_posy + m_height_img / 2 << "ZZZZZ : " << m_posz;

      if(m_choi_materiau != -1)
      {
        m_materiel_lego[m_choi_materiau].end();
      }
    }

    if (m_index_shader_select != -1)
    {
      m_shader->end();
      ofDisableLighting();

      m_objectImport.enableMaterials();
    
    }   
    


    //deactiver la texture
    if (m_enable_texture)
    {
      m_texture.unbind();
      m_objectImport.enableColors();
      m_objectImport.enableTextures();
    }

    if (m_toggle_x_rotation == true)
    {
      m_objectImport.setRotation(0, ofGetFrameNum() * vitesse_rotation + m_random_rotation, 1.0f, 0.0f, 0.0f);
    }
    if (m_toggle_y_rotation == true)
    {
      m_objectImport.setRotation(1, ofGetFrameNum() * vitesse_rotation + m_random_rotation, 0.0f, 1.0f, 0.0f);
    }
    if (m_toggle_z_rotation == true)
    {
      m_objectImport.setRotation(2, ofGetFrameNum() * vitesse_rotation + m_random_rotation, 0.0f, 0.0f, 1.0f);
    }


    // ofPopMatrix();                                           //on affiche la zone de sélection autour de l'image importée.
    if (!m_obj_du_menu)
      m_show_select();

  }
  void Import_obj::m_show_select()
  {
    if (m_image_selected) //Si l'image est sélectionnée.
    {
      // ofPushMatrix();
      // ofTranslate(0, 0, m_posz);
      ofNoFill(); //On dessine la sélection autour de l'image.
      ofSetLineWidth(1);
      if (m_lego_lock)
      {
        ofSetColor(255, 0, 0);
      }
      else
      {
        ofSetColor(0, 100, 20);
      }
      ofDrawRectangle(m_posx - 1, m_posy - 1, //On décale les x,y de -1 et on agrandit la zone de 2 pour qu'elle soit visible AUTOUR de
                      m_width_img + 2, m_height_img + 2);
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
      // ofPopMatrix();
    }

        //mise a jour des variables de la matrices du modele
        m_model_matrix = m_objectImport.getModelMatrix();
        m_scaling = m_model_matrix.getScale();
  }

  /**
 * \brief Sélectionne l'objet et enregistre les coordo du clic. Les bool redim, move, close sont ajuster en conséquence de la zone du clic
 */
  void Import_obj::select_obj(int p_x, int p_y, int p_button)
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
  void Import_obj::move_obj(int p_x, int p_y, int p_z, int p_button)
  {
    if (m_mouse_move_image == true && m_image_redim_selected == false && m_lego_lock == false) //SI nous avons activé le déplacement d'image....
    {
      m_posx = p_x - m_x_correction; //Déplacement de l'image importée avec l'attribution de la position
      m_posy = p_y - m_y_correction; //corrigée en fonction de l'endroit cliqué dans l'image ! :)
      m_posz = p_z ;     //corrigée en fonction de l'endroit cliqué dans l'image ! :)
    }
  }
  /**
 * \brief Sélectionne l'objet et enregistre les coordo du clic.
 */
  void Import_obj::redim_obj(int p_x, int p_y, int p_button)
  {

    // ofPushMatrix();
    // ofScale(0.5, 0.5, 0.5);
    if (m_image_redim_selected) //Et SI la redimension est aussi activée....
    {
      m_width_img = m_original_m_width_img + p_x - m_clicked_x; //On recalcul la grosseur de l'image en fonction du déplacement de la souris en (x, y).
      m_height_img = m_original_m_height_img + p_y - m_clicked_y;
      new_scale_x = (float)m_width_img / (float)m_original_m_width_img;
      new_scale_y = (float)m_height_img / (float)m_original_m_height_img;
      new_scale_z = new_scale_y;

    }
    // ofPopMatrix();
  }

  /**
 * \brief rotation de l'objet
 */
  void Import_obj::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
  {
    if (m_mode_lego)
    {
      m_objectImport.setRotation(which, round(angle / 90) * 90, rot_x, rot_y, r_z);
    }
    else
    {
      m_objectImport.setRotation(which, angle, rot_x, rot_y, r_z);
    }
  }

  /**
 * \brief retourne si l'objet doit être fermé
 * \return string de l'electeur formaté
 */
  bool Import_obj::req_close_true() const
  {
    return m_close_true;
  }
  /**
 * \brief retourne si l'image est sélectionnée
 * \return string de l'electeur formaté
 */
  bool Import_obj::req_image_selected() const
  {
    return m_image_selected;
  }
  /**
 * \brief retourne la textu tempo unable
 * \return exture de l'imaget
 */
  ofTexture Import_obj::req_texture() const 
  {
    ofTexture temp;
    return temp;
  }
  /**
 * \brief retourne si l'image est sélectionnée
 * \param selected Définit l'attribut à true ou false.
 */
  void Import_obj::asg_image_selected(bool p_selected)
  {
    m_image_selected = p_selected;
  }
  /**
 * \brief change le filtre
 */
  void Import_obj::asg_choix_filtre()
  {

  }

  /**
 * \brief Action sur le relachement de souris, On désactive le déplacement, la redimension et la sélection de l'image
 */
  void Import_obj::resetMouse(int p_x, int p_y, int p_button)
  {
    if (m_image_redim_selected)
    {

      m_x_scale = m_x_scale * new_scale_x;
      m_y_scale = m_y_scale * new_scale_y;
      m_z_scale = m_y_scale;
    }
    m_mouse_move_image = false; //Quand on relâche le bouton de la souris, on désactive le déplacement et la redimension.
    m_image_redim_selected = false;

    m_original_m_width_img = m_width_img;   //Réafectation de la nouvelle grosseur de l'image(Originale avant transfo) pour la prochaine transformation
    m_original_m_height_img = m_height_img; //Cet attribut est nécessaire pour le calcul de la grosseur en fonction de la souris dans mouseDragged(...).
  }
  /**
 * \brief Retourn le pathName de l'image.
 */
  const string Import_obj::getPathName() const
  {
    return m_path_name;
  }
  /**
 * \brief Toggle les bool des rotation d'Animation
 */
  void Import_obj::asg_toggle_rotation_x()
  {
    m_toggle_x_rotation = !m_toggle_x_rotation;
  }
  /**
 * \brief Toggle les bool des rotation d'Animation
 */
  void Import_obj::asg_toggle_rotation_y()
  {
    m_toggle_y_rotation = !m_toggle_y_rotation;
  }
  /**
 * \brief Toggle les bool des rotation d'Animation
 */
  void Import_obj::asg_toggle_rotation_z()
  {
    m_toggle_z_rotation = !m_toggle_z_rotation;
  }
  /**
 * \brief asg pour la vitesse de rotation
 */
  void Import_obj::asg_vitesse_rotation(float speed)
  {
    vitesse_rotation = speed;
  }
  /**
 * \brief asg toggle lego mode
 */
  void Import_obj::asg_toggle_mode_lego(bool p_condition)
  {
    m_mode_lego = p_condition;
  }
  /**
 * \brief req la poz_z
 */
  int Import_obj::req_pos_z() const
  {
    return m_posz;
  }
  /**
 * \brief asg new scaling au model
 */
  void Import_obj::asg_scale(float p_scale)
  {
   m_objectImport.setScale(p_scale, p_scale, p_scale);
   m_width_img = m_width_img * p_scale * 5;
   m_height_img = m_height_img * p_scale * 5;
  }
  /**
 * \brief asg setposition
 */
  void Import_obj::asg_position(float p_x, float p_y, float p_z)
  {
   m_posx = m_posx_lego = p_x;
   m_posy = m_posy_lego = p_y;
   m_posz = m_posz_lego = p_z;
  }
  /**
 * \brief asg la grosseur de la boite de sélection manuellement
 */
  void Import_obj::asg_bounding_size(int p_x, int p_y)
  {
    m_width_img = p_x;
    m_height_img = p_y;
  }
  /**
 * \brief asg la grosseur de la boite de sélection manuellement
 */
  void Import_obj::asg_toggle_lego_lock(bool p_cond)
  {
    m_lego_lock = p_cond;
  }
  const bool Import_obj::get_if_cubemap() const 
  {
      return false;
  }
  void Import_obj::set_shader(int p_shader)
  {
    m_index_shader_select = p_shader;
      m_choi_materiau = -1;
      m_enable_materiel = false;
  }
  void Import_obj::set_filling_color(ofVec3f p_fill_color)
  {
    m_fill_color = p_fill_color;
    m_fill_colorN = m_fill_color.normalized();
  }
  void Import_obj::set_enable_materiel()
  {
    if (m_enable_materiel == false)
    {
      m_enable_materiel = true;
      m_choi_materiau = -1;
      ofLog() << m_enable_materiel;
    }
    else
    {
      m_enable_materiel = false;
      ofLog() << m_enable_materiel;
      }
  }
  void Import_obj::set_texture(int p_texture)
  {

    m_enable_texture = true;
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
      break;
      case 3: 
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

  void Import_obj::set_choix_material(int p_choi)
  {
    m_choi_materiau = p_choi;
  }
  void Import_obj::set_nb_dynamic_light(int p_nbLight)
  {
    m__nb_light_dynamic = p_nbLight;
  }
  void Import_obj::set_pos_dynamic_light(ofVec3f p_pos)
  {
    ofVec3f postmp = m_light.getGlobalPosition();
    postmp += p_pos;
    m_light.setPosition(postmp);
    ofLog() << m_light.getGlobalPosition();
  }

} /*namespace objects_in_scene*/