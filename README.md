# Ronnie

Ronnie is an attempt to develop a modern game engine as much as possible from scratch using latest C++ & OpenGL.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them

```
python >= 3.8
pip >= 23.0.1
conan >= 2.0.4
clang >= 15.0.7
```

### Installing

Ronnie uses Conan2 as a package manager.
Before attempting to install any package, generate default profile for Conan2 (or make sure that you already have one):

```
conan profile default
```

On some systems (e.g. Ubuntu, Manjaro), Conan2 may attempt to install missing OS packages via native package manager (e.g. apt-get, pacman), to make that possible you need to slightly modify the default profile:

```
echo "[conf]" >> ~/.conan2/profiles/default
echo "tools.system.package_manager:mode=install" >> ~/.conan2/profiles/default
echo "tools.system.package_manager:sudo=sudo" >> ~/.conan2/profiles/default
```

After the configuration is done, the basic command to execute Conan2, retrieve, and install packages is:
```
conan install . -of=./build --build=missing
```

Starting from version 2, Conan generates toolchain files for cmake, so we need to take that into consideration when generating buildfiles using Cmake:

```
cmake --preset conan-release -DCMAKE_EXPORT_COMPILE_COMMANDS=On
```

After the generation is succeffully finished we can build the project:

```
cd build && make
```

## Running the tests


### Break down into end to end tests


### And coding style tests

## Deployment

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Vahag Bejanyan** - *Initial work* - [lnikon](https://github.com/lnikon)

See also the list of [contributors](https://github.com/lnikon/Ronnie/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used

