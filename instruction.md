# LAB 2: VIETNAMESE TEXT PREPROCESSING SYSTEM WITH TRIE AND AHO-CORASICK ALGORITHM

## 1. Real-world Problem
In the era of Artificial Intelligence (AI) and Data Science, your system collects tens of millions of raw text documents from the Internet every day. For Large Language Models (LLMs) to learn standard knowledge, the first and most crucial step is Preprocessing. You must clean the data by masking tens of thousands of junk keywords belonging to a Noise Dictionary, which includes:
- **Stop-words**: Meaningless phrases (e.g., "tuy nhiên" - however, "mặc dù là" - although).
- **Spam/SEO Keywords**: Junk advertising phrases (e.g., "quang cao shopee", "san sale gia re").

## 2. String Matching Algorithms
In previous lessons, you were introduced to the KMP (Knuth-Morris-Pratt) algorithm. KMP works extremely efficiently, but it only solves the Single-pattern problem (finding 1 pattern in 1 text). When dealing with tens of thousands of patterns, if you run KMP repeatedly for each text segment, the system will crash in terms of execution time.

To solve the Multi-pattern Search problem, this project requires you to implement and analyze the evolution of 4 approaches:
- **(0) Naive Search**: The most naive exhaustive approach, processing each pattern independently.
- **(1) Trie (Standard)**: Using a Prefix Tree to group keywords sharing the same prefix, traversing the text, and searching along the branches.
- **(2) Optimized Trie with Maximal Munch**: A "Greedy" strategy combined with Trie to jump over masked words, eliminating redundant loops.
- **(3) Aho-Corasick**: The perfect combination of a Trie and the Automaton concept of KMP. It allows scanning through the text at a static linear speed without ever having to backtrack the pointer.

## 3. Provided Data Structures (Input Data)
You are provided with 3 main components:
- **`trie_node.h` file**: Contains definitions of mandatory data structures:
  - `struct Match { int start; int end; };` (Stores the position of the found keyword).
  - `struct TrieNode`: Defines a node of the Trie tree using the First-Child / Next-Sibling design to save RAM.
- **`noise_dict_50k.txt` file**: A dictionary containing 50,000 noise phrases (each phrase on 1 line).
- **`clean_corpus.txt` file**: A large text corpus containing millions of words, acting as the input data. (Data source extracted from: HuggingFace - Vietnamese News Classification).

> [!IMPORTANT]
> **Important Note**: Each line in this corpus file is considered an independent document.

---

## 4. Implementation Steps & Technical Requirements
You need to write a C++ program that sequentially executes the following steps:

### Step 1: Load & Sample Data
The system does not run directly on the entire file but must have a dynamic sampling mechanism for each test run:
- **Prepare Text ($N$ words)**: Read the `clean_corpus.txt` file, extract words based on spaces or newline characters. Collect exactly $N$ words, then put them into a single string variable by concatenating the words, separated by a single space `' '`.
- **Prepare Dictionary ($K$ patterns)**: Read the entire list from the `noise_dict_50k.txt` file. For each run, you must **RANDOMLY** pick $K$ patterns from this list to insert into the Dictionary Array or Trie.
  *(Strictly prohibit taking the first $K$ sequential elements to avoid distribution bias. Students are ALLOWED to use `std::shuffle` from `<algorithm>` and `<random>` in this step to shuffle the dictionary).*

### Step 2: Implement Core Structure Functions
Implement the functions with the exact signatures and behaviors as follows:

```cpp
// Initialization and memory deallocation
TrieNode* createNode(char c);
void freeTrie(TrieNode* root);

// Structure building
void insertWord(TrieNode* root, const string& word);
void buildFailureLinks(TrieNode* root);

// Self-implemented sorting algorithm (for Aho-Corasick)
void sortMatches(Match* arr, int count);
```

- **Technical Requirements**: 
  - The `insertWord` function must operate on the First-Child / Next-Sibling linked list.
  - The `freeTrie` function must completely clean up the entire Heap.
  - The `sortMatches` function implements an algorithm (e.g., QuickSort) prioritizing ascending `start`; if `start` are equal, descending `end`.

