# Memory Checklist for Aho-Corasick

Use this checklist before and after implementing `ahoCorasickSearch`.

- Allocate the match buffer once with `new Match[MAX_SIZE]`.
- Keep a separate `matchCount` and never write past `MAX_SIZE`.
- Call `delete[] matches` before every return path after allocation.
- Do not use `std::vector` inside `ahoCorasickSearch`.
- Build Trie nodes only through `createNode`.
- Release the whole Trie with `freeTrie(root)` after each test or benchmark run.
- Do not delete child or sibling pointers manually after calling `freeTrie(root)`.
- Do not reuse a `TrieNode*` after it has been passed to `freeTrie`.
- Copy the original text before each search engine because masking mutates the string.
- For future leak checks, compile with debug symbols and run a small case under Valgrind or AddressSanitizer.
