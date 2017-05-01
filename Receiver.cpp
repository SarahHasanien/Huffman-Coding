#include "Receiver.h"

// implementation here

// constructor: initializes the "huffman" data member
//
	Receiver::Receiver(Huffman* h){
		hufffman = h;
	}
	// destructor
	Receiver::~Receiver(){
		delete hufffman;
	}


	void Receiver::ReadEncodedMessage(string encodedFile){
		//TODO
		// this function reads the encoded message in the file named in parameter "encodedFile"
		// it should set the class data member encodedMessage
		// hint: use getline to read encoded message from file.
		char c;
		ifstream f1(encodedFile);
		if (f1.is_open())
		{
			while (f1.get(c))
			{
				encodedMessage += c;
			}
			f1.close();
		}
	}

	void Receiver::Decode(string decodedFile){
		// TODO
		// this function decodes the "encodedMessage" using "huffman" tree 
		string decoded=hufffman->DecodeMessage(encodedMessage);
		ofstream ofs;
		ofs.open(decodedFile);
		ofs << decoded;
		ofs.close();
	}