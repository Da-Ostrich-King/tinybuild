// All paths are relative tinybuildConfig.hpp

#include "./tinybuild/defines.hpp"

#define BUILDDIR "./build"

// build config
const BuildConfig configs[] = {
    {
        .name="default",
        .CC="g++",
        .binarys={
            {// binary 1
                .bin="bin",
                .srcdirs={"src"},
                .srcfiles={"main.cpp"},
                .CCFLAGS="std=c++17 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
            }
        }
    } // add more configurations here    
};