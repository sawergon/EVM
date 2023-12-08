//
// Created by Alex on 23.11.2023.
//

#include "static_analyzer.h"
#include "iostream"

namespace global {
node* var_table = nullptr;
int data_field[SIZE_FIELD];
}

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
  int logic_data = stack.get_len() + 5;
  int label = stack.get_len();
  stack.push(-1);
  stack.push(AN_END_IF);
  stack.push(AN_AMOUNT_OPERATOR);
  stack.push(AN_RIGHT);
  stack.push(label);
  stack.push(-1);
  stack.push(AN_C_COND_GO_TO_0);
  stack.push(logic_data);
  stack.push(AN_LOGIC);
  stack.push(AN_LEFT);
  return AN_COMMAND_NEXT;
}

int rule_5(Stack& stack) {
  stack.pop();
  int label_cond = stack.pop();
  int label_non_cond = stack.get_len();
  stack.push(-1);
  stack.push(AN_C_LABEL);
  stack.push(AN_AMOUNT_OPERATOR);
  stack.push(label_cond);
  stack.push(AN_C_LABEL);
  stack.push(label_non_cond);
  stack.push(AN_C_NON_COND_GO_TO);
  return AN_COMMAND_NEXT;
}

int rule_6(Stack& stack) {
  stack.pop();
  stack.push(AN_C_LABEL);
  return AN_COMMAND_KEEP;
}

int rule_7(Stack &stack, int var) {
  stack.pop();
  int arith = stack.get_len() + 1;
  stack.push(AN_BREAK);
  stack.push(-1);
  stack.push(var);
  stack.push(AN_C_SET);
  stack.push(arith);
  stack.push(AN_ARITHMETIC);
  stack.push(AN_SET);
  return AN_COMMAND_NEXT;
}

int rule_8(Stack& stack) {
  stack.pop();
  int comp_label = new_label();
  int logic_val = stack.get_len() + 2;
  stack.push(AN_BREAK);
  stack.push(comp_label);
  stack.push(-1);
  stack.push(AN_C_COMP_GO_TO);
  stack.push(logic_val);
  stack.push(AN_LOGIC);
  stack.push(AN_UNTIL);
  stack.push(AN_AMOUNT_OPERATOR);
  stack.push(comp_label);
  stack.push(AN_C_LABEL);
  return AN_COMMAND_NEXT;
}

int rule_9(Stack &stack, lexeme &lx) {
  stack.pop();
  int arith_val = stack.pop();
  int t_val = stack.get_len();
  stack.push(-1);
  stack.push(arith_val);
  stack.push(AN_ARITHMETIC_LIST);
  stack.push(t_val);
  stack.push(AN_ARITHMETIC_END);
  return AN_COMMAND_KEEP;
}

int rule_10(Stack& stack) {
  stack.pop();
  int res = stack.pop();
  int prev_calculation = stack.pop();
  int t_val = stack.get_len() + 4;
  int sum_val = stack.get_len();
  stack.push(-1);
  stack.push(res);
  stack.push(AN_ARITHMETIC_LIST);
  stack.push(sum_val);
  stack.push(-1);
  stack.push(prev_calculation);
  stack.push(AN_C_SUM);
  stack.push(t_val);
  stack.push(AN_ARITHMETIC_END);
  return AN_COMMAND_NEXT;
}

int rule_11(Stack& stack) {
  stack.pop();
  int res = stack.pop();
  int prev_calculation = stack.pop();
  stack.set_to(prev_calculation, res);
  return AN_COMMAND_KEEP;
}

int rule_12(Stack& stack) {
  stack.pop();
  int res = stack.pop();
  int var = stack.get_len();
  stack.push(-1);
  stack.push(res);
  stack.push(AN_ARITHMETIC_END_LIST);
  stack.push(var);
  stack.push(AN_F);
  return AN_COMMAND_KEEP;
}

int rule_13(Stack& stack) {
  stack.pop();
  int res = stack.pop();
  int prev_calculation = stack.pop();
  int var = stack.get_len() + 4;
  int mul_res = stack.get_len();
  stack.push(-1);
  stack.push(res);
  stack.push(AN_ARITHMETIC_END_LIST);
  stack.push(mul_res);
  stack.push(-1);
  stack.push(prev_calculation);
  stack.push(AN_C_MUL);
  stack.push(var);
  stack.push(AN_F);
  return AN_COMMAND_NEXT;
}

int rule_14(Stack& stack) {
  stack.pop();
  int res = stack.pop();
  int prev_calculation = stack.pop();
//  global::data_field[res] = global::data_field[prev_calculation];
  stack.set_to(prev_calculation, res);
  return AN_COMMAND_KEEP;
}

int rule_15(Stack &stack, lexeme &lx) {
  stack.pop();
  int var = stack.pop();
  node *fd = find_name(global::var_table, lx.name);
  if (fd) {
    lx.key = fd->key.key;
    stack.set_to(lx.key, var);
    return AN_COMMAND_NEXT;
  }
  return AN_COMMAND_REJECT;
}

int rule_16(Stack &stack, lexeme &lx) {
  stack.pop();
  int var = stack.pop();
  node* fd = find_name(global::var_table, lx.name);
  if (!fd) {
    lx.key = new_data();
    lexeme k;
    k.key = lx.key;
    k.name = (char *)malloc(strlen(lx.name) + 1);
    strcpy(k.name, lx.name);
    global::var_table = insert(global::var_table, k);
    global::data_field[lx.key] = strtol(lx.name, nullptr, 10);
  } else {
    lx.key = fd->key.key;
  }
  stack.set_to(lx.key, var);
  return AN_COMMAND_NEXT;
}

int rule_17(Stack& stack) {
  stack.pop();
  int res = stack.pop();
  int t_val = stack.get_len() + 1;
  stack.push(res);
  stack.push(-1);
  stack.push(AN_LOGIC_LIST);
  stack.push(t_val);
  stack.push(AN_F);
  return AN_COMMAND_KEEP;
}

int rule_18(Stack& stack) {
  stack.pop();
  int prev_calculation = stack.pop();
  int res = stack.pop();
  int t_val = stack.get_len() + 1;
  stack.push(res);
  stack.push(-1);
  stack.push(prev_calculation);
  stack.push(AN_C_EQ);
  stack.push(t_val);
  stack.push(AN_F);
  return AN_COMMAND_NEXT;
}

int rule_19(Stack& stack) {
  stack.pop();
  int prev_calculation = stack.pop();
  int res = stack.pop();
  int t_val = stack.get_len() + 1;
  stack.push(res);
  stack.push(-1);
  stack.push(prev_calculation);
  stack.push(AN_C_NE);
  stack.push(t_val);
  stack.push(AN_F);
  return AN_COMMAND_NEXT;
}

int rule_20(Stack& stack) {
  stack.pop();
  return AN_COMMAND_NEXT;
}

int rule_21(Stack& stack) {
  return rule_20(stack);
}
int rule_22(Stack& stack) {
  return rule_20(stack);
}
int rule_23(Stack& stack) {
  return rule_20(stack);
}
int rule_24(Stack& stack) {
  return rule_20(stack);
}
