#include <sys/mman.h>
#include <stdio.h>
#include "api.h"

struct state_t {};

struct state_t * s = NULL;

static void * AppInit() {
  void * state = mmap(0, 256L * 1024L * 1024L * 1024L, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0);
  s = state;

  printf("Init\n");

  return state;
}

static void AppLoad(void * state) {
  s = state;

  printf("Reload\n");
}

static int AppStep(void * state) {
  s = state;

  printf("Step\n");
  return 0;
}

static void AppUnload(void * state) {
  s = state;

  printf("Unload\n");
}

static void AppDeinit(void * state) {
  s = state;

  printf("Finalize\n");
  munmap(state, 256L * 1024L * 1024L * 1024L);
}

struct api_t APP_API = {
  .Init   = AppInit,
  .Load   = AppLoad,
  .Step   = AppStep,
  .Unload = AppUnload,
  .Deinit = AppDeinit
};
