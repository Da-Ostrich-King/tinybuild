#include <vector>
#pragma once

struct Binarys {
    const char* bin;
    std::vector<const char*> srcdirs;
    std::vector<const char*> srcfiles;
    const char* CCFLAGS;
};


struct BuildConfig {
    const char* name;
    const char* CC;
    std::vector<Binarys> binarys;
};
