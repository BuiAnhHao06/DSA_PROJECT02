#ifndef DICTIONARY_SAMPLER_H
#define DICTIONARY_SAMPLER_H

#include <vector>
#include <string>

std::vector<std::string> sampleDictionary(const std::vector<std::string> &dictionary, int K, unsigned int seed);
std::string prepareText(const std::string &filename, int N);

#endif // DICTIONARY_SAMPLER_H
