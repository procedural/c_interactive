#pragma once

struct app_state_t {
};

struct app_api_t {
  struct app_state_t * (*Init)();
  void (*Reload)(struct app_state_t *);
  int  (*Step)(struct app_state_t *);
  void (*Unload)(struct app_state_t *);
  void (*Finalize)(struct app_state_t *);
};
