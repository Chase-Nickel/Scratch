#include <stdio.h>
#include <stdint.h>

int main(void) {
  int64_t fib[50] = {0, 1};
  for(int i = 2; i < 50; i++)
    fib[i] = fib[i - 1] + fib[i - 2];
  for(int i = 0; i < 50; i++)
    printf("%ld, ", fib[i]);
  putchar('\n');
  return 0;
}
