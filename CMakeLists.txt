cmake_minimum_required(VERSION 3.1)

# location of custom cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# custom utilities module
include("utilities")

# source files setup
#
# > libfw_src_files
#
set(libfw_src_files
    # temp, no files
)
fw_process_src_files(${libfw_src_files})

# include files setup
#
# > libfw_include_dir
# > libfw_include_files
#
set(libfw_include_dir "include")
fw_get_include_files(${libfw_include_dir} libfw_include_files)
fw_process_include_files(${libfw_include_files})

# project setup
#
# > libfw
#
add_library(libfw ${libfw_src_files} ${libfw_include_files})
fw_process_assembly(libfw)
target_include_directories(libfw PUBLIC ${libfw_include_dir})

# libfw already has a `lib` prepended so ensure any other prefix is removed
set_target_properties(libfw PROPERTIES PREFIX "")
set_target_properties(libfw PROPERTIES IMPORT_PREFIX "")