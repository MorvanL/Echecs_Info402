#include "piece.hpp"
#include "plateau.hpp"
#include "partie.hpp"
#include "joueur.hpp"

//Constructeur
Joueur::Joueur (int couleur, int score){
	this->couleur = couleur;
	this->score = score;
}


//getters / setters
int Joueur::getCouleur (){
	return couleur;
}

int Joueur::getScore (){
	return score;
}

void Joueur::setCouleur(int couleur){
	this->couleur = couleur;
}

void Joueur::setScore(int score){
	this->score = score;
}



//méthodes
void Joueur::demande_verif_creer_Coup (Plateau & P, vector <Coup*> & coupsJoues){
	vector <Case*> depPossible;
	unsigned int i;
	bool valideCoup = false;			
	bool valideDep = false;
	bool valideArr = false;		
	int ligneDep, colDep;
	int ligneArr, colArr;
	while( valideCoup == false ){		//redemande un coup jusqu'à ce qu'il soit valide
		while(valideDep == false){	//redemande case de dep jusqu'à ce qu'elle soit valide
			cout<<"Entrez la colonne de la pièce à déplacer"<<endl;
			cin>>colDep;
			cout<<"Entrez la ligne de la pièce à déplacer"<<endl;
			cin>>ligneDep;
			if( colDep>=0  && colDep<8  && ligneDep>=0 && ligneDep<8 ){	//verifie existance des coordonnées
				if( P.getCaseIJ(ligneDep, colDep).getP() != NULL  &&  (P.getCaseIJ(ligneDep, colDep).getP())->getCouleur() == couleur ){ 	//verifie que case de depart contient une piece du joueur
					valideDep = true;
				}
				else{
					cout<<"!!! Veuillez selectionner une pièce de votre couleur"<<endl;
				}
			}
			else{
				cout<<"!!! Veuillez entrer des coordonnées correctes"<<endl;
			}
		}
		while(valideArr == false){	//redemande case d'arriver jusqu'à ce qu'elle soit valide
			cout<<"Entrez la colonne où vous souhaitez déplacer la pièce"<<endl;
			cin>>colArr;
			cout<<"Entrez la ligne où vous souhaitez déplacer la pièce"<<endl;
			cin>>ligneArr;
			if( colArr>=0  && colArr<8  && ligneArr>=0 && ligneArr<8 ){ 	//verifie existance des coordonnées
				valideArr = true;
			}
			if(valideArr == false){
				cout<<"!!! Veuillez entrer des coordonnées de destinations existantes"<<endl;
			}
		}
		
		(P.getCaseIJ(ligneDep, colDep).getP())->deplacementPossible(P, depPossible); //etabli tt les dep possible pour la piece selectionnée
		for(i=0; i<depPossible.size(); i++){
			if( (depPossible[i]->getLigne() == ligneArr) && (depPossible[i]->getCol() == colArr) ){		//si case d'arriver est contenu dans les dep possible
				valideCoup = true;	
				coupsJoues.push_back( new Coup( P.getPlatIJ(ligneDep, colDep), P.getPlatIJ(ligneArr, colArr) ) );	//joue le coup
			}
		}
		if( valideCoup == false ){	//si coup pas possible
			if(depPossible.size() > 0){	//si piece a des dep possible
				cout<<"Veuillez entrer des coordonnées de destinations parmi les suivantes :"<<endl;
				for(i=0; i<depPossible.size(); i++){	//on affiche les dep possible et le joueur en selectionne un
					cout<<depPossible[i]->getCol()<<","<<depPossible[i]->getLigne()<<"   ;";
				}
				for(i=0; i<=depPossible.size(); i++){	//remet a 0 les coups possible
					depPossible.pop_back();
				}
			}
			else{		
				cout<<"Aucun déplacement possible pour cette pièce";
				valideDep = false;	//si aucun dep possible pour la piece on redemande une autre case de départ
			}
			cout<<endl;
			valideArr = false;
		}
	}
}
