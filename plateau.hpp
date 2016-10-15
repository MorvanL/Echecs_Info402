#ifndef __PLATEAU__
#define __PLATEAU__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Piece;
class Joueur;
class Partie;
class Coup;

class Case{
	
	protected :
		Piece *p;
		int couleur;
		int col;
		int ligne;
		
	public :
		Case (int, int, int, Piece* = NULL);
		void setP (Piece* = NULL);
		Piece* getP ();
		int getLigne ();
		int getCol ();
		int getCouleur ();
		void afficherCase ();
		
};

class Plateau{
	
	protected :
		Case* plat[8][8];  

	public :
		Plateau ();
		void afficherPlateau ();
		Case* getPlatIJ (int, int);	//renvoie un pointeur sur la case de la ligne I et de la colonne J
		Case getCaseIJ (int, int);	//renvoie  la case de la ligne I et de la colonne J
};

#endif
