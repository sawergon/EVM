//
// Created by alex on 03.10.23.
//

#include "Analyzer.h"

#include "string.h"

bool is_digit(char ch) {
  return ('0' <= ch && ch <= '9');
}

bool is_letter(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
}

bool is_sign(char ch) {
  return ('(' <= ch && ch <= '+') || (ch == '-') || (ch == '/') || (ch == '!') || (':' <= ch && ch <= '>');
}

int get_type(const char &c) {
  if (is_digit(c)) return TYPE_NUM;
  if (is_letter(c)) return TYPE_STR;
  if (is_sign(c)) return TYPE_SIG;
  return TYPE_TRASH;
}

int get_chars(char **str, const char *source, int *len, int type) {
  *len = 0;
  int capacity = 1;
  *str = (char *) malloc(capacity);
  char c = source[0];
  bool first_digit = is_digit(c);
  //
  while ((get_type(c) == type) || ((type == TYPE_STR) ? c != '\0' && is_digit(c) && !first_digit : 0)) {
    (*str)[(*len)++] = c;
    if (*len >= capacity) {
      capacity *= 2;
      *str = (char *) realloc(*str, capacity * sizeof(char));
    }
    c = *(source + *len);
    if (first_digit && get_type(c) == TYPE_STR) return CODE_ER;
  }
  (*str)[(*len)] = '\0';
  return CODE_OK;
}

int is_key_word(char *word) {
  if (!strcmp(word, KEY_IF)) return ID_IF;
  if (!strcmp(word, KEY_ELSE)) return ID_ELSE;
  if (!strcmp(word, KEY_REPEAT)) return ID_REPEAT;
  if (!strcmp(word, KEY_UNTIL)) return ID_UNTIL;
  return ID_VAR;
}

int what_sign(char *word) {
  if (!strcmp(word, KEY_SUM)) return ID_SUM;
  if (!strcmp(word, KEY_DIF)) return ID_DIF;
  if (!strcmp(word, KEY_MUL)) return ID_MUL;
  if (!strcmp(word, KEY_DIV)) return ID_DIV;
  if (!strcmp(word, KEY_LEFT)) return ID_LEFT;
  if (!strcmp(word, KEY_RIGHT)) return ID_RIGHT;
  if (!strcmp(word, KEY_BREAK)) return ID_BREAK;
  if (!strcmp(word, KEY_SET)) return ID_SET;
  if (!strcmp(word, KEY_EQ)) return ID_EQ;
  if (!strcmp(word, KEY_NOT_EQ)) return ID_NOT_EQ;
  if (!strcmp(word, KEY_LESS)) return ID_LESS;
  if (!strcmp(word, KEY_MORE)) return ID_MORE;
  return TYPE_TRASH;
}

int get_lexeme(char * source, int &pos, lexeme &l) {
  char c = source[pos];
  int len = 0, code, atribut;
  char *value;
  switch (get_type(c)) {
    case TYPE_NUM: {
      code = get_chars(&value, source + pos, &len, TYPE_NUM);
      atribut = ID_NUM;
      break;
    }
    case TYPE_STR: {
      code = get_chars(&value, source + pos, &len, TYPE_STR);
      atribut = is_key_word(value);
      break;
    }
    case TYPE_SIG: {
      code = get_chars(&value, source + pos, &len, TYPE_SIG);
      atribut = what_sign(value);
      break;
    }
    default: {
      if (source[pos] == '\0') {
        code = CODE_OK;
        value = (char *) malloc(3);
        value[0] = '-';
        value[1] = '|';
        value[2] = '\0';
        len = 1;
        atribut = ID_END_STRING;
      } else {
        code = CODE_SK;
      }
      break;
    }
  }
  if (code == CODE_OK) {
    pos += len;
    l.name = value;
    l.key = atribut;
  }
  return code;
}