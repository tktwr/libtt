# makefile.mk

LANG=C

BUILD_DIR.unix="build.unix"
CMAKE_GENERATOR.unix="Unix Makefiles"

BUILD_DIR.vs2017="build.vs2017"
CMAKE_GENERATOR.vs2017="Visual Studio 15 2017 Win64"

BUILD_DIR=$(BUILD_DIR.unix)
CMAKE_GENERATOR=$(CMAKE_GENERATOR.unix)
CONFIG=Release

-include local.mk

#------------------------------------------------------
default: build.unix.Release

all.unix.Release: cmake.unix build.unix.Release

all.unix.Debug: cmake.unix build.unix.Debug

all.vs2017.Release: cmake.vs2017 build.vs2017.Release

all.vs2017.Debug: cmake.vs2017 build.vs2017.Debug

#------------------------------------------------------
cmake.unix:
	make cmake BUILD_DIR=$(BUILD_DIR.unix) CMAKE_GENERATOR=$(CMAKE_GENERATOR.unix)

build.unix.Release:
	make build BUILD_DIR=$(BUILD_DIR.unix) CONFIG=Release

build.unix.Debug:
	make build BUILD_DIR=$(BUILD_DIR.unix) CONFIG=Debug

#------------------------------------------------------
cmake.vs2017:
	make cmake BUILD_DIR=$(BUILD_DIR.vs2017) CMAKE_GENERATOR=$(CMAKE_GENERATOR.vs2017)

build.vs2017.Release:
	winpty make build BUILD_DIR=$(BUILD_DIR.vs2017) CONFIG=Release

build.vs2017.Debug:
	winpty make build BUILD_DIR=$(BUILD_DIR.vs2017) CONFIG=Debug

#------------------------------------------------------
cmake:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -G "$(CMAKE_GENERATOR)" ..

build:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG)

install:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG) --target install

clean:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG) --target clean

clean.all:
	rm -rf $(BUILD_DIR.unix) $(BUILD_DIR.vs2017)
	rm -rf tags GPATH GRTAGS GTAGS
	rm -f _*.png

.PHONY: tags
tags:
	ctags -R .

gtags:
	gtags -v

format:
	clang-format -i *.h *.cpp

help:
	@echo "make all.unix.Release"
	@echo "make all.unix.Debug"
	@echo "make cmake.unix"
	@echo "make build.unix.Release"
	@echo "make build.unix.Debug"
	@echo "--"
	@echo "make all.vs2017.Release"
	@echo "make all.vs2017.Debug"
	@echo "make cmake.vs2017"
	@echo "make build.vs2017.Release"
	@echo "make build.vs2017.Debug"
	@echo "--"
	@echo "make"
	@echo 'make cmake   [BUILD_DIR="build"] [CMAKE_GENERATOR="Unix Makefiles|Visual Studio 15 2017 Win64"]'
	@echo 'make build   [BUILD_DIR="build"] [CONFIG=Release|Debug]'
	@echo 'make install [BUILD_DIR="build"] [CONFIG=Release|Debug]'
	@echo 'make clean   [BUILD_DIR="build"] [CONFIG=Release|Debug]'
	@echo 'make clean.all'
	@echo "make tags"
	@echo "make gtags"
	@echo "make format"
	@echo "make help"

