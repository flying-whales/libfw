# sets source group for all source files so that they show up in the
# correct directories in source views
function(fw_process_src_files)
    foreach(file ${ARGN})
        string(REPLACE ${CMAKE_CURRENT_LIST_DIR} "" formatted ${file})
		string(REGEX REPLACE "^/" "" formatted ${formatted})
		string(REGEX REPLACE "/[^/]([a-zA-Z0-9_.]*)$" "" formatted ${formatted})
		string(REGEX REPLACE "/" "\\\\" formatted ${formatted})
		source_group(${formatted} FILES ${file})
    endforeach()
endfunction()

# glob searches directories for source files
function(fw_get_include_files directory output)
    file(GLOB_RECURSE files "${directory}/*.*")
	set(${output} ${files} PARENT_SCOPE)
endfunction()

# sets all files to header only so that CMake does not mark them
# as a file to compile, only to include. this means that even if there is .cpp
# files that CMake would normally compile present, they will be ignored
function(fw_process_include_files)
    fw_process_src_files(${ARGN})
	set_source_files_properties(${ARGN} PROPERTIES HEADER_FILE_ONLY true)
endfunction()

# sets all required assembly properties
function(fw_process_assembly assembly)
    set_target_properties(${assembly} PROPERTIES CXX_STANDARD 14)
	set_target_properties(${assembly} PROPERTIES CXX_STANDARD_REQUIRED on)
endfunction()