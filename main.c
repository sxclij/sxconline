#include <unistd.h>

#define world_size (1 << 14)
#define chunk_size (1 << 8)
#define table_type_size (1 << 8)
#define term_size (1 << 8)
#define buf_kakkokari_size (1 << 16)

enum bool {
    false = 0,
    true = 1,
};
enum type {
    type_null,
    type_air,
    type_stone,
};
struct i32_2 {
    int x;
    int y;
};
struct block {
    enum type type;
    char size;
};
struct chunk {
    struct block block[chunk_size][chunk_size];
};
struct world {
    struct chunk chunk[world_size / chunk_size][world_size / chunk_size];
};
struct term_bit {
    char ch;
    char color;
};
struct term {
    struct i32_2 ws;
    struct term_bit display[term_size][term_size];
};
struct global {
    struct world world;
    struct term term;
    struct i32_2 camera;
    struct i32_2 cursor;
};

static struct global global;

void render() {

}
void global_update() {
    render();
    usleep(10000);
}
void global_init() {
    global.camera = (struct i32_2){world_size / 2, world_size / 2};
    global.cursor = (struct i32_2){world_size / 2, world_size / 2};
}
int main() {
    global_init();
    while (1) {
        global_update();
    }
    return 0;
}
