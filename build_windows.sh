#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
cd src

i386-mingw32-g++ *.cpp -I/Users/thahn/utils/SDL-1.2.15/include/SDL -D_GNU_SOURCE=1 -Dmain=SDL_main -L/Users/thahn/utils/SDL-1.2.15/lib -lmingw32 -lSDLmain -lSDL -mwindows -I/Users/thahn/codestuff/life/include -o ../bin/life.exe

