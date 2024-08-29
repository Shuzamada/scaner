#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <unordered_map>

struct Point {
    double x, y, z;
    int r, g, b; // Цвет
};

bool areCollinear(Point a, Point b, Point c) {
    // Векторное произведение векторов (b-a) и (c-a)
    double vx1 = b.x - a.x;
    double vy1 = b.y - a.y;
    double vz1 = b.z - a.z;

    double vx2 = c.x - a.x;
    double vy2 = c.y - a.y;
    double vz2 = c.z - a.z;

    // Вычисляем определитель для проверки компланарности
    double determinant = vx1 * vy2 - vy1 * vx2;
    if (std::fabs(determinant) > 3) return false;

    determinant = vx1 * vz2 - vz1 * vx2;
    if (std::fabs(determinant) > 3) return false;

    determinant = vy1 * vz2 - vz1 * vy2;
    return std::fabs(determinant) < 3;
}

int main() {
    std::ifstream infile("test.txt");
    std::ofstream outfile("output.txt");

    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    std::vector<Point> points;
    std::unordered_map<int, std::vector<int>> planes;
    int planeCount = 0;

    double x, y, z;
    while (infile >> x >> y >> z) {
        points.push_back({x, y, z, -1, -1, -1});
    }

    // Определение плоскостей и назначение цветов
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].r == -1)
        { 
            // Назначаем уникальный цвет
            int r = rand() % 256;
            int g = rand() % 256;
            int b = rand() % 256;
            points[i].r = r;
            points[i].g = g;
            points[i].b = b;

            for (size_t j = i + 1; j < points.size(); ++j) {
                for (size_t k = j + 1; k < points.size(); ++k) {
                    if (areCollinear(points[i], points[j], points[k])) {
                        points[j].r = r;
                        points[j].g = g;
                        points[j].b = b;
                        points[k].r = r;
                        points[k].g = g;
                        points[k].b = b;
                    }
                }
            }
        }
    }

    // Запись результата в файл
    for (const auto& p : points) {
        outfile << p.x << " " << p.y << " " << p.z << " "
                << p.r << " " << p.g << " " << p.b << std::endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
