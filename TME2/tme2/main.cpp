#include <chrono>
#include <cstddef>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

template <typename K, typename V>

class HashTable {
public:
  struct entry {
    const K key;
    V value;
    entry(K key, V value) : key(key), value(value) {}
  };

  std::vector<std::forward_list<entry>> vec;
  size_t _size;
  size_t _capacity;

  HashTable<K, V>(size_t sz) {
    _size = 0;
    _capacity = sz;
    for (size_t i = 0; i < _capacity; ++i) {
      std::forward_list<entry> tmp;
      vec.push_back(tmp);
    }
  }

  V *get(const K &key) {
    for (auto &entry_list : vec) {
      for (entry &e : entry_list) {
        if (e.key == key) {
          return &(e.value);
        }
      }
    }
    return nullptr;
  }

  bool put(const K &key, const V &value) {
    entry e(key, value);

    _size++;
    grow();
    for (std::forward_list<entry> &entry_list : vec) {
      if (!entry_list.empty() && entry_list.front().key == key) {
        entry_list.push_front(e);
        return true;
      }
    }

    std::forward_list<entry> entry_list;
    entry_list.push_front(e);
    vec.push_back(entry_list);
    return false;
  }

  size_t size() const { return _size; }

  void grow() {
    int capacity_limit = 80 * _capacity / 100;
    if (_size > capacity_limit) {
      for (size_t i = _capacity; i < _capacity * 2; ++i) {
        std::forward_list<entry> tmp;
        vec.push_back(tmp);
      }
      _capacity *= 2;
    }
  }
};

bool contains(const std::vector<std::string> vec, std::string target) {
  for (std::string word : vec) {
    if (word == target)
      return true;
  }
  return false;
}

void add_occurence(std::vector<std::pair<std::string, int>> &vec,
                   std::string target) {
  bool found = false;
  for (auto &entry : vec) {
    if (entry.first == target) {
      entry.second += 1;
      found = true;
      break;
    }
  }
  if (!found) {
    std::pair<std::string, int> p;
    p.first = target;
    p.second = 1;
    vec.push_back(p);
  }
}

int occurences_number(const std::vector<std::pair<std::string, int>> vec,
                      std::string target) {
  for (std::pair<std::string, int> entry : vec) {
    if (entry.first == target) {
      return entry.second;
    }
  }
  return 0;
}

int main() {
  using namespace std;
  using namespace std::chrono;

  ifstream input = ifstream("./WarAndPeace.txt");

  auto start = steady_clock::now();
  cout << "Parsing War and Peace" << endl;

  size_t nombre_lu = 0;
  // prochain mot lu
  string word;
  // une regex qui reconnait les caractères anormaux (négation des lettres)
  regex re(R"([^a-zA-Z])");

  // vector<string> mots_uniques;
  // vector<std::pair<string, int>> occurences;

  auto hashtable = HashTable<std::string, int>(10000);

  while (input >> word) {
    // élimine la ponctuation et les caractères spéciaux
    word = regex_replace(word, re, "");
    // passe en lowercase
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    // word est maintenant "tout propre"
    // -- vector string --
    // if (!contains(mots_uniques, word)) {
    //   mots_uniques.push_back(word);
    // }
    // -- vector pair string --
    // add_occurence(occurences, word);
    // -- hashtable
    // if (auto v = hashtable.get(word)) {
    //   hashtable.put(word, *v + 1);
    // } else {
      hashtable.put(word, 1);
    // }

    if (nombre_lu % 100 == 0)
      // on affiche un mot "propre" sur 100
      cout << nombre_lu << ": " << word << endl;
    nombre_lu++;
  }
  input.close();

  cout << "Finished Parsing War and Peace" << endl;

  auto end = steady_clock::now();
  cout << "Parsing took " << duration_cast<milliseconds>(end - start).count()
       << "ms.\n";

  cout << "Found a total of " << nombre_lu << " words." << endl;
  // cout << "Found a total of " << mots_uniques.size() << " unique words." <<
  // endl;
  // cout << "Nb occurence de \"war\": " << occurences_number(occurences, "war")
  //      << endl;
  // cout << "Nb occurence de \"peace\": "
  //      << occurences_number(occurences, "peace") << endl;
  // cout << "Nb occurence de \"toto\": " << occurences_number(occurences,
  // "toto")
  //      << endl;

  return 0;
}
