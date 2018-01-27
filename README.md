## Modern C++ Concepts

### Concept 1 : Variable Initialization in C++11/14 ([Code](variable-initialization))

#### C++ Parsing Problem

```c++
class ExampleClass {
  private:
    int m_Member;
  public:
    ExampleClass() = default;
    MyClass( const MyClass& rhs) = default;
};

int main()
{
  ExampleClass objectA;
  ExampleClass objectB(ExampleClass()); // <----- Parasing this line is the reason for error
  return 0;
}

```

Above code fails to compile because compiler confuses the declaration of objectB. A C++ compiler will not consider it as defining a variable named objectB of type ExampleClass calling a constructor that takes the object constructed by calling the ExampleClass constructor. Instead compiler will this think this line as a function named objectB which returns ExampleClass object and takes an unnamed function pointer that returns a ExampleClass object and does not take any parameters. Clang compiler lets you know of potential disambiguation.

```c++
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

#### Uniform Initialization

To fix this, C++11 has provided **Uniform Initialization**. The code with uniform initialization will look like this.

```c++
class ExampleClass {
  private:
    int m_Member;
  public:
    ExampleClass() = default;
    MyClass( const MyClass& rhs) = default;
};

int main()
{
  ExampleClass objectA;
  ExampleClass objectB{ ExampleClass{} }; // <----- Notice this initialization.
  return 0;
}

```
Boom! Compiler is no more confused.


#### Narrowing Conversion
**Uniform initialization** also prevent narrowing conversion. Lets take this example.

```c++
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

```c++
#include <iostream>

int main()
{
  int anInt{ 100 };
  char aChar{ static_cast<char>(512) };
  double aDouble{ 1.0 };
  float aFloat{ static_cast<float>(aDouble) };
  return 0;
}
```

This will be compiled easily.

### Concept 2 : Initializer Lists ([code](initializer-lists))

Initialization lists are used when you want to construct objects from multiple objects of a given type. C++11 provides initialization lists for this. We can supply many objects of same time together to a constructor. Initializer list are built upon [uniform initialization](variable-initialization/new-variable-initialization.cpp). Let's see following vector example.

```c++
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> vectorA(1);
  std::cout << "vectorA size: " << vectorA.size()
            << " vectorA[0]: " << vectorA[0] << std::endl;
  std::vector<int> vectorB(1, 10);
  std::cout << "vectorB size: " << vectorB.size()
            << " vectorB[0]: " << vectorB[0] << std::endl;
  return 0;
}
```
As we are used to initialize various objects in C++, example
```c++
int myInt(12);
```
Here *myInt* will hold value 12, however *vectorA* variable will be initialized with a single integer containing 0. Like *myInt*, we might expect it would contain a single integer containing 1 but that would be incorrect. **The first parameter to vector constructor determines the how many values initial vector would be storing.** In this case, we are asking it to store 1 value.
Similarly, *vectorB(1, 10)* is declaration of vector with size 1 and *vectorB[0]* will be 10. Parameter 2 specifies a value to use to instantiate the members of the vector rather than using the default value.

Hmm, so how do we initialize a vector with multiple values. For that, we use initialization-lists.

```c++
std::vector<int> vectorC{ 1, 10 }
```
*vectorC* here is initialized using **uniform initialization**. *vectorC* will be of size 2 and *vectorC[0]* would be 1, and *vectorC[1]* would be 10.  We could have also used explicit initialization list to initialize. Example:

```c++
std::initializer_list<int> aList{ 1, 10 };
std::vector<int> vectorD( aList ); // or std::vector<int> vectorD{ aList };
```
The vector constructor implicitly creates a initializer_list when we initialized *vectorC* using uniform initialization.

### Concept 3 : Deducing type of the object. ([code](type-deduction))

Modern C++ provides type deduction for determining the type of objects. It provides *auto* keyword and *typeid* method to determine types. Example.

```c++
#include <iostream>

int main()
{
  auto variable = 5.5;
  std::cout << "Type of Variable: " << typeid(variable).name() << std::endl;
  return 0;
}
```
We will see output of above program ( on clang )
```c++
Type of Variable: d
```

**d** here is clang's internal representation of **double** type. If you pass the above output of *c++filt* you will see the output as

```
Ravis-MacBook-Pro:type-deduction mandliya$ ./run | c++filt -t
Type of Variable: double
```
So what happened here. **auto** keyword based on the initializing object determined that variable is of type double. (Since we initialized variable with 5.5), and **typeid** provided us the internal type compiler assigned to variable which is than later translated by *c++filt*.

### auto for user created object types.
Let's use *auto* for user created objects.

```c++
#include <iostream>
#include <typeinfo>

class ExampleClass { };

int main()
{
  auto var = ExampleClass();
  std::cout << "Type of Variable: " << typeid(var).name() << std::endl;
  return 0;
}
```
Here the var is of type *ExampleClass* and using *c++filt* we get exactly that

