/*
  File   : WordLadder.cpp
  Purpose: Implements the core methods for the WordLadder class, including
           loading, sorting, deduplication, and word transformation logic.
*/

// Didnt organized yet

// WordLadder.cpp
#include "WordLadder.h"
#include <fstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <iostream>

using namespace std;

// Load dictionary file and convert each word to lowercase for consistency
void WordLadder::loadDictionary(const string& filePath)
{
    ifstream file(filePath);
    string word;
    while (file >> word)
    {
        transform(word.begin(), word.end(), word.begin(), ::tolower); // normalize case
        dictionary.push_back(word);
        dictSet.insert(word);
    }
}

// Task 1: Sorts words lexicographically using Radix Sort - Hawjun
// Sorts words lexicographically using Radix Sort (right-to-left character passes)
void WordLadder::radixSort(vector<string>& words)
{
    if (words.empty()) return;
    size_t maxLen = words[0].size();

    // Process characters from last to first
    for (size_t pos = maxLen; pos-- > 0; )
    {
        vector<queue<string>> buckets(26); // 26 buckets for a-z

        for (const string& word : words)
        {
            // Validate position before bucket indexing
            if (word.size() != maxLen || word[pos] < 'a' || word[pos] > 'z') continue;
            buckets[static_cast<size_t>(word[pos]) - static_cast<size_t>('a')].push(word);

        }

        words.clear();
        for (auto& bucket : buckets)
        {
            while (!bucket.empty())
            {
                words.push_back(bucket.front());
                bucket.pop();
            }
        }
    }
}
// Task 2: Removes duplicates from the word list using a set to track seen entries - Meena
// Removes duplicates from the word list using a set to track seen entries
void WordLadder::removeDuplicates(vector<string>& words)
{
    unordered_set<string> seen;
    vector<string> unique;
    for (const string& word : words)
    {
        if (!seen.count(word))
        {
            seen.insert(word);
            unique.push_back(word);
        }
    }
    words = unique;
}

// Task 3: Returns all words that differ by exactly one character and exist in the dictionary - Hawjun
// Returns all words that differ by exactly one character and exist in the dictionary
vector<string> WordLadder::getImmediateTransformations(const string& word)
{
    vector<string> result;
    string temp = word;

    for (size_t i = 0; i < word.size(); ++i)
    {
        char original = temp[i];

        for (char c = 'a'; c <= 'z'; ++c)
        {
            if (c == original) continue; // skip same character
            temp[i] = c;
            if (dictSet.count(temp))
            {
                result.push_back(temp);
            }
        }
        temp[i] = original; // restore original character
    }
    return result;
}

// Task 4: Finds any valid transformation path using BFS (not necessarily shortest) - Meena
// Finds any valid transformation path using BFS and reconstructs it using a stack
bool WordLadder::findAnyTransformation(const string& start, const string& end, vector<string>& path)
{
    unordered_set<string> visited;
    unordered_map<string, string> parent;
    stack<string> stk;
    queue<string> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty())
    {
        string current = q.front(); q.pop();
        if (current == end) break;

        for (const string& neighbor : getImmediateTransformations(current))
        {
            if (!visited.count(neighbor))
            {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    // no path found
    if (!parent.count(end)) return false;

    // Reconstruct path from end to start using stack
    string trace = end;
    while (trace != start)
    {
        stk.push(trace);
        trace = parent[trace];
    }
    stk.push(start);

    while (!stk.empty()) 
    {
        path.push_back(stk.top());
        stk.pop();
    }
    return true;
}

// Task 5: Finds the shortest transformation path using BFS - Meena
// Finds the shortest transformation path using BFS
bool WordLadder::findOptimalTransformation(const string& start, const string& end, vector<string>& path) 
{
    unordered_map<string, string> parent;
    unordered_set<string> visited;
    queue<string> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty())
    {
        string current = q.front(); q.pop();
        if (current == end) break;

        for (const string& neighbor : getImmediateTransformations(current))
        {
            if (!visited.count(neighbor))
            {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    if (!parent.count(end)) return false; // no path found

    // Reconstruct path by following parent links
    stack<string> stk;
    for (string at = end; at != start; at = parent[at])
        stk.push(at);
    stk.push(start);

    while (!stk.empty())
    {
        path.push_back(stk.top());
        stk.pop();
    }
    return true;
}

// Task 6: Describes a one-letter change between two words in the format: "word1 {x->y} word2" - Meena
// Describes a one-letter change between two words in the format: "word1 {x->y} word2"
string WordLadder::formatTransformation(const string& from, const string& to)
{
    for (size_t i = 0; i < from.size(); ++i)
    {
        if (from[i] != to[i]) 
        {
            return from + " {" + from[i] + "->" + to[i] + "} " + to;
        }
    }
    return from + " -> " + to;
}

