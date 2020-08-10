project(_Main)

Set_Path_Variables()

Build_Executable()

Link_Codebase()
Link_Qt()

target_link_libraries(${PROJECT_NAME} _Client)

add_subdirectory(client)
