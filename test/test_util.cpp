// *memo_cpp.util*
#include "test_common.h"
#include <tt/util/util.h>
#include <tt/util/log.h>

using namespace std;

void f_test_log() {
    f_print_title("f_test_log()");

    int w = 200;
    int h = 100;
    tt::Log::I("w h: %d %d\n", w, h);

    std::string s = "test.png";
    tt::Log::E("file open failed: %s\n", s.c_str());
}

void f_test_replace() {
    f_print_title("f_test_replace()");

    std::string s = "a bc de f";
    cout << "orig: " << s << endl;
    tt::f_replace(s, "bc", "BCD");
    cout << "replace: " << s << endl;
}

int main(int argc, char *argv[]) {
    f_test_log();
    f_test_replace();

    return 0;
}

