## C++ Parsing Problem

```
class ExampleClass {
  private:
    int m_Member;
  public:
    ExampleClass() = default
    MyClass( const MyClass& rhs) = default
};

int main()
{
  ExampleClass objectA;
  ExampleClass objectB(ExampleClass()); // <----- Parasing this line is the reason for error
  return 0;
}

```

Above code fails to compile because compiler confuses the declaration of objectB. A C++ compiler will not consider it as defining a variable named objectB of type ExampleClass calling a constructor that takes the object constructed by calling the ExampleClass constructor. Instead compiler will this think this line as a function named objectB which returns ExampleClass object and takes an unnamed function pointer that returns a ExampleClass object and does not take any parameters. Clang compiler lets you know of potential disambiguation.

```
main.cpp:14:20: warning: parentheses were disambiguated as a function
      declaration [-Wvexing-parse]
    MyClass objectB(MyClass());
            ^~~~~~~~~~~
main.cpp:14:21: note: add a pair of parentheses to declare a variable
    MyClass objectB(MyClass());
                    ^
                    (        )
```

Weird ha!

###Uniform Initialization

To fix this, C++11 has provided *Uniform Initialization*. The code with uniform initialization will look like this.

```
class ExampleClass {
  private:
    int m_Member;
  public:
    ExampleClass() = default
    MyClass( const MyClass& rhs) = default
};

int main()
{
  ExampleClass objectA;
  ExampleClass objectB{ ExampleClass{} }; // <----- Notice this initialization.
  return 0;
}

```
Boom! Compiler is no more confused.


###Narrowing Conversion
*Uniform initialization* also prevent narrowing conversion. Lets take this example.

```
#include <iostream>

int main()
{
  int anInt{ 100 };
  char aChar{ 512 };   // --> Danger Will Robinson!
  double aDouble{ 1.0 };
  float aFloat{ aDouble }; // --> Error! Abort!
  return 0;
}

```

This code will not compile, and compiler will throw bunch of errors. If we look carefully at the lines with comments above we can see that we are implicitly trying to do narrowing conversion.  A char type can store a maximum value of 255, therefore the value 512 would be narrowed into this data type. A C++11 or newer compiler will not compile this code. Similarly, the initialization of the float from a double type is also a narrowing conversion. To overcome this we use *static_cast<type>* to let compiler know that narrowing conversion are intentional.

```
#include <iostream>

int main()
{
  int anInt{ 100 };
  char aChar{ static_cast<char>(512) }
  double aDouble{ 1.0 }
  float aFloat{ static_cast<float>(aDouble) }
  return 0;
}
```

This will be compiled easily.
