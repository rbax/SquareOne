# -----------------------------------------------------------
#     set path variables
# ----------------------------------------------------------- [SetPathVariables]

macro(Set_Path_Variables)

# ------------------------------------- [Binary/Deploy]

    set (BUILD                      ${CMAKE_SOURCE_DIR}/build)

    set (DEPLOY                     ${CMAKE_BINARY_DIR}/deploy)

    set (DEPLOY_ASSETS              ${DEPLOY}/assets)
    set (DEPLOY_ASSETS_PROJECT      ${DEPLOY}/assets/${PROJECT_NAME})

    set (DEPLOY_BINARY              ${DEPLOY}/bin)
    set (DEPLOY_BINARY_RELEASE      ${DEPLOY_BINARY}/Release)
    set (DEPLOY_BINARY_DEBUG        ${DEPLOY_BINARY}/Debug)

    set (DEPLOY_DOCS                ${DEPLOY}/docs)
    set (DEPLOY_THIRD               ${DEPLOY}/thirdparty)

# ------------------------------------- [Binary/Generate]

    set (GENERATE                   ${CMAKE_BINARY_DIR}/generate)

    set (GENERATE_INCLUDE           ${GENERATE}/include)
    set (GENERATE_EXPORTS           ${GENERATE}/exports)
    set (GENERATE_LIBRARY           ${GENERATE}/library)

# ------------------------------------- [Project]

    set (PROJECT_ASSETS             ${PROJECT_SOURCE_DIR}/assets)

endmacro(Set_Path_Variables)

# -----------------------------------------------------------
#    Setup Directory Structure in Build Path
# ----------------------------------------------------------- [CreateBuildDirs]

macro(Create_Build_Directories)

    file (MAKE_DIRECTORY ${DEPLOY})
    file (MAKE_DIRECTORY ${DEPLOY_ASSETS})
    file (MAKE_DIRECTORY ${DEPLOY_BINARY})
    file (MAKE_DIRECTORY ${DEPLOY_BINARY_RELEASE})
    file (MAKE_DIRECTORY ${DEPLOY_BINARY_DEBUG})
    file (MAKE_DIRECTORY ${DEPLOY_DOCS})

    file (MAKE_DIRECTORY ${GENERATE_EXPORTS})
    file (MAKE_DIRECTORY ${GENERATE_INCLUDE})
    file (MAKE_DIRECTORY ${GENERATE_LIBRARY})

endmacro(Create_Build_Directories)
