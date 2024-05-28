#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>

// Координаты вершин куба
std::vector<GLfloat> points = {
    // -1.0, -1.0, -1.0,
    // 1.0, -1.0, -1.0,
    // 1.0, 1.0, -1.0,
    // -1.0, 1.0, -1.0,
    // -1.0, -1.0, 1.0,
    // 1.0, -1.0, 1.0,
    // 1.0, 1.0, 1.0,
    // -1.0, 1.0, 1.0

    // 0.0, 0.0, 2.0,
    // -2.0, -2.0, -2.0,
    // 2.0, 2.0, 2.0,

};
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat distanceZ = 5.0f;

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -distanceZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    glPointSize(5.0); // Устанавливаем размер точек
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, points.data());
    glDrawArrays(GL_POINTS, 0, points.size()/3); // Отображаем все точки объекта
    glDisableClientState(GL_VERTEX_ARRAY);

    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    double x_p = 0.0;
    double y_p = 0.0;
    double z_p = 0.0;
    switch (key) {
    case 'w':
        angleX += 2.0f;
        break;
    case 's':
        angleX -= 2.0f;
        break;
    case 'a':
        angleY -= 2.0f;
        break;
    case 'd':
        angleY += 2.0f;
        break;
    case 'q':
        distanceZ += 0.1f;
        break;
    case 'e':
        distanceZ -= 0.1f;
        break;
    case 'f':

        std::cin >> x_p >> y_p >> z_p;
        points.push_back(x_p);
        points.push_back(y_p);
        points.push_back(z_p);
        break;
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    points.push_back(0);
    points.push_back(0);
    points.push_back(0);
    points.push_back(1);
    points.push_back(0);
    points.push_back(1);
    points.push_back(-1);
    points.push_back(0);
    points.push_back(-1);
    points.push_back(1);
    points.push_back(0);
    points.push_back(-1);
    points.push_back(-1);
    points.push_back(0);
    points.push_back(1);

    for (double i = -2; i < 2; i+=0.05)
    {
        for (double j = -2; j < 2; j+=0.05)
        {
            for (double l = 0; l < 2; l+=0.05)
            {
                //if (std::sqrt((i * i + j * j)) + 0.01 > l && std::sqrt((i * i + j * j)) - 0.01 < l)
                double r = 2; 
                if (i < r && j < r && l < r && i > -r && j > -r && l > -r)
                {
                    //std::cout << i << " " << j << "\n";
                    points.push_back(i);
                    points.push_back(-l + 2);
                    points.push_back(j);
                }
            }
        }
    }
    std::cout << points.size()/3 << "\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Cube");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
