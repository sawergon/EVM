#include "include/Kuznechik/Kuznechik.hpp"
#include <iomanip>

int main() {
  std::vector<uint8_t> key = { 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
                      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                      0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
                      0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
  kuznechik::KuznechikCipher c(key);
  int k = 1;
  for (auto& i : c.round_keys) {
    std::cout << k++ << ' ';
    for (auto& j : i) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)j;
    }
    std::cout << std::endl;
  }

//  std::vector<uint8_t > opemMsg = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x00,
//                                   0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88};
//  std::string msg{opemMsg.begin(), opemMsg.end()};
  std::string msg = "Hello world!, Hello world!, Hello world!, Hello world!";
  std::cout << msg << std::endl;
  auto encMsg = c.encrypt(msg);
  std::cout << "Encrypted message: ";
  for (auto& j : encMsg) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)j;
  }
  std::cout << std::endl;
  std::string decMsg = c.decrypt(encMsg);
  std::cout << decMsg << std::endl;
  return 0;
}