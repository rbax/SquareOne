project(_Main)

Set_Path_Variables()

Build_Executable()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT _Main)

Link_Codebase()
Link_Qt()

target_link_libraries(${PROJECT_NAME} _Client)

add_subdirectory(client)
