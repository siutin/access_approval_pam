
BUILD_PATH := ./build
MODULE_NAME := pam_module

build: $(BUILD_PATH)/$(MODULE_NAME).so

$(BUILD_PATH)/$(MODULE_NAME).so: $(BUILD_PATH)/$(MODULE_NAME).o
	gcc -shared -o $(BUILD_PATH)/$(MODULE_NAME).so $(BUILD_PATH)/$(MODULE_NAME).o -lpam

$(BUILD_PATH)/$(MODULE_NAME).o: src/$(MODULE_NAME).c
	gcc -fPIC -c src/$(MODULE_NAME).c -o $(BUILD_PATH)/$(MODULE_NAME).o

.PHONY: clean

clean:
	-rm $(BUILD_PATH)/*