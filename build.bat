::@echo off

::set QT_DIR=%QT_PATH%\%QT_VERSION%\%QT_COMPILER%
::set SQUARE=%CD%

call "%SQUARE%\devops\scripts\config.bat"

call "%DEVOPS_SCRIPTS%\clean.bat"
call "%DEVOPS_SCRIPTS%\update.bat"
call "%DEVOPS_SCRIPTS%\build.bat"

set /p finished = Build C/W: Press ENTER to close.
exit