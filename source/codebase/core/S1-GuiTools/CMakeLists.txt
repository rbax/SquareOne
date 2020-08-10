project(S1-GuiTools)

Set_Path_Variables()

Export_Library()

Link_Qt()

target_link_libraries(${PROJECT_NAME} S1-DevTools)

Deploy()
