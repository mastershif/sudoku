# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Sudoku.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sudoku.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sudoku.dir/flags.make

CMakeFiles/Sudoku.dir/FileManager.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/FileManager.c.o: ../FileManager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Sudoku.dir/FileManager.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/FileManager.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/FileManager.c

CMakeFiles/Sudoku.dir/FileManager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/FileManager.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/FileManager.c > CMakeFiles/Sudoku.dir/FileManager.c.i

CMakeFiles/Sudoku.dir/FileManager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/FileManager.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/FileManager.c -o CMakeFiles/Sudoku.dir/FileManager.c.s

CMakeFiles/Sudoku.dir/Game.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/Game.c.o: ../Game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Sudoku.dir/Game.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/Game.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Game.c

CMakeFiles/Sudoku.dir/Game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/Game.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Game.c > CMakeFiles/Sudoku.dir/Game.c.i

CMakeFiles/Sudoku.dir/Game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/Game.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Game.c -o CMakeFiles/Sudoku.dir/Game.c.s

CMakeFiles/Sudoku.dir/ILPSolver.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/ILPSolver.c.o: ../ILPSolver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Sudoku.dir/ILPSolver.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/ILPSolver.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/ILPSolver.c

CMakeFiles/Sudoku.dir/ILPSolver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/ILPSolver.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/ILPSolver.c > CMakeFiles/Sudoku.dir/ILPSolver.c.i

CMakeFiles/Sudoku.dir/ILPSolver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/ILPSolver.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/ILPSolver.c -o CMakeFiles/Sudoku.dir/ILPSolver.c.s

CMakeFiles/Sudoku.dir/LinkedList.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/LinkedList.c.o: ../LinkedList.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Sudoku.dir/LinkedList.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/LinkedList.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/LinkedList.c

CMakeFiles/Sudoku.dir/LinkedList.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/LinkedList.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/LinkedList.c > CMakeFiles/Sudoku.dir/LinkedList.c.i

CMakeFiles/Sudoku.dir/LinkedList.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/LinkedList.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/LinkedList.c -o CMakeFiles/Sudoku.dir/LinkedList.c.s

CMakeFiles/Sudoku.dir/main.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Sudoku.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/main.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/main.c

CMakeFiles/Sudoku.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/main.c > CMakeFiles/Sudoku.dir/main.c.i

CMakeFiles/Sudoku.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/main.c -o CMakeFiles/Sudoku.dir/main.c.s

CMakeFiles/Sudoku.dir/Parser.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/Parser.c.o: ../Parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Sudoku.dir/Parser.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/Parser.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Parser.c

CMakeFiles/Sudoku.dir/Parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/Parser.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Parser.c > CMakeFiles/Sudoku.dir/Parser.c.i

CMakeFiles/Sudoku.dir/Parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/Parser.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Parser.c -o CMakeFiles/Sudoku.dir/Parser.c.s

CMakeFiles/Sudoku.dir/Solver.c.o: CMakeFiles/Sudoku.dir/flags.make
CMakeFiles/Sudoku.dir/Solver.c.o: ../Solver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Sudoku.dir/Solver.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Sudoku.dir/Solver.c.o   -c /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Solver.c

CMakeFiles/Sudoku.dir/Solver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Sudoku.dir/Solver.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Solver.c > CMakeFiles/Sudoku.dir/Solver.c.i

CMakeFiles/Sudoku.dir/Solver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Sudoku.dir/Solver.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/Solver.c -o CMakeFiles/Sudoku.dir/Solver.c.s

# Object files for target Sudoku
Sudoku_OBJECTS = \
"CMakeFiles/Sudoku.dir/FileManager.c.o" \
"CMakeFiles/Sudoku.dir/Game.c.o" \
"CMakeFiles/Sudoku.dir/ILPSolver.c.o" \
"CMakeFiles/Sudoku.dir/LinkedList.c.o" \
"CMakeFiles/Sudoku.dir/main.c.o" \
"CMakeFiles/Sudoku.dir/Parser.c.o" \
"CMakeFiles/Sudoku.dir/Solver.c.o"

# External object files for target Sudoku
Sudoku_EXTERNAL_OBJECTS =

Sudoku: CMakeFiles/Sudoku.dir/FileManager.c.o
Sudoku: CMakeFiles/Sudoku.dir/Game.c.o
Sudoku: CMakeFiles/Sudoku.dir/ILPSolver.c.o
Sudoku: CMakeFiles/Sudoku.dir/LinkedList.c.o
Sudoku: CMakeFiles/Sudoku.dir/main.c.o
Sudoku: CMakeFiles/Sudoku.dir/Parser.c.o
Sudoku: CMakeFiles/Sudoku.dir/Solver.c.o
Sudoku: CMakeFiles/Sudoku.dir/build.make
Sudoku: /Library/gurobi563/mac64/lib/libgurobi56.so
Sudoku: CMakeFiles/Sudoku.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable Sudoku"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sudoku.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sudoku.dir/build: Sudoku

.PHONY : CMakeFiles/Sudoku.dir/build

CMakeFiles/Sudoku.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Sudoku.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Sudoku.dir/clean

CMakeFiles/Sudoku.dir/depend:
	cd /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug /Users/Shif/Documents/TAU/year3/C/c_workspace/Sudoku/cmake-build-debug/CMakeFiles/Sudoku.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Sudoku.dir/depend
