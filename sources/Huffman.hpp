#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Aha.hpp"

using namespace std;

/**
 * Methode de compression selon Huffman Dynamique.
 * @param inFile
 * 		Fichier a compresser.
 * @param outFile
 * 		Fichier compresse.
 */
void Huffman_compression(ifstream& inFile, ofstream& outFile);
/**
 * Methode de decompression selon Huffman Dynamique.
 * @param inFile
 * 		Fichier a decompresser.
 * @param outFile
 * 		Fichier decompresse.
 */
void Huffman_decompression(ifstream&inFile, ofstream& outFile);

/**
 * Fonctions de debug pour afficher les transmissions lors du codage.
 */
string toBinary(char);
void printTransmission(string, unsigned char);
string inverse(string);

#endif /* HUFFMAN_HPP_ */
