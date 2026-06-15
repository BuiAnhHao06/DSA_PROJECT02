#define main project_main
#include "../Solution/main.cpp"
#undef main

#include <cassert>
#include <string>

using namespace std;

TrieNode *walkPath(TrieNode *root, const string &word)
{
    TrieNode *cur = root;

    for (char c : word)
    {
        cur = findChild(cur, c);
        if (cur == nullptr)
        {
            return nullptr;
        }
    }

    return cur;
}

void assertTerminalWord(TrieNode *root, const string &word)
{
    TrieNode *node = walkPath(root, word);

    assert(node != nullptr);
    assert(node->is_end_of_word);
    assert(node->word_length == static_cast<int>(word.length()));
}

int main()
{
    TrieNode *root = createNode('/');

    insertWord(root, "abc");
    insertWord(root, "abcd");
    insertWord(root, "abx");
    insertWord(root, "san sale");

    assert(findChild(root, 'a') != nullptr);
    assert(findChild(root, 's') != nullptr);
    assert(findChild(root, 'z') == nullptr);

    assertTerminalWord(root, "abc");
    assertTerminalWord(root, "abcd");
    assertTerminalWord(root, "abx");
    assertTerminalWord(root, "san sale");

    TrieNode *ab = walkPath(root, "ab");
    assert(ab != nullptr);
    assert(!ab->is_end_of_word);
    assert(findChild(ab, 'c') != nullptr);
    assert(findChild(ab, 'x') != nullptr);

    TrieNode *san = walkPath(root, "san");
    assert(san != nullptr);
    assert(!san->is_end_of_word);
    assert(findChild(san, ' ') != nullptr);

    freeTrie(root);

    return 0;
}
