#include <iostream>
#include <fstream>

#include "FastqParser.h"

#define C_DEFAULT   "\x1B[0m"
#define C_GREEN     "\x1B[32m"
#define C_YELLOW    "\x1B[33m"

/*
    prints out the Stats to the screen
*/
void
printStats (Stats stats)
{
    std::cout << "File statistics:\n";

    std::cout 
            << "Total reads                       : " << stats["totalReads"] << "\n"
            << "Reads with TSO                    : " << stats["readsWithTSO"] << "\n"
            << "Reads with TSO reverse complement : " << stats["readsWithTSORevComp"] << "\n"
            << "Reads with both (artifacts)       : " << stats["readsWithBoth"] << "\n";
    
    float
    percentage = (float)stats["readsWithBoth"] / (float)stats["totalReads"] * 100;
    std::cout << "\n" << C_YELLOW << percentage << "%" << C_DEFAULT << " of reads are TSO artifacts.\n";
}

/*
    prints out the Stats to a file, in CSV format
*/
void
printStatsToFile (Stats stats, Filename outFilename)
{
    std::ofstream
    outFile (outFilename, std::ios_base::app);

    float
    percentage = (float)stats["readsWithBoth"] / (float)stats["totalReads"] * 100;

    outFile << "total reads," << stats["totalReads"] << "\n"
            << "reads with TSO," << stats["readsWithTSO"] << "\n"
            << "reads with TSO reverse complement," << stats["readsWithTSORevComp"] << "\n"
            << "reads with both (artifacts)," << stats["readsWithBoth"] << "\n"
            << "percentage of reads that are TSO artifacts," << percentage << "\n";
    
    outFile.close();
}

/*
    prints out the TSO-artifact-finder parameters to a file, in CSV format
*/
void
printParameters (std::string inFilename, std::string outFilename, int sampleReads, std::string TSOSequence)
{
    std::ofstream
    outFile (outFilename);

    outFile << "input filename," << inFilename << "\n"
            << "output filename," << outFilename << "\n"
            << "TSO," << TSOSequence << "\n";
    
    outFile.close();
}

int
main (int argc, char *argv[])
{
    //  check the argument count
    if (argc < 3) {
        std::cout << C_YELLOW << "Not enough arguments!" << C_DEFAULT << " Expected format:\n"
                << "\tTSO-artifact-finder [input filename] [output filename] (optional: how many reads to sample) (optional: TSO sequence)\n";
        return 1;
    }

    Filename
    inFilename = argv[1],
    outFilename = argv[2];

    //  set up how many lines should be read
    int
    sampleReads = 100000;
    if (argc >= 4) {
        sampleReads = std::stoi(argv[3]);
    }

    //  set up which TSO sequence should be used
    std::string
    TSO = "AAGCAGTGGTATCAACGCAGAGTACATGGG";
    if (argc >= 5) {
        TSO = argv[4];
    }
    
    //  print out the parameters
    std::cout << "TSO-artifact-finder initialised.\n"
        << "\tInput filename  :\t" << inFilename << "\n"
        << "\tOutput filename :\t" << outFilename << "\n"
        << "\tSample reads    :\t" << sampleReads << "\n"
        << "\tTSO sequence    :\t" << TSO << "\n";
    printParameters(inFilename, outFilename, sampleReads, TSO);

    //  start the parser
    std::cout << C_GREEN << "\nStarted searching for TSO artifacts...\n" << C_DEFAULT;
    FastqParser
    parser (inFilename, sampleReads, TSO);
    Stats stats = parser.parse();
    std::cout << C_GREEN << "Finished searching for TSO artifacts!\n\n" << C_DEFAULT;
    
    //  print out the stats
    printStats(stats);
    printStatsToFile(stats, outFilename);
}
