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
CMAKE_SOURCE_DIR = "/home/admin1/Documents/resta (copy)/Server"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/admin1/Documents/resta (copy)/Server/build"

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/main.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/main.c.o: ../main.c
CMakeFiles/server.dir/main.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/main.c.o -MF CMakeFiles/server.dir/main.c.o.d -o CMakeFiles/server.dir/main.c.o -c "/home/admin1/Documents/resta (copy)/Server/main.c"

CMakeFiles/server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/main.c" > CMakeFiles/server.dir/main.c.i

CMakeFiles/server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/main.c" -o CMakeFiles/server.dir/main.c.s

CMakeFiles/server.dir/add_admin.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/add_admin.c.o: ../add_admin.c
CMakeFiles/server.dir/add_admin.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server.dir/add_admin.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/add_admin.c.o -MF CMakeFiles/server.dir/add_admin.c.o.d -o CMakeFiles/server.dir/add_admin.c.o -c "/home/admin1/Documents/resta (copy)/Server/add_admin.c"

CMakeFiles/server.dir/add_admin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/add_admin.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/add_admin.c" > CMakeFiles/server.dir/add_admin.c.i

CMakeFiles/server.dir/add_admin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/add_admin.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/add_admin.c" -o CMakeFiles/server.dir/add_admin.c.s

CMakeFiles/server.dir/add_item.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/add_item.c.o: ../add_item.c
CMakeFiles/server.dir/add_item.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/add_item.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/add_item.c.o -MF CMakeFiles/server.dir/add_item.c.o.d -o CMakeFiles/server.dir/add_item.c.o -c "/home/admin1/Documents/resta (copy)/Server/add_item.c"

CMakeFiles/server.dir/add_item.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/add_item.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/add_item.c" > CMakeFiles/server.dir/add_item.c.i

CMakeFiles/server.dir/add_item.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/add_item.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/add_item.c" -o CMakeFiles/server.dir/add_item.c.s

CMakeFiles/server.dir/add_order.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/add_order.c.o: ../add_order.c
CMakeFiles/server.dir/add_order.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/server.dir/add_order.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/add_order.c.o -MF CMakeFiles/server.dir/add_order.c.o.d -o CMakeFiles/server.dir/add_order.c.o -c "/home/admin1/Documents/resta (copy)/Server/add_order.c"

CMakeFiles/server.dir/add_order.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/add_order.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/add_order.c" > CMakeFiles/server.dir/add_order.c.i

CMakeFiles/server.dir/add_order.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/add_order.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/add_order.c" -o CMakeFiles/server.dir/add_order.c.s

CMakeFiles/server.dir/add_restaurants.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/add_restaurants.c.o: ../add_restaurants.c
CMakeFiles/server.dir/add_restaurants.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/server.dir/add_restaurants.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/add_restaurants.c.o -MF CMakeFiles/server.dir/add_restaurants.c.o.d -o CMakeFiles/server.dir/add_restaurants.c.o -c "/home/admin1/Documents/resta (copy)/Server/add_restaurants.c"

CMakeFiles/server.dir/add_restaurants.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/add_restaurants.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/add_restaurants.c" > CMakeFiles/server.dir/add_restaurants.c.i

CMakeFiles/server.dir/add_restaurants.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/add_restaurants.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/add_restaurants.c" -o CMakeFiles/server.dir/add_restaurants.c.s

CMakeFiles/server.dir/calculate_overall_sales.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/calculate_overall_sales.c.o: ../calculate_overall_sales.c
CMakeFiles/server.dir/calculate_overall_sales.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/server.dir/calculate_overall_sales.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/calculate_overall_sales.c.o -MF CMakeFiles/server.dir/calculate_overall_sales.c.o.d -o CMakeFiles/server.dir/calculate_overall_sales.c.o -c "/home/admin1/Documents/resta (copy)/Server/calculate_overall_sales.c"

CMakeFiles/server.dir/calculate_overall_sales.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/calculate_overall_sales.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/calculate_overall_sales.c" > CMakeFiles/server.dir/calculate_overall_sales.c.i

CMakeFiles/server.dir/calculate_overall_sales.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/calculate_overall_sales.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/calculate_overall_sales.c" -o CMakeFiles/server.dir/calculate_overall_sales.c.s

CMakeFiles/server.dir/check_admin.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/check_admin.c.o: ../check_admin.c
CMakeFiles/server.dir/check_admin.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/server.dir/check_admin.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/check_admin.c.o -MF CMakeFiles/server.dir/check_admin.c.o.d -o CMakeFiles/server.dir/check_admin.c.o -c "/home/admin1/Documents/resta (copy)/Server/check_admin.c"

