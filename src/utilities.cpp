#include <string>
#include <algorithm>

#include "utilities.h"
#include "fuzzyMatch.h"

/*
    gets the complement of an individual character
*/
char
complement(char c)
{
    switch(c) {
        case 'A':
            return 'T';
        case 'T':
            return 'A';
        case 'G':
            return 'C';
        case 'C':
            return 'G';
    }
    return ' ';
}

/*
    gets the complement of an entire string,
    by getting the complement of each character
*/
std::string
complement(std::string * s)
{
    std::string sComplement;
    for (const auto & c : *s) {
        sComplement += complement(c);
    }
    return sComplement;
}

/*
    copies a string, reverses the copy, and returns it
*/
std::string
reverse(std::string * s)
{
    std::string sReverse (*s);
    std::reverse(sReverse.begin(), sReverse.end());
    return sReverse;
}

/*
    gets the reverse complement of an entire string
*/
std::string
reverseComplement(std::string * s) 
{
    std::string sReverse = reverse(s);
    return complement(&sReverse);
}

/*
    checks whether a seq has a TSO artifact in the first searchSize characters, 
    with some edit distance tolerance
*/
bool
hasTSO(std::string* seq, int thresholdDist, std::string TSO, int searchSize)
{
    return isFuzzyMatchPresent(seq, &TSO, searchSize, thresholdDist);
}