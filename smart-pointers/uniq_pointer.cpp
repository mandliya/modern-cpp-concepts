/**
 *  Demonstration of uniq smart pointer.
 */

#include "String.h"
#include <memory>
#include <iostream>


using String = learn::String;

void debug( const char * s ) {
  std::cout << std::endl <<  s << std::endl;
}

void dump( std::unique_ptr<String> & s ) {
  if ( s ) {
    puts(s->cstr());
  } else {
    puts("null");
  }
}

namespace learn {
  template <typename T, typename P>
  std::unique_ptr<T> make_unique( P initializer ) {
    return std::unique_ptr<T>{ new T{initializer} };
  }
}


int main()
{
  debug("Creating unique pointer 1 ");
  std::unique_ptr<String> p1{ new String("one") };
  dump(p1);

  debug("Make unique pointer 2 ");
  auto p2 = learn::make_unique<String>("two");
  dump(p2);


  debug("Reset pointer 1 to three ");
  p1.reset( new String{"three"} );
  dump(p1);
  dump(p2);

  debug("Move pointer 2 to  pointer 3 ");
  auto p3 = std::move(p2);
  dump(p1);
  dump(p2);
  dump(p3);

  debug("Reset pointer 1 ");
  p1.reset();
  dump(p1);
  dump(p2);
  dump(p3);

  debug("Reset pointer 3 ");
  p3.reset();
  dump(p1);
  dump(p2);
  dump(p3);

  std::cout << "Done!" << std::endl;
  return 0;
}
