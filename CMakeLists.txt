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
        server/include/user.h
        message/type/include/message.h
        message/handler/server/include/serverMessageHandler.h
        message/type/include/newUserMessage.h
        message/handler/server/include/newUserMessageHandler.h
        message/parser/include/messageParser.h
        server/include/server.h

        custom/src/customLineEdit.cpp
#        message/handler/server/src/messageHandler.cpp
        message/type/src/newUserMessage.cpp
        message/handler/server/src/newUserMessageHandler.cpp
        message/parser/src/messageParser.cpp
        server/src/user.cpp
        server/src/server.cpp
        server/src/serverDialog.cpp
        server/src/main.cpp
        message/type/include/errorNickMessage.h
        message/type/src/errorNickMessage.cpp
        message/type/include/configChatMessage.h
        message/type/src/configChatMessage.cpp
        message/handler/server/include/chatroomReadyMessageHandler.h
        message/handler/server/src/chatroomReadyMessageHandler.cpp
        message/type/include/chatroomReadyMessage.h
        message/type/src/chatRoomReadyMessage.cpp
        message/type/include/broadcastUserConnectedMessage.h
        message/type/src/broadcastUserConnectedMessage.cpp
        message/type/include/broadcastUserDisconnectedMessage.h
        message/type/src/broadcastUserDisconnectedMessage.cpp
        message/type/include/chatroomTextMessage.h
        message/type/src/chatroomTextMessage.cpp
        message/handler/server/include/chatroomTextMessageHandler.h
        message/handler/server/src/chatroomTextMessageHandler.cpp
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
#        message/handler/server/include/messageHandler.h
#        message/handler/server/src/messageHandler.cpp
        thread/include/receiverThread.h
        thread/src/receiverThread.cpp
        message/type/include/message.h
        message/type/src/newUserMessage.cpp
        message/type/include/newUserMessage.h
        message/parser/include/messageParser.h
        message/parser/src/messageParser.cpp
        message/type/include/configChatMessage.h
        message/type/src/configChatMessage.cpp
        message/handler/client/include/clientMessageHandler.h
        message/handler/client/src/errorNickMessageHandler.cpp
        message/handler/client/include/errorNickMessageHandler.h
        message/handler/client/include/configChatMessageHandler.h
        message/handler/client/src/configChatMessageHandler.cpp
        chatroom/include/chatroom.h
        chatroom/src/chatroom.cpp
        server/include/user.h
        server/src/user.cpp
        custom/include/sortedListWidget.h
        custom/src/sortedListWidget.cpp
        message/type/include/chatroomReadyMessage.h
        message/type/src/chatRoomReadyMessage.cpp
        message/type/include/broadcastUserConnectedMessage.h
        message/type/src/broadcastUserConnectedMessage.cpp
        message/handler/client/include/broadcastUserConnectedMessageHandler.h
        message/handler/client/src/broadcastUserConnectedMessageHandler.cpp
        message/type/include/broadcastUserDisconnectedMessage.h
        message/type/src/broadcastUserDisconnectedMessage.cpp
        message/handler/client/include/broadcastUserDisconnectedMessageHandler.h
        message/handler/client/src/broadcastUserDisconnectedMessageHandler.cpp
        custom/include/clickLabel.h
        custom/src/clickLabel.cpp
        message/type/include/chatroomTextMessage.h
        message/type/src/chatroomTextMessage.cpp
        custom/include/messageWidget.h
        custom/src/messageWidget.cpp
        message/handler/client/include/chatroomTextMessageReceivedHandler.h
        message/handler/client/src/chatroomTextMessageReceivedHandler.cpp
)

target_link_libraries(client
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
)

