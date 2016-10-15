#include "plateau.hpp"
#include "piece.hpp"

//Case
//constructeur / destructeur
Case::Case (int ligne, int col, int couleur, Piece *p){
	this->ligne = ligne;
	this->col = col;      
	this->couleur = couleur;
	this->p = p;
}

//setters / getters
void Case::setP (Piece* p){
	this->p = p;
}

Piece* Case::getP (){
	return p;
}

int Case::getLigne (){
	return ligne;	
}

int Case::getCol (){
	return col;	
}

int Case::getCouleur (){
	return couleur;	
}

//affichage
void Case::afficherCase (){         // "0" pour blanc (minuscules), "1" pour noir (majuscules)
	if(p == NULL){
		cout<<"-  ";	
	}
	if(p != NULL){
		p->afficherPiece();
	}
}


//Plateau
//constructeur
Plateau::Plateau (){
	int i;
	int j;
	for (i=0; i<=7; i++) {				//création des cases
		for (j=0; j<=7; j++) {
			if ( (i+j)%2 == 0) {				//cases blanches 
				plat[i][j] = new Case(i, j, 0, NULL);
			}
			if ( (i+j)%2 == 1) {				//cases noires
				plat[i][j] = new Case(i, j, 1, NULL);    
			}
		}
	}
	for (i=0; i<=7; i++) {				//assignation des pieces aux cases
		for (j=0; j<=7; j++) {
			if( i==0 ){
				if( j==0 || j==7){
					plat[i][j]->setP(new Tour(i, j, 1, 'T'));
				}
				if( j==1 || j==6){
					plat[i][j]->setP(new Cavalier(i, j, 1, 'C'));
				}
				if( j==2 || j==5){
					plat[i][j]->setP(new Fou(i, j, 1, 'F'));
				}
				if( j==3){
					plat[i][j]->setP(new Dame(i, j, 1, 'D'));
				}
				if( j==4){
					plat[i][j]->setP(new Roi(i, j, 1, 'R'));
				}
			}
			if( i==1 ){
				plat[i][j]->setP(new Pion(i, j, 1, 'P'));
			}
			if( i==6 ){
				plat[i][j]->setP(new Pion(i, j, 0, 'p'));
			}
 			if( i==7 ){
				if( j==0 || j==7){
					plat[i][j]->setP(new Tour(i, j, 0, 't'));
				}
				if( j==1 || j==6){
					plat[i][j]->setP(new Cavalier(i, j, 0, 'c'));
				}
				if( j==2 || j==5){
					plat[i][j]->setP(new Fou(i, j, 0, 'f'));
				}
				if( j==3){
					plat[i][j]->setP(new Dame(i, j, 0, 'd'));
				}
				if( j==4){
					plat[i][j]->setP(new Roi(i, j, 0, 'r'));
				}
			}
		}
	}
	
}

//getters / setters
Case* Plateau::getPlatIJ (int ligne, int col){
	return (plat[ligne][col]);
}

Case Plateau::getCaseIJ (int ligne, int col){
	return *(plat[ligne][col]);
}
	 
//affichage
void Plateau::afficherPlateau(){
	int i;
	int j;
	cout<< "    0  " << "1  "<<"2  "<<"3  " << "4  "<<"5  "<<"6  "<<"7"<<endl;
	for (i=0; i<=7; i++) {
		cout <<endl;
		cout <<i<< "   ";
		for (j=0; j<=7; j++) {			
			plat[i][j]->afficherCase();
		}
	}
	cout <<endl;
}

