#include <sys/ioctl.h>
#include <unistd.h>

#define world_size (1 << 14)
#define chunk_size (1 << 8)
#define table_type_size (1 << 8)
#define term_size (1 << 10)
#define term_buf_size (1 << 16)
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
    char buf[buf_kakkokari_size];
    int buf_size;
};
struct global {
    struct world world;
    struct term term;
    struct i32_2 camera;
    struct i32_2 cursor;
};

static struct global global;

struct block* block_get(int x, int y) {
    if (x < 0 || world_size <= x || y < 0 || world_size <= y) {
        return NULL;
    } else {
        return &global.world.chunk[x / world_size][y / world_size].block[x % world_size][y % world_size];
    }
}
void block_set(int x, int y, enum type type, char size) {
    struct block* block = block_get(x, y);
    block->type = type;
    block->size = size;
}
void world_init() {
    for (int i = 0; i < world_size; i++) {
        for (int j = 0; j < world_size; j++) {
            block_set(i, j, type_air, 0);
        }
    }
    block_set(10, 3, type_stone, 3);
    block_set(6, 7, type_stone, 1);
}
void term_render_write(const char* str, int n) {
    for (int i = 0; i < n; i++) {
        global.term.buf[global.term.buf_size + i] = str[i];
    }
    global.term.buf_size += n;
}
void term_render_dot(int x, int y) {
    struct block* block = block_get(x, y);
    if (block == NULL) {
        term_render_write("\x1b[40m", 5);
        term_render_write("@@", 2);
        return;
    }
    if (block->type == type_air) {
        term_render_write("\x1b[40m", 5);
    } else if (block->type == type_stone) {
        term_render_write("\x1b[43m", 5);
    }
    if (block->size == 4) {
        term_render_write("04", 2);
    } else if (block->size == 3) {
        term_render_write("03", 2);
    } else if (block->size == 2) {
        term_render_write("02", 2);
    } else if (block->size == 1) {
        term_render_write("01", 2);
    } else {
        term_render_write("  ", 2);
    }
}
void term_render() {
    global.term.buf_size = 0;
    term_render_write("\x1b[1;1H", 6);
    for (int i = 0; i < global.term.ws.ws_row; i++) {
        for (int j = 0; j < global.term.ws.ws_col / 2; j++) {
            term_render_dot(global.camera.x - (global.term.ws.ws_col / 4) + j, global.camera.y + (global.term.ws.ws_row / 2) - i);
        }
        if (global.term.ws.ws_col % 2 == 1) {
            term_render_write("\x1b[40m", 5);
            term_render_write(" ", 1);
        }
    }
    write(STDOUT_FILENO, global.term.buf, global.term.buf_size);
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
    world_init();
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
