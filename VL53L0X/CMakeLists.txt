# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(proximidade-vl53l0x C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(proximidade-vl53l0x
    proximidade-vl53l0x.c
    vl53l0x_api.c
    vl53l0x_api_calibration.c
    vl53l0x_api_core.c
    vl53l0x_api_ranging.c
    vl53l0x_api_strings.c
    vl53l0x_i2c_platform.c

)

pico_set_program_name(proximidade-vl53l0x "proximidade-vl53l0x")
pico_set_program_version(proximidade-vl53l0x "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(proximidade-vl53l0x 1)
pico_enable_stdio_usb(proximidade-vl53l0x 1)

# Bibliotecas necessárias
target_link_libraries(proximidade-vl53l0x
    pico_stdlib
    hardware_i2c
)

# Diretórios de include
target_include_directories(proximidade-vl53l0x PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/inc
    ${CMAKE_CURRENT_LIST_DIR}
)

# Bibliotecas necessárias
target_link_libraries(proximidade-vl53l0x
    pico_stdlib
    hardware_i2c
    hardware_pwm
)

pico_add_extra_outputs(proximidade-vl53l0x)

