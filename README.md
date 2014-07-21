# Ocean's Keeper 2
## Commands
Move using ZQSD or the arrows
Fire with ctrl (left or right)
Bomb with space

## Developers of Ocean's Keeper 2
- Coding by [@mcdooda](https://github.com/mcdooda)
- Graphics by [@jrouillard](https://github.com/jrouillard) and [@IngloriousTom](https://github.com/IngloriousTom)

## External resources
- Thanks to CyborgJeff for his free music<br />
http://cyborgjeff.untergrund.net/<br />
Listen to the full album on Jamendo: http://www.jamendo.com/fr/album/22103
- Thanks to the lua team for Lua<br />
http://lua.org/
- Thanks to Laurent Gomila for SMFL<br />
http://sfml-dev.org/
- Thanks to the glew team for GLEW<br />
http://glew.sf.net/

## Compiling
### Linux
1. Install cmake, lua 5.1, sfml 2 and the latest version of GLEW
For example on debian-based systems:
```
$ sudo apt-get install cmake liblua5.1-0-dev libsfml-dev libglew1.10-dev
```
2. Create a Makefile using cmake:
```
$ cd <oceanskeeper2 directory>/
$ cmake . -G "Unix Makefiles"
$ make
$ ./oceanskeeper2
```

