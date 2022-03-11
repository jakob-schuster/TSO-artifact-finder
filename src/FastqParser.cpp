#include <fstream>
#include <iostream>

#include "FastqParser.h"
#include "utilities.h"

FastqParser::FastqParser(Filename inFilename, Filename outFilename)
{
    this->inFilename = inFilename;
    this->outFilename = outFilename;

    this->parse();
}

void
FastqParser::parse()
{
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
        if (fileLineNum % 1000 == 0 && fileLineNum > 0) {
            std::cout << "\tUp to line " << fileLineNum << "...\n";
        }

        //  work out where we are up to in the record
        int recLineNum = fileLineNum % 4;

        //  do whatever is appropriate for this line
        if (recLineNum == 1) {
            this->stats["total_records"]++;

            sequence = line;

            if (hasTSO(&sequence)) {
                this->stats["records_with_TSO"]++;
            } else {
                this->stats["records_without_TSO"]++;
            }
        }

        ++fileLineNum;
    }
};

void
FastqParser::getStats()
{
    std::cout << "File Stats:\n";
    for (const auto & [key, val] : this->stats) {
        std::cout << key << ":\t" << val << "\n";
    }
}
