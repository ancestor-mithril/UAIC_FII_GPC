#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <utility>
#include <vector>
#include <stdexcept>
#include <GL/glut.h>
#include <cfloat>

// dimensiunea ferestrei in pixeli
#define dim 600

// numarul maxim de iteratii pentru testarea apartenentei la mult.Julia-Fatou
#define NRITER_JF 5000
// modulul maxim pentru testarea apartenentei la mult.Julia-Fatou
#define MODMAX_JF 10000000
// ratii ptr. CJuliaFatou
#define RX_JF 0.01
#define RY_JF 0.01

unsigned char prevKey;
int nivel = 0;



void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    glPointSize(3);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
}



class GrilaCarteziana
{
    double epsilon;
    double cx;
    double cy;

    double dc;
    double dl;

    double p_rad;
public:
    int n;
    int m;

    GrilaCarteziana(int lines, int columns)
        :n(lines), m(columns)
    {
        epsilon = 0.001;
        dc = (2 - 2 * epsilon) / (double)m;
        dl = (2 - 2 * epsilon) / (double)n;
        cx = -1 + epsilon + 3 * dc;
        cy = -1 + epsilon + 3 * dl;
        p_rad = (dc < dl ? dc : dl) / 3;
    }

    void draw_grid()
    {
        glColor3f(1, 0, 1);
        for (float ln = -1 + epsilon; ln < 1; ln += dl) {
            glBegin(GL_LINES);
            glVertex2d(ln, -1);
            glVertex2d(ln, 1);
            glEnd();
        }
        for (float cm = -1 + epsilon; cm < 1; cm += dc) {
            glBegin(GL_LINES);
            glVertex2d(-1, cm);
            glVertex2d(1, cm);
            glEnd();
        }
    }

    void writePixel(int x, int y)
    {
        draw_circle(x * dl, y * dc, p_rad);
    }

    void draw_circle(float x, float y, float radius) {
        if (n % 2 == 1) x -= dl / 2;
        if (m % 2 == 1) y -= dc / 2;

        glColor3f(0.4, 0.2, 0.3);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(x, y, 0.0f);
        static const int circle_points = 100;
        static const float angle = 2.0f * 3.1416f / circle_points;

        // this code (mostly) copied from question:
        glBegin(GL_POLYGON);
        double angle1 = 0.0;
        glVertex2d(radius * cos(0.0), radius * sin(0.0));
        int i;
        for (i = 0; i < circle_points; i++)
        {
            glVertex2d(radius * cos(angle1), radius * sin(angle1));
            angle1 -= angle;
        }
        glEnd();
        glPopMatrix();
    }

    std::vector<std::pair<int, int>> AfisareSegmentDreapta3(float x0, float y0, float xn, float yn)
    {
        float dx = fabs(xn - x0);
        float dy = fabs(yn - y0);

        int x = x0, y = y0;

        std::vector<std::pair<int, int>> vertexes;
        vertexes.push_back({ (x0 - x > 0.5 ? x + 1 : x), (y0 - y > 0.5 ? y + 1 : y) });
        int delta_x = (x < xn ? 1 : -1);
        int delta_y = (y < yn ? 1 : -1);
        if (x < xn && y < yn) {
            int d = 2.0f * dy - dx;
            int dE = 2.0f * dy;
            int dNE = 2.0f * (dy - dx);
            while (x < xn)
            {
                if (d <= 0)
                {
                    d += dE;
                    x++;
                }
                else
                {
                    d += dNE;
                    y++;
                    x++;
                }
                vertexes.push_back({ x, y });
            }
        }
        else if (x < xn && y > yn) {
            int d = 2.0f * dy - dx;
            int dE = 2.0f * (dy);
            int dNE = 2.0f * (dy - dx);
            while (x < xn)
            {
                if (d <= 0)
                {
                    d += dE;
                    x++;
                }
                else
                {
                    d += dNE;
                    y--;
                    x++;
                }
                vertexes.push_back({ x, y + 1 });
            }
        }
        
        return vertexes;
    }

    void writeLine(float x0, float y0, float xn, float yn, int width = 1)
    {
        for (auto& p : AfisareSegmentDreapta3(x0, y0, xn, yn))
        {
            for (auto w = -width / 2; w <= width / 2; w++) {
                writePixel(p.first, p.second + w);
            }
        }
        glBegin(GL_LINES);
        glVertex2d(x0 * dl, y0 * dc);
        glVertex2d(xn * dl, yn * dc);
        glEnd();
    }
};

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    auto g = GrilaCarteziana(20, 25);
    g.draw_grid();
    //g.writePixel(0, 0);
    //g.writePixel(1, 0);
    //g.writePixel(0, 1);
    //g.writePixel(-1, 0);
    //g.writePixel(0, -1);
    ///g.writePixel(-5, -5);
    g.writeLine(-9, -8, 8, 0);
    g.writeLine(-7.6, 7.6, 8, 2.4, 3);

    glFlush();
}


int main(int argc, char** argv)
{
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


