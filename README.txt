asteroids
=========

This is a remake of the game 'asteroids' in C++.

http://github.com/zigarrre/asteroids

Please report any bugs to the issue tracker on the project page! Feature requests and improvements are also welcome!

Compiling
---------

Asteroids is tested under Linux (GCC). Windows (MinGW) should also work but is currently not tested. Visual Studio 2010/2012 isn't supported because it lacks proper C++11 support.

To compile asteroids, you need a recent version of SFML 2 (sfml-dev.org), Thor (developement version) (bromeon.ch/libraries/thor), Boost (boost.org) and a compiler which supports C++11.

Tested versions are:

SFML2: 2.0 (https://github.com/LaurentGomila/SFML/tree/2.0)
Thor: commit 9437226617 (https://github.com/Bromeon/Thor/tree/943722661702d1b4158edcb3c1833ea8f893ec34)
Boost: 1.48.0

Use cmake to generate a makefile/projectfile for the compiler/IDE of your choice.

The compiled binary depends on the 'res' folder.

Linux
-----

mkdir build
cd build
cmake ../
make
./asteroids
