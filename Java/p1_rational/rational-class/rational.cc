//Autor: Álvaro Ramos Fustero ~ 855798

#include "rational.h"

//Problema con operaciones, no son compatibles. uwuwuwu


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

// Entrada/salida

void Rational::write(std::ostream& out) const
{
	out<<this->num<<"/"<<this->den<<"\n"<<std::flush;
}

Rational Rational::read(std::istream& is){
	std::string expresion;
	is>>this->num;
	is.ignore(100,'/');
	is>>this->den;
	return *this;
}

// Operaciones aritmeticas

Rational Rational::add(const Rational &r)
{
	Rational res;
	res.num=(r.num*this->den)+(this->num*r.den);
	res.den = r.den*this->den;
	res.reduce();
	return res;
}

Rational Rational::sub(const Rational &r)
{
	Rational res;
	res.num=(r.num*this->den)-(this->num*r.den);
	res.den = r.den*this->den;
	res.reduce();
	return res;
}


Rational Rational::mul(const Rational &r)
{
	Rational res;
	res.num=r.num*this->num;
	res.den =r.den*this->den; 
	res.reduce(); 
	return res;
}

Rational Rational::div(const Rational &r)
{
	Rational res;
	res.num=r.num*this->den;
	res.den =r.den*this->num;   
	res.reduce();
	return res;
}

// Operaciones logicas

bool Rational::equal(const Rational &r)
{
	int producto1 = r.num * this->den;
	int producto2 = this->num * r.den;
	return producto1 == producto2;
}

bool Rational::lesser_than(const Rational &r)
{
	int producto1 = r.num * this->den;
	int producto2 = this->num * r.den;
	return producto1 < producto2;
}

bool Rational::greater_than(const Rational &r)
{
	int producto1 = r.num * this->den;
	int producto2 = this->num * r.den;
	return producto1 > producto2;
}
