#include "../Solution/dictionary_sampler.h"

#include <cassert>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

int countWords(const string &text)
{
    stringstream ss(text);
    string token;
    int count = 0;

    while (ss >> token)
    {
        count++;
    }

    return count;
}

bool hasNoEdgeWhitespace(const string &text)
{
    if (text.empty())
    {
        return true;
    }

    return !isspace(static_cast<unsigned char>(text.front())) &&
           !isspace(static_cast<unsigned char>(text.back()));
}

int main()
{
    const string path = "Tests/fake_clean_corpus.txt";

    string text = prepareText(path, 5);
    assert(text == "mot hai ba bon nam");
    assert(countWords(text) == 5);
    assert(hasNoEdgeWhitespace(text));

    string allText = prepareText(path, 10);
    assert(allText == "mot hai ba bon nam sau bay");
    assert(countWords(allText) == 7);
    assert(hasNoEdgeWhitespace(allText));

    assert(prepareText(path, 0).empty());
    assert(prepareText("Tests/missing_file.txt", 5).empty());

    return 0;
}
