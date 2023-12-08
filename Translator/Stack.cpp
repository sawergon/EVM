//
// Created by Alex on 16.11.2023.
//

#include "Stack.h"

#define SIZE sizeof(int)

Stack::Stack(int new_data) {
  for (int & i : data) {
    i = -3;
  }
  data[len++] = new_data;
}

void Stack::push(int new_data) {
  data[len++] = new_data;
}

int Stack::pop() {
  int r_data = data[--len];
  data[len] = -3;
  return r_data;
}

int Stack::get_len() const {
  return len;
}

int Stack::peek() {
  return data[len - 1];
}
int Stack::operator[](int i) {
  return data[i];
}
void Stack::set_to(int new_data, int pos) {
  data[pos] = new_data;
}
