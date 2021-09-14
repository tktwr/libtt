include makefile.mk

all: cmake build

.PHONY: test
test:
ifeq ($(BUILD_SYS),make)
	make test_make
else ifeq ($(BUILD_SYS),ninja)
	make test_make
else
	make test_vs
endif

tags: tags.libtt

#------------------------------------------------------
test_make:
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_array.exe
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_image.exe
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_util.exe
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_type.exe

test_vs:
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_array.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_image.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_util.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_type.exe

.PHONY: tags.libtt
tags.libtt:
	ctags -f tags.libtt -R tt

clang-format:
	clang-format-all.sh tt

