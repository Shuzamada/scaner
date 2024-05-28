#include <iostream>
#include <boost/asio.hpp>
#include <sstream>

using namespace std;
using namespace boost::asio;

int main() {
    io_service io;

    serial_port serial(io, "/dev/ttyACM0");

    // Настройка параметров порта
    serial.set_option(serial_port_base::baud_rate(9600));
    serial.set_option(serial_port_base::character_size(8));
    serial.set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    serial.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));

    char buf[512];
    string buffer;

    while (true) {
        // Чтение данных из последовательного порта
        boost::system::error_code ec;
        size_t len = serial.read_some(boost::asio::buffer(buf), ec);

        if (ec) {
            cerr << "Ошибка чтения: " << ec.message() << endl;
            break;
        }

        // Добавление прочитанных данных в буфер строки
        buffer.append(buf, len);

        // Обработка строк в буфере
        size_t pos;
        while ((pos = buffer.find('\n')) != string::npos) {
            string line = buffer.substr(0, pos);
            buffer.erase(0, pos + 1);

            cout << "Получено: " << line << endl;

            // Использование stringstream для разбора данных
            stringstream ss(line);
            int value1, value2, value3;
            if (ss >> value1 >> value2 >> value3) {
                // Вывод данных на экран
                cout << "Число 1: " << value1 << ", Число 2: " << value2 << ", Число 3: " << value3 << endl;
            } else {
                cerr << "Ошибка разбора строки: " << line << endl;
            }
        }
    }

    return 0;
}
