# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/pmavrodiev/Projects/lm-invoice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pmavrodiev/Projects/lm-invoice/build

# Include any dependencies generated for this target.
include CMakeFiles/Invoice_Generator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Invoice_Generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Invoice_Generator.dir/flags.make

CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o: CMakeFiles/Invoice_Generator.dir/flags.make
CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o: ../src/dialogs/SettingsDialog.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pmavrodiev/Projects/lm-invoice/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o -c /home/pmavrodiev/Projects/lm-invoice/src/dialogs/SettingsDialog.cpp

CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pmavrodiev/Projects/lm-invoice/src/dialogs/SettingsDialog.cpp > CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.i

CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pmavrodiev/Projects/lm-invoice/src/dialogs/SettingsDialog.cpp -o CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.s

CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.requires:
.PHONY : CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.requires

CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.provides: CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.requires
	$(MAKE) -f CMakeFiles/Invoice_Generator.dir/build.make CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.provides.build
.PHONY : CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.provides

CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.provides.build: CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o

CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o: CMakeFiles/Invoice_Generator.dir/flags.make
CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o: ../src/lm-invoice.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pmavrodiev/Projects/lm-invoice/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o -c /home/pmavrodiev/Projects/lm-invoice/src/lm-invoice.cpp

CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pmavrodiev/Projects/lm-invoice/src/lm-invoice.cpp > CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.i

CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pmavrodiev/Projects/lm-invoice/src/lm-invoice.cpp -o CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.s

CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.requires:
.PHONY : CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.requires

CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.provides: CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.requires
	$(MAKE) -f CMakeFiles/Invoice_Generator.dir/build.make CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.provides.build
.PHONY : CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.provides

CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.provides.build: CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o

CMakeFiles/Invoice_Generator.dir/src/main.cpp.o: CMakeFiles/Invoice_Generator.dir/flags.make
CMakeFiles/Invoice_Generator.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pmavrodiev/Projects/lm-invoice/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Invoice_Generator.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Invoice_Generator.dir/src/main.cpp.o -c /home/pmavrodiev/Projects/lm-invoice/src/main.cpp

CMakeFiles/Invoice_Generator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Invoice_Generator.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/pmavrodiev/Projects/lm-invoice/src/main.cpp > CMakeFiles/Invoice_Generator.dir/src/main.cpp.i

CMakeFiles/Invoice_Generator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Invoice_Generator.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/pmavrodiev/Projects/lm-invoice/src/main.cpp -o CMakeFiles/Invoice_Generator.dir/src/main.cpp.s

CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.requires

CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.provides: CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Invoice_Generator.dir/build.make CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.provides

CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.provides.build: CMakeFiles/Invoice_Generator.dir/src/main.cpp.o

# Object files for target Invoice_Generator
Invoice_Generator_OBJECTS = \
"CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o" \
"CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o" \
"CMakeFiles/Invoice_Generator.dir/src/main.cpp.o"

# External object files for target Invoice_Generator
Invoice_Generator_EXTERNAL_OBJECTS =

Invoice_Generator: CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o
Invoice_Generator: CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o
Invoice_Generator: CMakeFiles/Invoice_Generator.dir/src/main.cpp.o
Invoice_Generator: CMakeFiles/Invoice_Generator.dir/build.make
Invoice_Generator: /usr/lib/x86_64-linux-gnu/libQtCore.so
Invoice_Generator: /usr/lib/x86_64-linux-gnu/libQtGui.so
Invoice_Generator: CMakeFiles/Invoice_Generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Invoice_Generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Invoice_Generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Invoice_Generator.dir/build: Invoice_Generator
.PHONY : CMakeFiles/Invoice_Generator.dir/build

CMakeFiles/Invoice_Generator.dir/requires: CMakeFiles/Invoice_Generator.dir/src/dialogs/SettingsDialog.cpp.o.requires
CMakeFiles/Invoice_Generator.dir/requires: CMakeFiles/Invoice_Generator.dir/src/lm-invoice.cpp.o.requires
CMakeFiles/Invoice_Generator.dir/requires: CMakeFiles/Invoice_Generator.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/Invoice_Generator.dir/requires

CMakeFiles/Invoice_Generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Invoice_Generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Invoice_Generator.dir/clean

CMakeFiles/Invoice_Generator.dir/depend:
	cd /home/pmavrodiev/Projects/lm-invoice/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pmavrodiev/Projects/lm-invoice /home/pmavrodiev/Projects/lm-invoice /home/pmavrodiev/Projects/lm-invoice/build /home/pmavrodiev/Projects/lm-invoice/build /home/pmavrodiev/Projects/lm-invoice/build/CMakeFiles/Invoice_Generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Invoice_Generator.dir/depend
