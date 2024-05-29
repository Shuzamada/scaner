#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <boost/asio.hpp>
#include <sstream>
#include <thread>


double RANGE = 90;

using namespace boost::asio;

io_service io;

serial_port serial(io, "/dev/ttyACM0");

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
void pushScanerData(double h, double r, double degree)
{
    r =  (RANGE - r)/ 25;
    double z = h;
    double x = r * std::cos(degree * 3.14 / 180);
    double y = r * std::sin(degree * 3.14 / 180);
    points.push_back(x);
    points.push_back(z);
    points.push_back(y);
}
void readSerialData()
{
    std::string buffer;
    char buf[512];
    while (true)
    {
        boost::system::error_code ec;
        size_t len = serial.read_some(boost::asio::buffer(buf), ec);

        if (ec)
        {
            std::cerr << "Ошибка чтения: " << ec.message() << "\n";
            break;
        }

        buffer.append(buf, len);

        size_t pos;
        while ((pos = buffer.find('\n')) != std::string::npos)
        {
            std::string line = buffer.substr(0, pos);
            buffer.erase(0, pos + 1);

            std::cout << "Получено: " << line << "\n";

            std::stringstream ss(line);
            double h, r, dergee;
            if (ss >> h >> r >> dergee)
            {
                pushScanerData(h, r, dergee);
                glutPostRedisplay();
            }
            else
            {
                std::cerr << "Ошибка разбора строки: " << line << "\n";
            }
        }
    }
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
        distanceZ += 0.5f;
        break;
    case 'e':
        distanceZ -= 0.5f;
        break;
    case 'f':
        distanceZ -= 0.0f;
        break;
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}


int main(int argc, char **argv)
{


    // Настройка параметров порта
    serial.set_option(serial_port_base::baud_rate(9600));
    serial.set_option(serial_port_base::character_size(8));
    serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));



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

    // for (double i = -2; i < 2; i+=0.05)
    // {
    //     for (double j = -2; j < 2; j+=0.05)
    //     {
    //         for (double l = 0; l < 2; l+=0.05)
    //         {
    //             //if (std::sqrt((i * i + j * j)) + 0.01 > l && std::sqrt((i * i + j * j)) - 0.01 < l)
    //             double r = 2; 
    //             if (i < r && j < r && l < r && i > -r && j > -r && l > -r)
    //             {
    //                 //std::cout << i << " " << j << "\n";
    //                 points.push_back(i);
    //                 points.push_back(-l + 2);
    //                 points.push_back(j);
    //             }
    //         }
    //     }
    // }
    // for (double i = 0; i < 90; i += 0.9)
    // {
    //     pushScanerData(0.1, 300, i);
    // }
    std::cout << points.size()/3 << "\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Cube");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
        std::thread serialThread(readSerialData);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    serialThread.join();
    return 0;
}
