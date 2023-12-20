//
// Created by Alex on 23.11.2023.
//

#include "static_analyzer.h"

namespace global {
int label_table[SIZE_FIELD];
int command_field[SIZE_FIELD];
//int command_end = 0;
}

int an_start_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_IF:
    case ID_REPEAT: {
      result = rule_1(stack);
      break;
    }
    default:result = AN_COMMAND_REJECT;
  }
  return result;
}



int an_amount_operator_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_IF:
    case ID_REPEAT: {
      result = rule_2(stack);
      break;
    }
    case ID_ELSE:
    case ID_UNTIL:
    case ID_END_STRING: {
      result = rule_3(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_operator_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR: {
      node * fd = find_name(global::var_table, lx.name);
      if (!fd) {
        lx.key = new_data();
        lexeme k;
        k.key = lx.key;
        k.name = (char *) malloc(strlen(lx.name) + 1);
        strcpy(k.name, lx.name);
        global::var_table = insert(global::var_table, k);
      } else {
        lx.key = fd->key.key;
      }
      result = rule_7(stack, lx.key);
      break;
    }
    case ID_IF: {
      result = rule_4(stack);
      break;
    }
    case ID_REPEAT: {
      result = rule_8(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_end_if_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_IF:
    case ID_REPEAT:
    case ID_END_STRING: {
      result = rule_6(stack);
      break;
    }
    case ID_ELSE: {
      result = rule_5(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_arithmetic_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_NUM: {
      result = rule_9(stack, lx);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_arithmetic_list_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_BREAK: {
      result = rule_11(stack);
      break;
    }
    case ID_SUM: {
      result = rule_10(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_arithmetic_end_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_NUM: {
      result = rule_12(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}
int an_arithmetic_end_list_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_BREAK:
    case ID_SUM: {
      result = rule_14(stack);
      break;
    }
    case ID_MUL: {
      result = rule_13(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_f_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR: {
      result = rule_15(stack, lx);
      break;
    }
    case ID_NUM: {
      result = rule_16(stack, lx);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_logic_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_NUM: {
      result = rule_17(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}
int an_logic_list_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_EQ: {
      result = rule_18(stack);
      break;
    }
    case ID_NOT_EQ: {
      result = rule_19(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_left_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_LEFT: {
      result = rule_20(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_right_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_RIGHT: {
      result = rule_21(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_break_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_BREAK: {
      result = rule_22(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}
int an_set_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_SET: {
      result = rule_23(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_until_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_UNTIL: {
      result = rule_24(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_end_stack_action(Stack &stack, lexeme &lx) {
  int result = AN_COMMAND_ACCEPT;
  if (lx.key != ID_END_STRING) {
    result = AN_COMMAND_REJECT;
  }
  return result;
}

int an_make_set_action(Stack &stack, lexeme &lx) {
  global::command_field[global::command_end++] = stack.pop();
  global::command_field[global::command_end++] = stack.pop();
  global::command_field[global::command_end++] = stack.pop();
  return AN_COMMAND_KEEP;
}

int an_make_sum_action(Stack &stack, lexeme &lx) {
  int res_field = new_data();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = res_field;
  int move_to = stack.pop();
  stack.set_to(res_field, move_to);
  return AN_COMMAND_KEEP;
}

int an_make_mul_action(Stack &stack, lexeme &lx) {
  int res_field = new_data();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = res_field;
  int move_to = stack.pop();
  stack.set_to(res_field, move_to);
  return AN_COMMAND_KEEP;
}

int an_make_eq_action(Stack &stack, lexeme &lx) {
  int res_field = new_data();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = res_field;
  int move_to = stack.pop();
  stack.set_to(res_field, move_to);
  return AN_COMMAND_KEEP;
}

int an_make_ne_action(Stack &stack, lexeme &lx) {
  int res_field = new_data();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = res_field;
  int move_to = stack.pop();
  stack.set_to(res_field, move_to);
  return AN_COMMAND_KEEP;
}

int an_make_label_action(Stack &stack, lexeme &lx) {
  stack.pop();
  int label = stack.pop();
  global::label_table[label] = global::command_end;
  return AN_COMMAND_KEEP;
}

int an_make_cond_go_to_0_action(Stack &stack, lexeme &lx) {
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  int label = new_label();
  global::command_field[global::command_end++]  = label;
  int move_to = stack.pop();
  stack.set_to(label, move_to);
  return AN_COMMAND_KEEP;
}

int an_make_non_cond_go_to_action(Stack &stack, lexeme &lx) {
  global::command_field[global::command_end++]  = stack.pop();
  int label = new_label();
  global::command_field[global::command_end++]  = label;
  int move_to = stack.pop();
  stack.set_to(label, move_to);
  return AN_COMMAND_KEEP;
}

int an_make_comp_go_to_action(Stack &stack, lexeme &lx) {
  global::command_field[global::command_end++]  = stack.pop();
  global::command_field[global::command_end++]  = stack.pop();
  int move = stack.pop();
  int label = stack[move];
  global::command_field[global::command_end++]  = label;
  return AN_COMMAND_KEEP;
}

int new_data() {
  return global::data_end++;
}

int new_label() {
  return global::label_end++;
}

void set_label(int label, int pos) {
  global::label_table[label] = pos;
}

int get_label(int label) {
  return global::label_table[label];
}