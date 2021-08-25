# Ray Marching
*Josh Bailey*<br />
*Master's Project.*<br />
*NCCA, Bournemouth University.*<br />
*2020 - 2021.*<br />

## Contents
1. [Overview](#overview)
2. [Project Setup](#project-setup)<br />
	2.1. [Windows](#windows)<br />
	2.2. [Mac](#mac)<br />
3. [Dependencies](#dependencies)

## Overview
The nature of this project was to design and implement an interactive shader editor that is equally accessible to both programmers and artists. The tool provides users with the choice between a code or node editor, to develop fragment shaders. The former requires previous GLSL experience, with users expect to code their shaders from scratch. However, the latter requires no previous programming experiences and takes advantage of a node-based editor, using a pre-implemented Ray Marching algorithm.

## Project Setup
### Windows
1. Enter the root directory of the project
2. Create a 'build' directory and enter it
3. Run "cmake .."
4. Run "cmake --build ."
5. Enter the 'Debug' directory
6. Run '.\ray-marching.exe'

### Mac
1. Enter the root directory of the project
2. Create a 'build' directory and enter it
3. Run "cmake .."
4. Run "make"
5. Run './ray-marching'

### Dependencies
- NGL Graphics Library - https://github.com/ncca/ngl
- nodeeditor Library - https://github.com/paceholder/nodeeditor
- Qt - https://www.qt.io/
- CMake - https://cmake.org/<br />
- C++17
