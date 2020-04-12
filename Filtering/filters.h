#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>
#include <sstream>

// 平滑化フィルタ
void blur_filter(cv::Mat img, int kernel_size) {
	cv::Mat destination;
	//void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )
	cv::blur(img, destination, cv::Size(kernel_size, kernel_size));
	//copyMakeBorder( src, dst, top, bottom, left, right, borderType, value )
	cv::imwrite("../../Output/blur/blur_" + std::to_string(kernel_size) + ".jpg", destination);
}

//ガウシアンフィルタ
void gaussian_filter(cv::Mat img, int kernel_size) {
	cv::Mat destination;
	//void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )
	cv::GaussianBlur(img, destination, cv::Size(kernel_size, kernel_size), 3, 3);
	//copyMakeBorder( src, dst, top, bottom, left, right, borderType, value )
	cv::imwrite("../../Output/gaussian/gaussian_" + std::to_string(kernel_size) + ".jpg", destination);
}


//バイラテラルフィルタ
void bilateral_filter(cv::Mat img, int d, int sigma_color, double sigma_space, int repeat) {
	/*bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT )
	d – Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigmaSpace .
	sigmaColor – Filter sigma in the color space. A larger value of the parameter means that farther colors within
	 the pixel neighborhood (see sigmaSpace ) will be mixed together,resulting in larger areas of semi-equal color.
	sigmaSpace – Filter sigma in the coordinate space. A larger value of the parameter means
	 that farther pixels will influence each other as long as their colors are close enough (see sigmaColor ).
	When d>0 , it specifies the neighborhood size regardless of sigmaSpace . Otherwise, d is proportional to sigmaSpace*/

	/*
	 * Sigma values: For simplicity, you can set the 2 sigma values to be the same. If they are small (< 10),
	 * the filter will not have much effect, whereas if they are large (> 150), they will have a very strong effect, making the image look “cartoonish”.
	 * Filter size: Large filters (d > 5) are very slow, so it is recommended to use d=5 for real-time applications,
	 * and perhaps d=9 for offline applications that need heavy noise filtering
	 */
	cv::Mat temp;
	temp = img;
	for (int i = 0; i < repeat; i++) {
		cv::Mat destination;
		cv::bilateralFilter(temp, destination, d, sigma_color, sigma_space);
		temp = destination;
	}
	cv::imwrite("../../Output/bilateral/bilateral_" + std::to_string(d) + "_" + std::to_string(sigma_color) + "_" + std::to_string(sigma_space)+"_r"+ std::to_string(repeat) + ".jpg", temp);
}


// median filter
void median_filter(cv::Mat img, int kernel_size) {
	cv::Mat destination;
	//void medianBlur(InputArray src, OutputArray dst, int ksize)
	//The median filter uses BORDER_REPLICATE internally to cope with border pixels
	cv::medianBlur(img, destination, kernel_size);
	cv::imwrite("../../Output/median./median_" + std::to_string(kernel_size) + ".jpg", destination);
}