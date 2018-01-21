/**
 *  Concept 3 Deducing object type.
 */

#include <iostream>
#include <typeinfo>
#include <vector>

class ExampleClass{ };

template <typename T>
void print_vector (const std::vector<T>& vec) {
  for (auto v : vec) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}

int main() {

  auto var1{ 4.5 };
  std::cout << "Type of Variable: " << typeid(var1).name() << std::endl;

  auto var2{ ExampleClass{ } };
  std::cout << "Type of Variable: " << typeid(var2).name() << std::endl;

  // C++17 Only:  std::initializer_list<int>
  auto int_initializer_list = {1, 2, 3};
  std::cout << "Type of the list:" << typeid(int_initializer_list).name() << std::endl;

  // we can initialize a vector with it.
  std::vector<int> vec = int_initializer_list;
  std::cout << "Type of the vector:" << typeid(vec).name() << std::endl;
  std::cout << "Printing int vector created with auto deduced initializer list:";
  print_vector(vec);

  // C++17 only similarly initializer list for double
  auto double_initializer_list = {1.2, 1.3 , 1.4};
  std::cout << "Type of the list:" << typeid(double_initializer_list).name() << std::endl;

  // However this would be error, as types are not of same type.
  // auto error_initializer_list = {4.5 , 5, 2.4f};

  return 0;
}
