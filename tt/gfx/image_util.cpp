#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>
#include <string.h>
#include <iostream>
#include "image_util.h"

bool f_load_image(const std::string& fname, tt::Image4uc& image) {
    int w, h, n;
    unsigned char *data = stbi_load(fname.c_str(), &w, &h, &n, 4);
    if (!data) {
        std::cerr << "fail to load image" << std::endl;
        return false;
    }
    image.alloc(w, h);
    memcpy(image.data(), data, w*h*4);
    stbi_image_free(data);
    return true;
}

void f_save_image(const std::string& fname, const tt::Image4uc& image) {
    stbi_write_png(fname.c_str(), image.w(), image.h(), 4, image.data(), 0);
}

void f_save_image(const std::string& fname, const tt::Image3uc& image) {
    stbi_write_png(fname.c_str(), image.w(), image.h(), 3, image.data(), 0);
}

void f_draw_rect(tt::Image4uc& image, const tt::Vec2i& o, const tt::Vec2i& size, const tt::Color4uc& color) {
    image.foreach([&](tt::Color4uc& val, int x, int y) {
        if (x >= o[0] && x < o[0]+size[0] &&
            y >= o[1] && y < o[1]+size[1]) {
            if (x == o[0] || x == o[0]+size[0]-1 ||
                y == o[1] || y == o[1]+size[1]-1) {
                val = color;
            }
        }
    });
}

void f_fill_rect(tt::Image4uc& image, const tt::Vec2i& o, const tt::Vec2i& size, const tt::Color4uc& color) {
    image.foreach([&](tt::Color4uc& val, int x, int y) {
        if (x >= o[0] && x < o[0]+size[0] &&
            y >= o[1] && y < o[1]+size[1]) {
            val = color;
        }
    });
}

void f_create_vstripe_image(tt::Image4uc& image, int n, const tt::Color4uc& color0, const tt::Color4uc& color1) {
    int d = image.w() / n;
    int d2 = d * 2;
    image.foreach([&](tt::Color4uc& val, int x, int y) {
        if (x%d2 < d) {
            val = color0;
        } else {
            val = color1;
        }
    });
}

void f_create_hstripe_image(tt::Image4uc& image, int n, const tt::Color4uc& color0, const tt::Color4uc& color1) {
    int d = image.h() / n;
    int d2 = d * 2;
    image.foreach([&](tt::Color4uc& val, int x, int y) {
        if (y%d2 < d) {
            val = color0;
        } else {
            val = color1;
        }
    });
}

void f_create_checker_image(tt::Image4uc& image, int nw, int nh, const tt::Color4uc& color0, const tt::Color4uc& color1) {
    int dw = image.w() / nw;
    int dh = image.h() / nh;
    int dw2 = dw * 2;
    int dh2 = dh * 2;
    image.foreach([&](tt::Color4uc& val, int x, int y) {
        if ((x%dw2 <  dw && y%dh2 <  dh) ||
            (x%dw2 >= dw && y%dh2 >= dh)) {
            val = color0;
        } else {
            val = color1;
        }
    });
}

