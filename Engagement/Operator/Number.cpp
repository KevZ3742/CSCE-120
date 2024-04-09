#include <iostream>
#include "Complex.h"

int main() {
    Complex a;
    std::cout << "a.real: " << a.getReal() << std::endl;
    std::cout << "a.imag: " << a.getImaginary() << std::endl;

    Complex b(2.5, 3.8);
    std::cout << "b.real: " << b.getReal() << std::endl;
    std::cout << "b.imag: " << b.getImaginary() << std::endl;

    Complex c(5.7);
    std::cout << "c.real: " << c.getReal() << std::endl;
    std::cout << "c.imag: " << c.getImaginary() << std::endl;

    Complex d(b);
    std::cout << "d.real: " << d.getReal() << std::endl;
    std::cout << "d.imag: " << d.getImaginary() << std::endl;

    a.setReal(9.2);
    a.setImaginary(2.4);
    std::cout << "a.real: " << a.getReal() << std::endl;
    std::cout << "a.imag: " << a.getImaginary() << std::endl;

    return 0;
}
