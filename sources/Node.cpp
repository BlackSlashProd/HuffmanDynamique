#include "Node.hpp"

Node::Node(){
	val = '\0';	// Seul caractere que l'on ne peut pas ajouter a l'arbre.
	freq = 0;
	pere = filsGauche = filsDroit = next = back = NULL;
	special = false;
}
Node::~Node(){
	if(filsGauche) delete(filsGauche);
	if(filsDroit) delete(filsDroit);
}
void Node::printNode(){
	char value = val;
	if(special)
		value = '#';
	else {
		if(value=='\0')
			value = ' ';
	}
	cout << "( " << value << " , " << freq << " )";
	cout << " fg=";
	if(filsGauche != NULL){
		value = filsGauche->val;
		if(filsGauche->special)
			value = '#';
		else{
			if(value=='\0')
				value = ' ';
		}
		cout << "( " << value << " , " << filsGauche->freq << " )";
	}
	else
		cout << "None";
	cout << " fd=";
	if(filsDroit != NULL){
		value = filsDroit->val;
		if(filsDroit->special)
			value = '#';
		else{
			if(value=='\0')
				value = ' ';
		}
		cout << "( " << value << " , " << filsDroit->freq << " )";
	}
	else
		cout << "None";
	cout << endl;
	if(filsGauche != NULL)
		filsGauche->printNode();
	if(filsDroit != NULL)
		filsDroit->printNode();
}
