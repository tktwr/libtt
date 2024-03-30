# default.mk

LANG=C

-include local_default.mk

BUILD_SYS=$(MY_BUILD_SYS)
BUILD_DIR=$(MY_BUILD_DIR)

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
	mycmake-build.sh

.PHONY: clean
clean:
	mycmake-build.sh --target clean

.PHONY: install
install:
	mycmake-build.sh --target install

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
	rm -f tags GPATH GRTAGS GTAGS
	rm -f compile_commands.json
	rm -f _*.png

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
	@echo 'help       ... print help'

