//
// Created by Alex on 23.11.2023.
//

#include "static_analyzer.h"

int rule_1(Stack &stack) {
  stack.pop();
  stack.push(AN_AMOUNT_OPERATOR);
  stack.push(AN_OPERATOR);
  return AN_COMMAND_KEEP;
}

int rule_2(Stack &stack) {
  return rule_1(stack);
}

int rule_3(Stack& stack) {
  stack.pop();
  return AN_COMMAND_KEEP;
}

int rule_4(Stack& stack) {
  stack.pop();
  stack.push(AN_END_IF);
  stack.push(AN_AMOUNT_OPERATOR);
  stack.push(AN_RIGHT);
  stack.push(AN_LOGIC);
  stack.push(AN_LEFT);
  return AN_COMMAND_NEXT;
}

int rule_5(Stack& stack) {
  stack.pop();
  stack.push(AN_AMOUNT_OPERATOR);
  return AN_COMMAND_NEXT;
}

int rule_6(Stack& stack) {
  return rule_3(stack);
}

int rule_7(Stack& stack) {
  stack.pop();
  stack.push(AN_BREAK);
  stack.push(AN_ARITHMETIC);
  stack.push(AN_SET);
  return AN_COMMAND_NEXT;
}

int rule_8(Stack& stack) {
  stack.pop();
  stack.push(AN_BREAK);
  stack.push(AN_LOGIC);
  stack.push(AN_UNTIL);
  stack.push(AN_AMOUNT_OPERATOR);
  return AN_COMMAND_NEXT;
}

int rule_9(Stack& stack) {
  stack.pop();
  stack.push(AN_ARITHMETIC_LIST);
  stack.push(AN_ARITHMETIC_END);
  return AN_COMMAND_KEEP;
}

int rule_10(Stack& stack) {
  stack.pop();
  stack.push(AN_ARITHMETIC_LIST);
  stack.push(AN_ARITHMETIC_END);
  return AN_COMMAND_NEXT;
}

int rule_11(Stack& stack) {
  return rule_3(stack);
}

int rule_12(Stack& stack) {
  stack.pop();
  stack.push(AN_ARITHMETIC_END_LIST);
  stack.push(AN_F);
  return AN_COMMAND_KEEP;
}

int rule_13(Stack& stack) {
  stack.pop();
  stack.push(AN_ARITHMETIC_END_LIST);
  stack.push(AN_F);
  return AN_COMMAND_NEXT;
}

int rule_14(Stack& stack) {
  return rule_3(stack);
}

int rule_15(Stack& stack) {
  stack.pop();
  return AN_COMMAND_NEXT;
}

int rule_16(Stack& stack) {
  return rule_15(stack);
}

int rule_17(Stack& stack) {
  stack.pop();
  stack.push(AN_LOGIC_LIST);
  stack.push(AN_F);
  return AN_COMMAND_KEEP;
}

int rule_18(Stack& stack) {
  stack.pop();
  stack.push(AN_F);
  return AN_COMMAND_NEXT;
}

int rule_19(Stack& stack) {
  return rule_18(stack);
}

int rule_20(Stack& stack) {
  return rule_15(stack);
}

int rule_21(Stack& stack) {
  return rule_15(stack);
}
int rule_22(Stack& stack) {
  return rule_15(stack);
}
int rule_23(Stack& stack) {
  return rule_15(stack);
}
int rule_24(Stack& stack) {
  return rule_15(stack);
}
