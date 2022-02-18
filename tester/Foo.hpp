#ifndef __FOO_HPP
#define __FOO_HPP

#include <iostream>

class Foo
{
private:

	int _n;

public:

	Foo(int n) : _n(n) {}
	Foo(const Foo& x) { *this = x; }
	~Foo() {}

	Foo& operator=(const Foo& x) { _n = x.getN(); return *this; }

	const int &getN() const { return _n; }

};

bool operator==(const Foo& lhs, const Foo& rhs) { return lhs.getN() == rhs.getN();}
bool operator!=(const Foo& lhs, const Foo& rhs) { return lhs.getN() != rhs.getN();}
bool operator<(const Foo& lhs, const Foo& rhs) { return lhs.getN() < rhs.getN();}
bool operator<=(const Foo& lhs, const Foo& rhs) { return lhs.getN() <= rhs.getN();}
bool operator>(const Foo& lhs, const Foo& rhs) { return lhs.getN() > rhs.getN();}
bool operator>=(const Foo& lhs, const Foo& rhs) { return lhs.getN() >= rhs.getN();}

std::ostream & operator<<(std::ostream &o, const Foo& x)
{
	o << x.getN();
	return o;
}

#endif