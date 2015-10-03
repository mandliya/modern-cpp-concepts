/**
 *  A simple Rational number class. It prints messages to show which constructor (ctor) is being called.
 *  This version does not have move constructor, it is just showing how things are before using move semantics.
 */

#include <cstdio>
#include <string>

void message( const char * s ) {
  puts(s);
  fflush(stdout);
}

class Rational {
  int _n;                               // numerator
  int _d;                               // denominator
  static const int _bufsize = 128;      // c_str buffer size
  mutable char * _buf = nullptr;        // c_str buffer

public:
  //default constructor
  Rational() {
    reset();
    message("default contructor");
  }
  //int constructor
  Rational( int n )
    : _n{ n }, _d{ 1 } {
    message("int constructor");
  }
  //int, int constructor
  Rational( int n, int d )
    : _n{ n }, _d{ d } {
    message("int, int constructor");
  }
  //copy constructor
  Rational( const Rational & other )
    : _n{ other._n }, _d{ other._d} {
    message("copy constructor");
  }
  //destructor
  ~Rational();
  //reset
  void reset();
  //numerator
  inline int numerator() const {
    return _n;
  }
  //denominator
  inline int denominator() const {
    return _d;
  }
  //operator =
  Rational& operator = ( const Rational & );

  //operator +
  Rational operator + ( const Rational & ) const;
  //operator -
  Rational operator - ( const Rational & ) const;
  //operator *
  Rational operator * ( const Rational & ) const;
  //operator /
  Rational operator / ( const Rational & ) const;

  //operator std::string()
  operator std::string() const;
  //std::string string()
  std::string string() const;
  //const char * c_str()
  const char * c_str() const;
};

Rational :: ~Rational() {
  message("destructor");
  reset();
}

void Rational :: reset() {
  _n = 0;
  _d = 1;
  delete[] _buf;
  _buf = nullptr;
}

Rational & Rational :: operator = ( const Rational & rhs ) {
  message("assignment operator");
  if ( this != &rhs ) {
    _n = rhs.numerator();
    _d = rhs.denominator();
  }
  return *this;
}

Rational Rational :: operator + ( const Rational & rhs ) const {
  return Rational( (_n * rhs._d) + (_d * rhs._n), _d * rhs._d );
}

Rational Rational :: operator - ( const Rational & rhs ) const {
  return Rational( (_n * rhs._d) - (_d * rhs._n), _d * rhs._d );
}

Rational Rational :: operator * ( const Rational & rhs ) const {
  return Rational( (_n * rhs._n), (_d * rhs._d) );
}

Rational Rational :: operator / ( const Rational & rhs ) const {
  return Rational( (_n * rhs._d), (_d * rhs._n) );
}

Rational :: operator std::string() const {
  return string();
}

std::string Rational::string() const {
  return std::string{ c_str() };
}

const char * Rational :: c_str() const {
  if ( !_buf ) {
    _buf = new char[_bufsize]();
  }
  snprintf(_buf, _bufsize, "%d/%d", _n, _d);
  return _buf;
}

int main() {
  Rational a = 8;                               // 7/1
  Rational b( 5, 3 );                           // 5/3
  Rational c = b;                               // copy constructor
  Rational d;                                   // default constructor

  printf("a is: %s\n", a.c_str());
  printf("b is: %s\n", b.c_str());
  printf("c is: %s\n", c.c_str());
  printf("d is: %s\n", d.c_str());

  printf("%s + %s is %s\n", a.c_str(), b.c_str(), Rational(a + b).c_str());

  return 0;
}
