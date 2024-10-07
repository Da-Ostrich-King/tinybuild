# TinyBuild - A Small Build System Written in C++

<i>This project was made for fun as a side project, it is recommended not to rely on this software updating in the future. Also I am an ameteur, so expect ametuer level code.</i>

TinyBuild is a build system where all configuration is done in an hpp file, compiled into the tbuild binary.

A default config is provided in the repository under "tinybuild/tinybuildConfig.hpp", from now on refered to as TBConfig.

To use the TinyBuild build system, place the tinybuild folder from this repository at the root of your project, and put the TBConfig in the root as well. <br> <br>

Example directory structure.
```
.
├── build
│   └── default
│       └── bin
├── README.md
├── src
│   └── main.cpp
├── tbuild
├── tinybuild
    ├── defines.hpp
    ├── tinybuildConfig.hpp
    └── main.cpp

```

TinyBuild creates a directory in the build directory for each build configuration specified in TBConfig.


# Build
To build tinybuild with its current configuration, run
```
    g++ tinybuild/main.cpp -o tbuild --std=c++20
```
<i>You only have to do this the first time you build tbuild, each subsequent time you can run ```./tbuild --rebuild```, tbuild will rename the previous binary to "tbuild.old", it will delete this file whenever tbuild is run again. <b>Because Windows is stupid, this doesn't work, you have to rename tbuild to tbuild.old then run ```./tbuild.old --rebuild```, tbuild.old will automatically be removed when the new ```./tbuild``` binary is run.</b></i>
And then to build your project run
```./tbuild -c```. If you want to add defines on the command line add the ```-d | --define "<definition>"``` argument to ```./tbuild```. This is passed directly to CC on command line.<br>
<i>Currently I was stupid and ```-d | --define``` does absolutely nothing</i>

If you want to select a configuration other than "default", add ```--config``` to ```./tbuild```. If you are running ```--clean``` then this is the configuration that is cleen built. If you run ```--nuke``` then this is going to delete the build files for <i>all</i> configurations, specifically by deleting the build directory.


# Other
The default config is in the ```tinybuild/``` directory as ```tinybuild/tinybuildConfig.hpp``` <br>
You can also add per-config initFunctions, as a function pointer, function prototype is placed in the tbuild config like this.<br>
```
    void myFunFunction ();
```
<i>     It is required to be a void function with no parameters. </i> <br>
Then make a tinybuildConfig.cpp that says something like this
```
    #include <iostream>
    void myFunFunction () {
        std::cout << "fun init function\n";
    }
```
And then you can write normal c++.