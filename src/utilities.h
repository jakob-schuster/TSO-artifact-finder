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
hasTSO(std::string* seq, int thresholdDist=4, std::string TSO="AAGCAGTGGTATCAACGCAGAGTACATGGG", int searchSize=1000);