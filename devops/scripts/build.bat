::@echo off

IF NOT EXIST %BUILD% mkdir %BUILD%
cd build
::cmake -Bbuild -H.

cmake  ../ -G "%MSCV_COMPILER%" 


cmake --build . --target ALL_BUILD --config Debug
cmake --build . --target ALL_BUILD --config Release

set /p finished = Build finished: Press ENTER to close.
exit