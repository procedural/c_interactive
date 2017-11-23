#pragma once

struct api_t {
  void * (*Init)();
  void (*Reload)(void *);
  int  (*Step)(void *);
  void (*Unload)(void *);
  void (*Finalize)(void *);
};
