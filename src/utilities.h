#include <string>

char
complement(char c);

std::string
complement(std::string * s);

std::string
reverse(std::string * s);

std::string
reverseComplement(std::string * s);

bool
hasTSO(std::string* seq, int thresholdDist=2, std::string TSO="AAGCAGTGGTATCAACGCAGAGTACATGGG", int searchSize=1000);

bool
hasFullTSO(std::string* seq, int thresholdDist, std::string TSO, int searchSize=2000);