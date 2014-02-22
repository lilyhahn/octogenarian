#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
cd src

i386-mingw32-g++ *.cpp -I/Users/thahn/utils/SDL2-2.0.1/i686-w64-mingw32/include/SDL2 -D_GNU_SOURCE=1 -L/Users/thahn/utils/SDL2-2.0.1/i686-w64-mingw32/lib -lmingw32 -lSDL2Main -lSDL2 -mwindows -I/Users/thahn/codestuff/life/include -o ../bin/life.exe

