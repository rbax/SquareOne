# -----------------------------------------------------------
#     batch link entire code base
# ----------------------------------------------------------- [Link CodeBase]

macro(Link_CodeBase)  #link tier1-3

        Link_Core()    #tier1
        Link_Models()  #tier2
        Link_Systems() #tier3

endmacro(Link_CodeBase)


# -----------------------------------------------------------
#     Core libraries have no dependencies
# ----------------------------------------------------------- [Link Core]

macro(Link_Core)

    target_link_libraries( ${PROJECT_NAME}

        S1-DevTools
        S1-GuiTools
        #S1-PluginTools
    )

endmacro(Link_Core)


# -----------------------------------------------------------
#     Module Libraries may depend on Core Libraries
# ----------------------------------------------------------- [Link Models]

macro(Link_Models)

    target_link_libraries ( ${PROJECT_NAME}

        S2-DragModel
    )

endmacro(Link_Models)


# -----------------------------------------------------------
#     System/Product Libraries may depend on Core and Module Libraries
# ----------------------------------------------------------- [Link Systems]

macro(Link_Systems)

    target_link_libraries ( ${PROJECT_NAME}

        S3-TableFrame
    )

endmacro(Link_Systems)
