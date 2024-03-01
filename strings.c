#include <stdio.h>

typedef unsigned long int uint32_t;

typedef struct str8_t str8_t;
struct str8_t {
  uint32_t length;
  char    *data;
};

str8_t str8_make(const char *str, uint32_t len);
#define STR(s) str8_make(s, (uint32_t)(sizeof(s) - 1))
void str8_print(str8_t str);

int main(void) {
  str8_t a = STR("apple");
  str8_print(a);
  return 0;
}

str8_t str8_make(const char *str, uint32_t len) {
  str8_t out;
  out.data = (char *)str;
  out.length = len;
  return out;
}

void str8_print(str8_t str) {
  while(str.length--)
    putchar(*(str.data++));
}
