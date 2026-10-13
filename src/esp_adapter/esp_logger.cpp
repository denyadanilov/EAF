#include "adapter/logger.hpp"
#include <stdarg.h>
#include <stdio.h>

namespace eaf {

void log_message(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
}

} // namespace eaf