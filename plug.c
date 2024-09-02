#include <assert.h>
#include <string.h>

#include "raylib.h"
#include "plug.h"

#define KEY_GAP 10
#define KEYS (7 * 3)
#define KEY_WIDTH ((GetRenderWidth() - (KEYS - 1) * KEY_GAP) / KEYS)
#define KEY_HEIGHT 300
#define BLACK_KEY_WIDTH (KEY_WIDTH * 0.5f)
#define BLACK_KEY_HEIGHT (KEY_HEIGHT * 0.75f)

Plug plug_internal;

void plug_init(void *data) {
    plug_internal.plug_size = sizeof(Plug);
}

void plug_update(void *data) {
    ClearBackground(GRAY);
    for (int i = 0; i < KEYS; i++) {
        Rectangle rec = {
            .x = (KEY_WIDTH + KEY_GAP) * i + KEY_GAP,
            .y = GetRenderHeight() - KEY_HEIGHT,
            .width = KEY_WIDTH,
            .height = KEY_HEIGHT
        };
        bool white_colli = !plug_internal.in_black && CheckCollisionPointRec(GetMousePosition(), rec);
        DrawRectangleRec(rec, white_colli ? LIGHTGRAY : WHITE);
    }
    plug_internal.in_black = false;
    for (int i = 1; i < KEYS; i++) {
        if (i % 7 == 0 || i % 7 == 3) {
            continue;
        }
        Rectangle rec = {
            .x = (KEY_WIDTH + KEY_GAP) * i - BLACK_KEY_WIDTH / 2.0f + KEY_GAP / 2.0f,
            .y = GetRenderHeight() - KEY_HEIGHT,
            .width = BLACK_KEY_WIDTH,
            .height = BLACK_KEY_HEIGHT
        };
        bool black_colli = CheckCollisionPointRec(GetMousePosition(), rec);
        if (black_colli) {
            plug_internal.in_black = true;
        }
        DrawRectangleRec(rec, black_colli ? DARKGRAY : BLACK);
    }
}

void plug_destroy(void *data) {
}

size_t plug_size(void *data) {
    return sizeof(Plug);
}

void plug_save(Plug *dst, void *data) {
    memcpy(&plug_internal, dst, plug_internal.plug_size);
}

void plug_restore(Plug *src, void *data) {
    TraceLog(LOG_INFO, "Plug original size: %lu, new size: %lu", src->plug_size, sizeof(Plug));
    memset(&plug_internal, 0, sizeof(Plug));
    plug_internal.plug_size = sizeof(Plug);
    memcpy(src, &plug_internal, src->plug_size);
}