```c++
Ravis-MacBook-Pro:type-deduction mandliya$ ./run | c++filt -t
Type of Variable: ExampleClass
```

#### auto with initializer list ([code](type-deduction/auto-initializer-list.cpp))

In previous compiler versions, If our object is initialized using initializer list (or to say using *uniform initialization*), then auto won't be that helpful. For example

```c++
auto var1{ 4.5 };
auto var2{ ExampleClass{ } };
```
used to give output of 

```c++
std::cout << "Type of Variable: " << typeid(var1).name() << std::endl;
std::cout << "Type of Variable: " << typeid(var2).name() << std::endl;
```
as 

```c++
Ravis-MacBook-Pro:type-deduction mandliya$ ./run | c++filt -t
Type of Variable: std::initializer_list<double>
Type of Variable: std::initializer_list<ExampleClass>
```

However, after feedback, this is now changed to:

```c++
Ravis-MBP:type-deduction mandliya$ ./run | c++filt -t
Type of Variable: double
Type of Variable: ExampleClass
```

so for more than one elements,  auto will detect them as appropriate initializer list.


```c++
auto int_initializer_list = {1, 2, 3};
auto double_initiazer_list = {1.4, 1.2, 4.5};
std::cout << "Type of the list:" << typeid(int_initializer_list).name() << std::endl;
std::cout << "Type of the list:" << typeid(double_initializer_list).name() << std::endl;
```
Their types are deduced to:

```c++
Type of the list:std::initializer_list<int>
Type of the list:std::initializer_list<double>
```

This is error as compiler will not be able to determine the type.
```c++
auto error_initializer_list = {4.5 , 5, 2.4f};
```

Complete example is [here](type-deduction/auto-initializer-list.cpp) whose output in clang using c++filt

```c++
Ravis-MBP:type-deduction mandliya$ ./run | c++filt -t
Type of Variable: double
Type of Variable: ExampleClass
Type of the list:std::initializer_list<int>
Type of the vector:std::__1::vector<int, std::__1::allocator<int> >
Printing int vector created with auto deduced initializer list:1 2 3
Type of the list:std::initializer_list<double>
``` 

#### auto with functions

Below code snippet will only work in **C++14** and later.
```c++
#include <iostream>

template <typename T>
auto doSomething( T parameter )
{
  return parameter;
}

int main()
{
  std::cout << "Type of Variable: " << typeid(doSomething(1.5)).name() << std::endl;
  return 0;
}
```

*doSomething* returns a double type in this call. In C++11 we will get this error.

```
Ravis-MacBook-Pro:type-deduction mandliya$ g++ -Wall -pedantic -Wextra -o run -std=c++11 auto-with-functions.cpp
auto-with-functions.cpp:9:1: error: 'auto' return without trailing return type;
      deduced return types are a C++14 extension
auto doSomething( double parameter )
```

#### auto with function and trailing return-type

Another way to determine type of returning value of a function is using **decltype**. This method will work with C++11 and later.

```c++
template <typename T>
auto doSomethingAgain( T parameter )->decltype(parameter)
{
  return parameter;
}
```

Here we are using a *trailing return type* to decide return type of object. **decltype** is used to tell the compiler to use the type of a given expression. The expression can be a variable name however we could also give a function here and decltype would deduce the type returned from the function.

### Concept 4 : Move semantics ([code](move-semantics/))
Move semantics is one of the most powerful features introduced in C++11. Consider this code example.
```c++
T func(T o) {
  //do something with o
  return o
}
```

This function is using concept of **call by value**. When this function is called, an object copy of 'o' of type T is constructed. And since it also returns an object of type T, another copy of 'o' is constructed for the return value. Thus for a call of *func* two new objects of type T are constructed. First one is temporary object which is destroyed as we return. (Objects are destroyed when control flow moves out of scope in which object was created.)

What if, instead of creating new temporary object, we move data from one object to other directly. Let us understand first what are **rvalues** and **lvalues** in C++. Traditionally, any expression that **can appear** on the left side of an assignment is termed as *lvalue*. Likewise, an expression that **may only** appear on the right side is called *rvalue*. Note again that lvalue *can appear* on the left side of an assignment. It may also appear on the right side, but it's still an lvalue because it would be legal for it to appear on the left. That is how both lvalues and rvalues got their name. Specific to move semantics, we are discussing here, an rvalue can be *moved*.

```c++
a = b // a is lvalue and b is rvalue
a =  b + c;
//  ^ A nameless value
```

