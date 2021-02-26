#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}


/// <summary>
/// f(x) = d(x)/x, 0 < x <= 100, d(x) = fabs(round(x) - x)
/// f(x) = 1, x = 0
/// </summary>
void Display3() {
	double pi = 4 * atan(1.0);
	double xmax = 30.0;
	double ymax = 1.01;
	double ratia = 0.1;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, 1 / ymax);
	for (double x = 0 + ratia; x <= xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(round(x) - x) / x) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}


// graficul functiei 
void Display4() {
	double pi = 4 * atan(1);
	double a = 0.3;
	double b = 0.2;
	double xmax = 2 * (a * 1 + b) * 1;
	double ymax = 2 * (a * 1 + b) * 1;
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi; t < pi; t += ratia) {
		double x, y;
		x = 2 * (a * cos(t) + b) * cos(t) / xmax / 1.2;
		y = 2 * (a * cos(t) + b) * sin(t) / ymax / 1.2;

		glVertex2f(x, y);
	}
	glEnd();
}


void Display5()
{
	double pi = 4 * atan(1);
	double a = 0.2;
	double xmax = 1.2;
	double ymax = 1;
	double ratia = 0.05;
	double xcorner = -1 / 1.2;
	double ycorner = 0.95;
	
	bool flag = false;
	double epsilon = 0.01;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_TRIANGLES);
	double x, y;
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t == pi / 6 || t == -pi / 6) {
			continue;
		}
		x = a / (4 * cos(t) * cos(t) - 3);
		y = a * tan(t) / (4 * cos(t) * cos(t) - 3);
		if (x > 0 || y < 0) {
			continue;
		}
		if (y > 0.95) {
			y = 0.95;
		}
		if (flag && rand() % 100 > 10) {
			flag = false;
			
		}
		if (rand() % 100 > 40) {
			double previous_t = t - epsilon;
			if (previous_t == pi / 6 || previous_t == -pi / 6) {
				continue;
			}
			glVertex2f(x / xmax / 1.2, y / ymax);
			glVertex2f(xcorner, ycorner);
			double previous_x = a / (4 * cos(previous_t) * cos(previous_t) - 3);
			double previous_y = a * tan(previous_t) / (4 * cos(previous_t) * cos(previous_t) - 3);
			if (previous_x > 0 || previous_y < 0) {
				continue;
			}
			if (previous_y > 0.95) {
				previous_y = 0.95;
			}
			glVertex2f(previous_x / xmax / 1.2, previous_y / ymax);
		}
	}
	glEnd();
	glColor3f(0, 0, 0); // alb
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		if (t == pi / 6 || t == -pi / 6) {
			continue;
		}

		x = a / (4 * cos(t) * cos(t) - 3);
		y = a * tan(t) / (4 * cos(t) * cos(t) - 3);
		if (x > 0 || y < 0) {
			continue;
		}
		if (y > 0.95) {
			y = 0.95;
		}

		glVertex2f(x / xmax / 1.2, y / ymax);
	}
	glVertex2f(xcorner, ycorner);
	double t = -pi / 2 + ratia;
	x = a / (4 * cos(t) * cos(t) - 3);
	y = a * tan(t) / (4 * cos(t) * cos(t) - 3);
	if (y > 0.95) {
		y = 0.95;
	}
	glVertex2f(x / xmax / 1.2, y / ymax);

	printf("wow%f, %f\n", xmax, ymax);
	glEnd();
}


/// <summary>
/// cicloida
/// x = a * t - b * sin t, y = a - b * cos t, t \in R
/// </summary>
void Display6() {
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double a = 0.1;
	double b = 0.2;
	double xmax = 10;
	double ymax = a - b * (-1);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double t = -xmax; t <= xmax; t += ratia) {
		double x1, y1;
		x1 = (a * t - b * sin(t)) / xmax / 0.1;
		y1 = (a - b * cos(t)) / ymax / 2.5;

		glVertex2f(x1, y1);
	}
	glEnd();

}


/// <summary>
/// epicicloida
/// x = (R + r) * cos (r / R * t) - r * cos ( t + r/ R * t)
/// y = (R + r) * sin (r / R * t) - r * sin(t + r / R * t)
/// t \in [0, 2*pi]
/// </summary>
void Display7() {
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double R = 0.1;
	double r = 0.3;
	double xmax = (R + r) * 1 - r * (-1);
	double ymax = (R + r) * 1 - r * (-1);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x1, y1;
		x1 = ((R + r) * cos(r / R * t) - r * cos(t + r / R * t)) / xmax / 1.5;
		y1 = ((R + r) * sin(r / R * t) - r * sin(t + r / R * t)) / ymax / 1.5;

		glVertex2f(x1, y1);
	}
	glEnd();

}


/// <summary>
/// hipocicloida
/// x = (R - r) * cos (r / R * t) - r * cos(t - r / R * t)
/// y = (R - r) * sin (r / R * t) - r * sin(t - r / R * t)
///  t \in [0, 2*pi]
/// </summary>
void Display8() {
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double R = 0.1;
	double r = 0.3;
	double xmax = (R - r) * 1 - r * (-1);
	double ymax = (R - r) * 1 - r * (-1);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);

	for (double t = 0; t <= 2 * pi; t += ratia) {
		double x1, y1;
		x1 = ((R - r) * cos(r / R * t) - r * cos(t - r / R * t)) / xmax / 10;
		y1 = ((R - r) * sin(r / R * t) - r * sin(t - r / R * t)) / ymax / 10;

		glVertex2f(x1, y1);
	}
	glEnd();
}


/// <summary>
/// lemniscata lui bernoulli
/// r = +- a * sqrt(2 * cos(2*t))
/// x = r * cos(t)
/// y = r * sin(t)
/// t \in (-pi/4, pi/4)
/// </summary>
void Display9() {
	double pi = 4 * atan(1.0);
	double ratia = 0.001;
	double a = 0.4;
	double xmax = (a * sqrt(2 * 1)) * 1;
	double ymax = (a * sqrt(2 * 1)) * 1;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	double x1, y1;
	double x2, y2;

	for (double t = pi / 4 - ratia; t > -pi / 4; t -= ratia) {
		double r1 = a * sqrt(2 * cos(2 * t));
		x1 = r1 * cos(t) / xmax / 1.5;
		y1 = r1 * sin(t) / ymax / 1.5;

		glVertex2f(x1, y1);
	}

	for (double t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		double r2 = -a * sqrt(2 * cos(2 * t));
		x2 = r2 * cos(t) / xmax / 1.5;
		y2 = r2 * sin(t) / ymax / 1.5;

		glVertex2f(x2, y2);
	}
	glEnd();

}


/// <summary>
/// r = a * exp(t + 1);
/// x = r * cos(t)
/// y = r * sin(t)
/// t \in (0, inf)
/// </summary>
void Display10() {
	double pi = 4 * atan(1);
	double a = 0.02;
	double xmax = 100;
	double ymax = 100;
	double ratia = 0.1;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = 0 + 10 * ratia; t < 100; t += ratia) {
		double x, y, r;
		r = a * exp(t + 1);
		x = r * cos(t) / xmax;
		y = r * sin(t) / ymax;

		glVertex2f(-y, x);
	}
	glEnd();
}


void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display10();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
