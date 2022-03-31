#include "task.hpp"

int main() {
  std::string text = GetInput();
  if (text == "ERROR") {
    return -1;
  }

  SufAuto suf_auto(text.length());
  for (size_t i = 0; i < text.length(); ++i) {
    suf_auto.AddChar(text[i]);
  }

  Testing(suf_auto);
  return 0;
}

std::string GetInput() {
  std::string file_name;
  std::cout << "Enter your file name please: ";
  std::cin >> file_name;
  std::ifstream input(file_name);

  if (!input.is_open()) {
    std::cout << "ERROR: file" << file_name << "not find" << std::endl;
    input.close();
    return "ERROR";
  }

  std::string text;
  getline(input, text, '\0');
  input.close();
  return text;
}

void Testing(SufAuto suf_auto) {
  size_t tests = 3;
  std::string str[] = {"A platform",
                            "or",
                            "First Clown"};
  size_t true_ans[] = {10, 5, 132658};

  size_t v = 0;
  size_t ans = 0;
  for (size_t i = 0; i < tests; ++i) {
    v = 0;
    for (size_t j = 0; j < str[i].length(); ++j) {
      v = suf_auto.GetSt()[v].next[str[i][j]];
    }

    ans = suf_auto.GetSt()[v].first_pos - str[i].length() + 1;
    if (ans == true_ans[i]) {
      std::cout << "TEST_" << i << " SUCCESS" << std::endl;
    } else {
      std::cout << "TEST_" << i << " FAIL" << std::endl;
    }
  }
}
