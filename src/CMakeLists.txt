# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

# Filter out files ending with _native*
foreach(src_file ${all_sources})
    if (NOT src_file MATCHES ".*_native.*")
        list(APPEND app_sources ${src_file})
    endif()
endforeach()

idf_component_register(SRCS ${app_sources})
