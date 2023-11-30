//
// Created by Alex on 16.11.2023.
//

#ifndef STATICANALYZER_STACK_H_
#define STATICANALYZER_STACK_H_

struct Node {
  Node *next;
  int data;
};

class Stack {
 private:
  Node *start = nullptr;
  int len = 0;
 public:
  explicit Stack(int new_data);

  void push(int new_data);

  int pop();

  int get_len() const;

  int peek();

  ~Stack();
};

#endif //STATICANALYZER_STACK_H_
