#include "parser.hpp"

recvEnc parseMsgEnc(const std::string &msg) {
  recvEnc res{};

  // Создаем поток для разбора строки
  std::istringstream iss(msg);

  // Извлекаем число до запятой
  char delimiter; // Для хранения символа-разделителя
  if (iss >> res.from >> delimiter) {
    // Проверяем, что следующий символ - это запятая
    if (delimiter != ',')
      return {0, 0, {}, false};
    if (iss >> res.to >> delimiter) {
      // Проверяем, что следующий символ - это запятая
      if (delimiter != ',')
        return {0, 0, {}, false};

      // Извлекаем оставшуюся часть строки
      std::string temp;
      std::getline(iss, temp); // Читаем до конца строки

      // Удаляем фигурные скобки
      if (!temp.empty() && temp.front() == '{') {
        temp.erase(0, 1); // Удаляем открывающую фигурную скобку
      }
      if (!temp.empty() && temp.back() == '}') {
        temp.erase(temp.size() -
          1); // Удаляем закрывающую фигурную скобку
      }
      res.msg = temp; // Присваиваем результат переменной msg
    }
  }
  res.success = true;
  return res;
}
