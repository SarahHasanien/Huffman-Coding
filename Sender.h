#pragma once

#include "Symbol.h"
#include "Huffman.h"

#include <vector>
#include <string>
#include <math.h> 
#include <set>
using namespace std;


class Sender
{
private:
	// the message to be encoded and sent
	string message="";

	// vector of source unique symbols
	vector<Symbol> symbols;

	// huffman pointer to be able to use its functions for encoding
	Huffman* huffman;

public:

	// constructor: creates new object of huffman class and assigns it to the huffman data member
	Sender();

	// desctructor: Do "Not" delete the huffman object here because it will be used in receiver side
	~Sender();

	// reads the source message from input file
	// and sets the "message" data member
	void ReadMessage(string messageFile);

	// creates the vector of symbols and calculating probabilites of each symbol
	// sets the "symbols" data member
	void CalculateProbabilities();

	// A function to compute the entropy of the message
	// it uses the probabilities computed in CalculateProbabilities function
	float CalculateEntropy();

	// uses the huffman class to build the tree and generate the encoded message
	// it calls functions: buildTree and EncodeMessage of the huffman class
	// it 1- writes the encoded message in the passed file
	//    2- returns the huffman tree to be used in reciever side
	// [Note]: the encoded symbols should NOT be written separated by any characters like spaces
	//         it should be written instead as a sequence of zeros and ones without separation
	Huffman* Encode(string encodedFile);
};

