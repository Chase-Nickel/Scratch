#include <stdlib.h>

void tester(int val) {
    int* data = malloc(val*sizeof(int));
    (void)data;
}

int main() {
    int val = 10;
    for (int i = 0; i < 10; i++) {
        tester(val);
    }
}
