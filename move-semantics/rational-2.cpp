/**
 *  A simple Rational number class. It prints messages to show which constructor (ctor) is being called.
 *  This version have move constructor, showing its use using std::move.
 */

#include <cstdio>
#include <string>

void message( const char * msg ) {
  puts(msg);
  fflush(stdout);
}

class Rational {
  int _n;
  int _d;
  static const int _bufsize = 128;
  mutable char * _buf = nullptr;

public:
  Rational() { reset(); message("default constructor"); }
  Rational( const int n ) : _n{ n }, _d{ 1 } { message("int constructor"); }
  Rational( const int n, const int d ) : _n{ n }, _d{ d } { message("int int constructor"); }
  Rational( const Rational & other ) : _n{ other._n }, _d{ other._d } { message("copy constructor"); }
  Rational( Rational && );
  ~Rational();
  void reset();
  inline int numerator() const { return _n; }
  inline int denominator() const { return _d; }
  Rational & operator = ( const Rational & );
  Rational operator + ( const Rational & ) const;
  Rational operator - ( const Rational & ) const;
  Rational operator * ( const Rational & ) const;
  Rational operator / ( const Rational & ) const;
  operator std::string () const;
  std::string string() const;
  const char * c_str() const;
};

Rational::Rational( Rational && other ) {
  _n = other.numerator();
  _d = other.denominator();
  other.reset();
  message("move constructor");
}

Rational::~Rational() {
  message("destructor");
  reset();
}

void Rational :: reset() {
  _n = 0;
  _d = 1;
  delete[] _buf;
  _buf = nullptr;
}

Rational & Rational::operator = ( const Rational & rhs ) {
  if ( this != &rhs ) {
    _n = rhs.numerator();
    _d = rhs.denominator();
  }
  message("assignment operator");
  return *this;
}

Rational Rational::operator + ( const Rational & rhs ) const {
  return Rational( (_n * rhs._d) + (_d * rhs._n),  (_d * rhs._d) );
}

Rational Rational::operator - ( const Rational & rhs ) const {
  return Rational( (_n * rhs._d) - (_d * rhs._n),  (_d * rhs._d) );
}

Rational Rational::operator * ( const Rational & rhs ) const {
  return Rational( (_n * rhs._n), (_d * rhs._d) );
}

Rational Rational::operator / ( const Rational & rhs ) const {
  return Rational( (_n * rhs._d), (_d * rhs._n) );
}

Rational::operator std::string() const {
  return string();
}

std::string Rational::string() const {
  return std::string{ c_str() };
}

const char * Rational::c_str() const {
  if( !_buf ) {
    _buf = new char[_bufsize];
  }
  snprintf(_buf, _bufsize, "%d/%d", _n, _d);
  return _buf;
}


int main( int argc, char ** argv ) {

    Rational a = 7;     // 7/1
    Rational b(5, 3);   // 5/3
    Rational c = b;     // copy ctor
    Rational d = std::move(c);

    printf("a is: %s\n", a.c_str());
    printf("b is: %s\n", b.c_str());
    printf("c is: %s\n", c.c_str());
    printf("d is: %s\n", d.c_str());

    printf("%s + %s is %s\n", a.c_str(), b.c_str(), Rational(a + b).c_str());

    return 0;
}
