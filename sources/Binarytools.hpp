#ifndef BINARYTOOLS_HPP_
#define BINARYTOOLS_HPP_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

class NBuffer {
	private:
		char* buff8bits;
		int nb8bits;
	public:
		NBuffer();
		~NBuffer();
		void ajouterBit(bool);
		void ajouter(bool);
		void ecrireChar(char c);
		void ecrireCode(string);
		void writeandpurge(ofstream&);
};

bool getBitInOctect(char, int);
char decoder(string,int);

#endif /* BINARYTOOLS_HPP_ */
