#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
cd src

clang++ *.cpp -g -Wall -I/Library/Frameworks/SDL2.framework/Headers  -I/Library/Frameworks/SDL2_ttf.framework/Headers -D_GNU_SOURCE=1 -D_THREAD_SAFE -framework SDL2 -framework SDL2_ttf -Wl,-framework,Cocoa -I/Users/thahn/codestuff/life/include -o ../bin/life
cd ../bin
install_name_tool -add_rpath @executable_path/../Frameworks life
cp life osx/octogenarian.app/Contents/MacOS