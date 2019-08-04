#include <iostream>
#include <fstream>
#include <string.h>
#include <opencv2/opencv.hpp>
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

std::string ImageX::getType(int cv_type) const {
    std::string type;
    switch (cv_type) {
        case CV_8UC1:
            type = "i1uc";
            break;
        case CV_16UC1:
            type = "i1us";
            break;
        case CV_8UC3:
            type = "i3uc";
            break;
        case CV_8UC4:
            type = "i4uc";
            break;
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
        //load_mat(fname);
        m_type = "i4uc";
    }
    m_fname = fname;
}

void ImageX::save(const std::string& fname) const {
    std::string ext = getExt(fname);
    if (isType(ext)) {
        save_bin(fname);
    } else {
        save_mat(fname);
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
    int size = m_image->size() * m_image->sizeOfDataType();
    ifs.read(data, size);
}

void ImageX::save_bin(const std::string& fname) const {
    int w = m_image->w();
    int h = m_image->h();
    std::ofstream ofs(fname, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(&w), sizeof(int));
    ofs.write(reinterpret_cast<const char*>(&h), sizeof(int));

    char* data = (char*)(m_image->void_ptr());
    int size = m_image->size() * m_image->sizeOfDataType();
    ofs.write(data, size);
}

void ImageX::load_mat(const std::string& fname) {
    cv::Mat mat = cv::imread(fname, cv::IMREAD_UNCHANGED);

    m_type = getType(mat.type());
    int w = mat.cols;
    int h = mat.rows;
    create(m_type, w, h);

    if (m_type == "i3uc") {
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    } else if (m_type == "i4uc") {
        cv::cvtColor(mat, mat, cv::COLOR_BGRA2RGBA);
    }

    unsigned char* data = (unsigned char*)(m_image->void_ptr());
    int size = m_image->size() * m_image->sizeOfDataType();
    memcpy(data, mat.data, size);
}

void ImageX::save_mat(const std::string& fname) const {
    int w = m_image->w();
    int h = m_image->h();
    std::unique_ptr<cv::Mat> mat;
    if (m_type == "i1uc") {
        mat = std::make_unique<cv::Mat1b>(h, w);
    } else if (m_type == "i1us") {
        mat = std::make_unique<cv::Mat1w>(h, w);
    } else if (m_type == "i3uc") {
        mat = std::make_unique<cv::Mat3b>(h, w);
    } else if (m_type == "i4uc") {
        mat = std::make_unique<cv::Mat4b>(h, w);
    }

    char* data = (char*)(m_image->void_ptr());
    int size = m_image->size() * m_image->sizeOfDataType();
    memcpy(mat->data, data, size);

    if (m_type == "i3uc") {
        cv::cvtColor(*mat, *mat, cv::COLOR_RGB2BGR);
    } else if (m_type == "i4uc") {
        cv::cvtColor(*mat, *mat, cv::COLOR_RGBA2BGRA);
    }

    cv::imwrite(fname, *mat);
}

}