A temporary value that is ready to expire, it is also called an **xvalue** or an *expiring* value. A literal value is sometimes called **pure rvalue** or **prvalue**.
```
a = 42;
// a is lvalue, 42 is prvalue.
```
 Typically *prvalue* category includes literal values and anything returned from a function that is not a reference. The one thing all of these type categories have in common is that they can be moved.

 The C++ library provides a template function called move. It's used to tell the compiler to use an object as if it were an rvalue, which means that it makes it moveable. Let's see an example.

 ```c++
 #include <iostream>
 #include <vector>

 void printVec(std::vector<std::string> vec) {
     std::cout << "Vector size:" << vec.size() << std::endl;
     for (auto & str : vec ) {
         std::cout << str << " ";
     }
     std::cout << std::endl;
 }


 int main(int argc, const char * argv[]) {

     std::vector<std::string> vec1{ "One", "Two", "Three", "Four", "Five" };
     std::vector<std::string> vec2{ "Six", "Seven", "Eight", "Nine", "Ten" };

     //before move
     printVec(vec1);
     printVec(vec2);

     vec2 = std::move(vec1);
     std::cout << "Using std::move" << std::endl;

     //before move
     printVec(vec1);
     printVec(vec2);


     return 0;
 }

 ```
Following is the output of above program
```C++
Vector size:5
One Two Three Four Five
Vector size:5
Six Seven Eight Nine Ten


Using std::move

Vector size:0

Vector size:5
One Two Three Four Five
```
Clearly, contents of *vec1* are moved to *vec2* and *vec1* has become empty. *std::move* expects an argument which is castable to rvalue. Here, vector is castable. The other side of the equals sign, the thing that it's being moved to must support a move copy and in this case, vec2 does.

Now, let's take another example, lets create our own swap function using std::move.

```c++
template<typename T>
void swap(T & a, T & b)
{
    T tmp(std::move(a));
    a(std::move(b));
    b(std::move(tmp));
}
```

Instead of calling *vec2 = std::move(vec1)* in above program, if we call *swap(vec1, vec2)*, The output would be like this

```c++
Vector size:5
One Two Three Four Five
Vector size:5
Six Seven Eight Nine Ten


Using std::move

Vector size:5
Six Seven Eight Nine Ten
Vector size:5
One Two Three Four Five
```

See, the contents of two vectors are swapped. *Tmp* in swap is destroyed once we move out of scope, however, in the swap, we did not actually copy anything, we just moved things around.

We will get back to move semantics again.

### Concept 5 : Easier nested namespace syntax (C++17) ([code](easier-nested-namespace/easier-nested-namespace.cpp)))

The usual way of nested namespace syntax till C++14 is:
```c++
namespace game {
  namespace engine {
    namespace player {
      namespace action {
        int move;
      }
    }
  }
}
```
For a larger application, this could get a little cumbersome. In c++ 17, the easier nested namespace syntax is introduced. So the above nested namespace could be declared as:
```c++
namespace game::engine::player::action {
  int move;
}
```
Complete example could be found [here](easier-nested-namespace/easier-nested-namespace.cpp).

### Concept 6: Static Assert at compile time. ([code](static_assert/static_assert.cpp))

C++11 introduced static assert for compile time check. This helps in doing compile time checks to avoid building linking and then running to eventually fail some assumptions about the piece of code, or compiler behavior etc. For example checking for a version of a library which is declared as static const.

```c++
static const int major_version = 2;
```
Say version 3 of the library has new functions, and you need them for your project but you downloaded version 2 project. Now you compile your project,and the lib project link it and then eventually fail after 30 minutes.

Instead the below check would fail at compile time.

```c++
static_assert(lib::major_version > 2, "You are using version less than 2, which might not have newer functionalities");
```
C++11 had a compulsory requirement for second argument, as string literal message, however C++17 has relaxed this requirement and made it optional. Now if you don't provide the argument, compiler will print a default message.

```c++
const int x = 3;
const int y = 4;
static_assert(x == y, "x should be equal to y); // This will not fail.
static_assert(x > y, "x should be greater than y"); // This will fail at compile time.

// This will work in C++17 but not in C++11 or C++14.
static_assert(x < y);
```

Complete code example is [here](static_assert/static_assert.cpp). The compile time errors look like this.
```c++
Ravis-MBP:static_assert mandliya$ g++ -Wall -Wpedantic -o run -std=c++1z static_assert.cpp
static_assert.cpp:12:5: error: static_assert failed "x should be greater than y"
    static_assert(x > y, "x should be greater than y");
    ^             ~~~~~
static_assert.cpp:15:5: error: static_assert failed
    static_assert(x < y);
    ^             ~~~~~
2 errors generated.
```
### Concept 7: std::invoke
std::invoke is used to call functions, function pointers, and member pointers with the same syntax. This is generally called to any [Callable](http://en.cppreference.com/w/cpp/concept/Callable) object with/out parameters.

Example: 
```c++
void print_num(int i)
{
    std::cout << i << '\n';
}

.
.
.
 std::invoke(print_num, 10);
```
