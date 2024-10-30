#include <unistd.h>

#define world_size (1 << 14)
#define chunk_size (1 << 8)
#define table_type_size (1 << 8)
#define buf_kakkokari_size (1 << 16)

enum bool {
    false = 0,
    true = 1,
};
enum type {
    type_null,
    type_air,
};
struct i32_2 {
    int x;
    int y;
};
struct global {
    struct global_world {
        struct global_chunk {
            struct global_block {
                enum type type;
                char size;
            } block[chunk_size][chunk_size];
        } chunk[world_size / chunk_size][world_size / chunk_size];
    } world;
    struct global_term {
        struct i32_2 ws;
        char buf[buf_kakkokari_size];
    } term;
};

static struct global global;

void global_update() {
    usleep(10000);
}
void global_init() {
}
int main() {
    global_init();
    while (1) {
        global_update();
    }
    return 0;
}
