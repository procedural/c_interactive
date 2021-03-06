#include <unistd.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include "api.h"

struct app_t {
  struct api_t api;
  void * handle;
  void * state;
  ino_t  id;
};

static void AppLoad(struct app_t * app) {
  struct stat attr = {0};
  if ((stat("./libapp.so", &attr) == 0) && (app->id != attr.st_ino)) {
    if (app->handle != NULL) {
      app->api.Unload(app->state);
      dlclose(app->handle);
    }
    void * handle = dlopen("./libapp.so", RTLD_NOW);
    if (handle != NULL) {
      app->handle = handle;
      app->id = attr.st_ino;
      struct api_t * api = dlsym(app->handle, "APP_API");
      if (api != NULL) {
        app->api = api[0];
        if (app->state == NULL)
          app->state = app->api.Init();
        app->api.Load(app->state);
      } else {
        dlclose(app->handle);
        app->handle = NULL;
        app->id = 0;
      }
    } else {
      app->handle = NULL;
      app->id = 0;
    }
  }
}

void AppUnload(struct app_t * app) {
  if (app->handle != NULL) {
    app->api.Unload(app->state);
    app->api.Deinit(app->state);
    app->state = NULL;
    dlclose(app->handle);
    app->handle = NULL;
    app->id = 0;
  }
}

int main() {
  struct app_t app = {0};
  for (;;) {
    AppLoad(&app);
    if (app.handle != NULL)
      if (app.api.Step(app.state) != 0)
        break;
    usleep(500000); // Delete this line for full speed.
  }
  AppUnload(&app);
  return 0;
}
