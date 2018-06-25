SquareOne starter project
===========================

*****************************
by Ryan Baxter
Free to use - make it better!
*****************************

This project creates a GUI playground for coding in Visual Studio with CMAKE and Qt5.

It is useful for creating self-contained, deployable (zippable) apps. Build a project out of the codebase and thirdparty utilties as required.

Prerequisites
=============

1. CMake `(default: 3.3.1)`
2. Qt5 `(default: 5.11.1)`
3. MSVC `(default: Visual Studio 15 2017 Win64)`


Update software versions in ~\devops\scripts\config.bat

BUILD DIR
=========

*Run build.bat to create the build directory 

    VS proj
        \build\SquareOne.sln

    Deployable app:
        \build\deploy
        \build\deploy\bin\Release\_Main.exe

    Generated Code:
        \build\generate\exports
        \build\generate\include
        \build\generate\library

        
SOURCE DIR
==========

codebase
--------

1. core    `Core libraries have no dependencies`
2. models  `Module Libraries may depend on Core Libraries`
3. systems `System Libraries may depend on Core and Module Libraries`

projects
--------

create project apps from the codebase


thirdparty
----------

support libraries (if included)