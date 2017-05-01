#include "Sender.h"

// implementation here

// constructor: creates new object of huffman class and assigns it to the huffman data member
	Sender::Sender(){
		huffman = new Huffman();
		message="";
	}

	// desctructor: Do "Not" delete the huffman object here because it will be used in receiver side
	Sender::~Sender(){
	}


	void Sender::ReadMessage(string messageFile){
		//TODO 
		// this function will read the original message from the file name in parameter "messageFile"
		// the original message should be saved in the class data memebr "message"
		// hint: use getline to read the file lines
		//string msg = "";
		char c;
		ifstream f1(messageFile);
		if (f1.is_open())
		{
			while (f1.get(c)) 
			{
				message += c;
			}
			f1.close();
		}
		//cout << message;
	}


	void Sender::CalculateProbabilities(){
		//TODO 
		// this function will fill the class data member symbols  a vector of <Symbols> -> a struct defined in file Symbol.h
		// for every symbol calculate and set the {value, frequency, probability }
		// hint: you can use vector.push_back() to insert elements in the vector
		// hint: maps can be used to calculate the frequency of symbols.
		// hint use string.at(position) to access string characters individually
		set <char> myset;
		set <char>::iterator it;

		Symbol temp;
		float msgLnght = message.length();
		//Put all the used letters in a set.
		for (int i = 0; i < message.length(); i++)
		{
			myset.insert(message[i]);
		}
		//For every element in this set find the number of occurance in the orriginal message ;) (Frequency)
		for (it = myset.begin(); it != myset.end(); it++) 
		{
			temp.frequency = count(message.begin(), message.end(), *it);
			temp.probability = temp.frequency / msgLnght;
			temp.value = *it;
			symbols.push_back(temp);
		}
		//Only for testing (Y)
		/*cout << symbols[1].value << endl;
		cout << symbols[1].frequency << endl;
		cout << symbols[1].probability << endl;*/
	}

	float Sender::CalculateEntropy(){
		//TODO 
		// this function should calculate and return the entropy of the message after filling symbol vector in function CalculateProbabilities
		float h = 0.0;
		for (int i = 0; i < symbols.size(); i++)
		{
			h += symbols[i].probability * log2(symbols[i].probability);
		}
		h *= -1;
		return h ;
	}

	Huffman* Sender::Encode(string encodedFile){
		//TODO
		// uses the huffman class to build the tree and generate the encoded message
		// it calls functions: buildTree and EncodeMessage of the huffman class
		// it 1- writes the encoded message in the passed file
		//    2- returns the huffman tree to be used in reciever side
		// [Note]: the encoded symbols should NOT be written separated by any characters like spaces
		//         it should be written instead as a sequence of zeros and ones without separation
		huffman->buildTree(symbols);
		string encoded=huffman->EncodeMessage(message);
		ofstream ofs;
		ofs.open(encodedFile);
		ofs << encoded;
		ofs.close();

		return huffman;
	}
