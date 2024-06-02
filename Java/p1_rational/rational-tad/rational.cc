//Autor: Álvaro Ramos Fustero ~ 855798

#include "rational.h"

// Auxiliares, privadas

int mcd(int a, int b)
{
	return ( b==0 ? a : mcd(b,a%b) );
}

void reduce(Rational& r)
{
	unsigned int aux = mcd(r.num, r.den);
	r.num=r.num/aux;
	r.den=r.den/aux; 
	return;
}

// Inicializadores

void init(Rational& r)
{
	r.num=0;
	r.den=0;
	return;
}

void init(Rational& r,int num, int den)
{
	r.num=num;
	r.den=den;
	return;
}

// Entrada/salida

void write(std::ostream& os, const Rational& r)
{
	os<<r.num<<"/"<<r.den<<"\n"<<std::flush;
}

void read(std::istream& is, Rational& r)
{
	std::string expresion;
	is>>r.num;
	is.ignore(100,'/');
	is>>r.den;
}

// Operaciones aritmeticas

Rational add(const Rational& r1, const Rational& r2)
{
	Rational res;
	res.num=(r1.num*r2.den)+(r2.num*r1.den);
	res.den = r1.den*r2.den;
	reduce(res);
	return res;
}

Rational sub(const Rational& r1, const Rational& r2)
{
	Rational res;
	res.num=(r1.num*r2.den)-(r2.num*r1.den);
	res.den = r1.den*r2.den;   
	reduce(res);	
	return res;
}

Rational mul(const Rational& r1, const Rational& r2)
{
	Rational res;
	res.num=r1.num*r2.num;
	res.den =r1.den*r2.den; 
	reduce(res);  
	return res;
}

Rational div(const Rational& r1, const Rational& r2)
{
	Rational res;
	res.num=r1.num*r2.den;
	res.den =r1.den*r2.num;   
	reduce(res);
	return res;
}

// Operaciones logicas

bool equal(const Rational& r1, const Rational& r2)
{
	int producto1 = r1.num * r2.den;
	int producto2 = r2.num * r1.den;
	return producto1 == producto2;
}

bool lesser_than(const Rational& r1, const Rational& r2)
{
	int producto1 = r1.num * r2.den;
	int producto2 = r2.num * r1.den;
	return producto1 < producto2;
}

bool greater_than(const Rational& r1, const Rational& r2)
{
	int producto1 = r1.num * r2.den;
	int producto2 = r2.num * r1.den;
	return producto1 > producto2;
}
