
# Directory used for generated build files.
BUILD_DIR := build

# Path to the ARM cross-compilation toolchain.
TOOLCHAIN := cmake/arm-none-eabi-toolchain.cmake

# Declare command targets that do not represent files.
.PHONY: configure build clean rebuild size

# Configure the project with CMake and Ninja.
configure:
	cmake -S . -B $(BUILD_DIR) -G Ninja \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-DCMAKE_BUILD_TYPE=Debug

# Compile and link the firmware.
build: configure
	cmake --build $(BUILD_DIR)

# Remove generated build files.
clean:
	cmake -E rm -rf $(BUILD_DIR)

# Clean and rebuild the complete project.
rebuild: clean build

# Build the firmware and print its memory usage.
size: build
	arm-none-eabi-size $(BUILD_DIR)/hospital_robot_firmware.elf
