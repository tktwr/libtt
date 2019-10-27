include makefile.mk

tags: tags.libtt

.PHONY: tags.libtt
tags.libtt:
	ctags -f tags.libtt -R tt

.PHONY: test
test:
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_array.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_image.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_util.exe
	cd $(BUILD_DIR) && test/$(BUILD_CONFIG)/test_type.exe

