#include "piece.hpp"
#include "plateau.hpp"
#include "partie.hpp"
#include "joueur.hpp"

static int nbTour = 0;

//Coup
//constructeur
Coup::Coup (Case* depart, Case* arrive){
	this->depart = depart;
	this->arrive = arrive;
}

//getters
Case* Coup::getDepart (){
	return depart;
}

Case* Coup::getArrive (){
	return arrive;
}

//méthodes
void Coup::jouerCoup (Plateau & P, vector <Coup*> & coupsJoues, vector <Piece*> & blanchesPrises, vector <Piece*> & noiresPrises, int & blanche, int & noire){		
	//pour roque
	if( depart->getP()->getNom() == 'r'  ||  depart->getP()->getNom() == 'R' ){ //si c'est un roi
			if( arrive->getCol() == depart->getCol()+2 ){		//si joueur demande le roque
										//alors on créer et execute aussi le déplacement de tour
				coupsJoues.push_back( new Coup( P.getPlatIJ(depart->getLigne(), depart->getCol()+3), P.getPlatIJ(depart->getLigne(), depart->getCol()+1)));				
				coupsJoues[coupsJoues.size()-1]->jouerCoup(P, coupsJoues, blanchesPrises, noiresPrises, blanche, noire );
			}
			if( arrive->getCol() == depart->getCol()-2 ){	//si joueur demande le roque
									//alors on créer et execute aussi le déplacement de tour
				coupsJoues.push_back( new Coup( P.getPlatIJ(depart->getLigne(), depart->getCol()-4), P.getPlatIJ(depart->getLigne(), depart->getCol()-1)));
				coupsJoues[coupsJoues.size()-1]->jouerCoup(P, coupsJoues, blanchesPrises, noiresPrises, blanche, noire );
			}	
	}
	// promotion
	promotion(); 
	//pour tout les coups
	if( arrive->getP() != NULL ){	//si la case d'arrivée contient une piece ennemie
		if( (arrive->getP())->getCouleur() == 0 ){	//si blanche
			blanchesPrises.push_back(arrive->getP());	//ajoute aux pieces blanches prises
			blanche = 1;		//pour signifier qu'une piece blanche  été prise a "annuleCoup()"
		}
		else{
			noiresPrises.push_back(arrive->getP());		//ajoute aux pieces noires prises
			noire =1;		//pour signifier qu'une piece blanche  été prise a "annuleCoup()"
		}
	}
	arrive->setP(depart->getP());		//déplace la piece sur la case d'arrivée
	(arrive->getP())->setLigne(arrive->getLigne());	//met à jour coordonées de la piece déplacée
	(arrive->getP())->setCol(arrive->getCol());	//met à jour coordonées de la piece déplacée
	depart->setP(NULL);		//met vide la case de départ
	nbTour++; 		//met à jour le compteur de tour
}

void Coup::promotion (){
	if(depart->getP()->getNom() == 'p'  ||  depart->getP()->getNom() == 'P' ){	
		if( arrive->getLigne() == 7  ||  arrive->getLigne() == 0 ){
			char promotion = 'a';
			cout<<"Promotion d'un pion !"<<endl;
			while( promotion != 'p'  &&  promotion != 't'  &&  promotion != 'c'  &&  promotion != 'f'  &&  promotion != 'd' ){ 
				cout<<"Veuillez entrer 't' pour obtenir une tour, 'c' pour un cavalier, 'f' pour un fou, 'd' pour une dame, ou 'p' pour concerver votre pion :"<<endl;
				cin>>promotion;
			}
			if( depart->getP()->getCouleur() == 0 ){
				if( promotion == 't' ){
					depart->setP(new Tour(depart->getLigne(), depart->getCol(), 0, 't'));
				} 
				if( promotion == 'c' ){
					depart->setP(new Cavalier(depart->getLigne(), depart->getCol(), 0, 'c'));
				} 
				if( promotion == 'f' ){
					depart->setP(new Fou(depart->getLigne(), depart->getCol(), 0, 'f'));
				} 
				if( promotion == 'd' ){
					depart->setP(new Dame(depart->getLigne(), depart->getCol(), 0, 'd'));
				} 
			}
			else{
				if( promotion == 't' ){
					depart->setP(new Tour(depart->getLigne(), depart->getCol(), 1, 'T'));
				} 
				if( promotion == 'c' ){
					depart->setP(new Cavalier(depart->getLigne(), depart->getCol(), 1, 'C'));
				} 
				if( promotion == 'f' ){
					depart->setP(new Fou(depart->getLigne(), depart->getCol(), 1, 'F'));
				} 
				if( promotion == 'd' ){
					depart->setP(new Dame(depart->getLigne(), depart->getCol(), 1, 'D'));
				} 
			}
		}
	}
}

