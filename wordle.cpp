#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <functional>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

set<string> generatePermutations(string in, const string& floating, size_t pos);

set<string> wordle(
    const string& in,
    const string& floating,
    const set<string>& dict)
{
    set<string> permutations = generatePermutations(in, floating, 0);
    set<string> validWords;

    for (const auto& word : permutations) {
        if (dict.find(word) != dict.end()) {
            validWords.insert(word);
        }
    }
    return validWords;
}
set<string> generatePermutations(string in, const string& floating, size_t pos) {
    set<string> permutations;

    if (pos == in.size()) {
        permutations.insert(in);
        return permutations;
    }
    unsigned int count = 0;
    for (size_t i = 0; i < in.length(); i++) {
        if (in[i] == '-') {
            ++count;
        }
    }
    if (count == 0) {
        permutations.insert(in);
        return permutations;
    }
    if (in[pos] == '-') {
        for (size_t i = 0; i < floating.size(); ++i) {
            in[pos] = floating[i];
            string nextFloating = floating.substr(0, i) + floating.substr(i + 1);
            auto tempPermutations = generatePermutations(in, nextFloating, pos + 1);
            permutations.insert(tempPermutations.begin(), tempPermutations.end());
        }
        if (floating.length() < count) {
            for (char c = 'a'; c <= 'z'; ++c) {
                in[pos] = c;
                auto tempPermutations = generatePermutations(in, floating, pos + 1);
                permutations.insert(tempPermutations.begin(), tempPermutations.end());
            }
        }
        in[pos] = '-';
    } else {
        auto tempPermutations = generatePermutations(in, floating, pos + 1);
        permutations.insert(tempPermutations.begin(), tempPermutations.end());
    }

    return permutations;
}