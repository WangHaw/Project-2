/*
  File   : WordLadder.h
  Purpose: Declares the WordLadder class and its core methods for dictionary loading,
           sorting, duplicate removal, and word transformation logic.
*/

// WordLadder.h
#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// WordLadder class manages word dictionary and transformation logic
class WordLadder
{

public:
	// All loaded words
	vector<string> dictionary;

	// Fast lookup set for words
	unordered_set<string> dictSet;

	// Loads words from file into dictionary and converts them to lowercase
	void loadDictionary(const string& filePath);

	// Sorts words lexicographically using radix sort and queues
	void radixSort(vector<string>& words);

	// Removes duplicate words using a hash set
	void removeDuplicates(vector<string>& words);

	// Finds all valid 1-letter transformations of a given word
	vector<string> getImmediateTransformations(const string& word);

	// Finds any transformation path from start to end word (not necessarily shortest)
	bool findAnyTransformation(const string& start, const string& end, vector<string>& path);

	// Finds the shortest transformation path from start to end word
	bool findOptimalTransformation(const string& start, const string& end, vector<string>& path);

	// Highlights the character change between two words, formatted {x->y}
	string formatTransformation(const string& from, const string& to);

};

// WORDLADDER_H
#endif 
