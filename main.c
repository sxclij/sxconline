#include <unistd.h>


enum bool {
    false = 0,
    true = 1,
};
enum obj_type {
    obj_type_null,
    obj_type_camera,
};
struct f64_2 {
    double x;
    double y;
};
struct obj {
    enum obj_type type;
    struct f64_2 pos;
    struct obj* prev;
    struct obj* next;
};

int main() {
    write(1, "good morning world\n", 19);
    return 0;
}
