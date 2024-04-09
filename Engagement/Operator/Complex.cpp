#include "Complex.h"

Complex::Complex() : real(0.0), imag(0.0) {}

Complex::Complex(double real, double imaginary) : real(real), imag(imaginary) {}

Complex::Complex(double real) : real(real), imag(0.0) {}

Complex::Complex(const Complex& c) : real(c.real), imag(c.imag) {}

double Complex::getReal() const {
    return real;
}

double Complex::getImaginary() const {
    return imag;
}

void Complex::setReal(double re) {
    real = re;
}

void Complex::setImaginary(double im) {
    imag = im;
}
