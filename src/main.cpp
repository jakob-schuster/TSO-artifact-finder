#include <iostream>

#include "FastqParser.h"

int
main (int argc, char *argv[])
{
    //  check the arguments
    if (argc != 3) {
        std::cout << "wrong argc!\n";
        return 1;
    }

    Filename
    inFilename = argv[1],
    outFilename = argv[2];

    //  
    FastqParser
    fastqParser (inFilename, outFilename);

    fastqParser.getStats();
}
