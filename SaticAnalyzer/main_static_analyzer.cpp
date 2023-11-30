#include <iostream>
#include "static_analyzer.h"
using namespace std;

char *get_string(int *len) {
  *len = 0;
  int capacity = 1;
  char *str = (char *) malloc(capacity), c;
  c = getchar();
  while (c != '\n') {
    str[(*len)++] = c;
    if (*len >= capacity) {
      capacity *= 2;
      str = (char *) realloc(str, capacity * sizeof(char));
    }
    c = getchar();
  }
  str[(*len)] = '\0';
  return str;
}

int main() {
  int len = 0;
  char *source = get_string(&len);
  if (analyze(source, len) == AN_COMMAND_ACCEPT) {
    cout << "ACCEPT" << endl;
  } else {
    cout << "REJECT" << endl;
  }
  return 0;
}