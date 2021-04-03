# Tetris the Game
## About
This is my realisation of Tetris on _C++_ and _SFML library_.

## Installation
To build this game you need GNU GCC compiler with support for C++11/14+ and installed SFML library.
**_On Linux_**:
Open bash and install gcc:
```bash
sudo apt update
sudo apt install build-essential
```
Then install SFML library:
```bash
sudo apt install libsfml-dev
```

Then clone my repo:
```git
git clone -b dev https://github.com/legGalaxyCode/osi_tet.git
```
to clone from dev branch (with dev feauters) or
```git
git clone https://github.com/legGalaxyCode/osi_tet.git
```
to clone from master branch.

## Building
To build just open bash in the cloned dir and write:
**IF YOU HAVE CMAKE PREINSTALLED**
```bash
cmake CMakeLists.txt
make
```
**IF NOT**
```bash
g++ -o tetris -lsfml-system -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-network <.cpp files>
```
and then
```bash
./tetris
```
Well done. It works.