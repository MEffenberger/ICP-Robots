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

# Include any dependencies generated for this target.
include CMakeFiles/ICP.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ICP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ICP.dir/flags.make

CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.o: ICP_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/ICP_autogen/mocs_compilation.cpp

CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/ICP_autogen/mocs_compilation.cpp > CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.i

CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/ICP_autogen/mocs_compilation.cpp -o CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.s

CMakeFiles/ICP.dir/main.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ICP.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/main.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/main.cpp

CMakeFiles/ICP.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/main.cpp > CMakeFiles/ICP.dir/main.cpp.i

CMakeFiles/ICP.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/main.cpp -o CMakeFiles/ICP.dir/main.cpp.s

CMakeFiles/ICP.dir/mainwindow.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/mainwindow.cpp.o: ../mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ICP.dir/mainwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/mainwindow.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/mainwindow.cpp

CMakeFiles/ICP.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/mainwindow.cpp > CMakeFiles/ICP.dir/mainwindow.cpp.i

CMakeFiles/ICP.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/mainwindow.cpp -o CMakeFiles/ICP.dir/mainwindow.cpp.s

CMakeFiles/ICP.dir/user.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/user.cpp.o: ../user.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ICP.dir/user.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/user.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/user.cpp

CMakeFiles/ICP.dir/user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/user.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/user.cpp > CMakeFiles/ICP.dir/user.cpp.i

CMakeFiles/ICP.dir/user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/user.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/user.cpp -o CMakeFiles/ICP.dir/user.cpp.s

CMakeFiles/ICP.dir/obstacle.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/obstacle.cpp.o: ../obstacle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ICP.dir/obstacle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/obstacle.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/obstacle.cpp

CMakeFiles/ICP.dir/obstacle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/obstacle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/obstacle.cpp > CMakeFiles/ICP.dir/obstacle.cpp.i

CMakeFiles/ICP.dir/obstacle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/obstacle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/obstacle.cpp -o CMakeFiles/ICP.dir/obstacle.cpp.s

CMakeFiles/ICP.dir/enemy.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/enemy.cpp.o: ../enemy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ICP.dir/enemy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/enemy.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/enemy.cpp

CMakeFiles/ICP.dir/enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/enemy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/enemy.cpp > CMakeFiles/ICP.dir/enemy.cpp.i

CMakeFiles/ICP.dir/enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/enemy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/enemy.cpp -o CMakeFiles/ICP.dir/enemy.cpp.s

CMakeFiles/ICP.dir/button.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/button.cpp.o: ../button.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ICP.dir/button.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/button.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/button.cpp

CMakeFiles/ICP.dir/button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/button.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/button.cpp > CMakeFiles/ICP.dir/button.cpp.i

CMakeFiles/ICP.dir/button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/button.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/button.cpp -o CMakeFiles/ICP.dir/button.cpp.s

CMakeFiles/ICP.dir/horizontalbar.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/horizontalbar.cpp.o: ../horizontalbar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ICP.dir/horizontalbar.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/horizontalbar.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/horizontalbar.cpp

CMakeFiles/ICP.dir/horizontalbar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/horizontalbar.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/horizontalbar.cpp > CMakeFiles/ICP.dir/horizontalbar.cpp.i

CMakeFiles/ICP.dir/horizontalbar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/horizontalbar.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/horizontalbar.cpp -o CMakeFiles/ICP.dir/horizontalbar.cpp.s

CMakeFiles/ICP.dir/star.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/star.cpp.o: ../star.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ICP.dir/star.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/star.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/star.cpp

CMakeFiles/ICP.dir/star.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/star.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/star.cpp > CMakeFiles/ICP.dir/star.cpp.i

CMakeFiles/ICP.dir/star.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/star.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/star.cpp -o CMakeFiles/ICP.dir/star.cpp.s

CMakeFiles/ICP.dir/heart.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/heart.cpp.o: ../heart.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ICP.dir/heart.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/heart.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/heart.cpp

