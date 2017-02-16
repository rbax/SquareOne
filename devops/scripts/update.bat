@echo off

:: xcopy flags
:: /y Overwrites existing files without prompting you.
:: /c Continues copying even if errors occur.
:: /h Copies hidden and system files.

::----------------------------------------------------------- [MSVC]
::    Desc:	Copy MSVC debug dll's (msvcp120d, msvcr120d)
::
::    Ref:	/source/thirdparty/MSVC/Debug/
:: ----------------------------------------------------------

IF EXIST %THIRD_MSVC%\Debug xcopy /y /c /h %THIRD_MSVC%\Debug %DEPLOY_DEBUG%


::----------------------------------------------------------- [QT]
::    Desc:	Copy Qt dll's
::
::    Ref: 	/docs/notes/Qt-Dlls.txt (for all Qt dll's)
:: ---------------------------------------------------------- 

IF NOT EXIST %DEPLOY_RELEASE% MKDIR %DEPLOY_RELEASE%
IF NOT EXIST %DEPLOY_DEBUG% MKDIR %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Core]

xcopy /y /c /h "%QT_BIN%\Qt5Core.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5Cored.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Gui]

xcopy /y /c /h "%QT_BIN%\Qt5Gui.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5Guid.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Network]

xcopy /y /c /h "%QT_BIN%\Qt5Network.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5Networkd.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [QML]

xcopy /y /c /h "%QT_BIN%\Qt5Qml.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5Qmld.dll" %DEPLOY_DEBUG%

xcopy /y /c /h "%QT_BIN%\Qt5Quick.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5Quickd.dll" %DEPLOY_DEBUG%

xcopy /y /c /h "%QT_BIN%\Qt5QuickWidgets.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5QuickWidgetsd.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Widgets]

xcopy /y /c /h "%QT_BIN%\Qt5Widgets.dll" %DEPLOY_RELEASE%
xcopy /y /c /h "%QT_BIN%\Qt5Widgetsd.dll" %DEPLOY_DEBUG%