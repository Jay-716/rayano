#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "raylib.h"
#include "plug.h"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

static Plug plug;
static void *libplug = NULL;
static plug_func_t plug_init = NULL;
static plug_func_t plug_update = NULL;
static plug_func_t plug_destroy = NULL;

static void print_usage(const char *name) {
    printf("Usage:\n");
    printf("    %s <PLUG_PATH>\n", name);
}

static bool load_plug(const char *plug_path) {
    if (libplug != NULL) {
        dlclose(libplug);
    }
    libplug = dlopen(plug_path, RTLD_LAZY);
    if (libplug == NULL) {
        fprintf(stderr, "Error loading plug: %s\n", dlerror());
        return false;
    }
    plug_init = dlsym(libplug, "plug_init");
    plug_update = dlsym(libplug, "plug_update");
    plug_destroy = dlsym(libplug, "plug_destroy");
    if (plug_init == NULL || plug_update == NULL || plug_destroy == NULL) {
        fprintf(stderr, "Error loading plug symbol: %s\n", dlerror());
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        exit(1);
    }
    const char *plug_path = argv[1];
    if (!load_plug(plug_path)) {
        exit(1);
    }
    TraceLog(LOG_INFO, "Loaded plug: %s", plug_path);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "rayano - a simple piano");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    plug_init(&plug, NULL);

    while (!WindowShouldClose()) {
        BeginDrawing();
        if (IsKeyPressed(KEY_R)) {
            TraceLog(LOG_INFO, "Reloading plug: %s", plug_path);
            if (!load_plug(plug_path)) {
                exit(1);
            }
            TraceLog(LOG_INFO, "Reload success.");
        }
        plug_update(&plug, NULL);
        EndDrawing();
    }

    plug_destroy(&plug, NULL);
    dlclose(libplug);
    return 0;
}

