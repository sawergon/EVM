//
// Created by Alex on 23.11.2023.
//

#include "static_analyzer.h"

int an_start_action(Stack &stack, lexeme lx) {
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



int an_amount_operator_action(Stack &stack, lexeme lx) {
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

int an_operator_action(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR: {
      result = rule_7(stack);
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

int an_end_if_action(Stack &stack, lexeme lx) {
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

int an_arithmetic_action(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR:
    case ID_NUM: {
      result = rule_9(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_arithmetic_list_action(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_BREAK:
    case ID_END_STRING: {
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

int an_arithmetic_end_action(Stack &stack, lexeme lx) {
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
int an_arithmetic_end_list_action(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_BREAK:
    case ID_SUM:
    case ID_END_STRING: {
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

int an_f_action(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  switch (lx.key) {
    case ID_VAR: {
      result = rule_15(stack);
      break;
    }
    case ID_NUM: {
      result = rule_16(stack);
      break;
    }
    default: {
      result = AN_COMMAND_REJECT;
    }
  }
  return result;
}

int an_logic_action(Stack &stack, lexeme lx) {
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
int an_logic_list_action(Stack &stack, lexeme lx) {
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

int an_left_action(Stack &stack, lexeme lx) {
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

int an_right_action(Stack &stack, lexeme lx) {
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

int an_break_action(Stack &stack, lexeme lx) {
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
int an_set_action(Stack &stack, lexeme lx) {
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

int an_until_action(Stack &stack, lexeme lx) {
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

int an_end_stack_action(Stack &stack, lexeme lx) {
  int result = AN_COMMAND_ACCEPT;
  if (lx.key != ID_END_STRING) {
    result = AN_COMMAND_REJECT;
  }
  return result;
}