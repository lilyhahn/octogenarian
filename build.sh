#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
cd src

clang++ *.cpp -g -Wall -I/Users/thahn/utils/homebrew/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -L/Users/thahn/utils/homebrew/lib -lSDLmain -lSDL -Wl,-framework,Cocoa -I/Users/thahn/codestuff/life/include -o ../bin/life
