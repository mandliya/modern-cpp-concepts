/**
 *  A rudimentary string class for demonstrating smart pointer use
 */

#include <iostream>
#include <memory>
#include "String.h"


using String = learn::String;

void String::print( const char * s ) {
  if ( data ) {
    std::cout << __string_class << " : " << s << " (" << data << ")" << std::endl;
  } else {
    std::cout << __string_class << " : " << s << std::endl;
  }
}

size_t String::strlen( const char * s ) {
  size_t n;
  const char * e;
  for ( e = s, n = 0; *e && n < _maxlen; e++, n++ );
  return n;
}

String::String() : data{ nullptr } {
  print("Default Constructor" );
}

String::String( const char * s ) {
  size_t slen = strlen(s);
  data = new char[ slen + 1 ];
  data[ slen ] = '\0';
  memcpy( data, s, slen );
  print( "Cstring Constructor" );
}

String::String( const String & str ) {
  size_t slen = strlen( str.data );
  data = new char[ slen + 1 ];
  data[ slen ] = '\0';
  memcpy( data, str.data, slen );
  print( "Copy Constructor" );
}

String::String( String && str ) {
  data = std::move( str.data );
  str.data = nullptr;
  print( "Move Constructor" );
}

String::~String() {
  print( "Destructor" );
  delete[] data;
}

String & String::operator = ( String str ) {
  swap( str );
  print( "Copy and Swap = " );
  return *this;
}

const char * String::cstr() const {
  return data;
}

String::operator const char * () const {
  return cstr();
}

void String::swap( String & str ) {
  std::swap( this->data, str.data );
}
