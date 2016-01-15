all:
	g++ Homework1/Source.cpp -L /usr/X11R6/lib/ -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm