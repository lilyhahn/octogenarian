#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
cd src

clang++ *.cpp SDLMain.m -g -Wall -I/Library/Frameworks/SDL.framework/Headers -D_GNU_SOURCE=1 -D_THREAD_SAFE -framework SDL -Wl,-framework,Cocoa -I/Users/thahn/codestuff/life/include -o ../bin/life
cd ../bin
install_name_tool -add_rpath @executable_path/../Frameworks life
cp life octogenarian.app/Contents/MacOS