CMakeFiles/server.dir/check_admin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/check_admin.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/check_admin.c" > CMakeFiles/server.dir/check_admin.c.i

CMakeFiles/server.dir/check_admin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/check_admin.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/check_admin.c" -o CMakeFiles/server.dir/check_admin.c.s

CMakeFiles/server.dir/delete_restaurants.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/delete_restaurants.c.o: ../delete_restaurants.c
CMakeFiles/server.dir/delete_restaurants.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/server.dir/delete_restaurants.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/delete_restaurants.c.o -MF CMakeFiles/server.dir/delete_restaurants.c.o.d -o CMakeFiles/server.dir/delete_restaurants.c.o -c "/home/admin1/Documents/resta (copy)/Server/delete_restaurants.c"

CMakeFiles/server.dir/delete_restaurants.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/delete_restaurants.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/delete_restaurants.c" > CMakeFiles/server.dir/delete_restaurants.c.i

CMakeFiles/server.dir/delete_restaurants.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/delete_restaurants.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/delete_restaurants.c" -o CMakeFiles/server.dir/delete_restaurants.c.s

CMakeFiles/server.dir/generate_invoice.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/generate_invoice.c.o: ../generate_invoice.c
CMakeFiles/server.dir/generate_invoice.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/server.dir/generate_invoice.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/generate_invoice.c.o -MF CMakeFiles/server.dir/generate_invoice.c.o.d -o CMakeFiles/server.dir/generate_invoice.c.o -c "/home/admin1/Documents/resta (copy)/Server/generate_invoice.c"

CMakeFiles/server.dir/generate_invoice.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/generate_invoice.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/generate_invoice.c" > CMakeFiles/server.dir/generate_invoice.c.i

CMakeFiles/server.dir/generate_invoice.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/generate_invoice.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/generate_invoice.c" -o CMakeFiles/server.dir/generate_invoice.c.s

CMakeFiles/server.dir/get_customer_id.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/get_customer_id.c.o: ../get_customer_id.c
CMakeFiles/server.dir/get_customer_id.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/server.dir/get_customer_id.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/get_customer_id.c.o -MF CMakeFiles/server.dir/get_customer_id.c.o.d -o CMakeFiles/server.dir/get_customer_id.c.o -c "/home/admin1/Documents/resta (copy)/Server/get_customer_id.c"

CMakeFiles/server.dir/get_customer_id.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/get_customer_id.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/get_customer_id.c" > CMakeFiles/server.dir/get_customer_id.c.i

CMakeFiles/server.dir/get_customer_id.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/get_customer_id.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/get_customer_id.c" -o CMakeFiles/server.dir/get_customer_id.c.s

CMakeFiles/server.dir/get_item_price.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/get_item_price.c.o: ../get_item_price.c
CMakeFiles/server.dir/get_item_price.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/server.dir/get_item_price.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/get_item_price.c.o -MF CMakeFiles/server.dir/get_item_price.c.o.d -o CMakeFiles/server.dir/get_item_price.c.o -c "/home/admin1/Documents/resta (copy)/Server/get_item_price.c"

CMakeFiles/server.dir/get_item_price.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/get_item_price.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/get_item_price.c" > CMakeFiles/server.dir/get_item_price.c.i

CMakeFiles/server.dir/get_item_price.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/get_item_price.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/get_item_price.c" -o CMakeFiles/server.dir/get_item_price.c.s

CMakeFiles/server.dir/isItem.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/isItem.c.o: ../isItem.c
CMakeFiles/server.dir/isItem.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/server.dir/isItem.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/isItem.c.o -MF CMakeFiles/server.dir/isItem.c.o.d -o CMakeFiles/server.dir/isItem.c.o -c "/home/admin1/Documents/resta (copy)/Server/isItem.c"

CMakeFiles/server.dir/isItem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/isItem.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/isItem.c" > CMakeFiles/server.dir/isItem.c.i

CMakeFiles/server.dir/isItem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/isItem.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/isItem.c" -o CMakeFiles/server.dir/isItem.c.s

CMakeFiles/server.dir/place_order.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/place_order.c.o: ../place_order.c
CMakeFiles/server.dir/place_order.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/server.dir/place_order.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/place_order.c.o -MF CMakeFiles/server.dir/place_order.c.o.d -o CMakeFiles/server.dir/place_order.c.o -c "/home/admin1/Documents/resta (copy)/Server/place_order.c"

CMakeFiles/server.dir/place_order.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/place_order.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/place_order.c" > CMakeFiles/server.dir/place_order.c.i

CMakeFiles/server.dir/place_order.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/place_order.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/place_order.c" -o CMakeFiles/server.dir/place_order.c.s

