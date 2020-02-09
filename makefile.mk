# makefile.mk

LANG=C

-include local.mk

BUILD_SYS=$(shell mycmake.sh --build-sys)
BUILD_CONFIG=$(shell mycmake.sh --build-config)
BUILD_DIR=$(shell mycmake.sh --build-dir)

#------------------------------------------------------
build:
	time mycmake.sh --build

cmake:
	time mycmake.sh

clean:
	time mycmake.sh --build $(BUILD_SYS) $(BUILD_CONFIG) --target clean

install:
	time mycmake.sh --build $(BUILD_SYS) $(BUILD_CONFIG) --target install

#------------------------------------------------------
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
	rm -rf tags GPATH GRTAGS GTAGS
	rm -f _*.png

#------------------------------------------------------
all.all:
	time mycmake.sh         ninja Release
	time mycmake.sh --build ninja Release
	time mycmake.sh         ninja Debug
	time mycmake.sh --build ninja Debug
	time mycmake.sh         vs2019
	time mycmake.sh --build vs2019 Release
	time mycmake.sh --build vs2019 Debug
	time mycmake.sh --build vs2019 RelWithDebInfo
	time mycmake-android.sh

all.clean:
	rm -rf build.ninja
	rm -rf build.vs2019
	rm -rf build.android

#------------------------------------------------------
help:
	@echo 'make build'
	@echo 'make cmake'
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

