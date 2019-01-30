// *memo_cpp.array*
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <tt/util/array.h>
#include <tt/util/time.h>

using namespace std;

int main(int argc, char *argv[]) {
    int w, h;
    w = 4000;
    h = 4000;

    tt::Time t;
    for (int i=0; i<3; i++) {
        cout << "==========" << endl;

        {
            t.start();
            tt::Array<glm::vec3> ar;
            ar.resize(w * h);
            t.end();
            cout << "Array::resize: " << t.getElapsedMSec() << " ms" << endl;
            cout << "size: " << ar.size() << endl;
            cout << endl;
        }

        {
            t.start();
            tt::Array<glm::vec3> ar;
            ar.alloc(w * h);
            t.end();
            cout << "Array::alloc: " << t.getElapsedMSec() << " ms" << endl;
            cout << "size: " << ar.size() << endl;
            cout << endl;
        }

        {
            t.start();
            std::vector<glm::vec3> vec;
            vec.resize(w * h);
            t.end();
            cout << "vector::resize: " << t.getElapsedMSec() << " ms" << endl;
            cout << "size: " << vec.size() << endl;
            cout << "capacity: " << vec.capacity() << endl;
            cout << endl;
        }

        {
            t.start();
            std::vector<glm::vec3> vec;
            vec.reserve(w * h);
            t.end();
            cout << "vector::reserve: " << t.getElapsedMSec() << " ms" << endl;
            cout << "size: " << vec.size() << endl;
            cout << "capacity: " << vec.capacity() << endl;
            cout << endl;
        }
    }


    return 0;
}

