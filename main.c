#include <unistd.h>

#define obj_data_size (1 << 16)
#define table_type_size (1 << 8)
#define buf_kakkokari_size (1 << 16)

enum bool {
    false = 0,
    true = 1,
};
enum type {
    type_null,
    type_air,
    type_camera,
};
struct i32_2 {
    int x;
    int y;
};
struct obj {
    enum type type;
    enum bool is_allocated;
    struct i32_2 pos;
    struct obj* prev;
    struct obj* next;
};
struct global {
    struct global_obj {
        struct obj data[obj_data_size];
        struct obj* free;
        struct obj* origin;
        struct obj* camera;
    } obj;
    struct global_table {
        struct global_table_type {
            const char* name;
            char display_ch;
            void (*init)(struct obj*);
            void (*update)(struct obj*);
        } type[table_type_size];
    } table;
    struct global_term {
        struct i32_2 ws;
        char buf[buf_kakkokari_size];
    } term;
};

static struct global global;

void obj_free(struct obj* o1) {
    o1->is_allocated = false;
    o1->prev = global.obj.free;
    global.obj.free = global.obj.free->prev;
    global.obj.free = o1;
}
struct obj* obj_spawn(enum type type) {
    struct obj* o1 = global.obj.free;
    o1->is_allocated = true;
    global.obj.free = global.obj.free->prev;
    global.table.type[o1->type].init(o1);
    return o1;
}
void obj_update() {
    for (int i = 0; i < obj_data_size; i++) {
        struct obj* o1 = &global.obj.data[i];
        if (!o1->is_allocated) {
            continue;
        }
        global.table.type[o1->type].update(o1);
    }
}
void obj_init() {
    global.obj.free = global.obj.data;
    for (int i = 0; i < obj_data_size; i++) {
        obj_free(&global.obj.data[i]);
    }
    global.obj.origin = obj_spawn(type_air);
    global.obj.camera = obj_spawn(type_camera);
}
void global_update() {
    obj_update();
    usleep(10000);
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
