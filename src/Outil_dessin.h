/**
 * \file Outil_dessin.h
 * \brief Classe responsable de transformer les outils de dessin: �paisseur de ligne, couleur de ligne, couleur du remplissage et couleur du background
 * \author Jonathan B�dard
 * \version 2.0
 */

#pragma once
#include "ofMain.h"

/**
  * \class Outil_dessin
  * \brief Classe responsable de transformer les outils de dessin
  *	
  *     ---  Utilisation  ---
  * Inclure le Outil_dessin.h dans votre fichier
  * Cr�er une instance   ex:  Outil_dessin outil;  * 
  * Utiliser outil.req_LineWidth() pour acc�der � l'�paisseur de la ligne
  * Utiliser outil.req_lineColor(int index) index 0 pour R, index 1 pour G, index 2 pour B.
  * Utiliser outil.req_colorFilling(int index) index 0 pour R, index 1 pour G, index 2 pour B.
  * 
  * 
  * Exemple ---
  * Outil_dessin outil;
  * ofSetColor(outil.req_lineColor(0), outil.req_lineColor(1), outil.req_lineColor(2));
  * 
  * 
  * Remarque!  Les attribus seront le m�mes dans toutes les instances.
  */

class Outil_dessin
{
public:
  int req_LineWidth() const;
  int req_lineColor(int index) const;
  int req_colorFilling(int index) const;

  void set_LineWidth(int val);
  void set_lineColor(int index, int val);
  void set_colorFilling(int index, int val);

private:
  static int lineWitdh;
  static int lineColor[3];
  static int colorFilling[3];
};
