# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/cmake-3.18.2-cirtl5oah4d6bequfcoji6jbetertrna/bin/cmake

# The command to remove a file.
RM = /autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/cmake-3.18.2-cirtl5oah4d6bequfcoji6jbetertrna/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_cascaded_selector.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_cascaded_selector.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_cascaded_selector.dir/flags.make

tests/CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.o: tests/CMakeFiles/test_cascaded_selector.dir/flags.make
tests/CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.o: /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_cascaded_selector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.o"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && /sw/summit/gcc/10.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.o -c /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_cascaded_selector.cpp

tests/CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.i"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && /sw/summit/gcc/10.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_cascaded_selector.cpp > CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.i

tests/CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.s"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && /sw/summit/gcc/10.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_cascaded_selector.cpp -o CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.s

# Object files for target test_cascaded_selector
test_cascaded_selector_OBJECTS = \
"CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.o"

# External object files for target test_cascaded_selector
test_cascaded_selector_EXTERNAL_OBJECTS =

bin/test_cascaded_selector: tests/CMakeFiles/test_cascaded_selector.dir/test_cascaded_selector.cpp.o
bin/test_cascaded_selector: tests/CMakeFiles/test_cascaded_selector.dir/build.make
bin/test_cascaded_selector: lib/libnvcomp.so
bin/test_cascaded_selector: /sw/summit/cuda/11.1.0/lib64/libcudart.so
bin/test_cascaded_selector: tests/CMakeFiles/test_cascaded_selector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/test_cascaded_selector"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_cascaded_selector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_cascaded_selector.dir/build: bin/test_cascaded_selector

.PHONY : tests/CMakeFiles/test_cascaded_selector.dir/build

tests/CMakeFiles/test_cascaded_selector.dir/clean:
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_cascaded_selector.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_cascaded_selector.dir/clean

tests/CMakeFiles/test_cascaded_selector.dir/depend:
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests/CMakeFiles/test_cascaded_selector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_cascaded_selector.dir/depend