//Partie
//Constructeurs
Partie::Partie (){
	blanche = 0;
	noire =0;
}
	
//méthodes
void Partie::Menu(){
	int choix = 0;
	Joueur J1(0,0);
	Joueur J2(1,0);
	while( choix != 1  &&  choix != 2){
		cout<<"Pour commencer une nouvelle partie entrez 1, pour reprendre la partie enregistrée entrez 2"<<endl;
		cin>>choix;
		if( choix != 1  &&  choix != 2){ 
			cout<<"Veuillez entrer soit 1 soit 2"<<endl;
		}
	}
	cout<<"Votre partie sera automatiquement sauvegardée automatiquement"<<endl;
	if(choix == 1){
		remove("sauvegarde.txt"); //efface le fichier de sauvegarde pour enregistrer nouvelle partie
		jouerPartie(J1, J2);
	}
	if(choix == 2){
		restaurePartie(J1, J2);
		jouerPartie(J1, J2);
	}
}

void Partie::jouerPartie (Joueur & J1, Joueur & J2){
	P.afficherPlateau();
	bool continu = true;
	bool estEchec;
	while( nbTour < 100  &&  continu == true ){
		if(nbTour%2 == 0){
			cout<<"Au joueur blanc de jouer :"<<endl;
			estEchec = true;
			while( estEchec == true ){	//rejoue le coup si celui-ci met le joueur en echec
				J1.demande_verif_creer_Coup(P, coupsJoues);
				coupsJoues[coupsJoues.size()-1]->jouerCoup(P, coupsJoues, blanchesPrises, noiresPrises, blanche, noire );
				if( verifEchec(J1) == true ){ 	
					annuleCoup();
					cout<<"ce coup vous met en echec, veuillez choisir un autre coup"<<endl;
				}
				else{
					estEchec = false;
				}
			} 
			if( coupsJoues[coupsJoues.size()-1]->getArrive()->getP()->getNom() == 'r'  ||  coupsJoues[coupsJoues.size()-1]->getArrive()->getP()->getNom() == 't'){	//si la pièce déplacée est le roi ou une tour
				coupsJoues[coupsJoues.size()-1]->getArrive()->getP()->setPremierDep(false);	//on note qu'un déplacement a déjà été fait pour ne plus permettre roque 
			}
			enregistrerCoup();
			P.afficherPlateau();
			afficherPrises();
			if( verif_etatPartie(J2) == false ){	//verifie si joueur adverse est en pat ou echec ou echec et mat
				continu = false;	//stop la partie si victoire	
			}
			cout<<"Score : "<<endl;
			cout<<"-Joueur blanc : "<<J1.getScore()<<"      -Joueur noir : "<<J2.getScore()<<endl;
			noire = 0;		//remet à nul l'indicateur de pièce prise pour le tour suivant
			//abandon();		//méthode retirée pour cause pratique
			if( nbTour == 150 ){	
				cout<<"Fin de partie : abandon !"<<endl;
				continu = false;
			}
		}
		else{
			if( continu == true ){
				cout<<"Au joueur noir de jouer :"<<endl;
				estEchec = true;
				while( estEchec == true ){  	
					J2.demande_verif_creer_Coup(P, coupsJoues);
					coupsJoues[coupsJoues.size()-1]->jouerCoup(P, coupsJoues, blanchesPrises, noiresPrises, blanche, noire );
					if( verifEchec(J2) == true ){ 
						annuleCoup();
						cout<<"ce coup vous met en echec, veuillez choisir un autre coup"<<endl;
					}
					else{
						estEchec = false;
					}
				} 
				if( coupsJoues[coupsJoues.size()-1]->getArrive()->getP()->getNom() == 'R'  ||  coupsJoues[coupsJoues.size()-1]->getArrive()->getP()->getNom() == 'T'){	//si la pièce déplacée est un roi ou une tour
					coupsJoues[coupsJoues.size()-1]->getArrive()->getP()->setPremierDep(false);	//on note qu'un déplacement a déjà été fait pour ne plus permettre roque roque
				}
				enregistrerCoup();
				P.afficherPlateau();
				afficherPrises();
				if( verif_etatPartie(J1) == false ){
					continu = false;
				}
				cout<<"Score : "<<endl;
				cout<<"-Joueur blanc : "<<J1.getScore()<<"      -Joueur noir : "<<J2.getScore()<<endl;
				blanche = 0;	
				//abandon();       //méthode retirée pour cause pratique
				if( nbTour > 99 ){
					cout<<"Fin de partie !"<<endl;
					if( nbTour == 100 ){
						cout<<"Partie nulle : nombre de coups autorisés dépacé !"<<endl;
					}
					else{
						cout<<"Fin de partie : abandon !"<<endl;
					}
					continu = false;
				}
			}
		}
	}
	remove("sauvegarde.txt");	//efface l'enregistrement pour éviter restauration et reprise de la partie malgré la fin
}


