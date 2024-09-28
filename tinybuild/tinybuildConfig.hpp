// All paths are relative tinybuildConfig.hpp

// DEFAULT CONFIGURATION
// MOVE THE TINYBUILD DIRECTORY TO THE ROOT OF THE PROJECT AND THIS FROM THE TINYBUILD DIRECTORY TO THE ROOT OF THE PROJECT
// FOR MORE INFORMATION GO TO REAMDE.md
// FOR LICENSE INFORMAITION GO TO LICENSE
// IF I WAS STUPID AND FORGOT TO PUT A LICENSE, REFER TO https://www.gnu.org/licenses/gpl-3.0.en.html#license-text FOR LICENSE INFORMATION

#include "./tinybuild/defines.hpp"

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
        }
    } // add more configurations here    
};

// View defines.hpp for more information (if there isnt the information, too bad)