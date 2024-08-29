#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <boost/asio.hpp>
#include <sstream>
#include <thread>
#include <ctime>
#include <iomanip>

const double RANGE = 68;
const double SCALE_K = 20;
const double SENSOR_RANGE = 10;

using namespace boost::asio;
io_service io;

serial_port serial(io, "/dev/ttyACM0");

std::vector<GLfloat> points = {};
GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat distanceZ = 5.0f;

std::string getCurrentDateTime()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(now, "%Y%m%d%H%M%S");

    return oss.str() + ".txt";
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Черный цвет фона

    glEnable(GL_DEPTH_TEST); // Включаем буфер глубины
    glEnable(GL_LIGHTING);   // Включаем освещение
    glEnable(GL_LIGHT0);     // Включаем источник света

    GLfloat lightPos[] = {0.0f, 0.0f, 1.0f, 0.0f}; // Положение света
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -distanceZ);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    for (size_t i = 0; i < points.size(); i += 3) {
        glPushMatrix();
        glTranslatef(points[i], points[i+1], points[i+2]);
        glutSolidSphere(0.05f, 20, 20); // Рисуем сферу с радиусом 0.5
        glPopMatrix();
    }

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

void pushScanerData(double h, double r1, double r2, double r3, double degree, std::ofstream &out)
{
    r1 =  (RANGE - r1)/ 20;
    double z1 = h / 20;
    double x1 = r1 * std::cos(degree * 3.14 / 180) - SENSOR_RANGE;
    double y1 = r1 * std::sin(degree * 3.14 / 180);
    points.push_back(x1);
    points.push_back(z1);
    points.push_back(y1);
    
    out << x1 << " " << z1 << " " << y1 << "\n";

    r2 =  (RANGE - r2)/ 20;
    double z2 = h / 20;
    double x2 = r2 * std::cos(degree * 3.14 / 180);
    double y2 = r2 * std::sin(degree * 3.14 / 180);
    points.push_back(x2);
    points.push_back(z2);
    points.push_back(y2);
    
    // Запись в файл
    out << x2 << " " << z2 << " " << y2 << "\n";
    
    r3 =  (RANGE - r3)/ 20;
    double z3 = h / 20;
    double x3 = r3 * std::cos(degree * 3.14 / 180) + SENSOR_RANGE;
    double y3 = r3 * std::sin(degree * 3.14 / 180);
    points.push_back(x3);
    points.push_back(z3);
    points.push_back(y3);

    out << x3 << " " << z3 << " " << y3 << "\n";
}

void readSerialData(std::ofstream &out)
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
            double h, r1, r2, r3, degree;
            if (ss >> h >> r1 >> r2 >> r3 >> degree)
            {
                pushScanerData(h, r1, r2, r3, degree, out);
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
    std::string filename = getCurrentDateTime();
    std::ofstream out(filename);  // Открываем файл для записи

    if (!out.is_open())
    {
        std::cerr << "Не удалось открыть файл для записи!\n";
        return 1;
    }

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

    std::cout << points.size()/3 << "\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("3D Cube");

    init();

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    std::thread serialThread(readSerialData, std::ref(out));
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    serialThread.join();

    out.close();  // Закрываем файл
    return 0;
}
