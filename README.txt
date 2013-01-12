asteroids
=========

This is a remake of the game 'asteroids' in C++.

http://github.com/zigarrre/asteroids

Please report any bugs to the issue tracker on the project page! Feature requests and improvements are also welcome!

Compiling
---------

Asteroids is tested under Linux (GCC) and Windows 7 (VS 2010).

To compile asteroids, you need a recent version of SFML 2 (sfml-dev.org), Thor (developement version) (bromeon.ch/libraries/thor), Boost (boost.org) and a compiler which supports C++11.

Tested versions are:

SFML2: commit 91e1743516 (https://github.com/LaurentGomila/SFML/tarball/91e1743516377e16d675b6486301aeba5b20bef8)
Thor: commit c06e016821 (https://github.com/Bromeon/Thor/tarball/c06e01682175ba6d8b2a4217e4634910e2df1d44)

Use cmake to generate a makefile/projectfile for the compiler/IDE of your choice.

The compiled binary depends on the 'res' folder.

Linux
-----

mkdir build
cd build
cmake ../
make
./asteroids
