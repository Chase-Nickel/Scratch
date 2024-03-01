#include <stdio.h>

enum test_t {
  FLOAT,
  INT,
  DOUBLE
};

struct test {
  enum test_t type;
  union {
    float  f;
    int    i;
    double d;
  };
};

int main(void) {
  struct test foo = { FLOAT, { 5.0f }};
  switch(foo.type) {
    case FLOAT:
      printf("%f\n", foo.f);
      break;
    case DOUBLE:
      printf("%lf\n", foo.d);
      break;
    case INT:
      printf("%d\n", foo.i);
      break;
    default:
      puts("How did we get here...");
      break;
  }
  return 0;
}
  
