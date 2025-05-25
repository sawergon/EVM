#ifndef DIPLOMA_INCLUDE_FUNCTIONS_STRIBOG256_HPP_
#define DIPLOMA_INCLUDE_FUNCTIONS_STRIBOG256_HPP_

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void stribog256( const uint8_t *message, size_t len, uint8_t *hash );

std::string stribog256( const std::string &message );

#endif  // DIPLOMA_INCLUDE_FUNCTIONS_STRIBOG256_HPP_
