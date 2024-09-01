#include "raylib.h"
#include "plug.h"

#define KEY_GAP 10
#define KEYS (7 * 3)
#define KEY_WIDTH ((GetRenderWidth() - (KEYS - 1) * KEY_GAP) / KEYS)
#define KEY_HEIGHT 300
#define BLACK_KEY_WIDTH (KEY_WIDTH * 0.5f)
#define BLACK_KEY_HEIGHT (KEY_HEIGHT * 0.75f)

static void plug_init(Plug *plug, void *data) {
}

static void plug_update(Plug *plug, void *data) {
    ClearBackground(GRAY);
    for (int i = 0; i < KEYS; i++) {
        Rectangle rec = {
            .x = (KEY_WIDTH + KEY_GAP) * i + KEY_GAP,
            .y = GetRenderHeight() - KEY_HEIGHT,
            .width = KEY_WIDTH,
            .height = KEY_HEIGHT
        };
        DrawRectangleRec(rec, CheckCollisionPointRec(GetMousePosition(), rec) ? LIGHTGRAY : WHITE);
    }
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
        DrawRectangleRec(rec, CheckCollisionPointRec(GetMousePosition(), rec) ? DARKGRAY : BLACK);
    }
}

static void plug_destroy(Plug *plug, void *data) {
}

