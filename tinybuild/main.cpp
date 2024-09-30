// IF I WAS STUPID AND FORGOT TO PUT A LICENSE, REFER TO https://www.gnu.org/licenses/gpl-3.0.en.html#license-text FOR LICENSE INFORMATION



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
    bool clean = false;
    bool nuke = false;
};

int parseArgs(int argc, char* argv[], Args& args) {
    if (argc == 1) {
        std::cout << helpText;
        return 0;
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
        } else if (std::string(argv[i]) == "--clean") {
            args.clean = true;
        } else if (std::string(argv[i]) == "--nuke") {
            args.nuke = true;
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

    if (parseArgsReturnCode == 1) {
        return 1;
    }

    if (args.clean) {
        if (std::string(BUILDDIR) == ".") {
            std::cout << "Deleting " << BUILDDIR << "/" << args.config << ". Are you sure? [y/N] ";
            std::string answer;
            std::cin >> answer;
            if (answer == "y") {
                std::cout << "Deleting...\n";
                if (std::filesystem::exists(BUILDDIR + args.config)) {
                    std::filesystem::remove_all(std::filesystem::path(BUILDDIR + args.config));
                }
                std::cout << "Deleted.\n";
            } else {
                std::cout << "Not deleting.\n";
                return 1;
            }
        } else {
            std::cout << "Cannot clean build directory at root of project.\n";
            return 1;
        }
    }

    if (args.nuke) {
        if (std::string(BUILDDIR) == ".") {
            std::cout << "Deleting " << BUILDDIR << ". Are you sure? [y/N] ";
            std::string answer;
            std::cin >> answer;
            if (answer == "y") {
                std::cout << "Deleting...\n";
                if (std::filesystem::exists(BUILDDIR)) {
                    std::filesystem::remove_all(BUILDDIR);
                }
                std::cout << "Deleted.\n";
            } else {
                std::cout << "Not deleting.\n";
                return 1;
            }
        } else {
            std::cout << "Cannot clean build directory at root of project.";
            return 1;
        }
    }

    std::filesystem::path build = BUILDDIR;
    if (!std::filesystem::exists(build)) {
        std::cout << "Build directory not found, creating...\n";
        std::filesystem::create_directory(build);
        std::cout << "Build directory created.\n";
    }

    for (BuildConfig config : configs) {
        if (config.name == args.config) {
            if (config.MAKEBUILDDIR) {
                if (!std::filesystem::exists(build / config.name)) {
                    std::cout << "Configuration specified build directory not found, creating " << build / config.name << "...\n";
                    std::filesystem::create_directory(build / config.name);
                    std::cout << "Created " << build / config.name << ".\n";
                }
            } else {
                std::cout << "MAKEBUILDDIR is set to false, placing build files in BUILDDIR directly.\n";
            }

            if (args.compile) {
                for (Binarys binary : config.binarys) {
                    std::string srcFiles;
                    for (auto dir : binary.srcdirs) {
                        std::filesystem::path srcdir = dir;
                        if (std::filesystem::exists(srcdir)) {
                            for (const auto& file : std::filesystem::directory_iterator(srcdir)) { // get every file in src dir
                                bool matches = true;
                                if (file.path().generic_string().substr(file.path().generic_string().find_last_of(".") + 1) == std::string(EXTENSION)) {
                                    srcFiles += std::string(file.path().generic_string()); srcFiles += " ";
                                }
                            }
                        }
                    }
                    if (std::filesystem::exists((config.MAKEBUILDDIR) ? std::string((build/config.name/binary.bin).generic_string()) :
                                                                        std::string((build/binary.bin).generic_string()))) { //check if binary already exists, if it does remove it

                                                                        
                        std::filesystem::remove((config.MAKEBUILDDIR) ? std::string((build/config.name/binary.bin).generic_string()) :
                                                                        std::string((build/binary.bin).generic_string()));
                    }
                    std::string command = (config.MAKEBUILDDIR) ? 
                        std::format("{} {} {} {}", config.CC, srcFiles, binary.CCFLAGS, std::string("-o ") + std::string((build/config.name/binary.bin).generic_string())) :
                        std::format("{} {} {} {}", config.CC, srcFiles, binary.CCFLAGS, std::string("-o ") + std::string((build/binary.bin).generic_string()));
                    std::cout << "\nBuilding with configuration " << config.name << ":\n";
                    std::cout << "Command: " << command << "\n";
                    system(command.c_str());
                }
            }
        }
    }
    return 0;
}