# makefile.mk

LANG=C

-include local.mk

BUILD_SYS=$(shell mycmake.sh --build-sys)
BUILD_CONFIG=$(shell mycmake.sh --build-config)
BUILD_DIR=$(shell mycmake.sh --build-dir)

#------------------------------------------------------
.PHONY: default
default: build

#------------------------------------------------------
.PHONY: cmake
cmake:
	time mycmake.sh

.PHONY: build
build:
	time mycmake.sh --build

.PHONY: clean
clean:
	time mycmake.sh --build $(BUILD_SYS) $(BUILD_CONFIG) --target clean

.PHONY: install
install:
	time mycmake.sh --build $(BUILD_SYS) $(BUILD_CONFIG) --target install

#------------------------------------------------------
.PHONY: android
android:
	time mycmake-android.sh

#------------------------------------------------------
tags.all:
	ctags -R .

gtags.all:
	gtags -v

format.all:
	clang-format -i *.h *.cpp

clean.all:
	rm -rf build.$(BUILD_SYS)
	rm -f tags GPATH GRTAGS GTAGS
	rm -f compile_commands.json
	rm -f _*.png

#------------------------------------------------------
all.all:
	time mycmake.sh         make Release
	time mycmake.sh --build make Release
	time mycmake.sh         make Debug
	time mycmake.sh --build make Debug
	time mycmake.sh         vs2019
	time mycmake.sh --build vs2019 Release
	time mycmake.sh --build vs2019 Debug
	time mycmake.sh --build vs2019 RelWithDebInfo
	time mycmake-android.sh

all.clean:
	rm -rf build.make
	rm -rf build.ninja
	rm -rf build.vs2019
	rm -rf build.android

#------------------------------------------------------
help:
	@echo 'make cmake'
	@echo 'make build'
	@echo 'make clean'
	@echo 'make install'
	@echo "--"
	@echo 'make android'
	@echo "--"
	@echo "make tags.all"
	@echo "make gtags.all"
	@echo "make format.all"
	@echo 'make clean.all'
	@echo "--"
	@echo 'make all.all'
	@echo 'make all.clean'
	@echo "--"
	@echo "make help"

