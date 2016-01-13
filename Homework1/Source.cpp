#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float *PixelBuffer;
void display();
void setPixel(int, int);
void setColor(float, float, float);
void DDALine(int, int, int, int);
void bresenhamLine(int, int, int, int);
void gradient();

const int WIDTH = 300;
const int HEIGHT = 300;

float COLOR[3] = { 1,1,1 };

float D[] = {50,50,50,150,100,125,100,75,50,50};
float F[] = { 150,50,150,150,200,150,150,150,150,100,200,100 };

int main(int argc, char *argv[])
{
	//allocate new pixel buffer, need initialization!!
	PixelBuffer = new float[WIDTH * HEIGHT * 3];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(WIDTH, HEIGHT);
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Hello Graphics!!");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
							  //sets display function
	glutDisplayFunc(display);

	glutMainLoop();//main display loop, will display until terminate
	return 0;
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gradient();

	setColor(0, 1.0, 0);

	for (int i = 0; i < 4; i++) {
		bresenhamLine(D[i*2], D[i*2+1], D[i*2+2], D[i*2+3]);
	}

	for (int i = 0; i < 5; i++) {
		bresenhamLine(F[i * 2], F[i * 2 + 1], F[i * 2 + 2], F[i * 2 + 3]);
	}

	//draws pixel on screen, width and height must match pixel buffer dimension
	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_FLOAT, PixelBuffer);

	//window refresh
	glFlush();
}

void setPixel(int x, int y) {
	PixelBuffer[x * 3 + y * WIDTH * 3] = COLOR[0];
	PixelBuffer[x * 3 + y * WIDTH * 3 + 1] = COLOR[1];
	PixelBuffer[x * 3 + y * WIDTH * 3 + 2] = COLOR[2];
}

void setColor(float r, float g, float b) {
	COLOR[0] = r;
	COLOR[1] = g;
	COLOR[2] = b;
}


void gradient() {
	for (int i = 0; i < WIDTH*HEIGHT;i++) {
		float r = i/float(WIDTH*HEIGHT);
		float g = (WIDTH*HEIGHT-i) / float(WIDTH*HEIGHT);
		setColor(r, 0, 0);
		PixelBuffer[i*3] = COLOR[0];
		PixelBuffer[i*3 + 1] = COLOR[1];
		PixelBuffer[i*3 + 2] = COLOR[2];
	}
}

//Taken from Computer Graphics with GL
void DDALine(int startX, int startY, int endX, int endY) {
	int dx = endX - startX;
	int dy = endY - startY;
	int steps, k;
	
	float xInc, yInc, x = startX, y = startY;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);

	xInc = float(dx) / float(steps);
	yInc = float(dy) / float(steps);

	setPixel(round(x), round(y));
	for (k = 0; k < steps; k++) {
		x += xInc;
		y += yInc;
		setPixel(round(x), round(y));
	}
}

//Taken from Computer Graphics with GL
void bresenhamLine(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0;
	int fdx = fabs(dx), fdy = fabs(dy);
	int px = 2 * fdy - fdx, py = 2 * fdx - fdy;
	int x, y, i;

	//We have eight octants.
	//This can be reduced to four cases. 0 < m < 1.0, m > 1.0, m < -1.0, 0 > m > -1.0

	if (fdy <= fdx) {
		if (xEnd < x0) {
			x = xEnd;
			y = yEnd;
			xEnd = x0;
		}
		else {
			x = x0;
			y = y0;
		}

		setPixel(x, y);

		while (x < xEnd) {
			x++;
			if (px < 0) {
				px += 2 * fdy;
			}
			else {
				if ((dx>0 && dy>0) || (dx<0 && dy<0)){
					y++;
				}
				else{
					y--;
				}
				px += 2 * (fdy - fdx);
			}
			setPixel(x, y);
		}
	}
	else {
		if (yEnd < y0) {
			x = xEnd;
			y = yEnd;
			yEnd = y0;
		}
		else {
			x = x0;
			y = y0;
		}

		setPixel(x, y);

		while (y < yEnd) {
			y++;
			if (py < 0) {
				py += 2 * fdx;
			}
			else {
				if ((dx>0 && dy>0) || (dx<0 && dy<0)) {
					x++;
				}
				else {
					x--;
				}
				py += 2 * (fdx - fdy);
			}
			setPixel(x, y);
		}
	}

}