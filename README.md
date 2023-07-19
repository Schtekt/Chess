# Chess

My take on a chess application.
The ambition is to be able to play local games of chess with a stretch goal to implement AI and allow users to script and add their own AIs to the game.

This project is currently built on a windows machine and is therefore only supported on that operating system.

## Prerequisites
This repo uses premake as a build configuration tool. The user may therefore generate a build solution for visual studio.
The project is however developed mainly through vscode, for a more lightweight experience.

To be able to generate the build files, compile the code and run the application through vscode, the following is necessary to install/download:

* **Premake5**, can be downloaded from the premake [website](https://premake.github.io/). Make sure to place it somewhere appropriate and add the resulting folder to PATH. (Or you could simply have the executable reside in this repo)

* **Visual studio code** (Can be found here https://visualstudio.microsoft.com/downloads/)

* **MSBuild**, this can be obtained with ["Build tools for visual studio"](https://aka.ms/vs/17/release/vs_BuildTools.exe). Make sure to add the MSBuild bin directory to PATH.

## Build solution and compile program
Generate a solution with premake with the following command
    
    premake5 vs2022

This will generate a solution for visual studio IDE 2022 edition.

Next, run the following command to generate json build commands for visual studio code
    
    premake5 vscode

You should now be able to build the project from vscode. Open the project from the root of this repo, press **ctrl+shift+b** and select the appropriate options.

Once the application has been built, you should be able to run it from vscode with **f5**.