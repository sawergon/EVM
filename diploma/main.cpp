#include "stribog256.hpp"

int main() {
  // Тест 1: Сравнение двух одинаковых хэшей
  const char* message1 = "Hello, Stribog!";
  uint8_t hash1[32], hash2[32];

  stribog256(reinterpret_cast<const uint8_t*>(message1), strlen(message1), hash1);
  stribog256(reinterpret_cast<const uint8_t*>(message1), strlen(message1), hash2);

  std::cout << "Test 1: Same input -> Hashes should match\n";
  std::cout << "Hash1: ";
  for (int i = 0; i < 32; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash1[i];
  }
  std::cout << "\nHash2: ";
  for (int i = 0; i < 32; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash2[i];
  }

  if (memcmp(hash1, hash2, 32) == 0) {
    std::cout << "\nResult: HASHES MATCH ✅\n\n";
  } else {
    std::cout << "\nResult: HASHES DIFFER ❌\n\n";
  }

  // Тест 2: Сравнение двух разных хэшей
  const char* message2 = "Hello, World!";
  stribog256(reinterpret_cast<const uint8_t*>(message2), strlen(message2), hash2);

  std::cout << "Test 2: Different inputs -> Hashes should differ\n";
  std::cout << "Hash1 (from \"" << message1 << "\"): ";
  for (int i = 0; i < 32; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash1[i];
  }
  std::cout << "\nHash2 (from \"" << message2 << "\"): ";
  for (int i = 0; i < 32; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash2[i];
  }

  if (memcmp(hash1, hash2, 32) == 0) {
    std::cout << "\nResult: HASHES MATCH (UNEXPECTED!) ❌\n";
  } else {
    std::cout << "\nResult: HASHES DIFFER (CORRECT) ✅\n";
  }

  std::string messag = "Hello";
  std::cout << stribog256(messag) << std::endl;
  return 0;
}