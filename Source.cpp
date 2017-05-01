
#include "Sender.h"
#include "Receiver.h"
#include "Huffman.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool CompareDecodedWithOriginal(string inputMessageFile, string decodedMessageFile)
{
	//TODO
	//....
	// this compares the decoded messages with the original message 
	// decoded message is saved in the file that name in the parameter ""decodedMessageFile"
	// original message is saved in the file that name in the parameter ""inputMessageFile"
	// the function should return true if there are identical , false otherwise
	// hint use getline to read lines from the file 
	string s1, s2;
	char c;
	ifstream f1(inputMessageFile);
	if (f1.is_open())
	{
		while (f1.get(c))
		{
			s1 += c;
		}
		f1.close();
	}
	ifstream f2(decodedMessageFile);
	if (f2.is_open())
	{
		while (f2.get(c))
		{
			s2 += c;
		}
		f2.close();
	}
	if (s1 == s2) 
		return true;
	else
		return false; 
}


void main()
{
	string inputMessageFile = "inputMessage.txt";
	string encodedMessageFile = "encodedMessage.txt";
	string codeTableFile = "codeTableFile.txt";
	string decodedMessageFile = "decodedMessageFile.txt";

	Huffman* huffman;

	// [Note]: we created seder and receiver in different scopes {}
	//         to simulate that the sender side is made on a machine
	//         and the receiver side on another machine
	//         the only connection between them two files sent from sender to receiver which are:
	//         1- the encoded message file
	//         2- the code table file, 
	//            but here we don't use code table file in receiver
	//            and use directly the huffman tree created by the sender
	//            for simplicity purposes only
	//            but in real world app: the 2 files sent from sender to receiver are: 1- encoded message, 2- code table file
	//            and in receiver the huffman tree should be rebuilt from the passed code table then the decoding is made

	// Sender Side

	{
		Sender sender;		
		sender.ReadMessage(inputMessageFile);
		sender.CalculateProbabilities();
		float H = sender.CalculateEntropy();

		// Encoding
		huffman = sender.Encode(encodedMessageFile);
		huffman->printCodeTable(codeTableFile);
		float L = huffman->CalcAvgCWLength();
		
		cout<<"Source Entropy (H) = " << H << endl;
		cout<<"Average Codeword Length (L) = " << L <<  endl;
		cout<<"(H/L) ratio  " << H/L << endl <<endl;
		
	}
	// Receiver Side

	{
		Receiver receiver(huffman); //1- passing the huffman tree to reciver
		receiver.ReadEncodedMessage(encodedMessageFile); //2- passing te encoded message

		//Decoding
		receiver.Decode(decodedMessageFile);
	}

	bool correctlyDecoded = CompareDecodedWithOriginal(inputMessageFile, decodedMessageFile);
	cout<< (correctlyDecoded? "Yes!! correctly decoded." : "No!! not correctly decoded.") << endl;
}