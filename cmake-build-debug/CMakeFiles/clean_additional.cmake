# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ChatRoom_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ChatRoom_autogen.dir/ParseCache.txt"
  "ChatRoom_autogen"
  )
endif()
