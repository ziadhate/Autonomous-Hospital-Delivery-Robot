
cmake_minimum_required(VERSION 3.22)

# Define the firmware project and enable C and Assembly languages.
project(hospital_robot_firmware
    VERSION 0.1.0
    LANGUAGES C ASM
)

# Use the C11 language standard.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Name of the generated firmware target.
set(TARGET_NAME hospital_robot_firmware)

# CPU-specific flags for the STM32F401RE Cortex-M4F.
set(CPU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

# Keep the initial build intentionally small.
# Add drivers and services after their implementations are reviewed.
set(FIRMWARE_SOURCES
    Src/main.c
    startup/startup_stm32f401xe.s
)

# Create the embedded executable target.
add_executable(${TARGET_NAME} ${FIRMWARE_SOURCES})

# Make the project's public headers available to source files.
target_include_directories(${TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

# Configure CPU options and useful compiler warnings.
target_compile_options(${TARGET_NAME} PRIVATE
    ${CPU_FLAGS}

    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Wpedantic>
    $<$<COMPILE_LANGUAGE:C>:-Werror=implicit-function-declaration>

    # Place functions and data in separate sections for linker cleanup.
    $<$<COMPILE_LANGUAGE:C>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:C>:-fdata-sections>
)

# Configure the embedded linker.
target_link_options(${TARGET_NAME} PRIVATE
    ${CPU_FLAGS}

    # Use our custom memory layout.
    -T${CMAKE_CURRENT_SOURCE_DIR}/linker/STM32F401RE.ld

    # Remove unused sections where safe.
    -Wl,--gc-sections

    # Report Flash and RAM usage after linking.
    -Wl,--print-memory-usage

    # Generate a linker map for debugging memory placement.
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.map

    # Do not use the host-style default startup files.
    -nostartfiles

    # Supply minimal system-call stubs for embedded builds.
    --specs=nosys.specs
)

# Use the standard ELF extension for the linked firmware.
set_target_properties(${TARGET_NAME} PROPERTIES
    SUFFIX ".elf"
)

# Generate Intel HEX, raw binary, and a size report after linking.
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
        -O ihex
        $<TARGET_FILE:${TARGET_NAME}>
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.hex

    COMMAND ${CMAKE_OBJCOPY}
        -O binary
        $<TARGET_FILE:${TARGET_NAME}>
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.bin

    COMMAND ${CMAKE_SIZE}
        $<TARGET_FILE:${TARGET_NAME}>

    COMMENT "Generating HEX/BIN images and reporting firmware size"
)
