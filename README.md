# TinyBuild - A Small Build System Written in C++ (Ametuerishly)

TinyBuild is a build system where all configuration is done in an hpp file, compiled into the tbuild binary.

A default config is provided in the repository under "tinybuildConfig.hpp", from now on refered to as TBConfig.

To use the TinyBuild build system, place the tinybuild folder from this repository at the root of your project, and put the TBConfig in the root as well.
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
