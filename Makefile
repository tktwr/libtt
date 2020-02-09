include makefile.mk

tags: tags.libtt

.PHONY: tags.libtt
tags.libtt:
	ctags -f tags.libtt -R tt

.PHONY: test
test:
ifeq ($(BUILD_SYS),ninja)
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_array.exe
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_image.exe
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_util.exe
	cd $(BUILD_DIR) && $(BUILD_CONFIG)/test/test_type.exe
else
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_array.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_image.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_util.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_type.exe
endif

all: cmake build

