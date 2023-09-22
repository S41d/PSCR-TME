#pragma once
#include <cstring>
#include <ostream>

namespace pr {
class String {
  const char *str;

public:
  String(const char *ori = "");
  ~String();
  size_t length() const;
  friend std::ostream &operator<<(std::ostream &os, const String &string);
  void operator=(const String &string) noexcept;
};

std::ostream &operator<<(std::ostream &os, const String &string);
} // namespace pr