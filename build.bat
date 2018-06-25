::@echo off
:: Req: CMAKE in path, QT_DIR set

set SQUARE=%CD%
call "%SQUARE%\devops\scripts\config.bat"

::set QT_DIR "C:\Qt\5.11.1\msvc2017_64\bin"

call "%DEVOPS_SCRIPTS%\clean.bat"
call "%DEVOPS_SCRIPTS%\update.bat"
call "%DEVOPS_SCRIPTS%\build.bat"

set /p finished = Build C/W: Press ENTER to close.
exit