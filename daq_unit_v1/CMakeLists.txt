cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME controller_v2)
project(${PROJECT_NAME})

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/libraries)

set(${CMAKE_PROJECT_NAME}_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__manager__sensor__handlers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__manager__config__handlers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/util__cir__buff.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/util__checksum.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__software__timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__comms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__comms__handlers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__daq.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__can__mcp2515.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__wireless__xbee.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__lap__timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__damper__pots.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__yaw__sensor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__serial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__timers.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__fchmpplc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__brake__pressure.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hw/hw__timer.cpp
        controller_v2.ino)

set(${CMAKE_PROJECT_NAME}_HDRS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__manager__sensor__handlers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__manager__config__handlers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/sys/sys__datastore.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/util__cir__buff.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/util__checksum.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__software__timer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__comms.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__comms__handlers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__comms__protocols.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/srv/srv__daq.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__can__mcp2515.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__wireless__xbee.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__lap__timer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__damper__pots.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__yaw__sensor.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__serial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__timers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__fchmpplc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/dev/dev__brake__pressure.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hw/hw__timer.h
        )


#### Uncomment below additional settings as needed.

# mega
set(${CMAKE_PROJECT_NAME}_BOARD mega)
set(${CMAKE_PROJECT_NAME}_PORT COM5)
set(mega.build.mcu atmega2560)
set(mega.upload.protocol wiring)
set(mega.upload.speed 115200)

# uno
#set(${CMAKE_PROJECT_NAME}_BOARD uno)
#set(${CMAKE_PROJECT_NAME}_PORT COM6)
#set(mega.build.mcu atmega328p)
#set(mega.upload.protocol arduino)
#set(mega.upload.speed 115200)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
