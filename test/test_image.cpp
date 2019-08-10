// *memo_cpp.image*
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include <glm/glm.hpp>
#include <iostream>
#include <tt/util/util.h>
#include <tt/util/time.h>
#include <tt/util/log.h>
#include <tt/gfx/image.h>

using namespace std;

void f_image_save(const char* fname, int w, int h, int comp, const float* data) {
    unsigned char* dst_data = new unsigned char[w * h * 3];
    unsigned char* dst = dst_data;
    const float* src = data;

    for (int i=0; i<w*h*3; i++) {
        dst[i] = (unsigned char)(src[i] * 255);
    }
    stbi_write_png(fname, w, h, 3, dst_data, 0);

    delete [] dst_data;
}

void f_image() {
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
                val = glm::vec3(float(x)/width, float(y)/height, 1);
            }, j);
            t.end();
            tt::Log::I("Image<glm::vec3>::foreach(): nthreads=%d %.1f ms\n", j, t.getElapsedMSec());
        }

        f_image_save("out.png", image.w(), image.h(), 3, (float*)(image.data()));

        t.start();
        glm::vec3* p = image.data();
        for (int y=0; y<image.h(); y++) {
            for (int x=0; x<image.h(); x++) {
                *p = glm::vec3(x, y, 1);
                p++;
            }
        }
        t.end();
        tt::Log::I("loop: %.1f ms\n", t.getElapsedMSec());
    }
}

int main(int argc, char *argv[]) {
    f_image();

    return 0;
}
