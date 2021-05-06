// Cubemap->cpp
// Classe responsable d'importer une image sur la scène

#include "cubeMap.h"

namespace objects_in_scene
{

  /**
 * \brief Constructeur par défaut.
*/

  Cubemap::Cubemap() : Blocs()
  {
  }
  /**
 * \brief Mets toutes les valeurs par défaut de l'image et importe une image en proposant un path selector.
 */
  void Cubemap::setup(string p_path, bool p_obj_du_menu)
  {
    m_close_true = false;

    cube_map_cam.setVFlip(true);
    cube_map_cam.setPosition(0, 0, 0);
    cube_map_cam.lookAt(ofVec3f(0, 0, 0));
    cube_map_light.setPosition(ofVec3f(0, 0, -1100));
    cube_map_light.lookAt(ofVec3f(0, 0, 0));

      m_select_cube = stoi(p_path); // converti en choix de map 

    if (m_select_cube == 0)
    {
      ofLoadImage(imageTexture[0], "../../data/frontbeach.png");
      ofLoadImage(imageTexture[1], "../../data/rightbeach.png");
      ofLoadImage(imageTexture[2], "../../data/backbeach.png");
      ofLoadImage(imageTexture[3], "../../data/leftbeach.png");
      ofLoadImage(imageTexture[4], "../../data/bottombeach.png");
      ofLoadImage(imageTexture[5], "../../data/topbeach.png");
    }
    if (m_select_cube == 1)
    {
      ofLoadImage(imageTexture[0], "../../data/nebulafront.png");
      ofLoadImage(imageTexture[1], "../../data/nebularight.png");
      ofLoadImage(imageTexture[2], "../../data/nebulaback.png");
      ofLoadImage(imageTexture[3], "../../data/nebulaleft.png");
      ofLoadImage(imageTexture[4], "../../data/nebulabottom.png");
      ofLoadImage(imageTexture[5], "../../data/nebuletop.png");
    }
    if (m_select_cube == 2)
    {
      ofLoadImage(imageTexture[0], "../../data/rockfront.png");
      ofLoadImage(imageTexture[1], "../../data/rockright.png");
      ofLoadImage(imageTexture[2], "../../data/rockback.png");
      ofLoadImage(imageTexture[3], "../../data/rockleft.png");
      ofLoadImage(imageTexture[4], "../../data/rockbottom.png");
      ofLoadImage(imageTexture[5], "../../data/rocktop.png");
    }
    if (m_select_cube == 3)
    {
      ofLoadImage(imageTexture[0], "../../data/plainefront.png");
      ofLoadImage(imageTexture[1], "../../data/plaineright.png");
      ofLoadImage(imageTexture[2], "../../data/plaineback.png");
      ofLoadImage(imageTexture[3], "../../data/plaineleft.png");
      ofLoadImage(imageTexture[4], "../../data/plainebottom.png");
      ofLoadImage(imageTexture[5], "../../data/plainetop.png");
    }
    if (m_select_cube == 4)
    {
      ofLoadImage(imageTexture[0], "../../data/smoothfront.png");
      ofLoadImage(imageTexture[1], "../../data/smoothright.png");
      ofLoadImage(imageTexture[2], "../../data/smoothback.png");
      ofLoadImage(imageTexture[3], "../../data/smoothleft.png");
      ofLoadImage(imageTexture[4], "../../data/smoothbottom.png");
      ofLoadImage(imageTexture[5], "../../data/smoothtop.png");
    }
    points[0].x = -4096;
    points[0].y = -4096;
    points[0].z = 4096;

    points[1].x = 4096;
    points[1].y = -4096;
    points[1].z = 4096;

    points[2].x = 4096;
    points[2].y = 4096;
    points[2].z = 4096;

    points[3].x = -4096;
    points[3].y = 4096;
    points[3].z = 4096;

    points[4].x = -4096;
    points[4].y = -4096;
    points[4].z = -4096;

    points[5].x = 4096;
    points[5].y = -4096;
    points[5].z = -4096;

    points[6].x = 4096;
    points[6].y = 4096;
    points[6].z = -4096;

    points[7].x = -4096;
    points[7].y = 4096;
    points[7].z = -4096;



    // points[0].y = 0;
    // points[0].z = 0;

    // points[1].x = 256;
    // points[1].y = 0;
    // points[1].z = 0;

    // points[2].x = 256;
    // points[2].y = 256;
    // points[2].z = 0;

    // points[3].x = 0;
    // points[3].y = 256;
    // points[3].z = 0;

    // points[4].x = 0;
    // points[4].y = 0;
    // points[4].z = -256;

    // points[5].x = 256;
    // points[5].y = 0;
    // points[5].z = -256;

    // points[6].x = 256;
    // points[6].y = 256;
    // points[6].z = -256;

    // points[7].x = 0;
    // points[7].y = 256;
    // points[7].z = -256;
    // m_cube_scale = ofGetWindowWidth() / m_images[0].getWidth();

  }

