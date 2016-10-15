#ifndef __JOUEUR__
#define __JOUEUR__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Piece;
class Case;
class PLateau;
class Coup;
class Partie;


class Joueur{
	protected :
		int couleur;
		int score;

	public :
		Joueur (int, int);
		int getCouleur ();
		int getScore ();
		void setCouleur (int);
		void setScore (int);
		void demande_verif_creer_Coup (Plateau &, vector <Coup*> &);
};

#endif
