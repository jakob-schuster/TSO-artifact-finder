#include <fstream>
#include <iostream>

#include "FastqParser.h"
#include "utilities.h"

FastqParser::FastqParser(Filename inFilename, Filename outFilename, int sampleReads, std::string TSO)
{
    this->inFilename = inFilename;
    this->outFilename = outFilename;
    this->sampleReads = sampleReads;
    this->TSO = TSO;
    this->thresholdDist = 2;
}

Stats
FastqParser::parse()
{
    Stats stats;

    //  open the files
    std::ifstream
    inFile (this->inFilename);
    std::ofstream
    outFile (this->outFilename);

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

            if (hasTSO(&sequence, this->thresholdDist, this->TSO)) {
                stats["readsWithTSO"]++;
            } else {
                stats["readsWithoutTSO"]++;
            }
        }
        ++fileLineNum;

        //  don't read more than sampleReads
        if (stats["totalReads"] >= this->sampleReads) {
            break;
        }
    }

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

float
FastqParser::percentage()
{
    return (float)this->stats["records_with_TSO"] / (float)(this->stats["total_records"]) * 100;
}