#include <iostream>
#include <algorithm>

#ifdef NOTDEC_ENABLE_WASM
#include "frontend/wasm/parser.h"
#endif

// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

std::string getSuffix(std::string fname) {
    std::size_t ind = fname.find_last_of('.');
    if (ind != std::string::npos) {
        return fname.substr(ind);
    }
    return std::string();
}

int main(int argc, char * argv[]) {
    if(cmdOptionExists(argv, argv+argc, "-h") || cmdOptionExists(argv, argv+argc, "--help"))
    {
usage:
        std::cout << "Usage: " << argv[0] << "-i wasm_file -o llvm_ir_file" << std::endl;
        return 0;
    }

    char * outfilename = getCmdOption(argv, argv + argc, "-o");
    char * infilename = getCmdOption(argv, argv + argc, "-i");
    if (!(outfilename && infilename))
    {
        goto usage;
    }
    
    std::string insuffix = getSuffix(infilename);
    notdec::frontend::BaseContext ctx(infilename);
    if (insuffix.size() == 0) {
        std::cout << "no suffix for input file. exiting." << std::endl;
        return 0;
    }
#ifdef NOTDEC_ENABLE_WASM
    else if (insuffix == ".wasm") {
        std::cout << "using wasm frontend." << std::endl;
        notdec::frontend::wasm::parse_wasm(ctx, infilename);
        // TODO
    }
#endif
    else {
        std::cout << "unknown suffix " << insuffix << " for input file. exiting." << std::endl;
        return 0;
    }
    
    return 0;
}