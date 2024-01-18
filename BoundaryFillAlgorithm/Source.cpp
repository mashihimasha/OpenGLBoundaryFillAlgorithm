#include <glut.h>

int ww = 600, wh = 400;

typedef struct Color {
    float red;
    float green;
    float blue;
} Color;

void myInit() {
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}

void fillPoly(int x, int y, Color fillColor, Color borderColor) {
    //changed the data type to float from GLubyte 
    //because when comparing fillColor and borderColor with pixelColor 
    //all three must have the same data type
    float pixelColor[3]{};

    //changed to GL_RGB because GL_RGBA is not necessary to compare the current color
    //with fillColor and borderColor
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &pixelColor);
    
    if ((fillColor.red != pixelColor[0] || fillColor.green != pixelColor[1] || fillColor.blue != pixelColor[2]) &&
        (borderColor.red != pixelColor[0] || borderColor.green != pixelColor[1] || borderColor.blue != pixelColor[2])) {
        //put glVertex2i(x, y) within glBegin and glEnd 
        //to mark the start and end of drawing command
        //used GL_POINTS to denote that the vertices are points
        glColor3f(fillColor.red, fillColor.green, fillColor.blue);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        //must use glFlush to render each point while the program is running
        glFlush();
        fillPoly(x + 1, y, fillColor, borderColor);
        fillPoly(x, y + 1, fillColor, borderColor);
        fillPoly(x, y - 1, fillColor, borderColor);
        fillPoly(x - 1, y, fillColor, borderColor);
    }
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    Color borderColor = { 0.0, 0.0, 0.0 };    // Border color (black)
    Color fillColor = { 0.0, 0.0, 1.0 };      // Fill color (blue)

    // Draw a polygon to fill
    glColor3f(borderColor.red, borderColor.green, borderColor.blue);
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(300, 200);
    glVertex2i(360, 200);
    glVertex2i(360, 260);
    glVertex2i(320, 250);
    glVertex2i(300, 260);
    glEnd();

    fillPoly(301, 201, fillColor, borderColor);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Boundary Fill Algorithm");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
