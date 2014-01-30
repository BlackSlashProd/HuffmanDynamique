#include "Binarytools.hpp"

NBuffer::NBuffer(){
	this->buff8bits = new char;
	this->buff8bits[0] = 0x0;
	this->nb8bits = 0;
}

NBuffer::~NBuffer(){
	free(this->buff8bits);
}

void NBuffer::ajouterBit(bool val){
	char c = this->buff8bits[this->nb8bits/8];
	int n = 7 - (this->nb8bits%8);
	if(val)
		c |= (1 << n);
	else
		c &= ~(1 << n);
	this->buff8bits[this->nb8bits/8] = c;
	this->nb8bits++;
}

void NBuffer::ajouter(bool val){
	ajouterBit(val);
	if(this->nb8bits%8==0){
		this->buff8bits = (char*)realloc(this->buff8bits, (sizeof(char)*((int)(this->nb8bits/8)))+1);
		this->buff8bits[this->nb8bits/8] = 0x0;
	}
}

void NBuffer::ecrireChar(char c){
	for(int i=7; i>=0;i--){
		if(getBitInOctect(c, i))
			ajouter(true);
		else
			ajouter(false);
	}
}

void NBuffer::ecrireCode(string code){
	int length = code.size()-1;
	while(length>=0){
		if(code[length] == '1')
			ajouter(true);
		else
			ajouter(false);
		length--;
	}
}

void NBuffer::writeandpurge(ofstream& outFile){
	int i;
	for(i=0;i<this->nb8bits/8;i++){
		outFile.write(&(this->buff8bits[i]),1);
	}
	if(this->nb8bits%8!=0){
		outFile.write(&(this->buff8bits[i]),1);
	}
	char s[1];
	int nbbits = this->nb8bits%8;
	if(nbbits == 0)
		nbbits = 8;
	sprintf(s,"%d",nbbits);
	char numbit = s[0];
	outFile.write(&(numbit),1);
	this->nb8bits = 0;
	free(this->buff8bits);
}

bool getBitInOctect(char oct, int ind){
	switch(ind){
		case 0:	return ((oct & 0x01)==0x01);
		case 1:	return ((oct & 0x02)==0x02);
		case 2:	return ((oct & 0x04)==0x04);
		case 3:	return ((oct & 0x08)==0x08);
		case 4:	return ((oct & 0x10)==0x10);
		case 5:	return ((oct & 0x20)==0x20);
		case 6:	return ((oct & 0x40)==0x40);
		case 7:	return ((oct & 0x80)==0x80);
	}
	return false;
}

char decoder(string code,int rang){
	char dcode = 0x0;
	for(int i=rang;i<rang+8;i++){
		if(getBitInOctect(code[i/8],(7-i%8)))
			dcode |= (1 << (7-(i-rang)));
		else
			dcode &= ~(1 << (7-(i-rang)));
	}
	return dcode;
}
