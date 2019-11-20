@echo off

:: Qt Directory
set QT_PATH=C:\Qt
set QT_VERSION=5.13.1
set QT_COMPILER=msvc2017_64
set QT_DIR=%QT_PATH%\%QT_VERSION%\%QT_COMPILER%
set QT_PLATFORM=%QT_DIR%\plugins\platforms
set QT_BIN=%QT_DIR%\bin

set MSCV_COMPILER=Visual Studio 16 2019

:: Terms
set RELEASE=bin\Release
set DEBUG=bin\Debug

:: Square Directories
set DEVOPS=%SQUARE%\devops
set BUILD=%SQUARE%\build
set SOURCE=%SQUARE%\source

:: Deployment Directories
set DEPLOY=%BUILD%\deploy
set DEPLOY_DOCS=%DEPLOY%\docs
set DEPLOY_ASSETS=%DEPLOY%\assets
set DEPLOY_RELEASE=%DEPLOY%\%RELEASE%\
set DEPLOY_DEBUG=%DEPLOY%\%DEBUG%\
set DEPLOY_THIRD=%DEPLOY%\thirdparty

::DevOps Directories
set DEVOPS_SCRIPTS=%DEVOPS%\scripts
set DEVOPS_CMAKE=%DEVOPS%\cmake
set DEVOPS_TOOLS=%DEVOPS%\tools

:: Local Third Party Directories
set THIRD=%SOURCE%\thirdparty
set THIRD_QT=%THIRD%\Qt
set THIRD_MSVC=%THIRD%\MSVC
set THIRD_PYTHON=%THIRD%\Python

:: Command shell overview
:: https://technet.microsoft.com/en-us/library/bb490954.aspx
