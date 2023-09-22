#include "List.h"
#include "String.hh"
#include <cstring>
#include <iostream>
#include <string>

int main_ori() {
  std::string abc = "abc";
  char *str = new char[4];
  str[0] = 'a';
  str[1] = 'b';
  str[2] = 'c';
  str[3] = '\0';
  size_t i = 0;

  if (!strcmp(str, abc.c_str())) {
    std::cout << "Equal !" << std::endl;
  }

  pr::List list;
  list.push_front(abc);
  list.push_front(abc);

  std::cout << "Liste : " << list << std::endl;
  std::cout << "Taille : " << list.size() << std::endl;

  // Affiche à l'envers
  for (i = list.size() - 1; i >= 0 && i < list.size(); --i) {
    std::cout << "elt " << i << ": " << list[i] << std::endl;
  }

  // liberer les char de la chaine
  // for (char *cp = str; *cp; cp++) {
  //   delete cp;
  // }
  // et la chaine elle meme
  delete[] str;
  return 0;
}

void main_string() {
  char *str = new char[4];
  str[0] = 'a';
  str[1] = 'b';
  str[2] = 'c';
  str[3] = '\0';
  pr::String strn = pr::String(str);
  pr::String strn_c = strn;
  std::cout << strn.length() << std::endl;
  std::cout << strn << std::endl;
  std::cout << &strn << std::endl;
  std::cout << strn_c.length() << std::endl;
  std::cout << strn_c << std::endl;
  std::cout << &strn_c << std::endl;
}

int main() {
  main_string();
}