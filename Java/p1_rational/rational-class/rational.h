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

	// Entrada/salida

	void write(std::ostream& out) const;
	Rational read(std::istream& is);

	// Operaciones aritmeticas

	Rational add(const Rational& r);
	Rational sub(const Rational& r);
	Rational mul(const Rational& r);
	Rational div(const Rational& r);

	// Operaciones logicas

	bool equal(const Rational& r);
	bool lesser_than(const Rational& r);
	bool greater_than(const Rational& r);
};
