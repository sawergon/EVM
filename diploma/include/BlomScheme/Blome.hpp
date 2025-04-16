//
// Created by Alex on 16.04.2025.
//

#ifndef DIPLOMA_INCLUDE_BLOMSCHEME_BLOME_HPP_
#define DIPLOMA_INCLUDE_BLOMSCHEME_BLOME_HPP_

#pragma once
#include "IBlomeScheme.hpp"
#include <vector>
#include <random>
#include <stdexcept>

namespace Infrastructure::Crypto {

  class BlomSchemeImpl final : public IBlomScheme {
public:
    struct Config {
      size_t matrixSize;
      uint64_t primeModulus;
    };

    explicit BlomSchemeImpl(Config config)
        : m_config(config),
        m_secretMatrix(config.matrixSize,
                        std::vector<uint64_t>(config.matrixSize)),
        m_rng(std::random_device{}()) {
      generateSecretMatrix();
    }

    std::pair<PublicKey, PrivateKey> generateKeyPair() override {
      std::uniform_int_distribution<uint64_t> dist(0, m_config.primeModulus-1);

      PrivateKey privateKey(m_config.matrixSize);
      for(auto& val : privateKey) {
        val = dist(m_rng);
      }

      PublicKey publicKey = computePublicKey(privateKey);
      return {publicKey, privateKey};
    }

    std::vector<uint8_t> encrypt(const uint8_t* data, size_t size,
                                  const uint8_t* key, size_t keySize) override {
      // Реализация AES-GCM с использованием ключа
      // Упрощенная реализация для примера
      std::vector<uint8_t> encrypted(size);
      for(size_t i = 0; i < size; ++i) {
        encrypted[i] = data[i] ^ key[i % keySize];
      }
      return encrypted;
    }

    std::vector<uint8_t> decrypt(const uint8_t* data, size_t size,
                                  const uint8_t* key, size_t keySize) override {
      return encrypt(data, size, key, keySize); // XOR обратим
    }

    uint64_t calculateSharedKey(int id1, int id2) const {
      validateId(id1);
      validateId(id2);

      const auto& row = m_secretMatrix[id1];
      const auto& col = m_secretMatrix[id2];

      uint64_t result = 0;
      for(size_t i = 0; i < m_config.matrixSize; ++i) {
        result = (result + row[i] * col[i]) % m_config.primeModulus;
      }
      return result;
    }

private:
    Config m_config;
    std::vector<std::vector<uint64_t>> m_secretMatrix;
    std::mt19937_64 m_rng;

    void generateSecretMatrix() {
      std::uniform_int_distribution<uint64_t> dist(0, m_config.primeModulus-1);

      // Генерация симметричной матрицы
      for(size_t i = 0; i < m_config.matrixSize; ++i) {
        for(size_t j = i; j < m_config.matrixSize; ++j) {
          m_secretMatrix[i][j] = dist(m_rng);
          if(i != j) {
            m_secretMatrix[j][i] = m_secretMatrix[i][j];
          }
        }
      }
    }

    PublicKey computePublicKey(const PrivateKey& privateKey) const {
      PublicKey publicKey(m_config.matrixSize);
      for(size_t i = 0; i < m_config.matrixSize; ++i) {
        publicKey[i] = 0;
        for(size_t j = 0; j < m_config.matrixSize; ++j) {
          publicKey[i] = (publicKey[i] +
                           m_secretMatrix[i][j] * privateKey[j]) % m_config.primeModulus;
        }
      }
      return publicKey;
    }

    void validateId(int id) const {
      if(id < 0 || static_cast<size_t>(id) >= m_config.matrixSize) {
        throw std::out_of_range("Invalid node ID");
      }
    }
  };

} // namespace Infrastructure::Crypto

#endif  // DIPLOMA_INCLUDE_BLOMSCHEME_BLOME_HPP_
