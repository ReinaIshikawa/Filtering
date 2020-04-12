#include "filters.h"

int KERNELSIZE = 11;

// bilateral
int DIAMERER =11;
int SIGMA_COLOR = 50;
int SIGMA_SPACE = 50;
int REPEATNUM = 5;



void blur(cv::Mat img) {
	blur_filter(img, KERNELSIZE);
}

void gaussian(cv::Mat img) {
	gaussian_filter(img, KERNELSIZE);
}

void bilateral(cv::Mat img) {
	bilateral_filter(img, DIAMERER, SIGMA_COLOR, SIGMA_SPACE, REPEATNUM);
}

void median(cv::Mat img) {
	median_filter(img, KERNELSIZE);
}

int main(int argc, char **argv) {
	cv::Mat img;

	cv::imread("../../Input/flower.jpg", cv::IMREAD_UNCHANGED).copyTo(img);
	if (img.empty())
	{
		throw std::runtime_error("Failed to open image");
	}

	if (argc == 1) {
		blur(img);
		gaussian(img);
		bilateral(img);
		median(img);
	}
	if (argc == 2) {
		if (argv[1] == "blur") blur(img);
		else if (argv[1] == "gaussian") gaussian(img);
		else if (argv[1] == "bilateral") bilateral(img);
		else if (argv[1] == "median") median(img);
	}

	return 0;

}