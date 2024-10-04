// All paths are relative tinybuildConfig.hpp
#pragma once


#include "defines.hpp"


#define BUILDDIR "./build"
#define EXTENSION "cpp"


// build config
const BuildConfig configs[] = {
    {
        .name="default",
        .CC="g++",
        .binarys={
            {// binary 1
                .bin="bin",
                .srcdirs={"src"}, // every file in the srcdirs that matches "*.<EXTENSTION>" will be compiled together
                .CCFLAGS=""
            }
        },
        .MAKEBUILDDIR=true,
        .initFunction=nullptr
    } // add more configurations here    
};


// View defines.hpp for more information (if there isnt the information, too bad)