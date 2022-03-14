#include <string>
#include <algorithm>
#include <iostream>

#include "utilities.h"
#include "fuzzyMatch.h"
#include "definitions.h"

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

/*
    checks whether a seq is a TSO artifact or not
*/
bool
isTSOArtifact(std::string* seq, int thresholdDist, std::string TSO, int searchSize)
{
    auto
    size = std::min((int)seq->size(), searchSize);

    auto
    TSOSize = TSO.size();

    std::string
    TSORevComp = reverseComplement(&TSO);

    Stats stats;
    std::vector<int>
    TSOPositions, TSORevCompPositions;
    for (int i = 0; i < size; ++i) {
        if (isFuzzyMatch(seq, i, &TSO, 0, 0, thresholdDist)) {
            stats["TSO"]++;
            TSOPositions.push_back(i);
            //  jump i forward a bit
            i += TSOSize;
        }

        if (isFuzzyMatch(seq, i, &TSORevComp, 0, 0, thresholdDist)) {
            stats["TSORevComp"]++;
            TSORevCompPositions.push_back(i);
            i += TSOSize;
        }
    }

    //  artifact contains both TSO and TSO rev comp
    if (stats["TSO"] > 0 && stats["TSORevComp"]) {
        return true;
    }

    //  artifact contains multiple TSOs or multiple TSO rev comps
    if (stats["TSO"] > 1 || stats["TSORevComp"] > 1) {
        return true;
    }

    //  otherwise, it's a normal read
    return false;
}