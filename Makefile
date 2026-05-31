.PHONY: all build clean install uninstall

all: build

build:
	@echo "building..."
	@if [ ! -d "./build" ]; then mkdir build; fi
	@cmake -S ./ -B ./build
	@make -j4 -C ./build
	@if [ ! -d "./bin" ]; then mkdir bin; fi
	@cp -p ./build/bin/* ./bin/
	@echo "built! you can run it locally with: ./bin/broot"

clean:
	@echo "cleaning..."
	@if [ -d "./build" ]; then rm -rf build; fi
	@if [ -d "./bin" ]; then rm -rf bin; fi
	@rm -f broot_calibrated.root
	@echo "cleaned!"

install: build
	@echo "installing globally (requires admin password)..."
	@cd build && sudo make install
	@echo "installed! you can now run 'broot' from anywhere."

uninstall:
	@echo "uninstalling globally (requires admin password)..."
	@sudo rm -f /usr/local/bin/broot
	@echo "uninstalled!"
