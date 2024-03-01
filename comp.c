typedef signed char      int8_t;
typedef signed short int int16_t;
typedef signed long int  int32_t;

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int  uint32_t;

int32_t write(int32_t fd, char *buf, uint32_t len);
int32_t print(char *s, uint32_t len) {
  return write(1, s, len);
}

int main(void) {
  print("Hello, World!\n", sizeof("Hello, World!\n") - 1);
  return 0;
}
