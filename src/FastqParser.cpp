#include <fstream>
#include <iostream>

#include "FastqParser.h"
#include "utilities.h"

FastqParser::FastqParser(Filename inFilename, int sampleReads, std::string TSO)
{
    this->inFilename = inFilename;
    this->sampleReads = sampleReads;
    this->TSO = TSO;
    this->TSORevComp = reverseComplement(&TSO);
    this->thresholdDist = 2;
}

Stats
FastqParser::parse()
{
    Stats stats;

    //  open the files
    std::ifstream
    inFile (this->inFilename);

    std::string line, sequence;
    int 
    fileLineNum = 0,
    recLineNum = 0;

    while (getline(inFile, line)) {
        //  print out progress every few records
        if (fileLineNum % 10000 == 0 && fileLineNum > 0) {
            std::cout << "\tUp to line " << fileLineNum << "...\n";
        }

        //  work out where we are up to in the record
        int recLineNum = fileLineNum % 4;

        //  do whatever is appropriate for this line
        if (recLineNum == 1) {
            stats["totalReads"]++;

            sequence = line;

            if (isTSOArtifact(&sequence, this->thresholdDist, this->TSO)) {
                stats["artifacts"]++;
            }
        }
        ++fileLineNum;

        //  don't read more than sampleReads
        if (stats["totalReads"] >= this->sampleReads) {
            break;
        }
    }

    this->stats = stats;
    return stats;
};

void
FastqParser::getStats()
{
    std::cout << "File Stats:\n";
    for (const auto & [key, val] : this->stats) {
        std::cout << key << ":\t" << val << "\n";
    }
}