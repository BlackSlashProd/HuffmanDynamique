#ifndef AHA_HPP_
#define AHA_HPP_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Node.hpp"

using namespace std;

class Aha {
	public:
		Aha();
		~Aha();
		void ajouterCar(unsigned char);
		void incrementFreq(unsigned char);
		void incrementNode(Node*);
		string carCode(unsigned char);
		string getSpecialCode();
		bool existCar(unsigned char);
		bool estFeuille(Node*);
		bool estFeuilleSpeciale(Node*);
		Node* getRacine();
		void majRacine();
		void printAha();

	private:
		Node* root;
		Node* special;
		bool lst_car[256];

		string nodeCode(Node*);
		void Modification(Node*, Node*);
		void echanger2Fils(Node*, Node*);
		void echanger2Nodes(Node*, Node*);
		Node* finBloc(Node*);
		Node* getNode(unsigned char);
		bool estFilsGauche(Node*);
		bool estFilsDroit(Node*);
		void addNodeInWay(Node*,Node*);
		void supprNodeFromWay(Node*);
};

#endif /* AHA_HPP_ */
