---
Title: libviewer
Description: very simple OpenGL renderer
Author: Deon Poncini

---

libviewer
===============

Developed by Deon Poncini <dex1337@gmail.com>

Downloads
---------
[github](https://github.com/DeonPoncini/libviewer)

Description
-----------
A very simple OpenGL renderer, written to support mostly tile based 2D scenes.
Has a simple game object concept with wrappers for easily loading textures and
shaders, and using perspective or orthographic cameras.
Has a test application that builds a small tile zone with a player on it. Could
be the basis of a roguelike game.

Building
--------
Install my useful [cmake utilities](https://github.com/DeonPoncini/cmake)
Requires OpenGL 3.3, GLFW3, glew, glm

    git clone https://github.com/DeonPoncini/libviewer.git
    cd libviewer
    mkdir _build
    cd _build
    cmake ..
    make

Usage
-----
The test program can be ran by executing viewer-test from its own directory.
You can move around with arrow keys or WSAD.
The example application exercises the APIs used in the library

License
-------
Copyright (c) 2014 Deon Poncini. See the LICENSE file for license rights and limitations (MIT)
