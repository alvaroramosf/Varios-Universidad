//Autor: Álvaro Ramos Fustero ~ 855798

#pragma once

#include <iostream>

// Solucion con atributos privados.

class Rational
{
private:
	// Atributos
	struct {
		int num;
		int den;
	};

private:
	// Auxiliares

	static int mcd(int a, int b);
	void reduce();

public:
	// Constructores

	Rational();
	Rational(int num, int den);

	// Operadores aritmeticos

	Rational operator+(const Rational& r) const;
	Rational operator-(const Rational& r) const;
	friend Rational operator*(const Rational &r1, const Rational &r2); // Friend function
	friend Rational operator/(const Rational &r1, const Rational &r2); // Friend function


	// Operadores logicos
	bool operator==(const Rational &r) const;
	bool operator<(const Rational &r) const;
	bool operator>(const Rational &r) const;

	// Friends, en su caso
	friend std::ostream &operator<<(std::ostream &os, const Rational &r); // Friend function
	friend std::istream &operator>>(std::istream &is, Rational &r);

};

// Operadores aritmeticos

Rational operator*(const Rational &r1, const Rational &r2);
Rational operator/(const Rational &r1, const Rational &r2);


// Entrada/salida

std::istream &operator>>(std::istream &is, Rational &r);
std::ostream &operator<<(std::ostream &os, const Rational &r);

