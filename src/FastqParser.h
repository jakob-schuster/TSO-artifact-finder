#include <string>

#include "definitions.h"

class FastqParser
{
    private:
        Stats stats;
        Filename inFilename, outFilename;
        int sampleReads, thresholdDist;
        std::string TSO;
    
    public:
        FastqParser(Filename, Filename, int sampleReads, std::string TSO);

        Stats
        parse();

        void
        getStats();

        float
        percentage();
};