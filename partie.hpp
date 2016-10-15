#ifndef __PARTIE__
#define __PARTIE__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class PLateau;
class Piece;
class Case;
class Joueur;

class Coup{
	
	protected :
		Case* depart;     		
		Case* arrive;

	public :
		Coup (Case*, Case*);
		void jouerCoup (Plateau &, vector <Coup*> &, vector <Piece*> &, vector <Piece*> &, int &, int &);
		void promotion ();	//entraine  bug si partie restaurée contient une promotion
		Case* getDepart ();
		Case* getArrive ();
};


class Partie{
	protected :
		Plateau P;
		vector <Coup*> coupsJoues;		//permet de joues et d'enregistrer la partie
		vector <Piece*> blanchesPrises;
		vector <Piece*> noiresPrises;
		int blanche;  //verifie si blanche prise au dernier coup
		int noire;    //verifie si noire prise au dernier coup

	public :
		Partie ();
		void Menu ();	
		void jouerPartie (Joueur &, Joueur &);
		void afficherPrises ();
		void abandon ();		//non-active pour fluidifier la partie
		void rechercheRoi ( Joueur &, Piece* & );
		bool verif_etatPartie (Joueur &);
		bool verifPat (Joueur &);
		bool verifEchec (Joueur &);
		bool verifMat (Joueur &);
		void enregistrerCoup ();
		void restaurePartie (Joueur &, Joueur &);
		void annuleCoup ();
};
#endif
