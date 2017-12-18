
SHELL:=/bin/bash
BUILD_PATH := ./bin
MODULE_NAME := pam_access_approval

CFG_PATH:=/etc/pam.d
SO_PATH:=`ls -d /lib/*/security/`
CFG_NAME=$(subst pam_,,$(MODULE_NAME))

all: build install run

build: $(BUILD_PATH)/$(MODULE_NAME).so

$(BUILD_PATH)/$(MODULE_NAME).so: $(BUILD_PATH)/$(MODULE_NAME).o
	gcc -Wall -shared -o $(BUILD_PATH)/$(MODULE_NAME).so $(BUILD_PATH)/$(MODULE_NAME).o -lpam -lfswatch

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

run:
	pamtester $(CFG_NAME) root open_session
	pamtester $(CFG_NAME) root authenticate

.PHONY: clean

clean:
	-rm $(BUILD_PATH)/*