// All paths are relative "tbuild" executable, ideally placed at project root
#pragma once
// DEFAULT CONFIGURATION
// MOVE THE TINYBUILD DIRECTORY TO THE ROOT OF THE PROJECT AND THIS FROM THE TINYBUILD DIRECTORY TO THE ROOT OF THE PROJECT
// FOR MORE INFORMATION GO TO REAMDE.md
//
// FOR LICENSE INFORMAITION GO TO LICENSE
// IF I WAS STUPID AND FORGOT TO PUT A LICENSE, REFER TO https://www.gnu.org/licenses/gpl-3.0.en.html#license-text FOR LICENSE INFORMATION
#include "defines.hpp"
#include <cstdlib>
#include <string>
#include <filesystem>

#define BUILDDIR "./build"
#define EXTENSION "cpp"

void buildLib () {
    // override build command completely
    std::string srcFiles;
    for (auto dir : std::filesystem::path("./src")) {
        std::filesystem::path srcdir = dir;
        for (const auto& file : std::filesystem::directory_iterator(srcdir)) { // get every file in src dir
            if (file.path().generic_string().substr(file.path().generic_string().find_last_of(".") + 1) == std::string(EXTENSION)) {
                srcFiles += std::string(file.path().generic_string()); srcFiles += " ";
            }
        }    
    }

    std::system ("g++ -Iinclude -c -fPIC");
}

// build config
const BuildConfig configs[] = {
    {
        .name="lib",
        .CC="g++",
        .MAKEBUILDDIR=true,
        .initFunction=buildLib
    } // add more configurations here    
};


const char* TINYBUILD_SOURCE_PATH = "./tinybuild";
const char* REBUILD_COMMAND = "g++ {} -o {} --std=c++20"; 

// View defines.hpp for more information (if there isnt the information, too bad)