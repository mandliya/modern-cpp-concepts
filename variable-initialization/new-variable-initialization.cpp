/**
 *  Concept 1: Variable Initialization in C++11/14
 *  NOTE Comments contain error code
 */

class ExampleClass {
public:
  ExampleClass() = default;
  ExampleClass(const ExampleClass & rhs) = default;
private:
  int m_Member;
};

int main()
{
  ExampleClass objectA;
  //ExampleClass objectB(ExampleClass()); ---> Compiler will get confused here, see readme.
  ExampleClass objectB{ ExampleClass{ } };
  return 0;
}