CMakeFiles/ICP.dir/heart.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/heart.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/heart.cpp > CMakeFiles/ICP.dir/heart.cpp.i

CMakeFiles/ICP.dir/heart.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/heart.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/heart.cpp -o CMakeFiles/ICP.dir/heart.cpp.s

CMakeFiles/ICP.dir/gameinfo.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/gameinfo.cpp.o: ../gameinfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ICP.dir/gameinfo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/gameinfo.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/gameinfo.cpp

CMakeFiles/ICP.dir/gameinfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/gameinfo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/gameinfo.cpp > CMakeFiles/ICP.dir/gameinfo.cpp.i

CMakeFiles/ICP.dir/gameinfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/gameinfo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/gameinfo.cpp -o CMakeFiles/ICP.dir/gameinfo.cpp.s

CMakeFiles/ICP.dir/timer.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/timer.cpp.o: ../timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/ICP.dir/timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/timer.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/timer.cpp

CMakeFiles/ICP.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/timer.cpp > CMakeFiles/ICP.dir/timer.cpp.i

CMakeFiles/ICP.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/timer.cpp -o CMakeFiles/ICP.dir/timer.cpp.s

CMakeFiles/ICP.dir/popup.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/popup.cpp.o: ../popup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/ICP.dir/popup.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/popup.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/popup.cpp

CMakeFiles/ICP.dir/popup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/popup.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/popup.cpp > CMakeFiles/ICP.dir/popup.cpp.i

CMakeFiles/ICP.dir/popup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/popup.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/popup.cpp -o CMakeFiles/ICP.dir/popup.cpp.s

CMakeFiles/ICP.dir/enemyitem.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/enemyitem.cpp.o: ../enemyitem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/ICP.dir/enemyitem.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/enemyitem.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/enemyitem.cpp

CMakeFiles/ICP.dir/enemyitem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/enemyitem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/enemyitem.cpp > CMakeFiles/ICP.dir/enemyitem.cpp.i

CMakeFiles/ICP.dir/enemyitem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/enemyitem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/enemyitem.cpp -o CMakeFiles/ICP.dir/enemyitem.cpp.s

CMakeFiles/ICP.dir/mapwindow.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/mapwindow.cpp.o: ../mapwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/ICP.dir/mapwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/mapwindow.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/mapwindow.cpp

CMakeFiles/ICP.dir/mapwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/mapwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/mapwindow.cpp > CMakeFiles/ICP.dir/mapwindow.cpp.i

CMakeFiles/ICP.dir/mapwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/mapwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/mapwindow.cpp -o CMakeFiles/ICP.dir/mapwindow.cpp.s

CMakeFiles/ICP.dir/robotdialog.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/robotdialog.cpp.o: ../robotdialog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/ICP.dir/robotdialog.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/robotdialog.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/robotdialog.cpp

CMakeFiles/ICP.dir/robotdialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/robotdialog.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/robotdialog.cpp > CMakeFiles/ICP.dir/robotdialog.cpp.i

CMakeFiles/ICP.dir/robotdialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/robotdialog.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/robotdialog.cpp -o CMakeFiles/ICP.dir/robotdialog.cpp.s

CMakeFiles/ICP.dir/robotitem.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/robotitem.cpp.o: ../robotitem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/ICP.dir/robotitem.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/robotitem.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/robotitem.cpp

CMakeFiles/ICP.dir/robotitem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/robotitem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/robotitem.cpp > CMakeFiles/ICP.dir/robotitem.cpp.i

CMakeFiles/ICP.dir/robotitem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/robotitem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/robotitem.cpp -o CMakeFiles/ICP.dir/robotitem.cpp.s

CMakeFiles/ICP.dir/gamemaster.cpp.o: CMakeFiles/ICP.dir/flags.make
CMakeFiles/ICP.dir/gamemaster.cpp.o: ../gamemaster.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/ICP.dir/gamemaster.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ICP.dir/gamemaster.cpp.o -c /mnt/c/Users/marek/CLionProjects/ICP/gamemaster.cpp

