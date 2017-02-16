@echo off

:: RMDIR FLAGS
:: /s Removes the specified directory and all subdirectories including any files. Use /s to remove a tree.
:: /q Runs rmdir in quiet mode. Deletes directories without confirmation.

:: purge
IF EXIST %BUILD% rmdir /S /Q %BUILD%

:: echo clean complete
