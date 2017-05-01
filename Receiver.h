#pragma once

#include "Symbol.h"
#include "Huffman.h"

#include <vector>
#include <string>
using namespace std;

class Receiver
{
private:
	// the huffman tree sent by the sender
	Huffman* hufffman;

	// the encoded message sent by the sender
	string encodedMessage="";

public:
	// constructor: initializes the "huffman" data member
	Receiver(Huffman* h);
	// destructor
	~Receiver();

	// reads the encoded message sent by the sender
	// and sets "encodedMessage" data member
	void ReadEncodedMessage(string encodedFile);

	// decode the "encodedMessage" using "huffman" tree
	// and writes the decoded message in the passed file
	void Decode(string decodedFile);
};

