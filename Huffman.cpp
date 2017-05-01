#include "Huffman.h"

// Constructor and destructor
	Huffman::Huffman(){
	}
	Huffman::~Huffman(){
		//free the tree
	}
	
	bool operator< (const pair<int,Node*> p1, const pair<int,Node*> p2)
	{
		// this function is used in the sorting function 
		return p1.first < p2.first;
	}

	// A function to build the Huffman tree
	// using the passed symbols of the sender
	// [Note]: the huffman algorithm is written in this function
	// [Note]: the passed symbols have their probabilities calculated already in sender side
	void Huffman::buildTree(vector<Symbol>& senderSymbols)
	{
		
		//Create a set ... Initilally carrying all the symbols and is sorted based on
		multiset<pair<int,Node*>> setSymbols;
		for (std::vector<Symbol>::iterator it = senderSymbols.begin() ; it != senderSymbols.end(); ++it){
			Node* n = new Node();
			n->symbol = ((Symbol)(*it)).value;
			n->left= NULL;
			n->right= NULL;
			setSymbols.insert(pair<int,Node*>(((Symbol)(*it)).frequency,n));
			codeTableProbability.insert(pair<char,float>(n->symbol,((Symbol)(*it)).probability));
	}
		while(setSymbols.size()> 1){
			multiset<pair<int,Node*>>::iterator firstIt = setSymbols.begin();
			multiset<pair<int,Node*>>::iterator secondIt = ++setSymbols.begin();
			Node * n = new Node();
			n->left= ((pair<int,Node*>)(*firstIt)).second;
			n->right= ((pair<int,Node*>)(*secondIt)).second;
			n->probability = 0.0;
			int freq = ((pair<int,Node*>)(*firstIt)).first+((pair<int,Node*>)(*secondIt)).first;
			setSymbols.erase(firstIt);
			setSymbols.erase(secondIt);
			setSymbols.insert(pair<int,Node*> (freq,n));
		}
		if(setSymbols.size()==1)
			tree= ((pair<int,Node*>)(*setSymbols.begin())).second;
	}

	// A function to print the code table computed from the buildTree above.
	// prints the codeword of each symbol to the passed file
	void Huffman::printCodeTable(string codeTableFile)
	{
		ofstream outfile;
		outfile.open(codeTableFile,std::ofstream::out);
		for(std::map<char,string>::iterator it= codeTable.begin();it!=codeTable.end();it++){
			outfile<<((pair<char,string>)(*it)).first<<" "<<((pair<char,string>)(*it)).second<<endl;
		}
	}

	void Huffman::traverseTree( Node * ttree,string s)
	{
		// this function traverse the tree to build the code table for symbol
		if(ttree->left!=NULL){
			traverseTree(ttree->left,s+"0");
		}
		if(ttree->right!=NULL){
			traverseTree(ttree->right,s+"1");
		}
		if((ttree->left==NULL)&&(ttree->left==NULL))
			codeTable.insert(pair<char,string>(ttree->symbol,s));

	}


	string Huffman::EncodeMessage(string inputMessage){
		//TODO
		// uses the tree built previously to encode the passed message
		// and will be called by sender
		// the function firstly will call the traverse tree to construct the code table 
		// then it should encode every symbol in inputmessage using the code table 
		// finally it should return the encoded message.
		// hint use string.at(position) to access string characters individually
		traverseTree(tree,"");
		string encoded = "";
		for (int i = 0; i < inputMessage.length(); i++)
		{
			encoded += codeTable[inputMessage[i]];

		}
		return encoded;
	}

	
	string Huffman::DecodeMessage(string encodedMessage){
		//TODO
		// uses the tree built previously to decode the passed encoded message
		// the function logic is  :
		// for each encoded symbol in the "encodedMessage"
		//   start by the root of the tree 
		//   while not reaching leaf nodes 
		//     if the encoded symbol is =0 
		//        keeps traversing the left sub tree with taking next encoded symbol
		//     if the encoded symbol is =1 
		//        keeps traversing the right sub tree with taking next encoded symbol
		// the leaf node will be used to decode that encoded symbol 
		//  save all decoded messages in one string and return it 
		// and will be called by reciever
		// hint use string.at(position) to access string characters individually
		string decoded="";
		//I need to reach a leaf node to get the char value of it
		Node*n = tree;
		for (int i = 0; i < encodedMessage.size(); i++) {
		
			if (encodedMessage[i] == '0')
				n = n->left;
			
			else
				n = n->right;
			if (!n->left && !n->right)//leaf reached
			{
				decoded += n->symbol;
				n = tree;
			}
		}
		return decoded;//change this line
	}

	
	
	float Huffman::CalcAvgCWLength(){
		//TODO
		// calculates the average code word length of the generated code table
		// [Note]: calculating entropy doesn't depend on code words, so written in sender side
		//         however, average code word length depends on codewords, so witten here in huffman
		float avg = 0.0;
		for (int i = 97; i < 123; i++)
		{
			avg += codeTable[i].length()*codeTableProbability[i];
		}
		return avg;
	}