#ifndef TRIEUTIL_H_
#define TRIEUTIL_H_
#include <bits/stdc++.h>

using namespace std;

const int CELLPHONE_SIZE = 11;

struct TrieNode 
{ 
	struct TrieNode *children[CELLPHONE_SIZE]; 

	// isEndOfWord is true if the node represents 
	// end of a word 
	bool isEndOfWord; 
}; 

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void);


void insert(struct TrieNode *root, string key);
bool search(struct TrieNode *root, string key);


#endif
