#include "../tinybuildConfig.hpp"
#include "defines.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <format>


#define helpText \
"\
NAME\n\
    TinyBuild\n\
Usage\n\
    ./tinybuild -c|--compile [-dC|-h]\n\
    \n\
Options\n\
    -h --help     Display this help message\n\
    -c --compile  Run build with default options (as specified in tinybuildConfig.hpp)\n\
    -d --define   Add a definition to build\n\
    -C --config   Pick the configuration to build with\n\
    --clean       Delete all build files of specified configuration (rm -rf BUILDDIR/default)\n\
    --nuke        Delete all build files in the build folder (rm -rf BUILDDIR/*)\n\
    \n\
Examples\n\
    tinybuild -c -d 'BUILDTYPE \"RELEASE\"'\n\
\n"

struct Args {
    bool compile = false;
    std::vector<const char*> defines;
    std::string config = "default";
};

int parseArgs(int argc, char* argv[], Args& args) {
    if (argc == 1) {
        std::cout << helpText;
    }
    // List of defines supplied at command line
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-d" || std::string(argv[i]) == "--define") { // find all --defines specified on command line
            args.defines.push_back(argv[++i]);
            continue;
        } else if (std::string(argv[i]) == "-c" || std::string(argv[i]) == "--compile") { // check if compile directive is given
            args.compile = true;
            continue;
        } else if (std::string(argv[i]) == "-C" || std::string(argv[i]) == "--config") { // check for --config
            args.config = argv[++i];
            continue;
        } else if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            std::cout << helpText;
        } else { // if a command is unkown, recommend reading help text
            std::cout << "Unkown command \"" << argv[i] << "\"\n";
            std::cout << "Use -h | --help for help text";
            return 1;
        }
    }
    return 0;
}

int main (int argc, char* argv[]) {
    // List of configurations supplied at command line
    
    Args args;
    int parseArgsReturnCode = parseArgs(argc, argv, args);

    std::filesystem::path build = BUILDDIR;
    if (!std::filesystem::exists(build)) {
        std::cout << "Build directory not found, creating...\n";
        std::filesystem::create_directory(build);
        std::cout << "Build directory created.\n";
    }

    for (BuildConfig config : configs) {
        if (config.name == args.config) {
            if (args.compile) {
                for (Binarys binary : config.binarys) {
                    std::string command = std::format("{}", config.CC);
                }
            }
        }
    }
    return 0;
}