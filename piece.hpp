#ifndef __PIECE__
#define __PIECE__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class Plateau;	
class Case;
class Partie;
class Coup;
class Joueur;

class Piece{

	protected : 
		int col;
		int ligne;
		int couleur;
		char nom;
		bool premierDep;

	public :
		Piece (int, int , int, char);
		void afficherPiece ();
		char getNom ();
		int getCouleur();
		int getLigne();
		int getCol();
		void setLigne (int);
		void setCol (int);
		bool getPremierDep ();
		void setPremierDep (bool);
		virtual void deplacementPossible (Plateau &, vector <Case*> &) = 0; //etabli liste des déplacements possible dans vector
};

class Tour : public Piece{
	public :
		Tour (int, int, int, char);
		void deplacementPossible (Plateau &, vector <Case*> &);
};

class Cavalier : public Piece{
	public :
		Cavalier (int, int, int, char);
		void deplacementPossible (Plateau &, vector <Case*> &);
		void depValide (Plateau &, vector <Case*> &, int, int);   //permet de factoriser le code
};

class Fou : public Piece{
	public :
		Fou (int, int, int, char);
		void deplacementPossible (Plateau &, vector <Case*> &);
};

class Dame : public Piece{
	public :
		Dame (int, int, int, char);
		void deplacementPossible (Plateau &, vector <Case*> &);
};

class Roi : public Piece{
	public :
		Roi (int, int, int, char);
		void deplacementPossible (Plateau &, vector <Case*> &);
		void setDejaAppeler (bool);
};

class Pion : public Piece{
	public :
		Pion (int, int, int, char);
		void deplacementPossible (Plateau &, vector <Case*> &);
};
	
#endif
	

