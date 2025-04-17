
/*
------------------------------------------------------------
  Project: Word Ladder Transformation
  File   : main.cpp
  Author : Hawjun Wang, Meena Rahmani
  Date   : 4/16/2025

  Input:
- A dictionary file containing valid 3, 4, and 5-letter words.
- Start and end words from the user (same length, lowercase).

  Processing:
- Loads and normalizes the dictionary.
- Sorts words lexicographically using radix sort and queues.
- Removes duplicates.
- Validates user input for word length and existence in dictionary.
- Finds any valid transformation path using BFS.
- Finds the optimal (shortest) transformation path.
- Tracks each transformation using stack to reconstruct path.
- Displays character differences in `{x->y}` format.

  Output:
- Sorted list of dictionary words (filtered by length).
- Any transformation path from start to end.
- Shortest transformation path with character differences.
- Number of steps in each transformation sequence.
------------------------------------------------------------
*/

// main.cpp
#include "WordLadder.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	// Output heading and divider - Meena
	OutputHeading((ofstream&)cout);
	OutputDivider(cout, '-', SCREEN_WIDTH);

	WordLadder wl;

	// Load the dictionary file into memory - Hawjun
	wl.loadDictionary("dictionary345.txt");

	// Sort and deduplicate the dictionary words - Hawjun
	vector<string> sortedWords = wl.dictionary;
	wl.radixSort(sortedWords);
	wl.removeDuplicates(sortedWords);

	// Display all 4-letter words (can change size if needed)
	for (const string& w : sortedWords)
	{
		if (w.size() == 4) cout << w << endl;
	}

	// --- Task 4: Immediate Transformation ---

	// Display task number for clarity
	cout << endl;
	cout << "//-----------------------------------------------------//" << endl;
	cout << "//                       Task 4                        //" << endl;
	cout << "//-----------------------------------------------------//" << endl;

	// Prompt the user to enter a word to find its immediate transformations
	string wordToTransform;
	cout << "Enter a word to find immediate transformations: ";
	cin >> wordToTransform;  // User input word

	// Convert the input word to lowercase for consistency (to match dictionary)
	transform(wordToTransform.begin(), wordToTransform.end(), wordToTransform.begin(), ::tolower);

	// Get the list of words that differ by exactly one character and are in the dictionary
	vector<string> transformations = wl.getImmediateTransformations(wordToTransform);

	// Display the immediate transformations or a message if no transformations exist
	cout << "\nImmediate transformations of \"" << wordToTransform << "\":" << endl;

	// If no valid transformations are found
	if (transformations.empty())
	{
		cout << "No valid transformations found." << endl;
	}

	// If transformations are found, print each one
	else
	{
		for (const string& word : transformations)
		{
			// Display each valid transformation
			cout << word << endl;
		}
	}


	// Prompt user for input words - Hawjun
	string start, end;

	cout << endl;
	cout << "//-----------------------------------------------------//" << endl;
	cout << "Enter start word: "; cin >> start;
	cout << "//-----------------------------------------------------//" << endl << endl;

	cout << "//-----------------------------------------------------//" << endl;
	cout << "Enter end word: "; cin >> end;
	cout << "//-----------------------------------------------------//" << endl << endl;

	// Convert input to lowercase for consistency
	transform(start.begin(), start.end(), start.begin(), ::tolower);
	transform(end.begin(), end.end(), end.begin(), ::tolower);

	// Ensure both words are the same length - Meena
	if (start.length() != end.length())
	{
		cout << "Error: Words must be the same length." << endl;
		return 1;
	}

	// Check that both words exist in the dictionary - Hawjun
	if (!wl.dictSet.count(start) || !wl.dictSet.count(end))
	{
		cout << "Error: One or both words are not in the dictionary." << endl;
		return 1;
	}

	vector<string> path;

	// Find and display any transformation path (not necessarily optimal) - Meena
	if (wl.findAnyTransformation(start, end, path))
	{
		cout << "//-----------------------------------------------------//" << endl;
		cout << "//                       Task 5                        //" << endl;
		cout << "//-----------------------------------------------------//" << endl;

		cout << "\nAny transformation path:" << endl;
		for (const string& word : path) cout << word << endl << endl;

		cout << "//-----------------------------------------------------//" << endl;
		cout << "Steps: " << path.size() - 1 << endl;
	}

	// Clear and find optimal (shortest) transformation path - Meena
	path.clear();
	if (wl.findOptimalTransformation(start, end, path))
	{
		cout << "//-----------------------------------------------------//" << endl;
		cout << "//                       Task 6                        //" << endl;
		cout << "//-----------------------------------------------------//" << endl;

		cout << "\nOptimal transformation path:" << endl;
		for (size_t i = 1; i < path.size(); ++i)
		{
			cout << wl.formatTransformation(path[i - 1], path[i]) << endl;
		}

		cout << "//-----------------------------------------------------//" << endl;
		cout << "Steps: " << path.size() - 1 << endl << endl;
	}

	return 0;
}
