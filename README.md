# TinyBuild - A Small Build System Written in C++

<i>This project was made for fun as a side project, it is recommended not to rely on this software updating in the future. Also I am an ameteur, so expect ametuer level code.</i>

TinyBuild is a build system where all configuration is done in an hpp file, compiled into the tbuild binary.

A default config is provided in the repository under "tinybuildConfig.hpp", from now on refered to as TBConfig.

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
│   ├── defines.hpp
│   └── main.cpp
└── tinybuildConfig.hpp
```

TinyBuild creates a directory in the build directory for each build configuration specified in TBConfig.


# Build
To build tinybuild with its current configuration, run
```
    g++ tinybuild/main.cpp -o tbuild --std=c++20
```
And then to build your project run
```./tbuild -c```. If you want to add defines on the command line (ie defining wayland vs x11 etc.) add the ```-d | --define "<definition>"``` argument to ```./tbuild```. This is passed directly to CC on command line.<br>

If you want to select a configuration other than "default", add ```--config``` to ```./tbuild```. If you are running ```--clean``` then this is the configuration that is cleen built. If you run ```--nuke``` then this is going to delete the build files for <i>all</i> configurations, specifically by deleting the build directory.


# Other
The TBConfig in the root of the repository is the configuration for building tbuild with itself, the default config is in the ```tinybuild/``` directory as ```tinybuild/tinybuildConfig.hpp```
