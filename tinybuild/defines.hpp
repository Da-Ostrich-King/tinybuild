#include <vector>
#pragma once

struct Binarys {
    const char* bin;
    std::vector<const char*> srcdirs;
    const char* CCFLAGS;
    std::vector<const char*> explicitSrcFiles;
};


struct BuildConfig {
    const char* name;
    const char* CC;
    std::vector<Binarys> binarys;
    const bool MAKEBUILDDIR = true;
    void (*initFunction) () = nullptr;
};
