/*
 * fraction.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: BradG
 *      OS: Mac OS X 10.10
 *      Toolchain: Mac OSX
 *      IDE: Eclipse Luna
 */
#include <iostream>
#include "fraction.h"

using namespace std;

Fraction::Fraction(int num, int den) : numer(num), denom(den) {
	if (denom == 0)
		throw FractionException("Denominator cannot be zero!");
	normalize();
}

Fraction::Fraction(int num) : numer(num), denom(1) {}

Fraction::Fraction() : numer(0), denom(1) {}

int Fraction::gcd(int n, int m) {
	if (m <= n && n % m == 0)
		return m;
	else if (n < m)
		return gcd(m, n);
	else
		return gcd(m, n % m);
}

void Fraction::normalize() {
	int sign = 1;
	if (numer < 0) {
		sign = -1;
		numer = -numer;
	}
	if (denom < 0) {
		sign = -sign;
		denom = -denom;
	}
	int commonDenom = 1;
	if (numer > 0)
		commonDenom = gcd(numer, denom);
	numer = sign * (numer / commonDenom);
	denom = denom / commonDenom;
}

int Fraction::numerator() const {
	return numer;
}

int Fraction::denominator() const {
	return denom;
}

Fraction& Fraction::operator+=(const Fraction& fract) {
	numer = numer * fract.denominator() + denom * fract.denominator();
	denom *= fract.denominator();
	normalize();
	return *this;
}

//Pre-increment
Fraction& Fraction::operator++() {
	numer += denom;
	return *this;
}

//Post-increment
Fraction Fraction::operator++(int placeholder) {
	Fraction fract(numer, denom);
	numer += denom;
	return fract;
}

Fraction operator-(const Fraction& fract) {
	return Fraction(-fract.numerator(), fract.denominator());
}

Fraction operator+(const Fraction& left, const Fraction& right) {
	return Fraction(left.numerator() * right.denominator() +
			left.denominator() * right.numerator(),
			left.denominator() * right.denominator());
}

Fraction operator-(const Fraction& left, const Fraction& right) {
		return Fraction(left.numerator() * right.denominator() -
				left.denominator() * right.numerator(),
				left.denominator() * right.denominator());
}

Fraction operator*(const Fraction& left, const Fraction& right) {
	return Fraction(left.numerator() * right.numerator(),
			left.denominator() * right.denominator());
}

Fraction operator/(const Fraction& left, const Fraction& right) {
	return Fraction(left.numerator() * right.denominator(),
			left.denominator() * right.numerator());
}

int Fraction::compare(const Fraction& right) const {
	return this->numer * right.denominator() -
			this->denom * right.numerator();
}

bool operator<(const Fraction& left, const Fraction& right) {
	return left.compare(right) < 0;
}

bool operator<=(const Fraction& left, const Fraction& right) {
	return left.compare(right) <= 0;
}

bool operator==(const Fraction& left, const Fraction& right) {
	return left.compare(right) == 0;
}

bool operator!=(const Fraction& left, const Fraction& right) {
	return left.compare(right) != 0;
}

bool operator>=(const Fraction& left, const Fraction& right) {
	return left.compare(right) >= 0;
}

bool operator>(const Fraction& left, const Fraction& right) {
	return left.compare(right) > 0;
}

ostream& operator<<(ostream& outStream, const Fraction& fract) {
	outStream << fract.numerator() << "/" << fract.denominator();
	return outStream;
}

istream& operator>>(istream& inStream, Fraction& fract) {
	int inNumer, inDenom;
	inStream >> inNumer;
	if (inStream.peek() != 10) {
		char nextChar;
		inStream >> nextChar;
		if (nextChar == '/')
			inStream >> inDenom;
		else
			inDenom = 1;
		fract = Fraction(inNumer, inDenom);
	}
	else
		fract = Fraction(inNumer);
	return inStream;
}

FractionException::FractionException(const string& message) :
		message(message) {}

string& FractionException::what() {
	return message;
}
