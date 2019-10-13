// *memo_cpp.image*
#include <iostream>
#include <glm/glm.hpp>
#include <tt/util/util.h>
#include <tt/util/time.h>
#include <tt/util/log.h>
#include <tt/gfx/image.h>
#include <tt/gfx/image_util.h>

using namespace std;

void f_image_conv(tt::Image4uc& dst, const tt::Image<glm::vec3>& src) {
    dst.alloc(src.w(), src.h());
    tt::f_image_conv(dst, src, [&](tt::Color4uc& dval, const glm::vec3& sval) {
        glm::vec3 v = sval * 255.f;
        dval = {uchar(v[0]), uchar(v[1]), uchar(v[2]), 255};
    });
}

void f_image_conv(tt::Image3uc& dst, const tt::Image<glm::vec3>& src) {
    dst.alloc(src.w(), src.h());
    tt::f_image_conv(dst, src, [&](tt::Color3uc& dval, const glm::vec3& sval) {
        glm::vec3 v = sval * 255.f;
        dval = {uchar(v[0]), uchar(v[1]), uchar(v[2])};
    });
}

void f_test_image() {
    tt::Image<glm::vec3> image;
    tt::Time t;
    tt::TimeCollection tc;
    std::vector<int> nthreads{0, 1, 2, 4, -1};
    int width = 4000;
    int height = 4000;
    cout << "hardware_concurrency: " << std::thread::hardware_concurrency() << endl;

    for (int i=0; i<3; i++) {
        cout << "=== " << i << " ===" << endl;

        image.clear();

        t.start();
        image.resize(width, height);
        t.end();
        tt::Log::I("Image<glm::vec3>::resize() %.1f ms\n", t.getElapsedMSec());
        tt::Log::I("w=%d h=%d size=%.1f MB\n", image.w(), image.h(), tt::BytesToMB(image.size() * image.sizeOfDataType()));

        t.start();
        image.clear();
        t.end();
        tt::Log::I("Image<glm::vec3>::clear() %.1f ms\n", t.getElapsedMSec());

        t.start();
        image.alloc(width, height);
        t.end();
        tt::Log::I("Image<glm::vec3>::alloc() %.1f ms\n", t.getElapsedMSec());

        t.start();
        image.fill(glm::vec3(1, 1, 1));
        t.end();
        tt::Log::I("Image<glm::vec3>::fill() %.1f ms\n", t.getElapsedMSec());

        for (auto j : nthreads) {
            t.start();
            image.foreach([&](glm::vec3& val, int x, int y) {
                val = glm::vec3(float(x)/width, float(y)/height, 0);
            }, j);
            t.end();
            tt::Log::I("Image<glm::vec3>::foreach(): nthreads=%d %.1f ms\n", j, t.getElapsedMSec());
        }

        t.start();
        glm::vec3* p = image.data();
        for (int y=0; y<height; y++) {
            for (int x=0; x<width; x++) {
                *p = glm::vec3(float(x)/width, float(y)/height, 0);
                p++;
            }
        }
        t.end();
        tt::Log::I("loop: %.1f ms\n", t.getElapsedMSec());
    }

    tt::Image4uc i4uc;
    f_image_conv(i4uc, image);
    f_save_image("out_i4uc.png", i4uc);

    tt::Image3uc i3uc;
    f_image_conv(i3uc, image);
    f_save_image("out_i3uc.png", i3uc);
}

int main(int argc, char *argv[]) {
    f_test_image();

    return 0;
}
