#include "Outil_dessin.h"

int Outil_dessin::req_LineWidth() const
{
	return lineWitdh;
}

int Outil_dessin::req_lineColor(int index) const
{
	return lineColor[index];
}

int Outil_dessin::req_colorFilling(int index) const
{
	return colorFilling[index];
}

void Outil_dessin::set_LineWidth(int val)
{
	if (val >= 1 && val <= 50)
		lineWitdh = val; // S'assure que les valeurs entr�es correspondent aux valeurs attendues
	else
		cout << "La valeur de la ligne ne doit etre contenue entre 1 et 10 " << endl; // Dans le cas contraire, un message d'erreur est envoy�
} // Ps. En absence de valeur, la valeur par d�fault sera prise

void Outil_dessin::set_lineColor(int index, int val)
{
	if (index >= 0 && index <= 3 && val >= 0 && val <= 255)
		lineColor[index] = val; // S'assure que les valeurs entr�es correspondent aux valeurs attendues
	else
		cout << "Index entre 0 et 3. valeur entre 0 et 255" << endl; // Dans le cas contraire, un message d'erreur est envoy�
																	 // Ps. En absence de valeur, la valeur par d�fault sera prise
}

void Outil_dessin::set_colorFilling(int index, int val)
{
	if (index >= 0 && index <= 3 && val >= 0 && val <= 255)
		colorFilling[index] = val; // S'assure que les valeurs entr�es correspondent aux valeurs attendues
	else
		cout << "Index entre 0 et 3. valeur entre 0 et 255" << endl; // Dans le cas contraire, un message d'erreur est envoy�
} // Ps. En absence de valeur, la valeur par d�fault sera prise

//   D�claration des variables statiques
int Outil_dessin::lineWitdh = 1;
int Outil_dessin::colorFilling[3] = {255, 255, 255};
int Outil_dessin::lineColor[3] = {255, 255, 255};