CMakeFiles/ICP.dir/gamemaster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ICP.dir/gamemaster.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/marek/CLionProjects/ICP/gamemaster.cpp > CMakeFiles/ICP.dir/gamemaster.cpp.i

CMakeFiles/ICP.dir/gamemaster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ICP.dir/gamemaster.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/marek/CLionProjects/ICP/gamemaster.cpp -o CMakeFiles/ICP.dir/gamemaster.cpp.s

# Object files for target ICP
ICP_OBJECTS = \
"CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/ICP.dir/main.cpp.o" \
"CMakeFiles/ICP.dir/mainwindow.cpp.o" \
"CMakeFiles/ICP.dir/user.cpp.o" \
"CMakeFiles/ICP.dir/obstacle.cpp.o" \
"CMakeFiles/ICP.dir/enemy.cpp.o" \
"CMakeFiles/ICP.dir/button.cpp.o" \
"CMakeFiles/ICP.dir/horizontalbar.cpp.o" \
"CMakeFiles/ICP.dir/star.cpp.o" \
"CMakeFiles/ICP.dir/heart.cpp.o" \
"CMakeFiles/ICP.dir/gameinfo.cpp.o" \
"CMakeFiles/ICP.dir/timer.cpp.o" \
"CMakeFiles/ICP.dir/popup.cpp.o" \
"CMakeFiles/ICP.dir/enemyitem.cpp.o" \
"CMakeFiles/ICP.dir/mapwindow.cpp.o" \
"CMakeFiles/ICP.dir/robotdialog.cpp.o" \
"CMakeFiles/ICP.dir/robotitem.cpp.o" \
"CMakeFiles/ICP.dir/gamemaster.cpp.o"

# External object files for target ICP
ICP_EXTERNAL_OBJECTS =

ICP: CMakeFiles/ICP.dir/ICP_autogen/mocs_compilation.cpp.o
ICP: CMakeFiles/ICP.dir/main.cpp.o
ICP: CMakeFiles/ICP.dir/mainwindow.cpp.o
ICP: CMakeFiles/ICP.dir/user.cpp.o
ICP: CMakeFiles/ICP.dir/obstacle.cpp.o
ICP: CMakeFiles/ICP.dir/enemy.cpp.o
ICP: CMakeFiles/ICP.dir/button.cpp.o
ICP: CMakeFiles/ICP.dir/horizontalbar.cpp.o
ICP: CMakeFiles/ICP.dir/star.cpp.o
ICP: CMakeFiles/ICP.dir/heart.cpp.o
ICP: CMakeFiles/ICP.dir/gameinfo.cpp.o
ICP: CMakeFiles/ICP.dir/timer.cpp.o
ICP: CMakeFiles/ICP.dir/popup.cpp.o
ICP: CMakeFiles/ICP.dir/enemyitem.cpp.o
ICP: CMakeFiles/ICP.dir/mapwindow.cpp.o
ICP: CMakeFiles/ICP.dir/robotdialog.cpp.o
ICP: CMakeFiles/ICP.dir/robotitem.cpp.o
ICP: CMakeFiles/ICP.dir/gamemaster.cpp.o
ICP: CMakeFiles/ICP.dir/build.make
ICP: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
ICP: /usr/lib/x86_64-linux-gnu/libQt5Multimedia.so.5.12.8
ICP: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
ICP: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.12.8
ICP: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
ICP: CMakeFiles/ICP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking CXX executable ICP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ICP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ICP.dir/build: ICP

.PHONY : CMakeFiles/ICP.dir/build

CMakeFiles/ICP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ICP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ICP.dir/clean

CMakeFiles/ICP.dir/depend:
	cd /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/marek/CLionProjects/ICP /mnt/c/Users/marek/CLionProjects/ICP /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug /mnt/c/Users/marek/CLionProjects/ICP/cmake-build-debug/CMakeFiles/ICP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ICP.dir/depend

