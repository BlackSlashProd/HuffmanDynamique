/**
 * Classe representant un arbre d'huffman adaptatif.
 *
 * @author BARBIER Cl�ment
 *
 */
#include "Aha.hpp"

Aha::Aha(){
	this->root = NULL;
	this->special = new Node();
	this->special->special = true;
	for(int i=0; i<256; i++)
		this->lst_car[i] = false;
}

Aha::~Aha(){
	if(this->root) delete(this->root);
}

Node* Aha::getRacine(){
	return this->root;
}

void Aha::Modification(Node* n, Node* fin){
	if(fin != NULL && fin != n){
		// Si les deux noeuds ont le meme pere, on inverse ses deux fils.
		if(n->pere == fin->pere){
			if(estFilsGauche(n))
				echanger2Fils(n, fin);
			else
				echanger2Fils(fin, n);
		}
		else
			echanger2Nodes(n, fin);
	}

}

void Aha::echanger2Fils(Node* f1, Node* f2){
	// On met a jour le pere des deux fils.
	f1->pere->filsGauche = f2;
	f1->pere->filsDroit = f1;
	// Mis à jour du suivant et precedent du fils gauche.
	f1->next = f2->next;
	f1->next->back = f1;
	Node* savef1back = f1->back;	// sauvegarde du precedent de f1, avant de le modifier pour pouvoir le reassigner au fils droit.
	f1->back = f2;
	// Mis a jour du suivant et precedent du fils droit.
	f2->next = f1;
	f2->back = savef1back;
	if(f2->back != NULL)
		f2->back->next = f2;
}

void Aha::echanger2Nodes(Node* n1, Node* n2){
	if(estFilsGauche(n1)){
		// Si les deux noeuds sont des fils gauche.
		if(estFilsGauche(n2)){
			n1->pere->filsGauche = n2;
			n2->pere->filsGauche = n1;
		}
		// Si n1 est un fils gauche et n2 est un fils droit.
		else{
			n1->pere->filsGauche = n2;
			n2->pere->filsDroit = n1;
		}
	}
	else{
		// Si les deux noeuds sont des fils droit.
		if(estFilsDroit(n2)){
			n1->pere->filsDroit = n2;
			n2->pere->filsDroit = n1;
		}
		// Si n1 est un fils droit et n2 est un fils gauche.
		else{
			n1->pere->filsDroit = n2;
			n2->pere->filsGauche = n1;
		}
	}
	// Inversion des deux peres.
	Node* saveN1pere = n1->pere;
	n1->pere = n2->pere;
	n2->pere = saveN1pere;
	// Si le second noeud n'est pas le suivant du premier noeud.
	if(n1->next != n2){
		Node* saveN1Back = n1->back;
		Node* saveN2Back = n2->back;
		supprNodeFromWay(n1);
		supprNodeFromWay(n2);
		if(n2 != NULL && saveN1Back != NULL) addNodeInWay(saveN1Back, n2);
		if(n1 != NULL && saveN2Back != NULL) addNodeInWay(saveN2Back, n1);
	}else{
		supprNodeFromWay(n2);
		if(n1->back != NULL && n2 != NULL)
			addNodeInWay(n1->back, n2);
	}

}

Node* Aha::finBloc(Node* m){
	if(m == NULL)
		return NULL;
	Node* fin = m;
	while(fin->next != NULL && fin->next->freq == m->freq)
		fin = fin->next;
	return fin;
}

Node* Aha::getNode(unsigned char c){
	Node* ite = this->special;
	while(ite->val != c && ite->next != NULL)
		ite = ite->next;
	if(ite->val != c)
		return NULL;
	return ite;
}

bool Aha::estFeuille(Node* n){
	return (n->filsDroit == NULL && n->filsGauche == NULL);
}

bool Aha::estFeuilleSpeciale(Node* n){
	return (n==this->special);
}

bool Aha::estFilsGauche(Node* n){
	if(n->pere != NULL && n->pere->filsGauche == n) return true;
	return false;
}

bool Aha::estFilsDroit(Node* n){
	if(n->pere != NULL && n->pere->filsDroit == n) return true;
	return false;
}

string Aha::nodeCode(Node* n){
	string s = "";
	Node* ite = n;
	while(ite->pere != NULL){
		if(estFilsGauche(ite))
			s +='0';
		else
			s +='1';
		ite = ite->pere;
	}
	return s;
}

string Aha::carCode(unsigned char c){
	Node* n = getNode(c);
	if(n != NULL)
		return nodeCode(n);
	return "error";
}

string Aha::getSpecialCode(){
	return nodeCode(this->special);
}

bool Aha::existCar(unsigned char c){
	return this->lst_car[c];
}

void Aha::ajouterCar(unsigned char c){
	this->lst_car[(int)c] = true;
	// On cree un pere, son fils droit que l'on souhaite ajouter et la feuille speciale a gauche.
	Node* n = new Node();
	Node* f = new Node();
	n->freq = f->freq = 1;
	f->val = c;
	n->pere = this->special->pere;
	n->filsGauche = this->special;
	n->filsDroit = f;
	// Mis a jour des ordres de frequences (poids W).
	n->next = this->special->next;
	n->back = f;
	if(this->special->next != NULL)
		n->next->back = n;
	n->back->next = n;
	this->special->pere = n;
	this->special->next = f;
	f->pere = n;
	f->back = this->special;
	if(n->pere != NULL){
		n->pere->filsGauche = n;
		incrementNode(n->pere);
	}
	majRacine();
}

void Aha::incrementNode(Node* n){
	Node* fin = finBloc(n);
	// Modification de l'arbre si necessaire, puis increment de la frequence.
	if(fin != n && fin != n->pere)
		Modification(n,fin);
	n->freq++;
	// Recursion sur le pere.
	if(n->pere != NULL)
		incrementNode(n->pere);
}
void Aha::incrementFreq(unsigned char c) {
	incrementNode(getNode(c));
	majRacine();
}

void Aha::addNodeInWay(Node* n,Node* next){
	Node* saveNext = n->next;	// sauvegarde du suivant du noeud n pour pouvoir le modifier.
	n->next = next;
	saveNext->back = next;
	next->back = n;
	next->next = saveNext;
}

void Aha::supprNodeFromWay(Node* n) {
	// On fait pointer le precedent du suivant sur le precedent du noeud a supprimer.
	if( n->next != NULL ) n->next->back = n->back;
	// On fait pointer le suivant du precedent sur le suivant du noeud a supprimer.
	if( n->back != NULL ) n->back->next = n->next;
}

void Aha::majRacine(){
	Node* rac = this->special;
	while(rac->next != NULL)
		rac = rac->next;
	this->root = rac;
}

void Aha::printAha(){
	this->root->printNode();
	int n = 0;
	for(int i=0;i<256;i++)
		if(this->lst_car[i]) n++;
	cout << endl << "Nombre de caracteres differents : " << n << endl;
}
