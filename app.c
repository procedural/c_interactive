#include <sys/mman.h>
#include <stdio.h>
#include "api.h"

struct state_t {};

static void * AppInit() {
  struct state_t * state = mmap(0, 0xF00000000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0);

  printf("Init\n");

  return state;
}

static void AppLoad(struct state_t * state) {
  printf("Reload\n");
}

static int AppStep(struct state_t * state) {
  printf("Step\n");

  return 0;
}

static void AppUnload(struct state_t * state) {
  printf("Unload\n");
}

static void AppDeinit(struct state_t * state) {
  printf("Finalize\n");

  munmap(state, 0xF00000000);
}

struct api_t APP_API = {
  .Init   = (void *)AppInit,
  .Load   = (void *)AppLoad,
  .Step   = (void *)AppStep,
  .Unload = (void *)AppUnload,
  .Deinit = (void *)AppDeinit
};
