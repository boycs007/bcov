#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "bcov.h"

static struct sigaction g_original_sa;

static void bcov_signal_handler_wrapper(int signum) {
  if (signum == SIGTERM) {
    __gcov_dump();
    if (g_original_sa.sa_handler != nullptr &&
        g_original_sa.sa_handler != SIG_IGN &&
        g_original_sa.sa_handler != SIG_DFL) {
      g_original_sa.sa_handler(signum);
    } else {
      exit(0);
    }
  }
}

void InitChildCoverage() {
  // 获取并保存原有信号处理器
  sigaction(SIGTERM, nullptr, &g_original_sa);
  // 设置新的信号处理器
  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = bcov_signal_handler_wrapper;
  sa.sa_flags = 0;
  sigaction(SIGTERM, &sa, nullptr);

  pid_t pid = getpid();

  const char *base_dir = getenv("GCOV_PREFIX_CHILD");
  if (!base_dir) {
    base_dir = "/data/coverage_data";
  }

  char cov_path[256];
  snprintf(cov_path, sizeof(cov_path), "%s/cov_%d", base_dir, pid);
  setenv("GCOV_PREFIX", cov_path, 1);
  __gcov_reset();
}