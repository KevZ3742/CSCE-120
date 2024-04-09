#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
    double real;
    double imag;
public:
    Complex();
    Complex(double real, double imaginary);
    Complex(double real);
    Complex(const Complex& c);

    double getReal() const;
    double getImaginary() const;
    void setReal(double re);
    void setImaginary(double im);
};

#endif
