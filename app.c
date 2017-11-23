#include <sys/mman.h>
#include <stdio.h>
#include "api.h"

struct state_t {
};

static void * AppInit() {
  printf("Init\n");
  void * state = mmap(0, 256 * 1024 * 1024, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  return state;
}

static void AppReload(void * state) {
  struct state_t * s = state;
  printf("Reload\n");
}

static int AppStep(void * state) {
  struct state_t * s = state;
  printf("Step\n");
  return 0;
}

static void AppUnload(void * state) {
  struct state_t * s = state;
  printf("Unload\n");
}

static void AppFinalize(void * state) {
  struct state_t * s = state;
  printf("Finalize\n");
  munmap(state, 256 * 1024 * 1024);
}

struct api_t APP_API = {
  .Init     = AppInit,
  .Reload   = AppReload,
  .Step     = AppStep,
  .Unload   = AppUnload,
  .Finalize = AppFinalize
};
