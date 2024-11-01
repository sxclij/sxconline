#include <sys/ioctl.h>
#include <unistd.h>

#define world_size (1 << 14)
#define chunk_size (1 << 8)
#define table_type_size (1 << 8)
#define term_size (1 << 10)
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
    struct winsize ws;
};
struct global {
    struct world world;
    struct term term;
    struct i32_2 camera;
    struct i32_2 cursor;
};

static struct global global;

struct block* block_get(int x, int y) {
    return &global.world.chunk[x / world_size][y / world_size].block[x % world_size][y % world_size];
}
void block_set(int x, int y, enum type type, char size) {
    struct block* block = block_get(x, y);
    block->type = type;
    block->size = size;
}
void term_render_dot(int x, int y) {
    if (x < 0 || world_size <= x || y < 0 || world_size <= y) {
        write(STDOUT_FILENO, "@", 1);
    } else {
        struct block* block = block_get(x, y);
        write(STDOUT_FILENO, ".", 1);
    }
}
void term_render() {
    write(STDOUT_FILENO, "\x1b[1;1H", 6);
    for (int i = 0; i < global.term.ws.ws_row; i++) {
        for (int j = 0; j < global.term.ws.ws_col; j++) {
            term_render_dot(global.camera.x - (global.term.ws.ws_col / 2) + j, global.camera.y + (global.term.ws.ws_row / 2) - i);
        }
    }
}
void term_update() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &global.term.ws);
    term_render();
}
void global_update() {
    term_update();
    usleep(10000);
}
void global_init() {
    // global.camera = (struct i32_2){world_size / 2, world_size / 2};
    // global.cursor = (struct i32_2){world_size / 2, world_size / 2};
    global.camera = (struct i32_2){0, 0};
    global.cursor = (struct i32_2){0, 0};
}
int main() {
    global_init();
    while (1) {
        global_update();
    }
    return 0;
}
