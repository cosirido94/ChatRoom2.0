# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/265/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/265/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/ilcondor/Documents/Project C++/ChatRoom"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug"

# Utility rule file for client_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/client_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client_autogen.dir/progress.make

CMakeFiles/client_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target client"
	/snap/clion/265/bin/cmake/linux/x64/bin/cmake -E cmake_autogen "/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug/CMakeFiles/client_autogen.dir/AutogenInfo.json" Debug

client_autogen: CMakeFiles/client_autogen
client_autogen: CMakeFiles/client_autogen.dir/build.make
.PHONY : client_autogen

# Rule to build all files generated by this target.
CMakeFiles/client_autogen.dir/build: client_autogen
.PHONY : CMakeFiles/client_autogen.dir/build

CMakeFiles/client_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client_autogen.dir/clean

CMakeFiles/client_autogen.dir/depend:
	cd "/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ilcondor/Documents/Project C++/ChatRoom" "/home/ilcondor/Documents/Project C++/ChatRoom" "/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug" "/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug" "/home/ilcondor/Documents/Project C++/ChatRoom/cmake-build-debug/CMakeFiles/client_autogen.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/client_autogen.dir/depend
