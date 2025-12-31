# Arduino experiments helper
#
# Typical usage (WSL):
#   make attach BUSID=5-7
#   make upload PIO_ENV=uno-blink PORT=/dev/ttyACM0
#   make run BUSID=5-7 PIO_ENV=uno-blink PORT=/dev/ttyACM0

SHELL := /usr/bin/env bash

BUSID ?= 5-7
PIO_ENV ?= uno-blink
DEFAULT_PORT := $(firstword $(wildcard /dev/ttyACM0))
PORT ?= $(or $(DEFAULT_PORT),$(firstword $(wildcard /dev/ttyACM* /dev/ttyUSB*)))
BAUD ?= 115200

.PHONY: help setup envs ports attach detach usbipd-list build clean upload monitor run

help:
	@echo "Targets:"
	@echo "  make envs                          # list PlatformIO environments (from platformio.ini)"
	@echo "  make ports                         # list serial ports (pio + /dev/tty*)"
	@echo "  make attach      BUSID=5-7                # usbipd attach to WSL (Windows host)"
	@echo "  make detach      BUSID=5-7                # usbipd detach"
	@echo "  make build       PIO_ENV=uno-blink         # build env"
	@echo "  make clean       PIO_ENV=uno-blink         # clean env"
	@echo "  make upload      PIO_ENV=uno-blink PORT=/dev/ttyACM0"
	@echo "  make monitor     PORT=/dev/ttyACM0 BAUD=115200"
	@echo "  make run         BUSID=5-7 PIO_ENV=uno-blink PORT=/dev/ttyACM0"

setup:
	@command -v pio >/dev/null 2>&1 || { \
		echo "ERROR: PlatformIO (pio) not found."; \
		echo "Install (recommended): pipx install platformio"; \
		exit 1; \
	}
	@pio --version

envs:
	@awk -F'[][]' '/^\[env:/{print $$2}' platformio.ini

ports: setup
	@echo "PlatformIO detected devices:";
	@pio device list || true
	@echo
	@echo "Linux device nodes:";
	@ls -1 /dev/ttyACM* /dev/ttyUSB* 2>/dev/null || true

usbipd-list:
	@command -v powershell.exe >/dev/null 2>&1 || { \
		echo "ERROR: powershell.exe not found (this target is meant for WSL)."; \
		exit 1; \
	}
	@powershell.exe -NoProfile -Command "usbipd list" | tr -d '\r'

attach:
	@command -v powershell.exe >/dev/null 2>&1 || { \
		echo "ERROR: powershell.exe not found (this target is meant for WSL)."; \
		exit 1; \
	}
	@echo "Attaching USB device BUSID=$(BUSID) to WSL..."
	@powershell.exe -NoProfile -Command "usbipd attach --wsl --busid $(BUSID)" | tr -d '\r'

detach:
	@command -v powershell.exe >/dev/null 2>&1 || { \
		echo "ERROR: powershell.exe not found (this target is meant for WSL)."; \
		exit 1; \
	}
	@echo "Detaching USB device BUSID=$(BUSID)..."
	@powershell.exe -NoProfile -Command "usbipd detach --busid $(BUSID)" | tr -d '\r'

build: setup
	@pio run -e "$(PIO_ENV)"

clean: setup
	@pio run -e "$(PIO_ENV)" -t clean

upload: setup
	@test -n "$(PORT)" || { \
		echo "ERROR: PORT is empty. Try: make ports"; \
		exit 1; \
	}
	@pio run -e "$(PIO_ENV)" -t upload --upload-port "$(PORT)"

monitor: setup
	@test -n "$(PORT)" || { \
		echo "ERROR: PORT is empty. Try: make ports"; \
		exit 1; \
	}
	@pio device monitor -p "$(PORT)" -b "$(BAUD)"

run: attach upload monitor
