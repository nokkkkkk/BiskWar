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
    m_bloc_angle = 0;



    m_close_true = false;       //Est-ce que on doit detruire l'objet ?
    vitesse_rotation = 0.5;
    m_image_selected = false;
    m_toggle_x_rotation = false;
    m_toggle_y_rotation = false;
    m_toggle_z_rotation = false;
    string path;
    
    if (p_path == "") //Affiche et prélève le path de l'image à importer ou hardcodé selon le cas.
      {
        m_path_fichier_img = ofSystemLoadDialog("Load file");
        path = m_path_fichier_img.getPath(); //On récupère le path
        m_path_name = path;

      }
    else{ //Soi le path est hardcodé
        path = m_path_name = p_path;
    }

    if (true) //Si l'ouverture du fichier est un succès:
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
        m_model_matrix = m_objectImport.getModelMatrix();
        m_scaling = m_model_matrix.getScale();
        //On laod l'image avec le path
        m_width_img = m_original_m_width_img = (m_model_max_x - m_model_min_x) * m_scaling.x * 0.25; //on enregistre la taille en widht et height + on copie un original qui sert à la redimension.
        m_height_img = m_original_m_height_img = (m_model_max_y - m_model_min_y) * m_scaling.y * 0.25;
      }
      else
      {
        m_close_true = true;
      }

      m_x_scale = 1;
      m_y_scale = 1;
      m_z_scale = 1;
      m_posx = ofGetWindowWidth() / 2 - 250 / 2 + ofRandom(300) - ofRandom(400); //On affiche la nouvelle image aleatoire
      m_posy = 0;                              //On alligne l'image à 400 pixels de hauteur.
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
    
      m_objectImport.setScale(m_x_scale * 0.1, m_y_scale * 0.1, m_z_scale * 0.1);
   


    if (!m_image_redim_selected)
    {
     
      m_objectImport.drawFaces(); //on affiche l'image en (milieu,400) de grosseur native.
      // ofLog() << m_posx + m_width_img / 2 << "YYYYYYYYYYYYYYYYYY : " <<  m_posy + m_height_img / 2 << "ZZZZZ : " << m_posz;

    
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
        ofSetColor(0, 100, 20);
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
    // if (m_mouse_move_image == true && m_image_redim_selected == false) //SI nous avons activé le déplacement d'image....
    // {
      m_posx += p_x;
      m_posy += p_y;
      m_posz = p_z;
    // }
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
      m_bloc_angle += angle;
      m_objectImport.setRotation(which, m_bloc_angle, rot_x, rot_y, r_z);
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
 * \brief retourne si l'image est sélectionnée
 * \param selected Définit l'attribut à true ou false.
 */
  void Import_obj::asg_image_selected(bool p_selected)
  {
    m_image_selected = p_selected;
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
  }
  const bool Import_obj::get_if_cubemap() const 
  {
      return false;
  }
  void Import_obj::set_filling_color(ofVec3f p_fill_color)
  {
  }
  void Import_obj::set_enable_materiel()
  {
  }
  void Import_obj::set_texture(int p_texture)
  {
  }

  void Import_obj::set_choix_material(int p_choi)
  {
  }
  void Import_obj::set_nb_dynamic_light(int p_nbLight)
  {
  }
  void Import_obj::set_pos_dynamic_light(ofVec3f p_pos)
  {
  }

} /*namespace objects_in_scene*/