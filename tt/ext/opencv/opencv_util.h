#pragma once

#include <tt/gfx/image.h>
#include <tt/gfx/imagex.h>
#include <opencv2/opencv.hpp>
#include <string>

void f_image_to_cvmat(const tt::Image4uc& image, cv::Mat& mat);
void f_cvmat_to_image(const cv::Mat& mat, tt::Image4uc& image);
void f_load_mat(const std::string& fname, tt::ImageX& img);
void f_save_mat(const std::string& fname, const tt::ImageX& img);

