#include <string>

#include "definitions.h"

class FastqParser
{
    private:
        Stats stats;
        Filename inFilename, outFilename;
    
    public:
        FastqParser(Filename, Filename);

        void
        parse();

        void
        getStats();
};