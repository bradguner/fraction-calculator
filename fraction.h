/*
 *  Created on: Feb 21, 2015
 *      Author: Bradley Guner
 *      OS: Mac OS X 10.10
 *      Toolchain: Mac OSX
 *      IDE: Eclipse Luna
 */


#include <exception>
#include <iostream>

using namespace std;

//unary operators: negation, post-increment, pre-increment
//binary operators: +, -, *, /, +=, <, <=, ==, !=, >=, >, <<, >>

class Fraction {
	public:
		Fraction(int num, int denom);
		Fraction(int num); //Constructor to make a fraction with numerator num and denominator 1
		Fraction(); //Constructor to make a fraction with numerator 0 and denominator 1
		int numerator() const; //Accessor for numerator of a fraction object
		int denominator() const; //Accessor for denominator of a fraction object
		Fraction& operator++(); //Pre-increment
		Fraction operator++(int placeholder); //Post-increment
		Fraction& operator+=(const Fraction& fract); //Update fraction with addition of another fraction
		int compare(const Fraction& right) const; //Compare fraction values, return positive value if left > right, 0 if equal, negative if left < right

	private:
		void normalize(); //Reduces the fraction to its simplest form
		int gcd(int num, int denom); //Finds greatest common denominator of two values
		int numer;
		int denom;
};
//Arithmetic Operator Overloading
Fraction operator-(const Fraction& fract);
Fraction operator+(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& left, const Fraction& right);
Fraction operator*(const Fraction& left, const Fraction& right);
Fraction operator/(const Fraction& left, const Fraction& right);

//Boolean Operator Overloading
bool operator<(const Fraction& left, const Fraction& right);
bool operator<=(const Fraction& left, const Fraction& right);
bool operator==(const Fraction& left, const Fraction& right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator>=(const Fraction& left, const Fraction& right);
bool operator>(const Fraction& left, const Fraction& right);

//Stream Operator Overloading
ostream& operator<<(ostream& outStream, const Fraction& fract);
istream& operator>>(istream& inStream, Fraction& fract);


/*
 * The exception class for an illegal denominator value. This is thrown when
 * a value of 0 is tried to be initialized in a fraction.
 */
class FractionException {
	public:
		FractionException(const string& message);
		string& what();
	private:
		string message;
};
