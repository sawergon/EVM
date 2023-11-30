//
// Created by Alex on 16.11.2023.
//

#include "static_analyzer.h"

int new_lexem(char *source, int &pos, lexeme &lx, int len_source);
int analization(Stack &stack, lexeme lx);

int analyze(char *source, int len_source) {
  int result = AN_COMMAND_KEEP, pos = 0;
  Stack stack = Stack(AN_END_STACK);
  stack.push(AN_START);
  lexeme lx;
  while (pos <= len_source && result != AN_COMMAND_REJECT) {
    int code_lx = get_lexeme(source, pos, lx);
    if (code_lx == CODE_ER) {
      result = AN_COMMAND_REJECT;
    } else if (code_lx == CODE_SK) {
      pos++;
    } else {
      result = AN_COMMAND_KEEP;
      while (result == AN_COMMAND_KEEP) {
        result = analization(stack, lx);
      }
      free(lx.name);
    }
  }
  stack.~Stack();
  return result;
}

int new_lexem( char *source, int &pos, lexeme &lx, int len_source) {
  int result = AN_COMMAND_ACCEPT;
  while (pos < len_source && get_lexeme(source, pos, lx) == CODE_ER) {
    pos++;
  }
  if (pos >= len_source) {
    result = AN_COMMAND_REJECT;
  }
  return result;
}



int analization(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (stack.peek()) {
    case AN_START: {
      result = an_start_action(stack, lx);
      break;
    }
    case AN_AMOUNT_OPERATOR: {
      result = an_amount_operator_action(stack, lx);
      break;
    }
    case AN_OPERATOR: {
      result = an_operator_action(stack, lx);
      break;
    }
    case AN_END_IF: {
      result = an_end_if_action(stack, lx);
      break;
    }
    case AN_ARITHMETIC: {
      result = an_arithmetic_action(stack, lx);
      break;
    }
    case AN_ARITHMETIC_LIST: {
      result = an_arithmetic_list_action(stack, lx);
      break;
    }
    case AN_ARITHMETIC_END: {
      result = an_arithmetic_end_action(stack, lx);
      break;
    }
    case AN_ARITHMETIC_END_LIST: {
      result = an_arithmetic_end_list_action(stack, lx);
      break;
    }
    case AN_F: {
      result = an_f_action(stack, lx);
      break;
    }
    case AN_LOGIC: {
      result = an_logic_action(stack, lx);
      break;
    }
    case AN_LOGIC_LIST: {
      result = an_logic_list_action(stack, lx);
      break;
    }
    case AN_LEFT: {
      result = an_left_action(stack, lx);
      break;
    }
    case AN_RIGHT: {
      result = an_right_action(stack, lx);
      break;
    }
    case AN_BREAK: {
      result = an_break_action(stack, lx);
      break;
    }
    case AN_SET:{
      result = an_set_action(stack, lx);
      break;
    }
    case AN_UNTIL: {
      result = an_until_action(stack, lx);
      break;
    }
    case AN_END_STACK: {
      result = an_end_stack_action(stack, lx);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}
