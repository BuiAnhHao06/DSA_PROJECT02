#include "dictionary_sampler.h"

#include <algorithm>
#include <fstream>
#include <random>

using namespace std;

std::vector<std::string> sampleDictionary(const std::vector<std::string> &dictionary, int K, unsigned int seed)
{
    vector<string> temp = dictionary;

    mt19937 rng(seed);

    shuffle(temp.begin(), temp.end(), rng);

    if (K > temp.size())
    {
        K = temp.size();
    }

    vector<string> sample;

    for (int i = 0; i < K; i++)
    {
        sample.push_back(temp[i]);
    }

    return sample;
}

std::string prepareText(const std::string &filename, int N)
{
    if (N <= 0)
    {
        return "";
    }

    ifstream file(filename);
    if (!file.is_open())
    {
        return "";
    }

    string result;
    string token;
    int count = 0;

    while (count < N && file >> token)
    {
        if (!result.empty())
        {
            result += ' ';
        }
        result += token;
        count++;
    }

    return result;
}
