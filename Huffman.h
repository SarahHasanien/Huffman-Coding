#pragma once

#include "Symbol.h"

#include <set>
#include <vector>
#include <map>
#include <string>
#include<algorithm>
#include <fstream>
#include <iostream>
using namespace std;

// Define the tree node of the huffman tree struct here ...
struct Node {
	// symbol only meaningful if the node is a leaf node
	char symbol; //[Note]: symbol here should be of type char not "Symbol" struct
				 //        because it willl be sent later to reciever
				 //		   which should not anything else other than the symbol and codeword
				 //		   without knowing the probabilies
	// the binary codeword of the symbol
	string codeWord;

	// the left node
	Node* left;
	//the right node
	Node* right;
	// probability
	float probability;;
};


class Huffman
{
private:
	// huffman tree to generate the huffman codeword corresponding to each symbol
	Node* tree;

	// you can add a map data member that mapes: <symbol char, its codeword> 
	// or use the tree only (as you like)
	//..
	map<char,string> codeTable;
	map<char,float> codeTableProbability;
	void traverseTree(Node * tree,string s);
public:
	// Constructor and destructor
	Huffman();
	~Huffman();
		

	// A function to build the Huffman tree
	// using the passed symbols of the sender
	// [Note]: the huffman algorithm is written in this function
	// [Note]: the passed symbols have their probabilities calculated already in sender side
	void buildTree(vector<Symbol>& senderSymbols);

	// A function to print the code table computed from the buildTree above.
	// prints the codeword of each symbol to the passed file
	void printCodeTable(string codeTableFile);

	// uses the tree built previously to encode the passed message
	// the encoding logic is written here
	// and will be called by sender
	string EncodeMessage(string inputMessage);

	// uses the tree built previously to decoe the passed encoded message
	// the decoding logic is written here 
	// and will be called by reciever
	string DecodeMessage(string encodedMessage);

	// calculates the average code word length of the generated code table
	// [Note]: calculating entropy doesn't depend on code words, so written in sender side
	//         however, average code word length depends on codewords, so witten here in huffman
	float CalcAvgCWLength();
	
};

