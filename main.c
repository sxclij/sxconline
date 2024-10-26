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
    int x;
    int y;
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

static struct global global;

void obj_update() {
}
void obj_init() {
}
void global_update() {
    obj_update();
}
void global_init() {
    obj_init();
}

int main() {
    global_init();
    while (1) {
        global_update();
    }
    return 0;
}
