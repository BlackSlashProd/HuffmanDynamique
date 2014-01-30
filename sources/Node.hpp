#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Node {
	public:
		unsigned char val;
		int freq;
		bool special;
		Node* pere;
		Node* filsGauche; Node* filsDroit;
		Node* next; Node* back;
		Node();
		~Node();
		void printNode();
};

#endif
