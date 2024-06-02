//Autor: Álvaro Ramos Fustero ~ 855798

#include "rational.h"

// Auxiliares

int Rational::mcd(int a, int b)
{
	return ( b == 0 ? a : mcd(b,a%b));
}

void Rational::reduce()
{
	unsigned int aux = mcd(this->num, this->den);
	this->num=this->num/aux;
	this->den=this->den/aux; 
}

// Constructores

Rational::Rational()
{
	num = 0;
	den = 1;
}

Rational::Rational(int num, int den)
{
	this->num = num;
        this->den = den;
        reduce();
}

// Operadores aritmeticos

Rational Rational::operator+(const Rational &r) const
{
	Rational res;
	res.num=(r.num*this->den)+(this->num*r.den);
	res.den = r.den*this->den;
	res.reduce();
	return res;
}

Rational Rational::operator-(const Rational &r) const
{
	Rational res;
	res.num=(r.num*this->den)-(this->num*r.den);
	res.den = r.den*this->den;
	res.reduce();
	return res;
}

Rational operator*(const Rational &r1, const Rational &r2)
{
	Rational res;
	res.num = r1.num * r2.num;
	res.den = r1.den * r2.den;
	res.reduce();
	return res;
}

Rational operator/(const Rational &r1, const Rational &r2)
{
	Rational res;
	res.num = r1.num * r2.den;
	res.den = r1.den * r2.num;
	res.reduce();
	return res;
}
// Operadores logicos

bool Rational::operator==(const Rational& r) const
{
	int producto1 = r.num * this->den;
	int producto2 = this->num * r.den;
	return producto1 == producto2;
}

bool Rational::operator<(const Rational& r) const
{
	int producto1 = r.num * this->den;
	int producto2 = this->num * r.den;
	return producto1 < producto2;
}

bool Rational::operator>(const Rational& r) const
{
	int producto1 = r.num * this->den;
	int producto2 = this->num * r.den;
	return producto1 > producto2;
}



// Entrada/salida
std::istream &operator>>(std::istream &is, Rational &r)
{
    is >> r.num;
    is.ignore(100,'/');
    is >> r.den;
    r.reduce();
    return is;
}

std::ostream &operator<<(std::ostream &os, const Rational &r)
{
    os << r.num << "/" << r.den;
    return os;
}



