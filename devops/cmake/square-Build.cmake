# -----------------------------------------------------------
#     turn your project into an executable
# ----------------------------------------------------------- [Build Executable]

macro(Build_Executable)

    file(GLOB PROJECT_HEADERS *.h)
    file(GLOB PROJECT_SOURCES *.cc *.cpp)

    file(GLOB PROJECT_UIS *.ui)
    file(GLOB PROJECT_RCS *.qrc)

    include_directories (

        ${INCLUDE_DIR}
        ${GENERATE_INCLUDE}
    )

    add_executable (

        ${PROJECT_NAME}
        ${PROJECT_HEADERS}
        ${PROJECT_SOURCES}
        ${PROJECT_UIS}
        ${PROJECT_RCS}
    )

endmacro(Build_Executable)


# -----------------------------------------------------------
#     export your project as a library
# ----------------------------------------------------------- [Export Library]

macro(Export_Library)

    file(GLOB_RECURSE PROJECT_HEADERS *.h)
    file(GLOB_RECURSE PROJECT_SOURCES *.cc *.cpp)

    file(GLOB_RECURSE PROJECT_UIS     *.ui)
    file(GLOB_RECURSE PROJECT_RCS     *.qrc)

    # export compiler options
    set (CMAKE_CXX_VISIBILITY_PRESET hidden)
    set (CMAKE_VISIBILITY_INLINES_HIDDEN 1)

    add_library (

        ${PROJECT_NAME} SHARED
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UIS}
        ${PROJECT_RCS}
    )

    generate_export_header (

        ${PROJECT_NAME}
        EXPORT_FILE_NAME "${PROJECT_NAME}_Export.h"
    )

    add_custom_command ( # run before all other dependencies

        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND}
        ARGS -E copy_if_different
        "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}_Export.h"
        ${GENERATE_EXPORTS}
     )

endmacro(Export_Library)



# -----------------------------------------------------------
#     deploy project directories and files to dispatch folders
# ----------------------------------------------------------- [Deploy Project]

macro(Deploy)

# ------------------------------------- [Header Files]

install (
    
    FILES ${PROJECT_HEADERS} 
    DESTINATION ${GENERATE_INCLUDE}
)

# ------------------------------------- [Resource Directory]

if (EXISTS ${PROJECT_ASSETS})

    if (NOT EXISTS ${DEPLOY_ASSETS_PROJECT})

        file (MAKE_DIRECTORY ${DEPLOY_ASSETS_PROJECT})

    endif (NOT EXISTS ${DEPLOY_ASSETS_PROJECT})

    install (
        
        DIRECTORY "${PROJECT_ASSETS}/" 
        DESTINATION ${DEPLOY_ASSETS_PROJECT}
    )

endif (EXISTS ${PROJECT_ASSETS})

add_custom_command (
    
    TARGET ${PROJECT_NAME} 
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -D
    BUILD_TYPE=$(Configuration) -P
    cmake_install.cmake
)

endmacro(Deploy)