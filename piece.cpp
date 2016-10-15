#include "piece.hpp"
#include "plateau.hpp"

//Piece
//constructeurs / destructeur
Piece::Piece (int ligne, int col, int couleur, char nom){
	this->ligne = ligne;
	this->col = col; 
	this->couleur = couleur;
	this->nom = nom;
	premierDep = true;
}


//affichage
void Piece::afficherPiece (){
	cout << nom <<"  ";
}


// getters / setters
int Piece::getCouleur (){
	return couleur;
}

int Piece::getLigne (){
	return ligne;
}

int Piece::getCol(){
	return col;
}

char Piece::getNom (){
	return nom;
}

void Piece::setLigne (int l){
	ligne = l;
}

void Piece::setCol (int c){
	col = c;
}

bool Piece::getPremierDep (){
	return premierDep;
}

void Piece::setPremierDep (bool premierDep){
	this->premierDep = premierDep;
}




//Tour
//constructeur 
Tour::Tour (int col, int ligne, int couleur, char nom) : Piece(col, ligne, couleur, nom){}

//méthodes
void Tour::deplacementPossible (Plateau & P, vector <Case*> &v) {
	int i, j;
	int valide = 0;                         //vérifie le nombre de pièces rencontrées lors du déplacement
	i = ligne+1; 
	while( i<8  &&  valide == 0 ){			//test case vers le bas tant qu'il n'y a pas d'obstacle
		if( P.getCaseIJ(i, col).getP() != NULL ){ 	//si case en-dessous est non vide
			if( (P.getCaseIJ(i,col).getP())->getCouleur() != this->couleur ){    // si cas en-dessous contient une piece adverse
				v.push_back(P.getPlatIJ(i, col));	//dep sur cette case est possible
				valide = 1;				//on ne regarde pas les cases suivantes
			}
			else{					//si case en-dessous contient une piece amie
				valide = 1;	
			}
		}
		else{				//si case en-dessous est vide
			v.push_back(P.getPlatIJ(i, col));	//dep sur cette case est possible
		}
		i++;
	}
	valide = 0;
	i = ligne-1;
	while( i>=0  &&  valide == 0 ){  	//vers le haut
		if( P.getCaseIJ(i, col).getP() != NULL ){
			if( (P.getCaseIJ(i,col).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, col));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, col));
		}
		i--;
	}
	valide = 0;
	j = col+1;
	while( j<8  &&  valide == 0 ){	    	//vers la droite
		if( P.getCaseIJ(ligne, j).getP() != NULL ){
			if( (P.getCaseIJ(ligne, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(ligne, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(ligne, j));
		}
		j++;
	}
	valide = 0;
	j = col-1;
	while( j>=0  &&  valide == 0 ){		//vers la gauche
		if( P.getCaseIJ(ligne, j).getP() != NULL ){
			if( (P.getCaseIJ(ligne, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(ligne, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(ligne, j));
		}
		j--;
	}
}

//Cavalier
//constructeur 
Cavalier::Cavalier (int col, int ligne, int couleur, char nom) : Piece(col, ligne, couleur, nom){}

//méthodes
void Cavalier::deplacementPossible (Plateau & P, vector <Case*> &v) {
	int i, j;
	if( (i=ligne+2)<8 && (j=col+1)<8 ){          //premiere des 8 cases possiblement atteignable
		(*this).depValide(P, v, i, j);		//verifie cette caseetablir conjugaison
	}
	if( (i=ligne+2)<8 && (j=col-1)>=0 ){
		(*this).depValide(P, v, i, j);
	}
	if( (i=ligne-2)>=0 && (j=col+1)<8 ){
		(*this).depValide(P, v, i, j);
	}
	if( (i=ligne-2)>=0 && (j=col-1)>=0 ){
		(*this).depValide(P, v, i, j);
	}
	if( (i=ligne+1)<8 && (j=col+2)<8 ){
		(*this).depValide(P, v, i, j);
	}
	if( (i=ligne-1)>=0 && (j=col+2)<8 ){
		(*this).depValide(P, v, i, j);
	}
	if( (i=ligne+1)<8 && (j=col-2)>=0 ){
		(*this).depValide(P, v, i, j);
	}
	if( (i=ligne-1)>=0 && (j=col-2)>=0 ){
		(*this).depValide(P, v, i, j);
	}
}

void Cavalier::depValide (Plateau & P, vector <Case*> &v, int ligne, int col){
	if( P.getCaseIJ(ligne,col).getP() != NULL ){	//si case non vide 
		if( (P.getCaseIJ(ligne,col).getP())->getCouleur() != this->couleur ){	//si case contient piece ennemie
			v.push_back(P.getPlatIJ(ligne, col));		//dep possible
		}
	}
	else{						//si case vide
		v.push_back(P.getPlatIJ(ligne, col));	//dep possible
	}
}

//Fou
//constructeur 
Fou::Fou (int col, int ligne, int couleur, char nom) : Piece(col, ligne, couleur, nom){}


//méthodes
void Fou::deplacementPossible (Plateau & P, vector <Case*> &v) {
	int i, j;
	int valide = 0;
	i = ligne+1; 
	j = col+1;
	while( i<8  &&  j<8  &&  valide == 0 ){		//test premiere diagonale tant qu'aucun obstacle n'est rencontré
		if( P.getCaseIJ(i, j).getP() != NULL ){		//si case non vide 
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){     //si case contient piece ennemie
				v.push_back(P.getPlatIJ(i, j));  	//dep possible
				valide = 1;				//on ne regarde pas les cases suivantes
			}
			else{				//si case contient piece amie	
				valide = 1;			//on ne regarde pas les cases suivantes
			}
		}
		else{						//si case vide
			v.push_back(P.getPlatIJ(i, j));			//dep valide
		}
		i++;
		j++;
	}
	i = ligne+1; 
	j = col-1;
	valide = 0;
	while( i<8  &&  j>=0  &&  valide == 0 ){
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i++;
		j--;
	}
	i = ligne-1; 
	j = col-1;
	valide = 0;
	while( i>=0  &&  j>=0  &&  valide == 0 ){
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i--;
		j--;
	}
	i = ligne-1; 
	j = col+1;
	valide = 0;
	while( i>=0  &&  j<8  &&  valide == 0 ){
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i--;
		j++;
	}
}

//Dame
//constructeur 
Dame::Dame (int col, int ligne, int couleur, char nom) : Piece(col, ligne, couleur, nom){}

//méthodes
void Dame::deplacementPossible (Plateau & P, vector <Case*> &v) {
	int i, j;
	int valide = 0;
	i = ligne+1; 
	j = col+1;
	while( i<8  &&  j<8  &&  valide == 0 ){			//deplacement de Fou
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i++;
		j++;
	}
	i = ligne+1; 
	j = col-1;
	valide = 0;
	while( i<8  &&  j>=0  &&  valide == 0 ){
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i++;
		j--;
	}
	i = ligne-1; 
	j = col-1;
	valide = 0;
	while( i>=0  &&  j>=0  &&  valide == 0 ){
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i--;
		j--;
	}
	i = ligne-1; 
	j = col+1;
	valide = 0;
	while( i>=0  &&  j<8  &&  valide == 0 ){
		if( P.getCaseIJ(i, j).getP() != NULL ){
			if( (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, j));
		}
		i--;
		j++;
	}
					//deplacement de Tour
	valide = 0;                         
	i = ligne+1; 
	while( i<8  &&  valide == 0 ){			
		if( P.getCaseIJ(i, col).getP() != NULL ){
			if( (P.getCaseIJ(i,col).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, col));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, col));
		}
		i++;
	}
	valide = 0;
	i = ligne-1;
	while( i>=0  &&  valide == 0 ){
		if( P.getCaseIJ(i, col).getP() != NULL ){
			if( (P.getCaseIJ(i,col).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(i, col));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(i, col));
		}
		i--;
	}
	valide = 0;
	j = col+1;
	while( j<8  &&  valide == 0 ){
		if( P.getCaseIJ(ligne, j).getP() != NULL ){
			if( (P.getCaseIJ(ligne, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(ligne, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(ligne, j));
		}
		j++;
	}
	valide = 0;
	j = col-1;
	while( j>=0  &&  valide == 0 ){
		if( P.getCaseIJ(ligne, j).getP() != NULL ){
			if( (P.getCaseIJ(ligne, j).getP())->getCouleur() != this->couleur ){
				v.push_back(P.getPlatIJ(ligne, j));
				valide = 1;
			}
			else{
				valide = 1;	
			}
		}
		else{
			v.push_back(P.getPlatIJ(ligne, j));
		}
		j--;
	}
}

//Roi
//constructeur 
Roi::Roi (int col, int ligne, int couleur, char nom) : Piece(col, ligne, couleur, nom){}

//méthodes
void Roi::deplacementPossible (Plateau & P, vector <Case*> &v) { 
	unsigned int i, j;
	int valide = 0;
	bool roque = true;
	vector <Case*> estEchec;		//contient tout les dep adverses possible
		//permet d'ignorer les deplacements lorsqu'appeler par le roi adverse car inoffensif de tout		
		for(i=0; i<8; i++){		//calcul de tout les dep adverses possible
			for(j=0; j<8; j++){
				if( P.getCaseIJ(i, j).getP() != NULL  &&  (P.getCaseIJ(i, j).getP())->getCouleur() != this->couleur ){
					if( P.getCaseIJ(i, j).getP()->getNom() != 'r'  &&  P.getCaseIJ(i, j).getP()->getNom() != 'R'){
						(P.getCaseIJ(i, j).getP())->deplacementPossible(P, estEchec);
					}
				}
			}
		}
		if( premierDep == true ){ 
			if( P.getCaseIJ(ligne, 7).getP() != NULL ){
				if( (P.getCaseIJ(ligne, 7).getP())->getNom() == 't'  ||  (P.getCaseIJ(ligne, 7).getP())->getNom() == 'T' ){
					if( (P.getCaseIJ(ligne, 7).getP())->getPremierDep() == true ){
						i = 1;
						while ( col+i < 7 && roque == true ){
							if( P.getCaseIJ(ligne, col+i).getP() != NULL ){
								roque = false;
							}
							i++;
						}
						for(i=0; i<3; i++){
							j = 0;
							while( j < estEchec.size()  &&  roque == true ){
								if( estEchec[j] == P.getPlatIJ(ligne, col+i) ){
									roque = false;
								}
								j++;
							}
						}
						if( roque == true ){
							v.push_back(P.getPlatIJ(ligne, col+2));
						}
					}
				}
			}
			roque = true;
			if( P.getCaseIJ(ligne, 0).getP() != NULL ){
				if( (P.getCaseIJ(ligne, 0).getP())->getNom() == 't'  ||  (P.getCaseIJ(ligne, 0).getP())->getNom() == 'T' ){
					if( (P.getCaseIJ(ligne, 0).getP())->getPremierDep() == true ){
						i = 1;
						while ( col-i > 0  &&  roque == true ){
							if( P.getCaseIJ(ligne, col-i).getP() != NULL ){
								roque = false;
							}
							i++;
						}
						for(i=0; i<3; i++){
							j = 0;
							while( j < estEchec.size()  &&  roque == true ){
								if( estEchec[j] == P.getPlatIJ(ligne, col-i) ){
									roque = false;
								}
								j++;
							}
						}
						if( roque == true ){
							v.push_back(P.getPlatIJ(ligne, col-2));
						}	
					}
				}
			}
		}
		i = 0;
		if( ligne+1<8 ){		//premiere des 8 cases possiblement atteignables
			if( P.getCaseIJ(ligne+1, col).getP() == NULL  ||  (P.getCaseIJ(ligne+1, col).getP())->getCouleur() != this->couleur ){	//si case vide ou contient piece ennemie
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne+1, col) ){		//si case est dans les dep ennemie (mise en echec)
						valide = 1;				//dep non valide
					}
					i++;
				}
				if( valide == 0 ){		//sinon
					v.push_back(P.getPlatIJ(ligne+1, col) ); 	//dep valide
				}
			}
		}
		i = 0;
		valide = 0;
		if( ligne-1>=0 ){
			if( P.getCaseIJ(ligne-1, col).getP() == NULL  ||  (P.getCaseIJ(ligne-1, col).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne-1, col) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne-1, col) );
				}
			}
		}
		i = 0;
		valide = 0;
		if( col+1<8 ){ 
			if( P.getCaseIJ(ligne, col+1).getP() == NULL  ||  (P.getCaseIJ(ligne, col+1).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne, col+1) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne, col+1) );
				}
			}
		}
		i = 0;
		valide = 0;
		if( col-1>=0 ){ 
			if( P.getCaseIJ(ligne, col-1).getP() == NULL  ||  (P.getCaseIJ(ligne, col-1).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne, col-1) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne, col-1) );
				}
			}
		}
		i = 0;
		valide = 0;
		if( col-1>=0 && ligne-1>=0){ 
			if( P.getCaseIJ(ligne-1, col-1).getP() == NULL  ||  (P.getCaseIJ(ligne-1, col-1).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne-1, col-1) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne-1, col-1) );
				}
			}
		}
		i = 0;
		valide = 0;
		if( col-1>=0 && ligne+1<8){ 
			if( P.getCaseIJ(ligne+1, col-1).getP() == NULL  ||  (P.getCaseIJ(ligne+1, col-1).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne+1, col-1) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne+1, col-1) );
				}
			}
		}
		i = 0;
		valide = 0;
		if( col+1<8 && ligne-1>=0){ 
			if( P.getCaseIJ(ligne-1, col+1).getP() == NULL  ||  (P.getCaseIJ(ligne-1, col+1).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne-1, col+1) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne-1, col+1) );
				}
			}
		}
		i = 0;
		valide = 0;
		if( col+1<8 && ligne+1<8){ 
			if( P.getCaseIJ(ligne+1, col+1).getP() == NULL  ||  (P.getCaseIJ(ligne+1, col+1).getP())->getCouleur() != this->couleur ){
				while( i < estEchec.size()  &&  valide == 0 ){
					if( estEchec[i] == P.getPlatIJ(ligne+1, col+1) ){
						valide = 1;
					}
					i++;
				}
				if( valide == 0 ){
					v.push_back(P.getPlatIJ(ligne+1, col+1) );
				}
			}
		}
}


