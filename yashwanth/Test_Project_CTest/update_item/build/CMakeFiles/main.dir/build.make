# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/admin1/Downloads/Test_Project/update_item

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/admin1/Downloads/Test_Project/update_item/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/test.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/test.c.o: ../test.c
CMakeFiles/main.dir/test.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin1/Downloads/Test_Project/update_item/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/test.c.o -MF CMakeFiles/main.dir/test.c.o.d -o CMakeFiles/main.dir/test.c.o -c /home/admin1/Downloads/Test_Project/update_item/test.c

CMakeFiles/main.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/admin1/Downloads/Test_Project/update_item/test.c > CMakeFiles/main.dir/test.c.i

CMakeFiles/main.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/admin1/Downloads/Test_Project/update_item/test.c -o CMakeFiles/main.dir/test.c.s

CMakeFiles/main.dir/updateItem.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/updateItem.c.o: ../updateItem.c
CMakeFiles/main.dir/updateItem.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin1/Downloads/Test_Project/update_item/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/updateItem.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/updateItem.c.o -MF CMakeFiles/main.dir/updateItem.c.o.d -o CMakeFiles/main.dir/updateItem.c.o -c /home/admin1/Downloads/Test_Project/update_item/updateItem.c

CMakeFiles/main.dir/updateItem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/updateItem.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/admin1/Downloads/Test_Project/update_item/updateItem.c > CMakeFiles/main.dir/updateItem.c.i

CMakeFiles/main.dir/updateItem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/updateItem.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/admin1/Downloads/Test_Project/update_item/updateItem.c -o CMakeFiles/main.dir/updateItem.c.s

CMakeFiles/main.dir/T4.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/T4.c.o: ../T4.c
CMakeFiles/main.dir/T4.c.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/admin1/Downloads/Test_Project/update_item/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/T4.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/T4.c.o -MF CMakeFiles/main.dir/T4.c.o.d -o CMakeFiles/main.dir/T4.c.o -c /home/admin1/Downloads/Test_Project/update_item/T4.c

CMakeFiles/main.dir/T4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/T4.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/admin1/Downloads/Test_Project/update_item/T4.c > CMakeFiles/main.dir/T4.c.i

CMakeFiles/main.dir/T4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/T4.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/admin1/Downloads/Test_Project/update_item/T4.c -o CMakeFiles/main.dir/T4.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/test.c.o" \
"CMakeFiles/main.dir/updateItem.c.o" \
"CMakeFiles/main.dir/T4.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/test.c.o
main: CMakeFiles/main.dir/updateItem.c.o
main: CMakeFiles/main.dir/T4.c.o
main: CMakeFiles/main.dir/build.make
main: /usr/lib/x86_64-linux-gnu/libsqlite3.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/admin1/Downloads/Test_Project/update_item/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/admin1/Downloads/Test_Project/update_item/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/admin1/Downloads/Test_Project/update_item /home/admin1/Downloads/Test_Project/update_item /home/admin1/Downloads/Test_Project/update_item/build /home/admin1/Downloads/Test_Project/update_item/build /home/admin1/Downloads/Test_Project/update_item/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

