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
