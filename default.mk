# default.mk

LANG=C

-include local_default.mk

BUILD_SYS=$(shell mycmake.sh --build-sys)
BUILD_CONFIG=$(shell mycmake.sh --build-config)
BUILD_DIR=$(shell mycmake.sh --build-dir)

#------------------------------------------------------
.PHONY: default
default:
	test -d $(BUILD_DIR) || make cmake
	make build

#------------------------------------------------------
.PHONY: cmake
cmake:
	mycmake.sh

.PHONY: build
build:
	mycmake.sh --build

.PHONY: clean
clean:
	mycmake.sh --build $(BUILD_SYS) $(BUILD_CONFIG) --target clean

.PHONY: install
install:
	mycmake.sh --build $(BUILD_SYS) $(BUILD_CONFIG) --target install

.PHONY: db
db:
	mycmake-db.sh

#------------------------------------------------------
.PHONY: android
android:
	mycmake-android.sh

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
	mycmake.sh         make Release
	mycmake.sh --build make Release
	mycmake.sh         make Debug
	mycmake.sh --build make Debug
	mycmake.sh         vs2022
	mycmake.sh --build vs2022 Release
	mycmake.sh --build vs2022 Debug
	mycmake.sh --build vs2022 RelWithDebInfo
	mycmake-android.sh

all.clean:
	rm -rf build.make
	rm -rf build.ninja
	rm -rf build.vs2022
	rm -rf build.android

#------------------------------------------------------
base.help:
	@echo 'cmake      ... cmake'
	@echo 'build      ... build'
	@echo 'clean      ... clean'
	@echo 'install    ... install'
	@echo 'db         ... generate compile_commands.json'
	@echo 'android    ... android'
	@echo 'tags.all   ... tags.all'
	@echo 'gtags.all  ... gtags.all'
	@echo 'format.all ... format *.h *.cpp in the current dir'
	@echo 'clean.all  ... clean all config'
	@echo 'all.all    ... build all compiler and config'
	@echo 'all.clean  ... clean all compiler and config'
	@echo 'help       ... print help'