void Partie::afficherPrises (){
	unsigned int i;
	cout<<"Pièces blanches prises : "<<endl;
	for(i=0; i<blanchesPrises.size(); i++){
		blanchesPrises[i]->afficherPiece();
	}
	cout<<endl;
	cout<<"Pièces noires prises : "<<endl;
	for(i=0; i<noiresPrises.size(); i++){
		noiresPrises[i]->afficherPiece();
	}	
	cout<<endl;
}

void Partie::rechercheRoi ( Joueur & J, Piece* & roi ){ 	//parcours l'échiquier pour trouver le roi du joueur 
	int i;
	int j;
	if( J.getCouleur() == 0 ){
		for(i=0; i<8; i++){
			for(j=0; j<8; j++){
				if( P.getCaseIJ(i, j).getP() != NULL  &&  (P.getCaseIJ(i, j).getP())->getNom() == 'r' ){
					roi = P.getCaseIJ(i, j).getP();
				}
			}
		}
	}
	if( J.getCouleur() == 1 ){
		for(i=0; i<8; i++){
			for(j=0; j<8; j++){
				if( P.getCaseIJ(i, j).getP() != NULL  &&  (P.getCaseIJ(i, j).getP())->getNom() == 'R' ){
					roi = P.getCaseIJ(i, j).getP();
				}
			}
		}
	}
}

void Partie::abandon (){
	int abandon = 0;
	while( abandon == 0){
		cout<<"Entrer 1 pour continuer, 2 pour abandonner"<<endl;
		cin>>abandon;
		if( abandon != 1  &&  abandon != 2){
			cout<<"Veuillez entrer soit 1 soit 2"<<endl;
		}
		if( abandon == 2 ){
			nbTour = 150;
		}
	}
}


bool Partie::verif_etatPartie (Joueur & J){
	bool etat = true;
	if( verifEchec(J) == true ){
		cout<<"Mise en echec de l'adversaire"<<endl;
		if( verifMat(J) == true ){
			cout<<"Fin de partie : Echec et Mat !"<<endl;
			etat = false;
		}
	}
	else{
		if( verifPat(J) == true ){
			cout<<"Fin de partie : PAT partie nulle !"<<endl;
			etat = false;
		}
	}
	return etat;
}


bool Partie::verifEchec (Joueur & J){
	unsigned int i;
	int j;
	bool estEchec = false;
	vector <Case*> depPossible;
	Piece* roi = NULL;
	rechercheRoi(J, roi);
	for(i=0; i<8; i++){		//etablit tout les déplacements possible pour le joueur ennemie
		for(j=0; j<8; j++){
			if( P.getCaseIJ(i, j).getP() != NULL  &&  (P.getCaseIJ(i, j).getP())->getCouleur() != roi->getCouleur() ){
				(P.getCaseIJ(i, j).getP())->deplacementPossible(P, depPossible);
			}
		}
	}
	for(i=0; i<depPossible.size(); i++){
		if( P.getPlatIJ(roi->getLigne(), roi->getCol()) == depPossible[i] ){	//si emplacement du roi du joueur J est dans les dep possible du joueur ennemi alors le joueur J est en echec
			estEchec = true;
		}
	}
	return estEchec;
}

bool Partie::verifMat ( Joueur & J  ){
	unsigned int i=0;
	unsigned int j=0;
	unsigned int k=0;
	bool estMat = true;
	vector <Case*> depPossible;
	blanche = 0; //on remet nul le signalisateur de piece prise pour ne pas considérer et remettre en jeu dans "annuleCoup()" une pièce prise auparavant de façon définitive
	noire = 0; 
	//jouer tt les coups de J et regarder si le roi de J est encore echec apres
	while( i<8  &&  estMat == true ){	//parcours le plateau tant que echec et mat possible
		while( j<8  &&  estMat == true ){
			if( P.getCaseIJ(i, j).getP() != NULL  &&  (P.getCaseIJ(i, j).getP())->getCouleur() == J.getCouleur() ){	//pour piece de J
				(P.getCaseIJ(i, j).getP())->deplacementPossible(P, depPossible);
				k = 0;	
				while( k<depPossible.size()  &&  estMat == true ){		//test les coups de la pièce
					coupsJoues.push_back( new Coup( P.getPlatIJ(i, j), P.getPlatIJ(depPossible[k]->getLigne(), depPossible[k]->getCol()))); 	
					coupsJoues[coupsJoues.size()-1]->jouerCoup(P, coupsJoues, blanchesPrises, noiresPrises, blanche, noire ); //joue le coup			
					if(verifEchec(J) == false){	//si J n'est desormais plus en echec
						estMat = false;		//alors J n'est pas Mat
					}
					annuleCoup();			//annule le coup
					k++;
				}
				depPossible.clear();	//on vide le vecteur déplacement pour stoquer ceux de la pièce suivante
			}
			j++;
		}
		i++;
	}
	return estMat;
}


