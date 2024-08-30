#include <stdio.h>

#include "raylib.h"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

#define KEY_GAP 10
#define KEYS (7 * 3)
#define KEY_WIDTH ((GetRenderWidth() - (KEYS - 1) * KEY_GAP) / KEYS)
#define KEY_HEIGHT 300

int main(int argc, char *argv[]) {
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "rayano - a simple piano");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < KEYS; i++) {
            Rectangle rec = {
                .x = (KEY_WIDTH + KEY_GAP) * i + KEY_GAP,
                .y = GetRenderHeight() - KEY_HEIGHT,
                .width = KEY_WIDTH,
                .height = KEY_HEIGHT
            };
            DrawRectangleRec(rec, WHITE);
        }
        EndDrawing();
    }

    return 0;
}

