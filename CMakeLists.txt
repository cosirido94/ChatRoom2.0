cmake_minimum_required(VERSION 3.27)
project(ChatRoom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


include_directories(${CMAKE_SOURCE_DIR}/custom)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(server
        server/include/serverDialog.h
        custom/include/customLineEdit.h
        server/include/server.h

        custom/src/customLineEdit.cpp
        server/src/serverDialog.cpp
        server/src/server.cpp

        server/src/main.cpp
)

target_link_libraries(server
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

