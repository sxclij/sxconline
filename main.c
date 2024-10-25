#include <unistd.h>

int main() {
    write(1, "good morning world\n", 19);
    return 0;
}