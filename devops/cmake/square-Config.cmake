# -----------------------------------------------------------
#     Configuration for All Projects
# ----------------------------------------------------------- [Square Config]

macro(Config)

# ------------------------------------- [CMAKE FILES]

    include (square-Build)
    include (square-Link)
    include (square-Path)

    include (square-UseMSVC)
    include (square-UseQt)
    #include (square-UsePython)

# ------------------------------------- [Directories]

    Set_Path_Variables()	    # square-Path.cmake
    Create_Build_Directories()	# square-Path.cmake

# ------------------------------------- [CMAKE Options]

    mark_as_advanced (CMAKE_BUILD_TYPE)
    mark_as_advanced (CMAKE_INSTALL_PREFIX)
    mark_as_advanced (CMAKE_CONFIGURATION_TYPES)

    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GENERATE_LIBRARY})
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GENERATE_LIBRARY})
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DEPLOY_BINARY})
    set (CMAKE_BINARY_DIR ${BUILD})
    
    add_definitions(
    
        -DCMAKE_BUILD_TYPE=Release
	)

# ------------------------------------- [Compiler Options]

    set (CMAKE_INCLUDE_CURRENT_DIR ON)
    set (CMAKE_CXX_STANDARD 14)

    if(MSVC)

	    Config_MSVC() 	# square-UseMSVC.cmake

    endif()

    Config_Qt() 	    # square-UseQt.cmake
    #Config_Python()     # square-UsePython.cmake

# ------------------------------------- [Includes]

    include_directories (${GENERATE_EXPORTS})
    include_directories (${GENERATE_INCLUDE})
    include_directories (${CMAKE_BINARY_DIR})


    include (GenerateExportHeader)

endmacro(Config)
