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
CMAKE_SOURCE_DIR = /home/nimda/sources/BFVpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nimda/sources/BFVpp/build

# Include any dependencies generated for this target.
include test/CMakeFiles/encrypt-decrypt.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/encrypt-decrypt.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/encrypt-decrypt.dir/flags.make

test/CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.o: test/CMakeFiles/encrypt-decrypt.dir/flags.make
test/CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.o: ../test/encrypt-decrypt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nimda/sources/BFVpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.o"
	cd /home/nimda/sources/BFVpp/build/test && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.o -c /home/nimda/sources/BFVpp/test/encrypt-decrypt.cpp

test/CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.i"
	cd /home/nimda/sources/BFVpp/build/test && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nimda/sources/BFVpp/test/encrypt-decrypt.cpp > CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.i

test/CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.s"
	cd /home/nimda/sources/BFVpp/build/test && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nimda/sources/BFVpp/test/encrypt-decrypt.cpp -o CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.s

# Object files for target encrypt-decrypt
encrypt__decrypt_OBJECTS = \
"CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.o"

# External object files for target encrypt-decrypt
encrypt__decrypt_EXTERNAL_OBJECTS =

test/encrypt-decrypt: test/CMakeFiles/encrypt-decrypt.dir/encrypt-decrypt.cpp.o
test/encrypt-decrypt: test/CMakeFiles/encrypt-decrypt.dir/build.make
test/encrypt-decrypt: thirdparties/spqlios/libspqlios.a
test/encrypt-decrypt: thirdparties/randen/libranden.a
test/encrypt-decrypt: test/CMakeFiles/encrypt-decrypt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nimda/sources/BFVpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable encrypt-decrypt"
	cd /home/nimda/sources/BFVpp/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encrypt-decrypt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/encrypt-decrypt.dir/build: test/encrypt-decrypt

.PHONY : test/CMakeFiles/encrypt-decrypt.dir/build

test/CMakeFiles/encrypt-decrypt.dir/clean:
	cd /home/nimda/sources/BFVpp/build/test && $(CMAKE_COMMAND) -P CMakeFiles/encrypt-decrypt.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/encrypt-decrypt.dir/clean

test/CMakeFiles/encrypt-decrypt.dir/depend:
	cd /home/nimda/sources/BFVpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nimda/sources/BFVpp /home/nimda/sources/BFVpp/test /home/nimda/sources/BFVpp/build /home/nimda/sources/BFVpp/build/test /home/nimda/sources/BFVpp/build/test/CMakeFiles/encrypt-decrypt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/encrypt-decrypt.dir/depend

