#include <flint/flint.h>
#include <flint/fmpz.h>
#include <iostream>

int main() {
  fmpz_t num;
  fmpz_init(num);
  fmpz_set_ui(num, 12345);

  std::cout << "Number: ";
  fmpz_print(num);
  std::cout << std::endl;

  fmpz_clear(num);

  return 0;
}