/**
 *  A rudimentary string class, to be used for demonstration of smart pointers.
 */

#ifndef STRING_H
#define STRING_H

#include <cstddef>

namespace learn {
  static const char *__string_class = "str";
  static const char *__string_version = "1.0";

  class String {
    static const size_t _maxlen = 10240;
    char * data = nullptr;
    void print( const char * s );
    size_t strlen( const char * s );

  public:
    String();
    size_t length();
    String( const char * s );
    String( const String & str );
    String( String && str );
    ~String();
    String & operator = ( String str );
    const char * cstr() const;
    operator const char * () const;
    void swap( String & str );

  };
}

#endif
