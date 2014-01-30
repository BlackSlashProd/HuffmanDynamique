#include "Huffman.hpp"
#include "Binarytools.hpp"

void Huffman_compression(ifstream& inFile, ofstream& outFile){
	Aha* H = new Aha();
	NBuffer* Nbuff = new NBuffer();
	char car;
	string code;
	// Lecture du premier caractere.
	car = inFile.get();
	//printTransmission(inverse(H->getSpecialCode()), car);
    H->ajouterCar(car);
    outFile.write(&(car),1);

    car = inFile.get();
    while(inFile.good()){
		// Symbole non existant.
		if(!H->existCar(car)){
			// Recuperer le code de feuille speciale et ecrire dans le buffer.
			code = H->getSpecialCode();
			Nbuff->ecrireCode(code);
			// Ecrire le caractere dans le buffer.
			Nbuff->ecrireChar(car);
			// DEBUG
			//printTransmission(inverse(H->getSpecialCode()), car);
			// Ajouter le caractere a l'arbre.
			H->ajouterCar(car);
		}
		// Symbole existant.
		else {
			// Recuperer le code du symbole et l'ecrire dans le buffer.
			code = H->carCode(car);
			Nbuff->ecrireCode(code);
			// Incrementer le poids.
			H->incrementFreq(car);
			// DEBUG
			//cout << "Transmission(Increment) : " << inverse(H->carCode(car)) << " (" << car << ")" << endl;
		}
    	car = inFile.get();
    }
    Nbuff->writeandpurge(outFile);
    H->printAha();
	delete(H);
}

void Huffman_decompression(ifstream& inFile, ofstream& outFile){
	Aha* H = new Aha();
	Node* Htemp = NULL;
	char car;
	string buffread = "";
	// Lecture du premier caractere.
	inFile.read((char*)&car, sizeof(char));
	outFile.write(&(car),1);
	printTransmission(inverse(H->getSpecialCode()), car);
	H->ajouterCar(car);
	Htemp = H->getRacine();

	inFile.read((char*)&car, sizeof(char));
	// Copie du fichier dans un buffer que l'on pourra parcourir bit par bit.
	while(inFile){
		buffread += car;
		inFile.read((char*)&car, sizeof(char));
	}
	// On recupere le nombre de bits significatifs dans le dernier octect.
	int numbit = atoi(&buffread[buffread.size()-1]);
	buffread.resize(buffread.size()-1);
	// On calcul le nombre de bits significatifs au total.
	unsigned int nb_bits = (buffread.size()-1)*8 + numbit;
	unsigned int curbit = 0;
	// Boucle parcourant le buffer bit a bit.
	while(curbit < nb_bits){
		/*
		 * Parcourt de l'arbre en fonction du chemin d'une feuille speciale ou
		 * d'une feuille d'un symbole.
		 */
		while(!H->estFeuille(Htemp)){
			if(!getBitInOctect(buffread[curbit/8],(7-curbit%8)))
				Htemp = Htemp->filsGauche;
			else
				Htemp = Htemp->filsDroit;
			curbit++;
		}
		// Dans le cas de l'increment de l'occurence d'un symbole.
		if(!H->estFeuilleSpeciale(Htemp) ){
			// On �crit le symbole de la feuille dans le fichier.
			char towrite = Htemp->val;
			outFile.write(&(towrite),1);
			// On incr�mente la frequence du symbole.
			H->incrementNode(Htemp);
			// On met a jour l'arbre dans le cas ou une modification serait necessaire.
			H->majRacine();
			// DEBUG
			cout << "Transmission(Increment) : " << inverse(H->carCode(towrite)) << " (" << towrite << ")" << endl;
		}
		// Dans le cas de l'ajout d'un caractere pas encore dans l'arbre.
		else{
			// On �crit le nouveau symbole (8prochains bits) dans le fichier.
			car = decoder(buffread,curbit);
			outFile.write(&(car),1);
			curbit += 8 ;
			// DEBUG
			printTransmission(inverse(H->getSpecialCode()), car);
			// On ajoute le nouveau symbole � l'arbre.
			H->ajouterCar(car);
		}
		Htemp = H->getRacine();
	}
    H->printAha();
	delete(H);
}

string toBinary(char c){
	string s = "";
	int n = c;
	while(n != 0){
	    ostringstream oss;
	    oss << n%2;
	    s = oss.str()+s;
		n = n/2;
	}
	while(s.size() < 8) s = "0"+s; // On insere des bits de bourrage.
	return s;
}

void printTransmission(string fs, unsigned char c){
	string conv = toBinary(c);
	cout << "Transmission(Ajout) : " << fs+conv << " avec #="<< fs << " et " << c << "(" << conv  << ")" << endl;
}

string inverse(string in){
	string s = "";
	for(unsigned int i=0; i< in.size(); i++)
		s = in[i]+s;
	return s;
}
