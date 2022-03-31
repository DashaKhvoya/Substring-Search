#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

struct state {
  size_t len;
  long long link;
  std::unordered_map<char, long long> next;
  long long first_pos;
};

class SufAuto {
public:
  SufAuto(size_t max_len) : size_(0), last_(0), st_(2 * max_len) {
    st_[0].len = 0;
    st_[0].link = -1;
    st_[0].first_pos = -1;
    size_ += 1;
  }

  ~SufAuto() {}

  void AddChar(char c) {
    size_t current = size_++;
    st_[current].len = st_[last_].len + 1;
    st_[current].first_pos = st_[current].len - 1;

    long long i = 0;
    for (i = last_; i != -1 && !st_[i].next.count(c); i = st_[i].link) {
      st_[i].next[c] = current;
    }

    if (i == -1) {
      st_[current].link = 0;
    } else {
      size_t j = st_[i].next[c];

      if (st_[i].len + 1 == st_[j].len) {
        st_[current].link = j;
      } else {
        st_[size_].len = st_[i].len + 1;
        st_[size_].next = st_[j].next;
        st_[size_].link = st_[j].link;
        st_[size_].first_pos = st_[j].first_pos;

        for (; i != -1 && st_[i].next[c] == j; i = st_[i].link) {
          st_[i].next[c] = size_;
        }

        st_[current].link = size_;
        st_[j].link = st_[current].link;

        size_ += 1;
      }
    }

    last_ = current;
  }

  std::vector<state> GetSt() {
    return st_;
  }

private:
  std::vector<state> st_;
  size_t size_;
  size_t last_;
};

std::string GetInput();
void Testing(SufAuto suf_auto);
