// *memo_cpp.util*
#include <iostream>
#include <string>
#include <tt/util/type.h>
#include <tt/util/util.h>
#include <tt/util/log.h>

using namespace std;

void f_log() {
    int w = 200;
    int h = 100;
    tt::Log::I("w h: %d %d\n", w, h);

    std::string s = "test.png";
    tt::Log::E("file open failed: %s\n", s.c_str());
}

void f_replace() {
    cout << "=== f_replace() === " << endl;

    std::string s = "a bc de f";
    cout << "orig: " << s << endl;
    tt::f_replace(s, "bc", "BCD");
    cout << "replace: " << s << endl;
}

template<class T>
void f_test_type(const std::string& s, const T& rgba) {
    cout << "=== f_test_type() === " << s << endl;

    cout << "orig: " << rgba << endl;
    T add = rgba + rgba;
    cout << "add: " << add << endl;
    T sub = rgba - rgba;
    cout << "sub: " << sub << endl;
    T mul = rgba * rgba;
    cout << "mul: " << mul << endl;
    T div = rgba / rgba;
    cout << "div: " << div << endl;
    T mul_s = rgba * 0.5f;
    cout << "mul_s: " << mul_s << endl;
    T mul_s2 = 0.5f * rgba;
    cout << "mul_s2: " << mul_s2 << endl;
}

void f_type() {
    cout << "=== f_type() === " << endl;

    tt::Color1uc co1uc = {2};
    f_test_type("Color1uc: ", co1uc);

    tt::Color1us co1us = {2};
    f_test_type("Color1us: ", co1us);

    tt::Color1f co1f = {0.5};
    f_test_type("Color1f: ", co1f);

    tt::Color3uc co3uc = {1, 2, 3};
    f_test_type("Color3uc: ", co3uc);

    tt::Color3us co3us = {1, 2, 3};
    f_test_type("Color3us: ", co3us);

    tt::Color3f co3f = {0.5, 0.5, 0.5};
    f_test_type("Color3f: ", co3f);

    tt::Color4uc co4uc = {1, 2, 3, 255};
    f_test_type("Color4uc: ", co4uc);

    tt::Color4us co4us = {1, 2, 3, 65535};
    f_test_type("Color4us: ", co4us);

    tt::Color4f co4f = {0.5, 0.5, 0.5, 1.0};
    f_test_type("Color4f: ", co4f);

    tt::Color4uc conv = tt::float2uchar(co4f);
    f_test_type("conv: ", conv);
}

int main(int argc, char *argv[]) {
    f_log();
    f_replace();
    f_type();

    return 0;
}

