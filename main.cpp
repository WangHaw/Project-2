// Still need IPO header


// main.cpp
#include "WordLadder.h"
#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
    WordLadder wl;

    // Load the dictionary file into memory
    wl.loadDictionary("dictionary345.txt");

    // Sort and deduplicate the dictionary words
    vector<string> sortedWords = wl.dictionary;
    wl.radixSort(sortedWords);
    wl.removeDuplicates(sortedWords);

    // Display all 4-letter words (can change size if needed)
    for (const string& w : sortedWords) 
    {
        if (w.size() == 4) cout << w << endl;
    }

    // Prompt user for input words
    string start, end;
    cout << "Enter start word: "; cin >> start;
    cout << "Enter end word: "; cin >> end;

    // Convert input to lowercase for consistency
    transform(start.begin(), start.end(), start.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);

    // Ensure both words are the same length
    if (start.length() != end.length()) 
    {
        cout << "Error: Words must be the same length." << endl;
        return 1;
    }

    // Check that both words exist in the dictionary
    if (!wl.dictSet.count(start) || !wl.dictSet.count(end)) 
    {
        cout << "Error: One or both words are not in the dictionary." << endl;
        return 1;
    }

    vector<string> path;

    // Find and display any transformation path (not necessarily optimal)
    if (wl.findAnyTransformation(start, end, path))
    {
        cout << "\nAny transformation path:" << endl;
        for (const string& word : path) cout << word << endl;
        cout << "Steps: " << path.size() - 1 << endl;
    }

    // Clear and find optimal (shortest) transformation path
    path.clear();
    if (wl.findOptimalTransformation(start, end, path)) 
    {
        cout << "\nOptimal transformation path:" << endl;
        for (size_t i = 1; i < path.size(); ++i) 
        {
            cout << wl.formatTransformation(path[i - 1], path[i]) << endl;
        }
        cout << "Steps: " << path.size() - 1 << endl;
    }

    return 0;
}
