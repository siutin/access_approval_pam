
SHELL:=/bin/bash
BUILD_PATH := ./build
MODULE_NAME := pam_module

CFG_PATH:=/etc/pam.d
SO_PATH:=`ls -d /lib/*/security/`
CFG_NAME=$(subst pam_,,$(MODULE_NAME))

build: $(BUILD_PATH)/$(MODULE_NAME).so

$(BUILD_PATH)/$(MODULE_NAME).so: $(BUILD_PATH)/$(MODULE_NAME).o
	gcc -shared -o $(BUILD_PATH)/$(MODULE_NAME).so $(BUILD_PATH)/$(MODULE_NAME).o -lpam

$(BUILD_PATH)/$(MODULE_NAME).o: src/$(MODULE_NAME).c
	gcc -fPIC -c src/$(MODULE_NAME).c -o $(BUILD_PATH)/$(MODULE_NAME).o

info:
	@echo SO_PATH: $(SO_PATH)
	@echo CFG_PATH: $(CFG_PATH)
	@echo MODULE_NAME: $(MODULE_NAME)
	@echo CFG_NAME: $(CFG_NAME)

install:
	chmod 644 $(BUILD_PATH)/$(MODULE_NAME).so
	@cp --verbose $(BUILD_PATH)/$(MODULE_NAME).so $(SO_PATH)/
	./config.sh $(MODULE_NAME) > $(CFG_PATH)/$(CFG_NAME)

.PHONY: clean

clean:
	-rm $(BUILD_PATH)/*