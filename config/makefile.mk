# makefile.mk

LANG=C

BUILD_DIR.unix=build.unix
CMAKE_GENERATOR.unix="Unix Makefiles"

BUILD_DIR.vs2017=build.vs2017
CMAKE_GENERATOR.vs2017="Visual Studio 15 2017 Win64"

CONFIG=Release
BUILD_DIR=$(BUILD_DIR.unix).$(CONFIG)
CMAKE_GENERATOR=$(CMAKE_GENERATOR.unix)

-include local.mk

#------------------------------------------------------
default: build.unix.Release

all.Release: all.unix.Release all.vs2017.Release

all.Debug: all.unix.Debug all.vs2017.Debug

all.unix.Release: cmake.unix.Release build.unix.Release

all.unix.Debug: cmake.unix.Debug build.unix.Debug

all.vs2017.Release: cmake.vs2017 build.vs2017.Release

all.vs2017.Debug: cmake.vs2017 build.vs2017.Debug

#------------------------------------------------------
cmake.unix.Release:
	make cmake BUILD_DIR=$(BUILD_DIR.unix).Release CMAKE_GENERATOR=$(CMAKE_GENERATOR.unix) CONFIG=Release

cmake.unix.Debug:
	make cmake BUILD_DIR=$(BUILD_DIR.unix).Debug CMAKE_GENERATOR=$(CMAKE_GENERATOR.unix) CONFIG=Debug

.PHONY: build.unix.Release
build.unix.Release:
	make build BUILD_DIR=$(BUILD_DIR.unix).Release CONFIG=Release

.PHONY: build.unix.Debug
build.unix.Debug:
	make build BUILD_DIR=$(BUILD_DIR.unix).Debug CONFIG=Debug

#------------------------------------------------------
cmake.vs2017:
	make cmake BUILD_DIR=$(BUILD_DIR.vs2017) CMAKE_GENERATOR=$(CMAKE_GENERATOR.vs2017)

build.vs2017.Release:
	winpty make build BUILD_DIR=$(BUILD_DIR.vs2017) CONFIG=Release

build.vs2017.Debug:
	winpty make build BUILD_DIR=$(BUILD_DIR.vs2017) CONFIG=Debug

#------------------------------------------------------
.PHONY: cmake
cmake:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -G "$(CMAKE_GENERATOR)" -D CMAKE_BUILD_TYPE=$(CONFIG) ..

build:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG)

install:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG) --target install

clean:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG) --target clean

clean.all:
	rm -rf $(BUILD_DIR.unix).Release $(BUILD_DIR.unix).Debug $(BUILD_DIR.vs2017)
	rm -rf tags GPATH GRTAGS GTAGS
	rm -f _*.png

#------------------------------------------------------
.PHONY: tags
tags:
	ctags -R .

gtags:
	gtags -v

format:
	clang-format -i *.h *.cpp

help:
	@echo "make all.Release"
	@echo "make all.Debug"
	@echo "make all.unix.Release"
	@echo "make all.unix.Debug"
	@echo "make all.vs2017.Release"
	@echo "make all.vs2017.Debug"
	@echo "--"
	@echo "make cmake.unix.Release"
	@echo "make cmake.unix.Debug"
	@echo "make build.unix.Release"
	@echo "make build.unix.Debug"
	@echo "--"
	@echo "make cmake.vs2017"
	@echo "make build.vs2017.Release"
	@echo "make build.vs2017.Debug"
	@echo "--"
	@echo "make"
	@echo 'make cmake   [BUILD_DIR=build] [CMAKE_GENERATOR="Unix Makefiles|Visual Studio 15 2017 Win64"] [CONFIG=Release|Debug]'
	@echo 'make build   [BUILD_DIR=build] [CONFIG=Release|Debug]'
	@echo 'make install [BUILD_DIR=build] [CONFIG=Release|Debug]'
	@echo 'make clean   [BUILD_DIR=build] [CONFIG=Release|Debug]'
	@echo 'make clean.all'
	@echo "--"
	@echo "make tags"
	@echo "make gtags"
	@echo "make format"
	@echo "make help"

