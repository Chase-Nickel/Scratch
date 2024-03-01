#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *addBinary(char *a, char *b) {
  int alen = strlen(a);
  int blen = strlen(b);
  char *out;
  int len;
  if (alen == blen) {
    len = alen + (*a == '1' && *b == '1');
  } else {
    len = alen > blen ? alen : blen;
  }
  out = calloc(len + 1, 1);

  int carry = 0;
  while (alen > 0 || blen > 0) {
    len--;
    alen--;
    blen--;
    char x = alen >= 0? a[alen] - '0' : 0;
    char y = blen >= 0? b[blen] - '0' : 0;

    int res   = x ^ y ^ carry;
    carry = (x + y + carry) > 1;
    out[len] = res + '0';
  }
  if (carry)
    out[0] = '1';
  return out;
}

int main(void) {
  char *o = addBinary("1011","111");
  puts(o);
  free(o);
  return 0;
}