### Step 3: Implement Search Engines
The search functions are tasked with finding and replacing (masking) **all** characters of the found keyword directly (in-place) with the `*` character on the input string (Example: The keyword "san sale" with 8 characters will be replaced by 8 asterisks `********`). The search process matches by substring matching.

```cpp
void naiveSearch(const vector<string>& dict, string& text);
void trieSearch(TrieNode* root, string& text);
void trieMaximalMunchSearch(TrieNode* root, string& text);
void ahoCorasickSearch(TrieNode* root, string& text);
```

- **`naiveSearch`**: This algorithm is "naive" because it does not use any data structures. It loops through each keyword in the `dict` array, and for each keyword, it scans along the entire length of the `text` string to find and mask. This means the text will be scanned repeatedly $K$ times independently.
- **`trieSearch`**: Scans the text from left to right, using Trie branches to traverse. Must implement a backtracking logic when matching fails in the middle of a phrase.
- **`trieMaximalMunchSearch`**: Greedy algorithm. Once the longest phrase starting at position $i$ is masked, the iterator $i$ is allowed to jump over the masked portion to save loop steps.
- **`ahoCorasickSearch`**: Uses the `fail_link` pointer to traverse continuously. It must collect ALL overlapping results into an array `Match*`, sort this array using `sortMatches`, and then iterate through the array one final time to mask the `text` with `*`.

---

## 5. Rules & Constraints
- **Testing Mechanism (Anti-Mutation)**: Because the Search functions replace characters directly with `*` in-place on the `text` string, when testing the 4 algorithms, you MUST copy the original text string into 4 independent copies before passing them into the timing functions. If this is not done, from the 2nd algorithm onwards, it will only search on a string full of `*` and return an artificially low time.
- **Dynamic Array Management Ban**: Strictly prohibit using `std::vector` (especially `.push_back()`) inside the `ahoCorasickSearch` engine. You are required to use a statically allocated array on the heap: `Match* matches = new Match[MAX_SIZE];` to prevent the OS reallocation bottleneck.
- **Algorithm Library Ban**: Strictly prohibit using `std::sort` for sorting the result array, and do not use `std::regex` or built-in search functions as search engines. (Note: Only `std::shuffle` is allowed in the main function for random sampling).

## 6. Assumptions & Clarifications
- **Space Character**: Is considered a normal Character. Searching is computed character by character (including letters, numbers, punctuation, spaces).
- **Case-sensitivity**: The system distinguishes between uppercase and lowercase letters ('A' is different from 'a').
- **Result Array Size**: For static allocation purposes, assume the maximum number of overlapping keywords found in a text will not exceed 2,000,000 matches.
- **Benchmark Timing**: Mandatory use of `<chrono>`. Only measure the execution time of the Search functions. Do not include the time for reading files, random sampling, or building the Trie in the timer.

---

## 7. Output & Submission Requirements

### 7.1. Empirical Benchmark
The system must automatically run experiments and get the **Average of 100 runs** for each search function on the 2 following Scenarios:

#### Scenario 1: Fixed Dictionary ($K=10,000$ patterns), Increasing Text Length ($N$)
- Word milestones: $N \in \{10,000, 30,000, 100,000, 300,000, 1,000,000, 3,000,000, 10,000,000\}$ words.

| Extracted Text Volume ($N$) | Naive Search (s) | Standard Trie (s) | Trie+Maximal Munch (s) | Aho-Corasick (s) |
| :-------------------------------| :----------------:| :-----------------:| :----------------------:| :----------------:|
| **10,000 words**               |                  |                   |                        |                  |
| **30,000 words**               |                  |                   |                        |                  |
| **100,000 words**              |                  |                   |                        |                  |
| **300,000 words**              |                  |                   |                        |                  |
| **1,000,000 words**            |                  |                   |                        |                  |
| **3,000,000 words**            |                  |                   |                        |                  |
| **10,000,000 words**           |                  |                   |                        |                  |

#### Scenario 2: Fixed Text ($N=1,000,000$ words), Increasing Dictionary ($K$)
- Pattern milestones: $K \in \{1,000, 3,000, 5,000, 10,000, 30,000, 50,000\}$ patterns.

