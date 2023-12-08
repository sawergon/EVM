//
// Created by Alex on 16.11.2023.
//

#include "static_analyzer.h"
#include "iostream"

using namespace std;

namespace global {
int data_end = 0, command_end = 0, label_end = 0;
}

int translator(char *source, int len_source) {
  int translation_result = analyze(source, len_source);
  if (translation_result == AN_COMMAND_ACCEPT) {
    int pos = 0;
    while (pos < global::command_end) {
      int command = global::command_field[pos];
      switch (command) {
        case AN_C_SET: {
          pos++;
          int res = global::command_field[pos++];
          int value = global::command_field[pos++];
          global::data_field[res] = global::data_field[value];
          break;
        }
        case AN_C_SUM: {
          pos++;
          int a = global::command_field[pos++];
          int b = global::command_field[pos++];
          int res = global::command_field[pos++];
          global::data_field[res] = global::data_field[a] + global::data_field[b];
          break;
        }
        case AN_C_MUL: {
          pos++;
          int a = global::command_field[pos++];
          int b = global::command_field[pos++];
          int res = global::command_field[pos++];
          global::data_field[res] = global::data_field[a] * global::data_field[b];
          break;
        }
        case AN_C_EQ: {
          pos++;
          int a = global::command_field[pos++];
          int b = global::command_field[pos++];
          int res = global::command_field[pos++];
          global::data_field[res] = global::data_field[a] == global::data_field[b];
          break;
        }
        case AN_C_NE: {
          pos++;
          int a = global::command_field[pos++];
          int b = global::command_field[pos++];
          int res = global::command_field[pos++];
          global::data_field[res] = global::data_field[a] != global::data_field[b];
          break;
        }
        case AN_C_COND_GO_TO_0: {
          pos++;
          int logic = global::command_field[pos++];
          int move_to = global::label_table[global::command_field[pos++]];
          if (!global::data_field[logic]) {
            pos = move_to;
          }
          break;
        }
        case AN_C_NON_COND_GO_TO: {
          pos++;
          int move_to = global::label_table[global::command_field[pos++]];
          pos = move_to;
          break;
        }
        case AN_C_COMP_GO_TO: {
          pos++;
          int logic = global::command_field[pos++];
          int move_to = global::label_table[global::command_field[pos++]];
          if (global::data_field[logic]) {
            pos = move_to;
          }
          break;
        }
        default:pos++;
      }
    }
  }
  return translation_result;
}

int analization(Stack &stack, lexeme &lx);

int analyze(char *source, int len_source) {
  global::data_end = global::command_end = global::label_end = 0;
  int result = AN_COMMAND_KEEP, pos = 0;
  Stack stack = Stack(AN_END_STACK);
  stack.push(AN_START);
  lexeme lx;
  while (pos <= len_source && result != AN_COMMAND_REJECT) {
    int code_lx = get_lexeme(source, pos, lx);
//    if (lx.key == ID_VAR)
//    node *is_var_exist = find_name(global::var_table, lx.name);
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
//  stack.~Stack();
  return result;
}

int analization(Stack &stack, lexeme &lx) {
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
    case AN_SET: {
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
    case AN_C_SET: {
      result = an_make_set_action(stack, lx);
      break;
    }
    case AN_C_SUM: {
      result = an_make_sum_action(stack, lx);
      break;
    }
    case AN_C_MUL: {
      result = an_make_mul_action(stack, lx);
      break;
    }
    case AN_C_EQ: {
      result = an_make_eq_action(stack, lx);
      break;
    }
    case AN_C_NE: {
      result = an_make_ne_action(stack, lx);
      break;
    }
    case AN_C_LABEL: {
      result = an_make_label_action(stack, lx);
      break;
    }
    case AN_C_NON_COND_GO_TO: {
      result = an_make_non_cond_go_to_action(stack, lx);
      break;
    }
    case AN_C_COND_GO_TO_0: {
      result = an_make_cond_go_to_0_action(stack, lx);
      break;
    }
    case AN_C_COMP_GO_TO: {
      result = an_make_comp_go_to_action(stack, lx);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}
