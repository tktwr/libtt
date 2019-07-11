# makefile.mk

LANG=C

-include local.mk

#------------------------------------------------------
#build: build.ninja.Debug
build: build.vs2019.RelWithDebInfo

#all: all.ninja.Debug
all: all.vs2019.RelWithDebInfo

all.clean:
	rm -rf build.ninja build.vs2017 build.vs2019
	rm -rf tags GPATH GRTAGS GTAGS
	rm -f _*.png

#------------------------------------------------------
# ninja
#------------------------------------------------------
all.ninja: all.ninja.Debug all.ninja.Release

all.ninja.Debug: cmake.ninja.Debug build.ninja.Debug

all.ninja.Release: cmake.ninja.Release build.ninja.Release

cmake.ninja.Debug:
	mycmake.sh ninja Debug

cmake.ninja.Release:
	mycmake.sh ninja Release

build.ninja.Debug:
	mycmake-build.sh ninja Debug

build.ninja.Release:
	mycmake-build.sh ninja Release

clean.ninja.Debug:
	mycmake-build.sh ninja Debug --target clean

clean.ninja.Release:
	mycmake-build.sh ninja Release --target clean

install.ninja.Release:
	mycmake-build.sh ninja Release --target install

#------------------------------------------------------
# vs2017
#------------------------------------------------------
all.vs2017: all.vs2017.Debug all.vs2017.Release all.vs2017.RelWithDebInfo

all.vs2017.Debug: cmake.vs2017 build.vs2017.Debug

all.vs2017.Release: cmake.vs2017 build.vs2017.Release

all.vs2017.RelWithDebInfo: cmake.vs2017 build.vs2017.RelWithDebInfo

cmake.vs2017:
	mycmake.sh vs2017

build.vs2017.Debug:
	mycmake-build.sh vs2017 Debug

build.vs2017.Release:
	mycmake-build.sh vs2017 Release

build.vs2017.RelWithDebInfo:
	mycmake-build.sh vs2017 RelWithDebInfo

clean.vs2017.Debug:
	mycmake-build.sh vs2017 Debug --target clean

clean.vs2017.Release:
	mycmake-build.sh vs2017 Release --target clean

clean.vs2017.RelWithDebInfo:
	mycmake-build.sh vs2017 RelWithDebInfo --target clean

install.vs2017.Release:
	mycmake-build.sh vs2017 Release --target install

#------------------------------------------------------
# vs2019
#------------------------------------------------------
all.vs2019: all.vs2019.Debug all.vs2019.Release all.vs2019.RelWithDebInfo

all.vs2019.Debug: cmake.vs2019 build.vs2019.Debug

all.vs2019.Release: cmake.vs2019 build.vs2019.Release

all.vs2019.RelWithDebInfo: cmake.vs2019 build.vs2019.RelWithDebInfo

cmake.vs2019:
	mycmake.sh vs2019

build.vs2019.Debug:
	mycmake-build.sh vs2019 Debug

build.vs2019.Release:
	mycmake-build.sh vs2019 Release

build.vs2019.RelWithDebInfo:
	mycmake-build.sh vs2019 RelWithDebInfo

clean.vs2019.Debug:
	mycmake-build.sh vs2019 Debug --target clean

clean.vs2019.Release:
	mycmake-build.sh vs2019 Release --target clean

clean.vs2019.RelWithDebInfo:
	mycmake-build.sh vs2019 RelWithDebInfo --target clean

install.vs2019.Release:
	mycmake-build.sh vs2019 Release --target install

#------------------------------------------------------
.PHONY: tags
tags:
	ctags -R .

gtags:
	gtags -v

format:
	clang-format -i *.h *.cpp

help:
	@echo 'make all'
	@echo 'make all.clean'
	@echo "--"
	@echo "make all.ninja"
	@echo "make all.ninja.Debug"
	@echo "make all.ninja.Release"
	@echo "make cmake.ninja.Debug"
	@echo "make cmake.ninja.Release"
	@echo "make build.ninja.Debug"
	@echo "make build.ninja.Release"
	@echo "make clean.ninja.Debug"
	@echo "make clean.ninja.Release"
	@echo "make install.ninja.Release"
	@echo "--"
	@echo "make all.vs2017"
	@echo "make all.vs2017.Debug"
	@echo "make all.vs2017.Release"
	@echo "make all.vs2017.RelWithDebInfo"
	@echo "make cmake.vs2017"
	@echo "make build.vs2017.Debug"
	@echo "make build.vs2017.Release"
	@echo "make build.vs2017.RelWithDebInfo"
	@echo "make clean.vs2017.Debug"
	@echo "make clean.vs2017.Release"
	@echo "make clean.vs2017.RelWithDebInfo"
	@echo "make install.vs2017.Release"
	@echo "--"
	@echo "make all.vs2019"
	@echo "make all.vs2019.Debug"
	@echo "make all.vs2019.Release"
	@echo "make all.vs2019.RelWithDebInfo"
	@echo "make cmake.vs2019"
	@echo "make build.vs2019.Debug"
	@echo "make build.vs2019.Release"
	@echo "make build.vs2019.RelWithDebInfo"
	@echo "make clean.vs2019.Debug"
	@echo "make clean.vs2019.Release"
	@echo "make clean.vs2019.RelWithDebInfo"
	@echo "make install.vs2019.Release"
	@echo "--"
	@echo "make tags"
	@echo "make gtags"
	@echo "make format"
	@echo "make help"

