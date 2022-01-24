//
// Created by User on 18.11.2021.
//

#include <fstream>
#include "FFT.h"

using namespace std;

vector_complex FFT::fft(const vector_complex &as) {
    int n = as.size();
    int k = 0; // Длина n в битах
    while ((1 << k) < n) k++;
    vector<int> rev(n);
    rev[0] = 0;
    int high1 = -1;
    for (int i = 1; i < n; i++) {
        if ((i & (i - 1)) == 0) // Проверка на степень двойки. Если i ей является, то i-1 будет состоять из кучи единиц.
            high1++;
        rev[i] = rev[i ^ (1 << high1)]; // Переворачиваем остаток
        rev[i] |= (1 << (k - high1 - 1)); // Добавляем старший бит
    }
    vector_complex roots(n);
    for (int i = 0; i < n; i++) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = std::complex<double>(cos(alpha), sin(alpha));
    }

    vector_complex cur(n);
    for (int i = 0; i < n; i++)
        cur[i] = as[rev[i]];

    for (int len = 1; len < n; len <<= 1) {
        vector_complex ncur(n);
        int rstep = roots.size() / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            for (int i = 0; i < len; i++) {
                std::complex<double> val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        cur.swap(ncur);
    }
    return cur;
}

vector_complex FFT::fft_rev(const vector_complex &as) {
    vector_complex res = fft(as);
    for (auto &re: res) re /= as.size();
    reverse(res.begin() + 1, res.end());
    return res;
}

vector_complex FFT::multiplication(const vector_complex &num1, const vector_complex &num2) {
    vector_complex res = fft(num1);
    vector_complex res2 = fft(num2);
    vector_complex c_vals(res.size());
    for (int i = 0; i < res.size(); i++)
        c_vals[i] = res[i] * res2[i];
    vector_complex result = fft_rev(c_vals);
    for (auto i = 0; i < result.size() - 1; i++) {
        if (result[i].real() >= 10) {
            auto tmp = static_cast<int>(result[i].real()) / 10;
            result[i + 1] += tmp;
            result[i] -= tmp * 10;
        }
    }
    return result;
}

int FFT::power(int n) {
    n = 2 * n;
    int i = 2;
    while (pow(2, i) < n) {
        i++;
    }
    return pow(2, i);
}

void FFT::ref_outc(const vector_complex &v) {
    auto rev = v;
    reverse(rev.begin(), rev.end());
    bool flag = false;
    for (auto &re: rev) {
        if (!flag && int(re.real()) != 0) {
            flag = true;
        }
        if (flag) {
            cout << setprecision(5) << static_cast<int>(re.real());
        }
    }
}

void FFT::res_outf(const vector_complex &v, std::string name) {
    auto rev = v;
    reverse(rev.begin(), rev.end());
    bool flag = false;
    std::ofstream out;
    out.open(name);
    for (auto &re: rev) {
        if (!flag && int(re.real()) != 0) {
            flag = true;
        }
        if (flag) {
            out << setprecision(5) << static_cast<int>(re.real());
        }
    }
    out.close();
}
