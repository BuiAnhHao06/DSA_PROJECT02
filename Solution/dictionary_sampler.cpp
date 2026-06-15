#include "dictionary_sampler.h"

#include <algorithm>
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