CMakeFiles/server.dir/remove_item.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/remove_item.c.o: ../remove_item.c
CMakeFiles/server.dir/remove_item.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/server.dir/remove_item.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/remove_item.c.o -MF CMakeFiles/server.dir/remove_item.c.o.d -o CMakeFiles/server.dir/remove_item.c.o -c "/home/admin1/Documents/resta (copy)/Server/remove_item.c"

CMakeFiles/server.dir/remove_item.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/remove_item.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/remove_item.c" > CMakeFiles/server.dir/remove_item.c.i

CMakeFiles/server.dir/remove_item.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/remove_item.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/remove_item.c" -o CMakeFiles/server.dir/remove_item.c.s

CMakeFiles/server.dir/update_item.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/update_item.c.o: ../update_item.c
CMakeFiles/server.dir/update_item.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/server.dir/update_item.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/update_item.c.o -MF CMakeFiles/server.dir/update_item.c.o.d -o CMakeFiles/server.dir/update_item.c.o -c "/home/admin1/Documents/resta (copy)/Server/update_item.c"

CMakeFiles/server.dir/update_item.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/update_item.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/update_item.c" > CMakeFiles/server.dir/update_item.c.i

CMakeFiles/server.dir/update_item.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/update_item.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/update_item.c" -o CMakeFiles/server.dir/update_item.c.s

CMakeFiles/server.dir/view_order_history.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/view_order_history.c.o: ../view_order_history.c
CMakeFiles/server.dir/view_order_history.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/server.dir/view_order_history.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/view_order_history.c.o -MF CMakeFiles/server.dir/view_order_history.c.o.d -o CMakeFiles/server.dir/view_order_history.c.o -c "/home/admin1/Documents/resta (copy)/Server/view_order_history.c"

CMakeFiles/server.dir/view_order_history.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/view_order_history.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/admin1/Documents/resta (copy)/Server/view_order_history.c" > CMakeFiles/server.dir/view_order_history.c.i

CMakeFiles/server.dir/view_order_history.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/view_order_history.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/admin1/Documents/resta (copy)/Server/view_order_history.c" -o CMakeFiles/server.dir/view_order_history.c.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.c.o" \
"CMakeFiles/server.dir/add_admin.c.o" \
"CMakeFiles/server.dir/add_item.c.o" \
"CMakeFiles/server.dir/add_order.c.o" \
"CMakeFiles/server.dir/add_restaurants.c.o" \
"CMakeFiles/server.dir/calculate_overall_sales.c.o" \
"CMakeFiles/server.dir/check_admin.c.o" \
"CMakeFiles/server.dir/delete_restaurants.c.o" \
"CMakeFiles/server.dir/generate_invoice.c.o" \
"CMakeFiles/server.dir/get_customer_id.c.o" \
"CMakeFiles/server.dir/get_item_price.c.o" \
"CMakeFiles/server.dir/isItem.c.o" \
"CMakeFiles/server.dir/place_order.c.o" \
"CMakeFiles/server.dir/remove_item.c.o" \
"CMakeFiles/server.dir/update_item.c.o" \
"CMakeFiles/server.dir/view_order_history.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/main.c.o
server: CMakeFiles/server.dir/add_admin.c.o
server: CMakeFiles/server.dir/add_item.c.o
server: CMakeFiles/server.dir/add_order.c.o
server: CMakeFiles/server.dir/add_restaurants.c.o
server: CMakeFiles/server.dir/calculate_overall_sales.c.o
server: CMakeFiles/server.dir/check_admin.c.o
server: CMakeFiles/server.dir/delete_restaurants.c.o
server: CMakeFiles/server.dir/generate_invoice.c.o
server: CMakeFiles/server.dir/get_customer_id.c.o
server: CMakeFiles/server.dir/get_item_price.c.o
server: CMakeFiles/server.dir/isItem.c.o
server: CMakeFiles/server.dir/place_order.c.o
server: CMakeFiles/server.dir/remove_item.c.o
server: CMakeFiles/server.dir/update_item.c.o
server: CMakeFiles/server.dir/view_order_history.c.o
server: CMakeFiles/server.dir/build.make
server: libmylibrary.a
server: /usr/lib/x86_64-linux-gnu/libsqlite3.so
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_17) "Linking C executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd "/home/admin1/Documents/resta (copy)/Server/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/admin1/Documents/resta (copy)/Server" "/home/admin1/Documents/resta (copy)/Server" "/home/admin1/Documents/resta (copy)/Server/build" "/home/admin1/Documents/resta (copy)/Server/build" "/home/admin1/Documents/resta (copy)/Server/build/CMakeFiles/server.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

