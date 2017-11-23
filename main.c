#define _BSD_SOURCE // usleep()
#include <unistd.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include "game.h"

struct game_t {
  void * handle;
  ino_t  id;
  struct game_api_t api;
  struct game_state_t * state;
};

static void game_load(struct game_t * game) {
  struct stat attr = {0};
  if ((stat("./libgame.so", &attr) == 0) && (game->id != attr.st_ino)) {
    if (game->handle != NULL) {
      game->api.unload(game->state);
      dlclose(game->handle);
    }
    void * handle = dlopen("./libgame.so", RTLD_NOW);
    if (handle != NULL) {
      game->handle = handle;
      game->id = attr.st_ino;
      struct game_api_t * api = dlsym(game->handle, "GAME_API");
      if (api != NULL) {
        game->api = api[0];
        if (game->state == NULL)
          game->state = game->api.init();
        game->api.reload(game->state);
      } else {
        dlclose(game->handle);
        game->handle = NULL;
        game->id = 0;
      }
    } else {
      game->handle = NULL;
      game->id = 0;
    }
  }
}

void game_unload(struct game_t * game) {
  if (game->handle != NULL) {
    game->api.finalize(game->state);
    game->state = NULL;
    dlclose(game->handle);
    game->handle = NULL;
    game->id = 0;
  }
}

int main() {
  struct game_t game = {0};
  for (;;) {
    game_load(&game);
    if (game.handle != NULL)
      if (game.api.step(game.state) == false)
        break;
    usleep(100000);
  }
  game_unload(&game);
  return 0;
}
