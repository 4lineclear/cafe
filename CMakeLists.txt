cmake_minimum_required(VERSION 3.0)
project(cafe)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources      src/*.c src/*.h)
file(GLOB_RECURSE sources_test tests/*.c)
file(GLOB_RECURSE data resources/*)

###############################################################################
## target definitions #########################################################
###############################################################################

add_library(cafe ${sources} ${data})

# this lets me include files relative to the root source directory with a <> pair
target_include_directories(cafe PUBLIC src/main)

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
file(COPY ${data} DESTINATION resources)


###############################################################################
## testing ####################################################################
###############################################################################
## includes valgrind

enable_testing()

set(testBin ${CMAKE_CURRENT_SOURCE_DIR}/build/testBin)

foreach(testSrc ${sources_test})
    get_filename_component(testName ${testSrc} NAME_WE)
    add_executable(${testName} ${testSrc})
    set_target_properties(${testName} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${testBin})
    add_test(
        NAME ${testName}
        WORKING_DIRECTORY ${testBin}
        COMMAND ${testBin}/${testName})
    add_test(
        NAME ${testName}Memcheck
        WORKING_DIRECTORY ${testBin}
        COMMAND valgrind
            --track-origins=yes
            --error-exitcode=1
            --tool=memcheck
            --leak-check=full
            --errors-for-leak-kinds=definite
            --show-leak-kinds=definite $<TARGET_FILE:${testName}>)
endforeach()
