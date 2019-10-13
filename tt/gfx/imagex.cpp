#include <iostream>
#include <fstream>
#include <string.h>
#include "imagex.h"
#include "image_util.h"

namespace tt {

std::string ImageX::getExt(const tt::FileName& fname) const {
    return fname.ext().substr(1);
}

std::string ImageX::getType(const std::string& ext) const {
    std::string type;
    if (ext == "jpg") {
        type = "i4uc";
    } else if (ext == "png") {
        type = "i4uc";
    } else {
        type = ext;
    }
    return type;
}

bool ImageX::isType(const std::string& ext) const {
    if (ext == "i1uc" ||
        ext == "i1us" ||
        ext == "i3uc" ||
        ext == "i4uc") {
        return true;
    }
    return false;
}

void ImageX::create(const std::string& type, int w, int h) {
    destroy();

    if (type == "i1uc") {
        m_image = std::make_shared<Image1uc>(w, h);
    } else if (type == "i1us") {
        m_image = std::make_shared<Image1us>(w, h);
    } else if (type == "i3uc") {
        m_image = std::make_shared<Image3uc>(w, h);
    } else if (type == "i4uc") {
        m_image = std::make_shared<Image4uc>(w, h);
    }
    m_type = type;
    m_fname = "";
}

void ImageX::load(const std::string& fname) {
    std::string ext = getExt(fname);
    if (isType(ext)) {
        load_bin(fname);
        m_type = ext;
    } else {
        tt::Image4uc& img = tt::toImage4ucRef(*this);
        f_load_image(fname, img);
        m_type = "i4uc";
    }
    m_fname = fname;
}

void ImageX::save(const std::string& fname) const {
    std::string ext = getExt(fname);
    if (isType(ext)) {
        save_bin(fname);
    } else {
        tt::Image4ucConstPtr img = tt::toImage4ucConstPtr(*this);
        f_save_image(fname, *img);
    }
}

void ImageX::load_bin(const std::string& fname) {
    int w = 0;
    int h = 0;
    std::ifstream ifs(fname, std::ios::binary);
    ifs.read(reinterpret_cast<char*>(&w), sizeof(int));
    ifs.read(reinterpret_cast<char*>(&h), sizeof(int));

    m_type = getType(getExt(fname));
    create(m_type, w, h);

    char* data = (char*)(m_image->void_ptr());
    std::size_t size = m_image->size() * m_image->sizeOfDataType();
    ifs.read(data, size);
}

void ImageX::save_bin(const std::string& fname) const {
    int w = m_image->w();
    int h = m_image->h();
    std::ofstream ofs(fname, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(&w), sizeof(int));
    ofs.write(reinterpret_cast<const char*>(&h), sizeof(int));

    char* data = (char*)(m_image->void_ptr());
    std::size_t size = m_image->size() * m_image->sizeOfDataType();
    ofs.write(data, size);
}

}

