#include <unistd.h>

#define obj_data_capacity (1 << 16)

enum bool {
    false = 0,
    true = 1,
};
enum obj_type {
    obj_type_null,
    obj_type_camera,
};
struct i32_2 {
    unsigned int x;
    unsigned int y;
};
struct obj {
    enum obj_type type;
    struct i32_2 pos;
    struct obj* prev;
    struct obj* next;
};
struct global {
    struct global_obj {
        struct obj data[obj_data_capacity];
    } obj;
};

int main() {
    write(1, "good morning world\n", 19);
    return 0;
}
