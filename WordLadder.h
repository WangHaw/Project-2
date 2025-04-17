/*
  File   : WordLadder.h
  Purpose: Declares the WordLadder class and its core methods for dictionary loading,
		   sorting, duplicate removal, and word transformation logic.
*/

// WordLadder.h
#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// Constants - Meena
const string COLLEGE_NAME = "SUNY Broome Community College";
const string NAME = "Meena Rahmani - Hawjun Wang";
const string COURSE_INFO = "CST - 202  Project 2";

// Width used for formatting output
const int SCREEN_WIDTH = 80;

// Function to output the heading of the program to a file stream
void OutputHeading(ofstream& fout);

// Function to output a divider line 
void OutputDivider(ostream& out, char character, int width);


// WordLadder class manages word dictionary and transformation logic
class WordLadder
{

public:

	// All loaded words
	vector<string> dictionary;

	// Fast lookup set for words
	unordered_set<string> dictSet;

	// Loads words from file into dictionary and converts them to lowercase - Hawjun
	void loadDictionary(const string& filePath);

	//Task 1: Lexicographic Sort(Radix Sort) - Hawjun
	// Sorts words lexicographically using radix sort and queues
	void radixSort(vector<string>& words);

	//Task 2: Remove Duplicates - Meena
	// Removes duplicate words using a hash set
	void removeDuplicates(vector<string>& words);

	//Task 3: Find All Valid One - Character Transformations - Hawjun
	// Finds all valid 1-letter transformations of a given word
	vector<string> getImmediateTransformations(const string& word);

	//Task 4: Find One Valid Transformation Path - Meena
	// Finds any transformation path from start to end word (not necessarily shortest)
	bool findAnyTransformation(const string& start, const string& end, vector<string>& path);

	//Task 5: Find Optimal(Shortest) Transformation Path - Meena
	// Finds the shortest transformation path from start to end word
	bool findOptimalTransformation(const string& start, const string& end, vector<string>& path);

	// Task 6: Show Character Changes During Transformation - Hawjun, Meena
	// Highlights the character change between two words, formatted {x->y}
	string formatTransformation(const string& from, const string& to);

};

// WORDLADDER_H
#endif
