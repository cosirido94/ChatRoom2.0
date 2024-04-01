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
        Network
        REQUIRED)

add_executable(server
        server/include/serverDialog.h
        custom/include/customLineEdit.h
        server/include/server.h

        custom/src/customLineEdit.cpp
        server/src/serverDialog.cpp
        server/src/server.cpp

        server/src/main.cpp
        message/include/messageHandler.h
        message/src/messageHandler.cpp
        server/include/user.h
        server/src/user.cpp
)

target_link_libraries(server
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)

add_executable(client
        client/include/clientDialog.h
        custom/include/customLineEdit.h
        client/include/client.h

        custom/src/customLineEdit.cpp
        client/src/clientDialog.cpp
        client/src/client.cpp
        client/src/main.cpp
        message/include/messageHandler.h
        message/src/messageHandler.cpp
        thread/include/receiverThread.h
        thread/src/receiverThread.cpp
)

target_link_libraries(client
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)