//Pion
//constructeur
Pion::Pion (int col, int ligne, int couleur, char nom) : Piece(col, ligne, couleur, nom){}

//méthodes
void Pion::deplacementPossible (Plateau & P, vector <Case*> &v) { 
	if( this->couleur == 0 ){		//blanc
		if( P.getCaseIJ(ligne-1, col).getP() == NULL ){		//si case en-dessous est vide
			v.push_back(P.getPlatIJ(ligne-1, col));		//dep possible
			if( ligne == 6 ){				//si premier dep
				if( P.getCaseIJ(ligne-2, col).getP() == NULL ){		//si 2eme case en-dessous est vide
					v.push_back(P.getPlatIJ(ligne-2, col));		//dep possible
				}
			}
		}
		if( col-1>=0  &&  P.getCaseIJ(ligne-1, col-1).getP() != NULL  &&  (P.getCaseIJ(ligne-1, col-1).getP())->getCouleur() != this->couleur ){							//si case en diag contient piece ennemie
			v.push_back(P.getPlatIJ(ligne-1, col-1));	//dep possible
		}
		if( col+1<8  &&   P.getCaseIJ(ligne-1, col+1).getP() != NULL  &&  (P.getCaseIJ(ligne-1, col+1).getP())->getCouleur() != this->couleur ){							//autre case en diag
			v.push_back(P.getPlatIJ(ligne-1, col+1));
		}
	}
	if( this->couleur == 1 ){		//noir
		if( P.getCaseIJ(ligne+1, col).getP() == NULL ){
			v.push_back(P.getPlatIJ(ligne+1, col));
			if( ligne == 1 ){
				if( P.getCaseIJ(ligne+2, col).getP() == NULL ){
					v.push_back(P.getPlatIJ(ligne+2, col));
				}
			}
		}
		if( col-1>=0  &&  P.getCaseIJ(ligne+1, col-1).getP() != NULL  &&  (P.getCaseIJ(ligne+1, col-1).getP())->getCouleur() != this->couleur ){
			v.push_back(P.getPlatIJ(ligne+1, col-1));
		}
		if( col+1<8  &&  P.getCaseIJ(ligne+1, col+1).getP() != NULL  &&  (P.getCaseIJ(ligne+1, col+1).getP())->getCouleur() != this->couleur ){
			v.push_back(P.getPlatIJ(ligne+1, col+1));
		}
	}
}
	





