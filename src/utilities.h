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
isTSOArtifact(std::string* seq, int thresholdDist, std::string TSO, int searchSize=2000);