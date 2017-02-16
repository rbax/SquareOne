@echo off

:: xcopy flags
:: /y Overwrites existing files without prompting you.
:: /c Continues copying even if errors occur.
:: /h Copies hidden and system files.

::----------------------------------------------------------- [MSVC]
::    Desc:	Unpack the embedded python package into the deployment directory
::
::    Ref:	/source/thirdparty/Python/python-3.6.0-embed-amd64
:: ----------------------------------------------------------

::for /F %DEPLOY_THIRD% %%I in ("*.zip") do ("%DEVOPS_TOOLS%\7z.exe" x -y -o"%%~dpI" "%%~fI")

::IF EXIST %THIRD_PYTHON% 

::FORFILES /p %THIRD_PYTHON% 