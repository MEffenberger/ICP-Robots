# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/marek/CLionProjects/ICP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug

# Utility rule file for ICP_autogen.

# Include the progress variables for this target.
include CMakeFiles/ICP_autogen.dir/progress.make

CMakeFiles/ICP_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target ICP"
	/usr/bin/cmake -E cmake_autogen /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles/ICP_autogen.dir/AutogenInfo.json Debug

ICP_autogen: CMakeFiles/ICP_autogen
ICP_autogen: CMakeFiles/ICP_autogen.dir/build.make

.PHONY : ICP_autogen

# Rule to build all files generated by this target.
CMakeFiles/ICP_autogen.dir/build: ICP_autogen

.PHONY : CMakeFiles/ICP_autogen.dir/build

CMakeFiles/ICP_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ICP_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ICP_autogen.dir/clean

CMakeFiles/ICP_autogen.dir/depend:
	cd /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/marek/CLionProjects/ICP /mnt/c/Users/marek/CLionProjects/ICP /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles/ICP_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ICP_autogen.dir/depend

