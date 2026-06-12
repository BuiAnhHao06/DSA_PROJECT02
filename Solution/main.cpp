#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <queue>
#include <iomanip>
#include "trie_node.h"

using namespace std;
using namespace std::chrono;

// ==========================================
// 1. SORTING ALGORITHM
// ==========================================

// TODO 1: Students implement the sorting algorithm (QuickSort / MergeSort)
// Requirement: Sort the Match array prioritizing ascending 'start'.
// If 'start' are equal, prioritize descending 'end'.
// Strictly DO NOT use the <algorithm> library (std::sort).
void sortMatches(Match* arr, int count) {
    // Write sorting code here...
}

// ==========================================
// 2. TRIE MEMORY MANAGEMENT
// ==========================================

// TODO 2: Dynamically allocate a new Node and manually initialize its fields
// (Assign nullptr to pointers, false to is_end_of_word, etc...)
TrieNode* createNode(char c) {
    return nullptr; 
}

// TODO 3: Traverse the tree and free memory (delete) to prevent Memory Leak
void freeTrie(TrieNode* root) {
    // Write memory deallocation code here...
}

// ==========================================
// 3. BUILDING TRIE AND FAILURE LINKS
// ==========================================

// TODO 4: Insert a word into the Trie using linked lists (first_child, next_sibling)
void insertWord(TrieNode* root, const string& word) {
    // Write insert code here...
}

// TODO 5: Use Queue (std::queue) to traverse BFS and compute fail_link pointers
// Hint: Because the Trie uses Linked Lists (first_child, next_sibling) instead of a children[256] array,
// you should write an auxiliary function `TrieNode* findChild(TrieNode* node, char c)`
// to easily find the child node when building fail_links.
void buildFailureLinks(TrieNode* root) {
    // Write failure link building code here...
}

// ==========================================
// 4. THE FOUR SEARCH ENGINES
// ==========================================

// TODO 6: Naive approach. Use 2 nested loops or std::string::find to find and mask with '*'
void naiveSearch(const vector<string>& dict, string& text) {
    // Write naive search code here...
}

// TODO 7: Traverse the text using the Trie. Need to implement backtracking logic
// when matching fails in the middle of a phrase.
void trieSearch(TrieNode* root, string& text) {
    // Write Trie search code here...
}

// TODO 8: Traverse the text using an optimized Trie with Maximal Munch (Greedy).
// When the longest phrase starting at position i is masked, the iterator i is allowed to jump.
void trieMaximalMunchSearch(TrieNode* root, string& text) {
    // Write Maximal Munch search code here...
}

// TODO 9: Traverse the text using an Automaton (no backtracking).
// - Collect ALL overlapping results into a Match* array (statically allocated on the heap)
// - Call the sortMatches() function implemented above to sort.
// - Apply the Greedy algorithm to keep the longest non-overlapping intervals.
//   (Hint: Use a variable int last_end = -1. Iterate through the sorted Match array, if match[i].start > last_end
//    then mask with '*' and update last_end = match[i].end. Otherwise skip it because it is overlapped).
// - Execute the '*' masking and free the memory of the Match* array.
void ahoCorasickSearch(TrieNode* root, string& text) {
    // Write Aho-Corasick search code here...
}

// ==========================================
// 5. BASIC MAIN FUNCTION (FOR DEBUGGING)
// ==========================================
// NOTE: Students must write additional functions to load files, perform random sampling,
// measure execution time (chrono), and run the Benchmark loop to collect data for the report!
int main() {
    cout << "--- NLP PREPROCESSING SYSTEM ---" << endl;

    // 1. Read the dictionary
    vector<string> dictionary;
    ifstream dictFile("noise_dict_50k.txt");
    if (!dictFile.is_open()) {
        cerr << "Error: Cannot read noise_dict_50k.txt file\n";
        return 1;
    }
    string word;
    while (getline(dictFile, word)) {
        if (!word.empty()) dictionary.push_back(word);
    }
    dictFile.close();
    cout << "Loaded " << dictionary.size() << " keywords into the dictionary.\n";

    // 2. Read a small text to test accuracy
    string text = "nhieu san pham cong nghe khung tai asus expo 2012 to chuc doc lap";
    cout << "\nOriginal text: " << text << endl;

    // 3. Test Trie & Aho-Corasick
    TrieNode* root = createNode('/');
    
    // (Students can test by calling these functions after implementation)
    // for (const string& w : dictionary) insertWord(root, w);
    // buildFailureLinks(root);
    // ahoCorasickSearch(root, text);
    
    // cout << "Result: " << text << endl;

    if (root) {
        freeTrie(root);
    }
    return 0;
}