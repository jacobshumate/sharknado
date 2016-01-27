# sharknado
Sharknado Animation is written in C++ which originally started off as a 
model of a house that the user could rotate objects and change into different 
perspectives. With a growing understanding of the OpenGL Utility Toolkit (GLUT), 
there were many more objects and features added including zooming in and out, 
switching perspectives, moving the camera angle, and starting and stopping the animation.

To Compile:

OS X: g++ -framework GLUT -framework OpenGL -framework Cocoa sharknado.cpp -o test

Linux: g++ -o test sharknado.cpp -lglut -lGL -lGLU -lX11 -lm

