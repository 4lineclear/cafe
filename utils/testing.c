#include <assert.h>
#include <errno.h>
#include <stdio.h>  // IWYU pragma: keep
#include <string.h> // IWYU pragma: keep

/*
 * Taken from
 *
 * https://stackoverflow.com/a/22732645/15847822
 * */

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_error(M, ...)                                                      \
  fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,    \
          clean_errno(), ##__VA_ARGS__)
#define assertf(A, M, ...)                                                     \
  if (!(A)) {                                                                  \
    log_error(M, ##__VA_ARGS__);                                               \
    assert(A);                                                                 \
  }
