#include "String.hh"
#include "mystring.hh"
#include <cstddef>
#include <cstring>
#include <ostream>

namespace pr {
String::String(const char *ori) : str(ori){};
size_t String::length() const { return pr::length(str); }
String::~String() { delete[] str; }
std::ostream &operator<<(std::ostream &os, const String &string) {
  os << string.str;
  return os;
}
void String::operator=(const String &other) noexcept {
  size_t len = other.length() + 1;
  char *str_c = new char[len];
  memcpy(str_c, other.str, len * sizeof(char));
  str = str_c;
}
} // namespace pr