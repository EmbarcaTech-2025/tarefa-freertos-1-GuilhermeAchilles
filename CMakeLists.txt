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
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

SET(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS)

message("FreeRTOS Kernel located in ${FREERTOS_PATH}")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(Atividade_1_free_rtos C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Atividade_1_free_rtos src/main.c)

add_library(driver STATIC
    driver/buzzer.c
    driver/button.c
    driver/led.c
)



pico_set_program_name(Atividade_1_free_rtos "Atividade_1_free_rtos")
pico_set_program_version(Atividade_1_free_rtos "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Atividade_1_free_rtos 0)
pico_enable_stdio_usb(Atividade_1_free_rtos 1)

# Add the standard library to the build
target_link_libraries(Atividade_1_free_rtos
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Atividade_1_free_rtos PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(driver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)


# Add any user requested libraries
target_link_libraries(Atividade_1_free_rtos 
        FreeRTOS-Kernel-Heap4
        driver
        )

target_link_libraries(driver 
        pico_stdlib
        hardware_dma
        hardware_timer
        hardware_adc
        hardware_pio
        hardware_clocks
        hardware_i2c
        hardware_pwm
)


pico_add_extra_outputs(Atividade_1_free_rtos)

