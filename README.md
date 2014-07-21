# Ocean's Keeper 2
## Commands
Move using ZQSD or the arrows
Fire with ctrl (left or right)
Bomb with space

## Developers of Ocean's Keeper 2
- Code by Nikaulus
    http://sourceforge.net/users/nikaulus
- Graphics by Molokov
    http://tom.rouillard.net/

## External resources
- Thanks to CyborgJeff for his free music
    http://cyborgjeff.untergrund.net/
    Listen to the full album on Jamendo: http://www.jamendo.com/fr/album/22103
- Thanks to the lua team for Lua
    http://lua.org/
- Thanks to Laurent Gomila for SMFL
    http://sfml-dev.org/
- Thanks to the glew team for GLEW
    http://glew.sf.net/

## Compiling
### Linux
1. Install cmake, lua 5.1, sfml 2 and the latest version of GLEW
For example on debian-based systems:
$ sudo apt-get install cmake liblua5.1-0-dev libsfml-dev libglew1.10-dev
2. Create a Makefile using cmake:
$ cd <oceanskeeper2 directory>/
$ cmake . -G "Unix Makefiles"
$ make
3. Then, run the game:
$ ./oceanskeeper2

