# makefile.mk

LANG=C

COMPILER=unix
#COMPILER=vs2017

CONFIG=Release
#CONFIG=Debug

-include local.mk

ifeq ($(COMPILER),unix)
	BUILD_DIR=build.$(COMPILER).$(CONFIG)
	CMAKE_GENERATOR="Unix Makefiles"
else
	BUILD_DIR=build.vs2017
	CMAKE_GENERATOR="Visual Studio 15 2017 Win64"
endif

default: build

all: cmake build

cmake:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -G $(CMAKE_GENERATOR) ..

build:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG)

install:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG) --target install

clean:
	cd $(BUILD_DIR) && cmake --build . --config $(CONFIG) --target clean

clean.all:
	rm -rf $(BUILD_DIR)
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
	@echo "make"
	@echo "make all"
	@echo "make cmake"
	@echo "make build"
	@echo "make install"
	@echo "make clean"
	@echo "make clean.all"
	@echo "make tags"
	@echo "make gtags"
	@echo "make format"
	@echo "make help"