bool Partie::verifPat ( Joueur & J ){  		//joueur non mis en echec au moment de l'appel
	int i;
	int j;
	bool estPat = false;
	vector <Case*> depPossibleJ;
	for(i=0; i<8; i++){		//etablit tout les déplacements possible pour le joueur
		for(j=0; j<8; j++){
			if( P.getCaseIJ(i, j).getP() != NULL  &&  (P.getCaseIJ(i, j).getP())->getCouleur() == J.getCouleur() ){
				(P.getCaseIJ(i, j).getP())->deplacementPossible(P, depPossibleJ);
			}
		}
	}
	if( depPossibleJ.size() == 0 ){		//si aucun déplacement possible
		estPat = true;			//joueur est en pat
	}
	return estPat;
}

void Partie::enregistrerCoup (){
	ofstream fichier("sauvegarde.txt", ios::out | ios::app);
		if(fichier){  
		 	fichier << (coupsJoues[coupsJoues.size()-1]->getDepart())->getLigne()<<" ";	//coordonnées de la case de départ
			fichier << (coupsJoues[coupsJoues.size()-1]->getDepart())->getCol()<<" ";
			fichier << (coupsJoues[coupsJoues.size()-1]->getArrive())->getLigne()<<" ";	//coordonnées de la case d'arrivé
			fichier << (coupsJoues[coupsJoues.size()-1]->getArrive())->getCol()<<" ";
		}
     		else  {
               		cerr << "Impossible d'ouvrir le fichier !" << endl;
		}
	fichier.close();
}

void Partie::restaurePartie (Joueur & J1, Joueur & J2){
	ifstream fichier("sauvegarde.txt", ios::in);
	if(fichier){  
		int ligneDep;
		int colDep;
		int ligneArr;
		int colArr;
		string ligne;
		while(fichier.good()){
			fichier >> ligneDep;
			fichier >> colDep;
			fichier >> ligneArr;
			fichier >> colArr;
			coupsJoues.push_back( new Coup( P.getPlatIJ(ligneDep, colDep), P.getPlatIJ(ligneArr, colArr) ) );	//crée cop selon les coordonnées lues dans le fichier
			coupsJoues[coupsJoues.size()-1]->jouerCoup(P, coupsJoues, blanchesPrises, noiresPrises, blanche, noire );	//joue le coup
			P.afficherPlateau();
			afficherPrises();
			cout<<"Score : "<<endl;
			cout<<"-Joueur blanc : "<<J1.getScore()<<"      -Joueur noir : "<<J2.getScore()<<endl;
		}
	}
     	else {
               		cerr << "Impossible d'ouvrir le fichier de sauvegarde !" << endl;
	}
	fichier.close();
}

void Partie::annuleCoup (){
	Coup c( coupsJoues[coupsJoues.size()-1]->getArrive(), coupsJoues[coupsJoues.size()-1]->getDepart() );
	c.getArrive()->setP(c.getDepart()->getP());		//déplace la piece sur la case d'arrivée
	(c.getArrive()->getP())->setLigne(c.getArrive()->getLigne());	//met à jour coordonées de la piece déplacée
	(c.getArrive()->getP())->setCol(c.getArrive()->getCol());	//met à jour coordonées de la piece déplacée
	if(blanche == 0  &&  noire == 0){
		c.getDepart()->setP(NULL);	
	}
	if(blanche == 1){		//si blanche prise au dernier coup
		c.getDepart()->setP(blanchesPrises[blanchesPrises.size()-1]);	//remet la piece sur le plateau
		blanchesPrises.pop_back();		
	}
	if(noire == 1){			//si noire prise au dernier coup
		c.getDepart()->setP(noiresPrises[noiresPrises.size()-1]);	
		noiresPrises.pop_back();
	}
	coupsJoues.pop_back();		//retire le dernier coup du vecteur recapitulatif
	noire = 0; 		//on remet nul le signalisateur de piece prise pour le prochain coup
	blanche = 0;		//on remet nul le signalisateur de piece prise pour le prochain coup
	nbTour--;		//annule la mise a jour du compteur de tour
}






