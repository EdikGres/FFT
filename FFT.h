
#ifndef FFT_H
#define FFT_H

#define _USE_MATH_DEFINES
#include <algorithm>
#include <ctime>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

typedef std::vector<std::complex<double>> vector_complex;

class FFT {
private:
    static vector_complex fft(const vector_complex &as);

    static vector_complex fft_rev(const vector_complex &as);

public:
    static int power(int);

    static vector_complex multiplication(const vector_complex &num1, const vector_complex &num2);

    static void ref_outc(const vector_complex &v);

    void res_outf(const vector_complex &v, std::string name);

};


#endif //FFT_H
