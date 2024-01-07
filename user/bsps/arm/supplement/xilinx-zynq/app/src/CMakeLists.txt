cmake_minimum_required(VERSION 3.18.4)
project(ZynqDemo)

# Wipe out the flags that have been set to make the compiler tests work and to optionally build some libraries on top of libbsd
set(CMAKE_EXE_LINKER_FLAGS ""  CACHE INTERNAL "exe link flags" FORCE)
set(CMAKE_C_FLAGS_RELEASE ""  CACHE INTERNAL "c flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE ""  CACHE INTERNAL "c++ flags" FORCE)
set(CMAKE_C_FLAGS_DEBUG ""  CACHE INTERNAL "c flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG ""  CACHE INTERNAL "c++ flags" FORCE)
set(CMAKE_C_FLAGS ""  CACHE INTERNAL "c flags" FORCE)
set(CMAKE_CXX_FLAGS ""  CACHE INTERNAL "c++ flags" FORCE)


add_executable(${PROJECT_NAME}
  #p1
  #${CMAKE_CURRENT_LIST_DIR}/main/main.cpp
  #${CMAKE_CURRENT_LIST_DIR}/main/pre_main.c
  #${CMAKE_CURRENT_LIST_DIR}/main/mmu.c
  # p2
  #/home/blofeld/quick-start/src/rtems/testsuites/libtests/flashdev01/init.c
  #/home/blofeld/quick-start/src/rtems/testsuites/libtests/flashdev01/test_flashdev.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs01/init.c
  /home/blofeld/quick-start/src/rtems/testsuites/libtests/flashdev01/test_flashdev.c
  
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_alloc.t.a.c  
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_attrs.t.c        
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_bd.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_compat.t.c  
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_entries.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_evil.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_files.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_interspersed.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_orphans.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_paths.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_relocations.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_seek.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_truncate.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_alloc.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_badblocks.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_bd.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_dirs.t.a.c  
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_entries.t.c    
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_exhaustion.t.a.c  
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_files.t.c           
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_move.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_orphans.t.c    
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_powerloss.t.a.c  
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_relocations.t.c    
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_superblocks.t.a.c  
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_truncate.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_attrs.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_badblocks.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_compat.t.a.c  
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_dirs.t.c    
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_evil.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_exhaustion.t.c    
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_interspersed.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_move.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_paths.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_powerloss.t.c
  #/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_seek.t.a.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/tests/test_superblocks.t.c

  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/bd/lfs_emubd.t.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/bd/lfs_filebd.t.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/bd/lfs_rambd.t.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/bd/lfs_emubd.t.c
  /home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02/runners/test_runner.t.c
)
target_include_directories(${PROJECT_NAME} PUBLIC "/home/blofeld/quick-start/src/rtems/testsuites/fstests/fslfs02")

target_include_directories(${PROJECT_NAME} PUBLIC "/home/blofeld/quick-start/src/rtems/testsuites/support/include")
target_link_libraries(${PROJECT_NAME}  rtemstest lfs)
target_compile_options(${PROJECT_NAME} PUBLIC -fcallgraph-info=su -g3 -std=c99 -Wall -Wextra -pedantic -Wmissing-prototypes -ftrack-macro-expansion=0 -Os -Wno-missing-prototypes --coverage)
target_link_options(${PROJECT_NAME} PUBLIC -fcallgraph-info=su -g3 -std=c99 -Wall -Wextra -pedantic -Wmissing-prototypes -ftrack-macro-expansion=0 -Os -Wno-missing-prototypes --coverage)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${RTEMS_CMAKE_APPLICATION_EXE_LINKER_FLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
target_compile_options(${PROJECT_NAME} 
  PUBLIC
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CONFIG:Debug>:SHELL:${RTEMS_CMAKE_APPLICATION_CXX_FLAGS_DEBUG}>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CONFIG:Release>:SHELL:${RTEMS_CMAKE_APPLICATION_CXX_FLAGS_RELEASE}>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CONFIG:RelWithDebInfo>:SHELL:${RTEMS_CMAKE_APPLICATION_CXX_FLAGS_RELWITHDEBINFO}>>
  $<$<COMPILE_LANGUAGE:CXX>:$<$<CONFIG:MinSizeRel>:SHELL:${RTEMS_CMAKE_APPLICATION_CXX_FLAGS_MINSIZEREL}>>
  $<$<COMPILE_LANGUAGE:C>:$<$<CONFIG:Debug>:SHELL:${RTEMS_CMAKE_APPLICATION_C_FLAGS_DEBUG}>>
  $<$<COMPILE_LANGUAGE:C>:$<$<CONFIG:Release>:SHELL:${RTEMS_CMAKE_APPLICATION_C_FLAGS_RELEASE}>>
  $<$<COMPILE_LANGUAGE:C>:$<$<CONFIG:RelWithDebInfo>:SHELL:${RTEMS_CMAKE_APPLICATION_C_FLAGS_RELWITHDEBINFO}>>
  $<$<COMPILE_LANGUAGE:C>:$<$<CONFIG:MinSizeRel>:SHELL:${RTEMS_CMAKE_APPLICATION_C_FLAGS_MINSIZEREL}>>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}  $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.exe    
    #COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.dbg
    #COMMAND ${CMAKE_OBJCOPY} --strip-unneeded $<TARGET_FILE:${PROJECT_NAME}>
    #COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.dbg $<TARGET_FILE:${PROJECT_NAME}>
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Splitting off debug symbols from ${PROJECT_NAME}"
)

# if you use -G"Unix Makefiles" you'll receive a more verbose output, doesnt work well for ninja
# call ninja -v to get more info
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# add an install target - not required
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/../install)
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.exe DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.elf DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.dbg DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
