# makefile.mk

LANG=C

-include local.mk

#------------------------------------------------------
default: build.ninja.Release


all.ninja: all.ninja.Release all.ninja.Debug

all.vs2017: all.vs2017.Release all.vs2017.RelWithDebInfo all.vs2017.Debug

all.Release: all.ninja.Release all.vs2017.Release

all.Debug: all.ninja.Debug all.vs2017.Debug


all.ninja.Release: cmake.ninja.Release build.ninja.Release

all.ninja.Debug: cmake.ninja.Debug build.ninja.Debug

all.vs2017.Release: cmake.vs2017 build.vs2017.Release

all.vs2017.RelWithDebInfo: cmake.vs2017 build.vs2017.RelWithDebInfo

all.vs2017.Debug: cmake.vs2017 build.vs2017.Debug

#------------------------------------------------------
cmake.ninja.Release:
	mycmake.sh ninja Release

cmake.ninja.Debug:
	mycmake.sh ninja Debug

build.ninja.Release:
	mycmake-build.sh ninja Release

build.ninja.Debug:
	mycmake-build.sh ninja Debug

install.ninja.Release:
	mycmake-build.sh ninja Release --target install

clean.ninja.Release:
	mycmake-build.sh ninja Release --target clean

clean.ninja.Debug:
	mycmake-build.sh ninja Debug --target clean

#------------------------------------------------------
cmake.vs2017:
	mycmake.sh vs2017

build.vs2017.Release:
	mycmake-build.sh vs2017 Release

build.vs2017.RelWithDebInfo:
	mycmake-build.sh vs2017 RelWithDebInfo

build.vs2017.Debug:
	mycmake-build.sh vs2017 Debug

install.vs2017.Release:
	mycmake-build.sh vs2017 Release --target install

clean.vs2017.Release:
	mycmake-build.sh vs2017 Release --target clean

clean.vs2017.RelWithDebInfo:
	mycmake-build.sh vs2017 RelWithDebInfo --target clean

clean.vs2017.Debug:
	mycmake-build.sh vs2017 Debug --target clean

#------------------------------------------------------
all.clean:
	rm -rf build.ninja build.vs2017
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
	@echo "make all.ninja"
	@echo "make all.vs2017"
	@echo "make all.Release"
	@echo "make all.Debug"
	@echo "make all.ninja.Release"
	@echo "make all.ninja.Debug"
	@echo "make all.vs2017.Release"
	@echo "make all.vs2017.Debug"
	@echo 'make all.clean'
	@echo "--"
	@echo "make tags"
	@echo "make gtags"
	@echo "make format"
	@echo "make help"