  /**
 * \brief On rends l'image au (milieu, 400), on tace un contour sélectif, on affiche un X au coin supérieur gauche
 * et une option de redimension au bas droite de la barre contour de sélection.
 */
  void Cubemap::show_obj()
  {

    // cube_map_light.enable();
    cube_map_cam.begin();


    ofPushMatrix();


    // ofTranslate(-(imageTexture[0].getWidth() / 2) * 4, -(imageTexture[0].getHeight() / 2) * 4, (imageTexture[0].getHeight() / 2 * 4));

    ofTranslate(0, 0, 0);
    // ofScale(1);
    imageTexture[0].draw(points[4], points[5],points[6], points[7]); // Front
    imageTexture[1].draw(points[5], points[1],points[2], points[6]);  //right
    imageTexture[2].draw(points[1], points[0],points[3], points[2]);  //back
    imageTexture[3].draw(points[0], points[4],points[7], points[3]);  //left
    imageTexture[4].draw(points[7], points[6],points[2], points[3]);  //bottom
    imageTexture[5].draw(points[0], points[1],points[5], points[4]);  //top


      
    ofPopMatrix();



    cube_map_cam.end();
    // cube_map_light.disable();


    


    // ofPushMatrix();
    //   ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    //   ofBox(300);
    // ofPopMatrix();
    // ofPushMatrix();
    // // ofTranslate(ofGetWindowWidth() / 2 - m_images[0].getWidth() / 2, ofGetWindowHeight() / 2 -  m_images[0].getHeight() / 2);
    // // ofScale(m_cube_scale, m_cube_scale, m_cube_scale);
    // ofTranslate(0, 0, -100);
    
    //   m_images[0].draw(0,0,0);

    //   m_images[1].rotate90(1);
    //   m_images[1].draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    // ofPopMatrix();
  }


  /**
 * \brief retourne si l'objet doit être fermé
 * \return string de l'electeur formaté
 */
  bool Cubemap::req_close_true() const
  {
    return m_close_true;
  }

    void Cubemap::set_close_true()
    {
      m_close_true = true;
    }

  void Cubemap::move_obj(int p_x, int p_y, int p_z, int p_button)
    {
      cube_map_cam.panDeg(p_x);

      cube_map_cam.tiltDeg(p_y);

      cube_map_cam.dolly(p_z / 5);

      cube_map_cam.truck(p_button);

    }

  /**
 * \brief retourne si l'image est sélectionnée
 * \return string de l'electeur formaté
 */
  bool Cubemap::req_image_selected() const
  {
    return false;
  }
  /**
 * \brief req la poz_z
 */
  int Cubemap::req_pos_z() const
  {
    return false;
  }
    const bool Cubemap::get_if_cubemap() const 
    {
        return true;
    }


} /*namespace objects_in_scene*/