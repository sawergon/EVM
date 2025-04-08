#ifndef DIPLOMA_INCLUDE_FUNCTIONS_STRIBOG256_HPP_
#define DIPLOMA_INCLUDE_FUNCTIONS_STRIBOG256_HPP_

#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <cstdint>
#include <string>

void stribog256(const uint8_t* message, size_t len, uint8_t* hash);

std::string stribog256(const std::string& message);

#endif  // DIPLOMA_INCLUDE_FUNCTIONS_STRIBOG256_HPP_
