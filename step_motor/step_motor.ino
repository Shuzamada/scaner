void setup() {
  // Инициализация серийного порта с частотой передачи данных 9600 бит/сек
  Serial.begin(9600);
}

void loop() {
  static unsigned long lastIterationTime = 0; // Переменная для хранения времени последней итерации
  unsigned long currentTime = millis(); // Получение текущего времени в миллисекундах

  // Вычисляем количество прошедших секунд с момента запуска программы
  unsigned long elapsedTime = currentTime - lastIterationTime;
  lastIterationTime = currentTime; // Обновляем время последней итерации

  // Выводим количество прошедших секунд в серийный порт
  Serial.println(elapsedTime / 1000); // Делим на 1000, чтобы получить количество секунд

  delay(1000); // Задержка в 1 секунду между выводами
}
