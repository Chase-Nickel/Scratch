#include <malloc.h>
#include <stdio.h>

int main(void) {
  char *u = malloc(14);
  *u = 'a';
  *(u + 1) = 'b';
  *(u + 2) = 'c';
  *(u + 3) = 0;
  puts(u);
  return 0;
}
