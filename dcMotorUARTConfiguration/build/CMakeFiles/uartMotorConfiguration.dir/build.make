# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build

# Include any dependencies generated for this target.
include CMakeFiles/uartMotorConfiguration.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uartMotorConfiguration.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uartMotorConfiguration.dir/flags.make

moc_configDataHandling.cxx: /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/configDataHandling.h
moc_configDataHandling.cxx: moc_configDataHandling.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating moc_configDataHandling.cxx"
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_configDataHandling.cxx_parameters

moc_SerialCommunication.cxx: /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/SerialCommunication.h
moc_SerialCommunication.cxx: moc_SerialCommunication.cxx_parameters
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating moc_SerialCommunication.cxx"
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc @/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_SerialCommunication.cxx_parameters

CMakeFiles/uartMotorConfiguration.dir/main.o: CMakeFiles/uartMotorConfiguration.dir/flags.make
CMakeFiles/uartMotorConfiguration.dir/main.o: /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/uartMotorConfiguration.dir/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uartMotorConfiguration.dir/main.o -c /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/main.cpp

CMakeFiles/uartMotorConfiguration.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uartMotorConfiguration.dir/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/main.cpp > CMakeFiles/uartMotorConfiguration.dir/main.i

CMakeFiles/uartMotorConfiguration.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uartMotorConfiguration.dir/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/main.cpp -o CMakeFiles/uartMotorConfiguration.dir/main.s

CMakeFiles/uartMotorConfiguration.dir/main.o.requires:

.PHONY : CMakeFiles/uartMotorConfiguration.dir/main.o.requires

CMakeFiles/uartMotorConfiguration.dir/main.o.provides: CMakeFiles/uartMotorConfiguration.dir/main.o.requires
	$(MAKE) -f CMakeFiles/uartMotorConfiguration.dir/build.make CMakeFiles/uartMotorConfiguration.dir/main.o.provides.build
.PHONY : CMakeFiles/uartMotorConfiguration.dir/main.o.provides

CMakeFiles/uartMotorConfiguration.dir/main.o.provides.build: CMakeFiles/uartMotorConfiguration.dir/main.o


CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o: CMakeFiles/uartMotorConfiguration.dir/flags.make
CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o: /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/configDataHandling.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o -c /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/configDataHandling.cpp

CMakeFiles/uartMotorConfiguration.dir/configDataHandling.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uartMotorConfiguration.dir/configDataHandling.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/configDataHandling.cpp > CMakeFiles/uartMotorConfiguration.dir/configDataHandling.i

CMakeFiles/uartMotorConfiguration.dir/configDataHandling.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uartMotorConfiguration.dir/configDataHandling.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/configDataHandling.cpp -o CMakeFiles/uartMotorConfiguration.dir/configDataHandling.s

CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.requires:

.PHONY : CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.requires

CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.provides: CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.requires
	$(MAKE) -f CMakeFiles/uartMotorConfiguration.dir/build.make CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.provides.build
.PHONY : CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.provides

CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.provides.build: CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o


CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o: CMakeFiles/uartMotorConfiguration.dir/flags.make
CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o: /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/SerialCommunication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o -c /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/SerialCommunication.cpp

CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/SerialCommunication.cpp > CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.i

CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source/SerialCommunication.cpp -o CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.s

CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.requires:

.PHONY : CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.requires

CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.provides: CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.requires
	$(MAKE) -f CMakeFiles/uartMotorConfiguration.dir/build.make CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.provides.build
.PHONY : CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.provides

CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.provides.build: CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o


CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o: CMakeFiles/uartMotorConfiguration.dir/flags.make
CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o: moc_configDataHandling.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o -c /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_configDataHandling.cxx

CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_configDataHandling.cxx > CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.i

CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_configDataHandling.cxx -o CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.s

CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.requires:

.PHONY : CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.requires

CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.provides: CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.requires
	$(MAKE) -f CMakeFiles/uartMotorConfiguration.dir/build.make CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.provides.build
.PHONY : CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.provides

CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.provides.build: CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o


CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o: CMakeFiles/uartMotorConfiguration.dir/flags.make
CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o: moc_SerialCommunication.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o -c /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_SerialCommunication.cxx

CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_SerialCommunication.cxx > CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.i

CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/moc_SerialCommunication.cxx -o CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.s

CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.requires:

.PHONY : CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.requires

CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.provides: CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.requires
	$(MAKE) -f CMakeFiles/uartMotorConfiguration.dir/build.make CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.provides.build
.PHONY : CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.provides

CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.provides.build: CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o


# Object files for target uartMotorConfiguration
uartMotorConfiguration_OBJECTS = \
"CMakeFiles/uartMotorConfiguration.dir/main.o" \
"CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o" \
"CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o" \
"CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o" \
"CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o"

# External object files for target uartMotorConfiguration
uartMotorConfiguration_EXTERNAL_OBJECTS =

uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/main.o
uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o
uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o
uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o
uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o
uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/build.make
uartMotorConfiguration: /usr/lib/x86_64-linux-gnu/libQtGui.so
uartMotorConfiguration: /usr/lib/x86_64-linux-gnu/libQtCore.so
uartMotorConfiguration: CMakeFiles/uartMotorConfiguration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable uartMotorConfiguration"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uartMotorConfiguration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uartMotorConfiguration.dir/build: uartMotorConfiguration

.PHONY : CMakeFiles/uartMotorConfiguration.dir/build

CMakeFiles/uartMotorConfiguration.dir/requires: CMakeFiles/uartMotorConfiguration.dir/main.o.requires
CMakeFiles/uartMotorConfiguration.dir/requires: CMakeFiles/uartMotorConfiguration.dir/configDataHandling.o.requires
CMakeFiles/uartMotorConfiguration.dir/requires: CMakeFiles/uartMotorConfiguration.dir/SerialCommunication.o.requires
CMakeFiles/uartMotorConfiguration.dir/requires: CMakeFiles/uartMotorConfiguration.dir/moc_configDataHandling.o.requires
CMakeFiles/uartMotorConfiguration.dir/requires: CMakeFiles/uartMotorConfiguration.dir/moc_SerialCommunication.o.requires

.PHONY : CMakeFiles/uartMotorConfiguration.dir/requires

CMakeFiles/uartMotorConfiguration.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uartMotorConfiguration.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uartMotorConfiguration.dir/clean

CMakeFiles/uartMotorConfiguration.dir/depend: moc_configDataHandling.cxx
CMakeFiles/uartMotorConfiguration.dir/depend: moc_SerialCommunication.cxx
	cd /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/source /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build /home/roboy/workspace/motorDriver/dcMotorUARTConfiguration/build/CMakeFiles/uartMotorConfiguration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uartMotorConfiguration.dir/depend
