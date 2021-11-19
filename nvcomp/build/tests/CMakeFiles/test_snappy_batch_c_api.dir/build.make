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
include tests/CMakeFiles/test_snappy_batch_c_api.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_snappy_batch_c_api.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_snappy_batch_c_api.dir/flags.make

tests/CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.o: tests/CMakeFiles/test_snappy_batch_c_api.dir/flags.make
tests/CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.o: /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_snappy_batch_c_api.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.o"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && /sw/summit/gcc/10.2.0/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.o -c /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_snappy_batch_c_api.c

tests/CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.i"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && /sw/summit/gcc/10.2.0/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_snappy_batch_c_api.c > CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.i

tests/CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.s"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && /sw/summit/gcc/10.2.0/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests/test_snappy_batch_c_api.c -o CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.s

# Object files for target test_snappy_batch_c_api
test_snappy_batch_c_api_OBJECTS = \
"CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.o"

# External object files for target test_snappy_batch_c_api
test_snappy_batch_c_api_EXTERNAL_OBJECTS =

bin/test_snappy_batch_c_api: tests/CMakeFiles/test_snappy_batch_c_api.dir/test_snappy_batch_c_api.c.o
bin/test_snappy_batch_c_api: tests/CMakeFiles/test_snappy_batch_c_api.dir/build.make
bin/test_snappy_batch_c_api: lib/libnvcomp.so
bin/test_snappy_batch_c_api: /sw/summit/cuda/11.1.0/lib64/libcudart.so
bin/test_snappy_batch_c_api: tests/CMakeFiles/test_snappy_batch_c_api.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/test_snappy_batch_c_api"
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_snappy_batch_c_api.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_snappy_batch_c_api.dir/build: bin/test_snappy_batch_c_api

.PHONY : tests/CMakeFiles/test_snappy_batch_c_api.dir/build

tests/CMakeFiles/test_snappy_batch_c_api.dir/clean:
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_snappy_batch_c_api.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_snappy_batch_c_api.dir/clean

tests/CMakeFiles/test_snappy_batch_c_api.dir/depend:
	cd /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/src/tests /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests /gpfs/alpine/proj-shared/csc143/gongq/andes/MReduction/MGARD/external/nvcomp/build/tests/CMakeFiles/test_snappy_batch_c_api.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_snappy_batch_c_api.dir/depend

