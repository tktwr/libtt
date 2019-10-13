#include "test_common.h"
#include <tt/util/type.h>

using namespace std;

template<class T>
void f_test_type(const std::string& s, const T& rgba) {
    f_print_title("f_test_type()");

    cout << s << endl;
    cout << "orig: " << rgba << endl;
    cout << "rgba + rgba: " << rgba + rgba << endl;
    cout << "rgba - rgba: " << rgba - rgba << endl;
    cout << "rgba * rgba: " << rgba * rgba << endl;
    cout << "rgba / rgba: " << rgba / rgba << endl;
    cout << "rgba * 0.5f: " << rgba * 0.5f << endl;
    cout << "0.5f * rgba: " << 0.5f * rgba << endl;
}

void f_test_types() {
    f_print_title("f_test_types()");

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
    f_test_types();

    return 0;
}

