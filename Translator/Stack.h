//
// Created by Alex on 16.11.2023.
//

#ifndef STATICANALYZER_STACK_H_
#define STATICANALYZER_STACK_H_

#include <cstdlib>

#define STACK_SIZE 3000

class Stack {
 private:
  int data[STACK_SIZE];
  int len = 0;
 public:
  explicit Stack(int new_data);

  void push(int new_data);

  int pop();

  int get_len() const;

  int peek();

  int operator[](int i);

  void set_to(int new_data, int pos);
};

#endif //STATICANALYZER_STACK_H_
