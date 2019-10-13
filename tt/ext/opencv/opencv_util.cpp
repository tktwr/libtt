#include "opencv_util.h"

void f_image_to_cvmat(const tt::Image4uc& image, cv::Mat& mat) {
    mat = cv::Mat(image.h(), image.w(), CV_8UC4, (tt::Color4uc*)(image.data()));
}

void f_cvmat_to_image(const cv::Mat& mat, tt::Image4uc& image) {
    image.alloc(mat.cols, mat.rows);
    memcpy(image.data(), mat.data, image.size() * image.sizeOfDataType());
}

std::string getType(int cv_type) {
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

void f_load_mat(const std::string& fname, tt::ImageX& img) {
    cv::Mat mat = cv::imread(fname, cv::IMREAD_UNCHANGED);

    std::string type = getType(mat.type());
    int w = mat.cols;
    int h = mat.rows;
    img.create(type, w, h);

    if (type == "i3uc") {
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    } else if (type == "i4uc") {
        cv::cvtColor(mat, mat, cv::COLOR_BGRA2RGBA);
    }

    unsigned char* data = (unsigned char*)(img.void_ptr());
    std::size_t size = img.size() * img.sizeOfDataType();
    memcpy(data, mat.data, size);
}

void f_save_mat(const std::string& fname, const tt::ImageX& img) {
    std::string type = img.getType();
    int w = img.w();
    int h = img.h();
    std::shared_ptr<cv::Mat> mat;
    if (type == "i1uc") {
        mat = std::make_shared<cv::Mat1b>(h, w);
    } else if (type == "i1us") {
        mat = std::make_shared<cv::Mat1w>(h, w);
    } else if (type == "i3uc") {
        mat = std::make_shared<cv::Mat3b>(h, w);
    } else if (type == "i4uc") {
        mat = std::make_shared<cv::Mat4b>(h, w);
    }

    char* data = (char*)(img.void_ptr());
    std::size_t size = img.size() * img.sizeOfDataType();
    memcpy(mat->data, data, size);

    if (type == "i3uc") {
        cv::cvtColor(*mat, *mat, cv::COLOR_RGB2BGR);
    } else if (type == "i4uc") {
        cv::cvtColor(*mat, *mat, cv::COLOR_RGBA2BGRA);
    }

    cv::imwrite(fname, *mat);
}

