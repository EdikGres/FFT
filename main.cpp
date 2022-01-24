#include <iostream>
#include <fstream>
#include "FFT.h"
using namespace std;
int main() {
    FFT f;
    string s1, s2;
    ifstream in("test.txt");
    if(in.is_open()) {
        //cout << "Okay!";
        getline(in, s1);
        getline(in, s2);
    }
    std::vector<std::complex<double>> vc1(f.power(s1.size()));
    std::vector<std::complex<double>> vc2(f.power(s2.size()));
    int i = s1.size()-1;
    for (char c : s1) {
        vc1[i--]=static_cast<int>(c) - 48;
         //vc1.push_back();
    }
    i = s2.size()-1;
    for (char c : s2) {
        vc2[i--]=static_cast<int>(c) - 48;
    }
    for (auto i : vc1) {
        cout << i;
    }
    cout << endl;
    for (auto i : vc2) {
        cout << i;
    }
    in.close();
    auto res = f.multiplication(vc1, vc2);
    f.res_outf(res, "res.txt");
    //f.ref_outc(res);
    return 0;
}
