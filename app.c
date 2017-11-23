#include <stdlib.h>
#include <stdio.h>
#include "app.h"

static struct app_state_t * AppInit() {
  printf("Init\n");
  struct app_state_t * state = calloc(1, sizeof(struct app_state_t));
  return state;
}

static void AppReload(struct app_state_t * state) {
  printf("Reload\n");
}

static int AppStep(struct app_state_t * state) {
  printf("Step\n");
  return 0;
}

static void AppUnload(struct app_state_t * state) {
  printf("Unload\n");
}

static void AppFinalize(struct app_state_t * state) {
  printf("Finalize\n");
  free(state);
}

struct app_api_t APP_API = {
  .Init     = AppInit,
  .Reload   = AppReload,
  .Step     = AppStep,
  .Unload   = AppUnload,
  .Finalize = AppFinalize
};
