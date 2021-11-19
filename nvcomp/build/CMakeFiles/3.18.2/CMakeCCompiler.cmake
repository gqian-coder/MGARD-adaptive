set(CMAKE_C_COMPILER "/sw/summit/gcc/10.2.0/bin/gcc")
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_C_COMPILER_ID "GNU")
set(CMAKE_C_COMPILER_VERSION "10.2.0")
set(CMAKE_C_COMPILER_VERSION_INTERNAL "")
set(CMAKE_C_COMPILER_WRAPPER "")
set(CMAKE_C_STANDARD_COMPUTED_DEFAULT "11")
set(CMAKE_C_COMPILE_FEATURES "c_std_90;c_function_prototypes;c_std_99;c_restrict;c_variadic_macros;c_std_11;c_static_assert")
set(CMAKE_C90_COMPILE_FEATURES "c_std_90;c_function_prototypes")
set(CMAKE_C99_COMPILE_FEATURES "c_std_99;c_restrict;c_variadic_macros")
set(CMAKE_C11_COMPILE_FEATURES "c_std_11;c_static_assert")

set(CMAKE_C_PLATFORM_ID "Linux")
set(CMAKE_C_SIMULATE_ID "")
set(CMAKE_C_COMPILER_FRONTEND_VARIANT "")
set(CMAKE_C_SIMULATE_VERSION "")




set(CMAKE_AR "/usr/bin/ar")
set(CMAKE_C_COMPILER_AR "/sw/summit/gcc/10.2.0/bin/gcc-ar")
set(CMAKE_RANLIB "/usr/bin/ranlib")
set(CMAKE_C_COMPILER_RANLIB "/sw/summit/gcc/10.2.0/bin/gcc-ranlib")
set(CMAKE_LINKER "/sw/summit/xalt/1.2.1/bin/ld")
set(CMAKE_MT "")
set(CMAKE_COMPILER_IS_GNUCC 1)
set(CMAKE_C_COMPILER_LOADED 1)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_C_COMPILER_ENV_VAR "CC")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_C_COMPILER_ID_RUN 1)
set(CMAKE_C_SOURCE_FILE_EXTENSIONS c;m)
set(CMAKE_C_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_C_LINKER_PREFERENCE 10)

# Save compiler ABI information.
set(CMAKE_C_SIZEOF_DATA_PTR "8")
set(CMAKE_C_COMPILER_ABI "ELF")
set(CMAKE_C_LIBRARY_ARCHITECTURE "")

if(CMAKE_C_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_C_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_C_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_C_COMPILER_ABI}")
endif()

if(CMAKE_C_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_C_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_C_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_C_CL_SHOWINCLUDES_PREFIX}")
endif()





set(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES "/sw/summit/cuda/11.1.0/include;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-10.2.0/hdf5-1.10.4-bbs4dtnlib3xajj6tpylzksrnoctwg7j/include;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-10.2.0/spectrum-mpi-10.3.1.2-20200121-4pokcfvq4efu6vh7gofiiszc7t7iyzqc/include;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-10.2.0/zlib-1.2.11-az5626myguoq2wq7uik36rpga4dsaz23/include;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/libpng-1.6.34-uvunthywhufrluoiwgdfkqxdyk7n3r3y/include;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/zstd-1.3.0-ceiov3tyabxamzbrvmpdbxsrc5mtzi2f/include;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/zeromq-4.2.5-6xg35r6xag6l7yqtjq7uyhue7oqxknh2/include;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/libfabric-1.7.0-tx5vgycf5fppsvfyzkokselan5ivoa65/include;/autofs/nccs-svm1_sw/summit/gcc/10.2.0/lib/gcc/powerpc64le-unknown-linux-gnu/10.2.0/include;/autofs/nccs-svm1_sw/summit/gcc/10.2.0/lib/gcc/powerpc64le-unknown-linux-gnu/10.2.0/include-fixed;/usr/local/include;/autofs/nccs-svm1_sw/summit/gcc/10.2.0/include;/usr/include")
set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "gcc;gcc_s;c;gcc;gcc_s")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "/autofs/nccs-svm1_sw/summit/gcc/10.2.0/lib/gcc/powerpc64le-unknown-linux-gnu/10.2.0;/autofs/nccs-svm1_sw/summit/gcc/10.2.0/lib/gcc;/autofs/nccs-svm1_sw/summit/gcc/10.2.0/lib64;/lib64;/usr/lib64;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-10.2.0/hdf5-1.10.4-bbs4dtnlib3xajj6tpylzksrnoctwg7j/lib;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-10.2.0/spectrum-mpi-10.3.1.2-20200121-4pokcfvq4efu6vh7gofiiszc7t7iyzqc/lib;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-10.2.0/zlib-1.2.11-az5626myguoq2wq7uik36rpga4dsaz23/lib;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/libpng-1.6.34-uvunthywhufrluoiwgdfkqxdyk7n3r3y/lib;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/zstd-1.3.0-ceiov3tyabxamzbrvmpdbxsrc5mtzi2f/lib;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/zeromq-4.2.5-6xg35r6xag6l7yqtjq7uyhue7oqxknh2/lib;/autofs/nccs-svm1_sw/summit/.swci/0-core/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/libfabric-1.7.0-tx5vgycf5fppsvfyzkokselan5ivoa65/lib;/autofs/nccs-svm1_sw/summit/.swci/1-compute/opt/spack/20180914/linux-rhel7-ppc64le/gcc-4.8.5/darshan-runtime-3.1.7-cnvxicgf5j4ap64qi6v5gxp67hmrjz43/lib;/autofs/nccs-svm1_sw/summit/gcc/10.2.0/lib")
set(CMAKE_C_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
