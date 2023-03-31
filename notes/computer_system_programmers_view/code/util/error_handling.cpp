#include "error_handling.h"

#include <fmt/format.h>

#include <iostream>
#include <cstdlib>
#include <cstring>

#include <netdb.h> // for h_errno

extern int h_errno;    /* defined by BIND for DNS errors */

void unix_error(std::string_view msg) /* unix-style error */
{
  std::cerr << fmt::format("{}: {}\n", msg, std::strerror(errno));
  exit(0);
}

void posix_error(int code, std::string_view msg) /* posix-style error */
{
  std::cerr << fmt::format("{}: {}\n", msg, std::strerror(code));
  exit(0);
}

void dns_error(std::string_view msg) /* dns-style error */
{
  std::cerr << fmt::format("{}: DNS error {}\n", msg, h_errno);
  exit(0);
}

void app_error(std::string_view msg) /* application error */
{
  std::cerr << fmt::format("{}\n", msg);
  exit(0);
}
