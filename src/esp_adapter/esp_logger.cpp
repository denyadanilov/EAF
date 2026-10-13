#include "adapter/logger.h"
#include "esp_log.h"
#include <stdarg.h>

namespace eaf {

static void log_message(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

} // namespace eaf