//
// Created by Alex on 16.11.2023.
//

#include "Stack.h"

Stack::Stack(int new_data) {
  start = new Node;
  start->data = new_data;
  start->next = nullptr;
  len++;
}

void Stack::push(int new_data) {
  Node *p_node = new Node;
  p_node->data = new_data;
  p_node->next = start;
  start = p_node;
  len++;
}

int Stack::pop() {
  int r_data = start->data;
  Node *next = start->next;
  delete start;
  start = next;
  len--;
  return r_data;
}

int Stack::get_len() const {
  return len;
}

Stack::~Stack() {
  for (Node *p_st = start; p_st ;) {
    p_st = p_st->next;
    delete start;
    start = p_st;
  }
}
int Stack::peek() {
  return start->data;
}
