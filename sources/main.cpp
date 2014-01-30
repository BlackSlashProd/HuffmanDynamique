#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include "Huffman.hpp"

using namespace std;

/**
 * Calculer la taille d'un fichier.
 */
long GetFileSize( std::ifstream & Fichier ) {
    long pos = Fichier.tellg();
    Fichier.seekg( 0 , std::ios_base::end );
    long size = Fichier.tellg() ;
    Fichier.seekg( pos,  std::ios_base::beg ) ;
    return size ;
}

int main(int argc,char **argv)
{
	/* Test des arguments passes en parametre. */
	if((argc != 4) || ((argc == 4) && (strcmp(argv[1],"-c") && strcmp(argv[1],"-d")))) {
		fprintf(stderr, "Please use huffmandyn like : huffmandyn [-cd] [inputFile] [outputFile].\n");
		return 0;
	}
	ifstream ficin(argv[2], ios::in | ios::binary);
	ofstream ficout(argv[3], ios::out | ios::binary);
	if(ficin == NULL || ficout == NULL)	{
			fprintf(stderr, "Error can't open file.\n");
			return 0;
	}
	int fsize = GetFileSize(ficin);
	if(fsize > 0){
		clock_t beginTime = clock();
		if(strcmp(argv[1],"-c") == 0) {
			cout << "Compression de " << argv[2] << " vers " << argv[3] << endl;
			Huffman_compression(ficin, ficout);
		}
		else {
			cout << "Decompression de " << argv[2] << " vers " << argv[3] << endl;
			Huffman_decompression(ficin, ficout);
		}
		clock_t endTime = clock();
		cout << "Time : " << (float)(((float)endTime - (float)beginTime) / (float)CLOCKS_PER_SEC) << " secs." << endl;
		ficin.close();
		ficout.close();

		/* Comparaisons des tailles des fichiers. */
		cout << "Taille de " << argv[2] << " = " << fsize << endl;
		ifstream fic2(argv[3]);
		if(fic2){
			int fsize2 = GetFileSize(fic2);
			cout << "Taille de " << argv[3] << " = " << fsize2 << endl;
			if(strcmp(argv[1],"-c") == 0)
				cout << "Taux de compression : " << (float)(100.-(100.*fsize2/fsize)) << " %" << endl;
			fic2.close();
		}
	}
	else{
		cout << "Fichier vide, aucune compression ou decompression possible." << endl;
	}
	return 0;
}
