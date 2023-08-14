Compiler=g++
OutputRelease=-o bin/Game.out
IncludePathRelease=-Iinclude -Isrc
WFlags=-Wall -Wextra
PFlags=-pthread
LFlags=-ldl
StaticLibs=lib/libraylib.a 
all: src/ include/ bin/ src/config.h
	@echo Compiling for Linux
	@$(Compiler) $(OutputRelease) src/*.cc $(StaticLibs) $(PFlags) $(LFlags) $(IncludePathRelease) $(WFlags) -std=c++20
	@echo Done!

debug: src/ include/ dbg/ src/config.h
	@echo compiling for Linux in Debug mode...
	@$(Compiler) -g3 -odbg/Game.out src/*.cc $(StaticLibs) $(PFlags) $(LFlags) $(IncludePathRelease) $(WFlags) -std=c++20
	@echo Done!

expand:
	gcc -E src/Main.cc $(IncludePathRelease)