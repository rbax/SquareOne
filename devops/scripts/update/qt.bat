@echo off

:: xcopy flags
:: /y Overwrites existing files without prompting you.
:: /c Continues copying even if errors occur.
:: /h Copies hidden and system files.

::----------------------------------------------------------- [QT]
::    Desc:	Copy Qt dll's
::
::    Ref: 	/docs/notes/Qt-Dlls.txt (for all Qt dll's)
:: ---------------------------------------------------------- 

IF NOT EXIST %DEPLOY_RELEASE% MKDIR %DEPLOY_RELEASE%
IF NOT EXIST %DEPLOY_RELEASE% MKDIR %DEPLOY_RELEASE%/platforms
IF NOT EXIST %DEPLOY_DEBUG% MKDIR %DEPLOY_DEBUG%
IF NOT EXIST %DEPLOY_DEBUG% MKDIR %DEPLOY_DEBUG%/platforms

:: ----------------------------------------------------------- [Core]

xcopy /f /y /c /h "%QT_BIN%\Qt5Core.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5Cored.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Gui]

xcopy /f /y /c /h "%QT_BIN%\Qt5Gui.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5Guid.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Network]

xcopy /f /y /c /h "%QT_BIN%\Qt5Network.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5Networkd.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [QML]

xcopy /f /y /c /h "%QT_BIN%\Qt5Qml.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5Qmld.dll" %DEPLOY_DEBUG%

xcopy /f /y /c /h "%QT_BIN%\Qt5Quick.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5Quickd.dll" %DEPLOY_DEBUG%

xcopy /f /y /c /h "%QT_BIN%\Qt5QuickWidgets.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5QuickWidgetsd.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Widgets]

xcopy /f /y /c /h "%QT_BIN%\Qt5Widgets.dll" %DEPLOY_RELEASE%
xcopy /f /y /c /h "%QT_BIN%\Qt5Widgetsd.dll" %DEPLOY_DEBUG%

:: ----------------------------------------------------------- [Platform]

xcopy /f /y /c /h "%QT_PLATFORM%\qwindows.dll" "%DEPLOY_RELEASE%\platforms\"
xcopy /f /y /c /h "%QT_PLATFORM%\qwindowsd.dll" "%DEPLOY_DEBUG%\platforms\"
