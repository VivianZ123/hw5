#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    for (char c : floating) {
        floating_counts[c]++;
    }

    void generate(int index) {
        if (index == in.size()) {
            if (all floating letters are used and current_word is in dict) {
                results.insert(current_word);
            }
            return;
        }

        if (in[index] != '-') {
            current_word[index] = in[index];
            generate(index + 1);
        } else { 
            for (char c = 'a'; c <= 'z'; c++) {
                current_word[index] = c;
                if (floating_counts[c] > 0) {
                    floating_counts[c]--;
                    generate(index + 1);
                    floating_counts[c]++;
                } else {
                    generate(index + 1);
                }
            }
        }
        current_word[index] = '-';
    }

    generate(0);
    return results;
}

// Define any helper functions here
