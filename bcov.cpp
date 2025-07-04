#include <unistd.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>

#include "bcov.h"


static void bcov_signal_handler(int signum) {
  if (signum == SIGTERM) {
    __gcov_dump();
    exit(0);
  }
}

void InitChildCoverage() {
  struct sigaction sa;
  sa.sa_handler = bcov_signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGTERM, &sa, nullptr);

  pid_t pid = getpid();

  const char* base_dir = getenv("GCOV_PREFIX_CHILD");
  if (!base_dir) {
    base_dir = "/data/coverage_data";
  }

  char cov_path[256];
  snprintf(cov_path, sizeof(cov_path), "%s/cov_%d", base_dir, pid);
  setenv("GCOV_PREFIX", cov_path, 1);
  __gcov_reset();
}