| Dictionary Size ($K$) | Naive Search (s) | Standard Trie (s) | Trie+Maximal Munch (s) | Aho-Corasick (s) |
| :-------------------------| :----------------:| :-----------------:| :----------------------:| :----------------:|
| **1,000 phrases**        |                  |                   |                        |                  |
| **3,000 phrases**        |                  |                   |                        |                  |
| **5,000 phrases**        |                  |                   |                        |                  |
| **10,000 phrases**       |                  |                   |                        |                  |
| **30,000 phrases**       |                  |                   |                        |                  |
| **50,000 phrases**       |                  |                   |                        |                  |

*(Print all measurement results to the Console).*

### 7.2. Submission Format
Create a compressed file in `.zip` format with the naming syntax: `[StudentID1]_[StudentID2]_Lab2.zip`. 

Submission directory structure:
```plaintext
[StudentID1]_[StudentID2]_Lab2/
│
├── Solution/
│   ├── main.cpp
│   ├── trie_node.h
│   └── (other .cpp/.h files defined by you)
│
└── Report.pdf
```

> [!WARNING]
> **Warning**: Do not include executable files (`.exe`, `.o`), build directories (`.vs`, `cmake`), and absolutely **DO NOT** attach the data files.

### 7.3. PDF Report & Discussion Guidelines
Create tables and plot 2 Line Charts comparing the 4 algorithms based on the data obtained from the Console to show the time growth trends. 
> [!TIP]
> **Charting Tip**: If the data on a certain axis (e.g., the Time axis) grows exponentially or there is an extremely large discrepancy between algorithms (like Naive Search and Aho-Corasick), students should use a Logarithmic Scale to transform that axis, helping the chart appear balanced, intuitive, and easier to observe.

Based on the obtained results, answer the following issues based on the guidelines:

#### 7.3.1. Topic 1: The Backtracking Bottleneck
**Analysis Guidelines**:
- Based on the graph for Scenario 1 (Increasing text length $N$), compare and explain the difference in execution time growth trends between `trieSearch` (Standard Trie) and `ahoCorasickSearch`.
- Analyze the root cause leading to this difference based on theoretical complexity. Specifically, explain the role of the "Backtracking" mechanism in the Standard Trie compared to the "Failure Link" (Automaton) mechanism of Aho-Corasick.
- Design and describe an Adversarial Dataset - including a small dictionary and a text snippet - such that the Standard Trie algorithm is forced to perform the worst-case backtracking.

#### 7.3.2. Topic 2: Dictionary Scalability Impact
**Analysis Guidelines**:
- Based on the graph for Scenario 2 (Increasing keyword count $K$), comment on the shape of the graph and the growth rate of the execution time of `naiveSearch` compared to tree-structure algorithms (Trie, AC).
- Analyze the mathematical property of Aho-Corasick: *"Searching in linear time $\mathcal{O}(N)$ is almost independent of the Dictionary scale"*. Explain why when $K$ increases tenfold, the text scanning time of Aho-Corasick does not multiply correspondingly.
- Analysis: Even though the Automaton scanning time is $\mathcal{O}(N)$, why does the actual measured time of Aho-Corasick still show a slight upward trend when $K$ reaches a very large milestone (50,000)? *(Hint: Consider the operation of collecting and sorting the output results).*

#### 7.3.3. Topic 3: Algorithm Strategy - Maximal Munch vs. All-Matches
**Analysis Guidelines**:
- Compare the empirical execution time between `trieSearch` and `trieMaximalMunchSearch`. Analyze the "Greedy" mechanism and the "Jump" behavior that helped Maximal Munch eliminate which redundant loops?
- Despite running very fast, the Maximal Munch strategy trades off by causing Data Loss. Analyze what valid results this algorithm will skip if there are many nested keywords appearing in the text.
- Provide an example of a real-world NLP problem (other than filtering junk words) where applying Maximal Munch is reasonable, and a real-world problem that strictly requires the All-matches scanning strategy of Aho-Corasick.