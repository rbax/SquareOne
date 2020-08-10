macro(Config_Qt)

    Define_Qt()
    Settings_Qt()
    # Deploy_Qt()

endmacro(Config_Qt)


# -----------------------------------------------------------
# Directory Scope Command options for Qt Specific Definitions
# ----------------------------------------------------------- [Define]

macro(Define_Qt)

    add_definitions(

        -DQT_CORE_LIB
        -DQT_GUI_LIB
        -DQT_WIDGETS_LIB
        -DQT_QUICK_LIB
        -DQT_QML_LIB
        -DQT_NETWORK_LIB
        -DQT_COMPILING_QSTRING_COMPAT_CPP		# QString (toUTF8)
	)

endmacro(Define_Qt)


# -----------------------------------------------------------
# Compiler Settings
# ----------------------------------------------------------- [Settings]

macro(Settings_Qt)

    find_package ( Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network

        Quick
        QuickWidgets
        QML
        OpenGL

        REQUIRED
    )

    set (CMAKE_AUTOMOC ON)	# Q_OBJECT
    set (CMAKE_AUTOUIC ON)	# .ui files
    set (CMAKE_AUTORCC ON)	# .rcc & .qrc files
    SET (QT_MIN_VERSION "5.2.0")

endmacro(Settings_Qt)


# -----------------------------------------------------------
# Move Files
# ----------------------------------------------------------- [Deploy]

macro(Deploy_Qt)
# @todo
endmacro(Deploy_Qt)


# -----------------------------------------------------------
# batch use_modules for qt components
# ----------------------------------------------------------- [Link]

macro(Link_Qt)

    target_link_libraries( ${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network

        Qt5::Quick
        Qt5::QuickWidgets
        Qt5::Qml
        Qt5::OpenGL
		#Qt5::Xml
		#Qt5::WebEngineWidgets
		#Qt5::WebEngineCore
		#Qt5::WebEngine
    )

endmacro(Link_Qt)


# -----------------------------------------------------------
#
# ----------------------------------------------------------- [LINK NOTES]

# AxContainer 		# Module is a Windows-only extension for accessing ActiveX controls and COM objects
# 3DCore 		    # foundation for Qt 3D simulation framework, as well as trender using the Qt 3D framework
# 3DInput 		    # Contains classes that enable user input
# 3DLogic 		    # Qt 3D Logic module enables synchronizing frames with the Qt 3D backend
# 3DRender 		    # Qt 3D Render module contains functionality to support 2D and 3D rendering using Qt 3D
# AndroidExtras 	# Qt Android Extras module contains additional functionality for development on Android
# Bluetooth 		# Enables basic Bluetooth operations like scanning for devices and connecting them
# Concurrent 		# Qt Concurrent module contains functionality to support concurrent execution of program code
# Core 		       	# Provides core non-GUI functionality
# DBus 			# Qt D-Bus module is a Unix-only library that you can use to perform Inter-Process Communication using the D-Bus protocol
# Designer 		# Provides classes to create your own custom widget plugins for Qt Designer and classes to access Qt Designer components
# Gui 			# Qt GUI module provides the basic enablers for graphical applications written with Qt
# Help 			# Provides classes for integrating online documentation in applications
# Location 		# Provides C++ interfaces to retrieve location and navigational information
# MacExtras 		# Provides classes and functions specific to OS X and iOS operating systems
# Multimedia 		# Qt Multimedia module provides audio, video, radio and camera functionality
# Network 		# Provides classes to make network programming easier and portable
# NFC 			# An API for accessing NFC Forum Tags
# OpenGL 		# Qt OpenGL module offers classes that make it easy to use OpenGL in Qt applications
# PlatformHeaders 	# inline classes to encapsulate platform-specific info tied to a runtime configuration of a platform plugin
# Positioning 		# Positioning module provides positioning information via QML and C++ interfaces
# PrintSupport 		# Qt PrintSupport module provides classes to make printing easier and portable
# Qml 			# C++ API provided by the Qt QML module
# Quick 		# Qt Quick module provides classes for embedding Qt Quick in Qt/C++ applications
# QuickWidgets 		# C++ API provided by the Qt Quick Widgets module
# Script 		# Qt Script module provides classes for making Qt applications scriptable
# ScriptTools 		# Provides additional components for applications that use Qt Script
# Sensors 		# Provides classes for reading sensor data
# SerialBus 		# Provides classes to read and write serial bus data
# SerialPort 		# List of C++ classes that enable access to a serial port
# Sql 			# Provides a driver layer, SQL API layer, and a user interface layer for SQL databases
# Svg 			# Qt SVG module provides functionality for handling SVG images
# Test 			# Provides classes for unit testing Qt applications and libraries
# UiTools 		# Provides classes to handle forms created with Qt Designer
# WebChannel 		# List of C++ classes that provide the Qt WebChannel functionality
# WebEngineWidgets 	# Provides a web browser engine as well as C++ classes to render and interact with web content
# WebSockets 		# List of C++ classes that enable WebSocket-based communication
# WebView 		# Provides a helper function to set up and use the WebView
# Widgets 		# Qt Widgets module extends Qt GUI with C++ widget functionality
# WinExtras 		# Provides classes and functions for using some Windows APIs in a Qt way
# X11Extras 		# Provides classes for developing for the X11 platform
# Xml 			# Qt XML module provides C++ implementations of the SAX and DOM standards for XML
# XmlPatterns 		# Qt XML Patterns module provides support for XPath, XQuery, XSLT and XML Schema validation



# -----------------------------------------------------------
# DEFINE NOTES
# -----------------------------------------------------------

# [Libraries]

# add_definitions(-DQT_CORE_LIB)
# add_definitions(-DQT_GUI_LIB)
# add_definitions(-DQT_WIDGETS_LIB)
# add_definitions(-DQT_QUICK_LIB)
# add_definitions(-DQT_QML_LIB)
# add_definitions(-DQT_NETWORK_LIB)
# add_definitions(-DQT_OPENGL_LIB)

# [OFF]

# add_definitions(-DQT_NO_MTDEV
# add_definitions(-DQT_NO_LIBUDEV)
# add_definitions(-DQT_NO_XKB)
# add_definitions(-DQT_NO_EXCEPTIONS)
# add_definitions(-DQT_NO_DEBUG)

# [Files]

# add_definitions(-D_LARGEFILE64_SOURCE)
# add_definitions(-D_LARGEFILE_SOURCE)

# [Misc]

# add_definitions(-DQT_PLUGIN)                       # Qt Plugin System
# add_definitions(-DQT_COMPILING_QSTRING_COMPAT_CPP)  # QString (toUTF8)
