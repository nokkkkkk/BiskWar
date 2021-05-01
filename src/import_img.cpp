// import_img->cpp
// Classe responsable d'importer une image sur la scène

#include "import_img.h"

namespace objects_in_scene
{

  /**
 * \brief Constructeur par défaut.
*/

  Import_img::Import_img() : Instance_Imported()
  {
  }
  /**
 * \brief Mets toutes les valeurs par défaut de l'image et importe une image en proposant un path selector.
 */
  void Import_img::setup(string p_path, bool p_obj_du_menu)
  {
    m_rotx = 0;
    m_roty = 0;
    m_rotz = 0;
    m_close_true = false;       //Est-ce que on doit detruire l'objet ?
    m_mouse_move_image = false; //Bool qui vérifie si on doit bouger l'image.
    m_image_selected = false;
    m_image_redim_selected = false;
    m_path_fichier_img = ofSystemLoadDialog("Load file"); //Affiche et prélève le path de l'image à importer.
    if (m_path_fichier_img.bSuccess)                      //Si l'ouverture du fichier est un succès:
    {
      string path = m_path_fichier_img.getPath(); //On récupère le path
      m_path_name = path;
      m_imageImport.load(path);                                        //On laod l'image avec le path
      m_width_img = m_original_m_width_img = m_imageImport.getWidth(); //on enregistre la taille en widht et height + on copie un original qui sert à la redimension.
      m_height_img = m_original_m_height_img = m_imageImport.getHeight();
      m_posx = ofGetWindowWidth() / 2 - m_imageImport.getWidth() / 2 + ofRandom(300) - ofRandom(600); //On affiche la nouvelle image au milieu de la scène,
      m_posy = 400 + ofRandom(300) - ofRandom(600);                                                   //On alligne l'image à 400 pixels de hauteur.
      m_image_selected = true;                                        //Bool : Par défaut la sélection est à true donc on affiche
      m_redim_box_height = 10;                                        //Hauteur de la zone de redimensionnage de l'image.
      m_redim_box_width = 10;                                         //Largeur de la zone de redimensionnage de l'image.
      m_close_box_height = 13;                                        //Hauteur de la zone de destruction de l'image.
      m_close_box_width = 13;                                         //Largeur de la zone de destruction de l'image.
    }
    else
    {
      m_close_true = true;
    }
  m_choix_filtre = 0;
  m_nb_choix_filtre = 5;
    // chargement du code source des shaders
  shader_passthrough.load(
    "image_passthrough_330_vs.glsl",
    "image_passthrough_330_fs.glsl");

  shader_off_red.load(
    "image_invert_330_vs.glsl",
    "image_invert_330_fs.glsl");
    
  shader_grayscale.load(
  "image_gray_330_vs.glsl",
  "image_gray_330_fs.glsl");
    
  shader_off_blue.load(
  "image_off blue_330_vs.glsl",
  "image_off blue_330_fs.glsl");
    
  shader_off_green.load(
  "image_offgreen_330_vs.glsl",
  "image_offgreen_330_fs.glsl");


  // shader actif au lancement de l'application
  shader = shader_passthrough;
  }

  /**
 * \brief On rends l'image au (milieu, 400), on tace un contour sélectif, on affiche un X au coin supérieur gauche
 * et une option de redimension au bas droite de la barre contour de sélection.
 */
  void Import_img::show_obj()
  {
    switch (m_choix_filtre)
    {
      case 0: 
        shader = shader_passthrough;
      break;
      case 1: 
        shader = shader_grayscale;
      break;
      case 2: 
        shader = shader_off_red;
      break;
      case 3: 
        shader = shader_off_blue;
      break;
      case 4: 
        shader = shader_off_green;
      break;
    }
    m_show_select();
    ofPushMatrix();
    ofTranslate(m_posx + m_imageImport.getWidth() / 2, m_posy + m_imageImport.getHeight() / 2); //move pivot to centre
    ofRotateXDeg(m_rotx);
    ofRotateYDeg(m_roty);
    ofRotateZDeg(m_rotz);
    ofPushMatrix();
    ofTranslate(-m_imageImport.getWidth() / 2, -m_imageImport.getHeight() / 2); //move back by the centre offset
    
      shader.begin();
      shader.setUniformTexture("image", m_imageImport.getTexture(), 1);
        m_imageImport.draw(0, 0, m_width_img, m_height_img);
      shader.end();
    ofPopMatrix();
    ofPopMatrix(); //on affiche la zone de sélection autour de l'image importée.
        // m_imageImport.draw(m_posx, m_posy, m_width_img, m_height_img);        //on affiche l'image en (milieu,400) de grosseur native.
  }
  void Import_img::m_show_select()
  {
    if (m_image_selected) //Si l'image est sélectionnée.
    {
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
    }
  }

  /**
 * \brief Sélectionne l'objet et enregistre les coordo du clic. Les bool redim, move, close sont ajuster en conséquence de la zone du clic
 */
  void Import_img::select_obj(int p_x, int p_y, int p_button)
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
  void Import_img::move_obj(int p_x, int p_y, int p_z, int p_button)
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
  void Import_img::redim_obj(int p_x, int p_y, int p_button)
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
  bool Import_img::req_close_true() const
  {
    return m_close_true;
  }
  /**
 * \brief retourne si l'image est sélectionnée
 * \return string de l'electeur formaté
 */
  bool Import_img::req_image_selected() const
  {
    return m_image_selected;
  }
  /**
 * \brief retourne la textu enable
 * \return exture de l'image
 */
  ofTexture Import_img::req_texture() const 
  {
    return m_imageImport.getTexture();
  }
  /**
 * \brief retourne si l'image est sélectionnée
 * \param selected Définit l'attribut à true ou false.
 */
  void Import_img::asg_image_selected(bool p_selected)
  {
    m_image_selected = p_selected;
  }
  /**
 * \brief change le filtre
 */
  void Import_img::asg_choix_filtre()
  {
    if (m_choix_filtre < m_nb_choix_filtre - 1)
      m_choix_filtre = m_choix_filtre + 1;
    else
      m_choix_filtre = 0;

  }

  /**
 * \brief rotation de l'objet
 */
  void Import_img::rotate_obj(int which, float angle, float rot_x, float rot_y, float r_z)
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
  void Import_img::resetMouse(int p_x, int p_y, int p_button)
  {
    m_mouse_move_image = false; //Quand on relâche le bouton de la souris, on désactive le déplacement et la redimension.
    m_image_redim_selected = false;

    m_original_m_width_img = m_width_img;   //Réafectation de la nouvelle grosseur de l'image(Originale avant transfo) pour la prochaine transformation
    m_original_m_height_img = m_height_img; //Cet attribut est nécessaire pour le calcul de la grosseur en fonction de la souris dans mouseDragged(...).
  }
  /**
 * \brief Retourn le pathName de l'image.
 */
  const string Import_img::getPathName() const
  {
    return m_path_name;
  }
  /**
 * \brief req la poz_z
 */
  int Import_img::req_pos_z() const
  {
    return 0;
  }
  const bool Import_img::get_if_cubemap() const 
  {
      return false;
  }

} /*namespace objects_in_scene*/