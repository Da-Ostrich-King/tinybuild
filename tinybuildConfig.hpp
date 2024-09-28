// All paths are relative tinybuildConfig.hpp

#include "./tinybuild/defines.hpp"

#define BUILDDIR "./"
#define EXTENSION "cpp"

// build config
const BuildConfig configs[] = {
    {
        .name="default",
        .CC="g++",
        .binarys={
            {// binary 1
                .bin="tbuild",
                .srcdirs={"tinybuild"}, // every file in the srcdirs that matches "*.<EXTENSTION>" will be compiled together
                .CCFLAGS="-std=c++20"
            }
        },
        .MAKEBUILDDIR=false
    } // add more configurations here    
};

// View defines.hpp for more information (if there isnt the information, too bad)