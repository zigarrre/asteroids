# asteroids

This is a remake of the arcade game asteroids in C++.

http://github.com/zigarrre/asteroids

Please report any bugs to the issue tracker on the project page! Feature requests and improvements are also welcome!

## Compiling

Asteroids is tested under Arch Linux (GCC) and Windows 7 (VS 2013). MinGW should also work but is not tested. Older versions of Visual Studio (e.g. 2010/2012) aren't supported because they lack proper C++11 support.

To compile asteroids, you need SFML 2.1 (sfml-dev.org), Thor (SFML 2.1 compatible version) (bromeon.ch/libraries/thor), Boost (boost.org) and a compiler which supports C++11.

Tested versions are:

* **SFML:** 2.1
* **Thor:** commit f57666d (https://github.com/Bromeon/Thor/tree/f57666db6f187eb57bbc0947456cce2159a9b617)
* **Boost:** 1.56.0 (older versions should work too)

Use cmake to generate a makefile/projectfile for the compiler/IDE of your choice.

The compiled binary depends on the 'res' folder to be in the same directory.

### Linux

```
mkdir build
cd build
cmake ../
make
./asteroids
```
