# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(3d-renderer C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(3d-renderer 3d-renderer.cpp ILI9341.cpp engine/Vector.cpp engine/Matrix4.cpp engine/Color.cpp engine/Mesh.cpp)

pico_set_program_name(3d-renderer "3d-renderer")
pico_set_program_version(3d-renderer "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(3d-renderer 0)
pico_enable_stdio_usb(3d-renderer 0)

# Add the standard library to the build
target_link_libraries(3d-renderer
        pico_stdlib
        hardware_spi
        hardware_dma
        pico_multicore)

# Add the standard include files to the build
target_include_directories(3d-renderer PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(3d-renderer 
        
        )

pico_add_extra_outputs(3d-renderer)

