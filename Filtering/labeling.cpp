#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <random>

int main() {

	cv::Mat img, img_th, img_inv;
	cv::imread("../../Input/building.jpg", cv::IMREAD_GRAYSCALE).copyTo(
		img);
	if (img.empty()) {
		throw std::runtime_error("Failed to open image");
	}

	cv::threshold(img, img_th, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
	//dilate erode処理
	cv::Mat dst1, dst2, dst3;
	cv::erode(img_th, dst1, cv::Mat(), cv::Point(-1, -1), 1);
	cv::dilate(dst1, dst2, cv::Mat(), cv::Point(-1, -1), 2);
	cv::erode(dst2, dst3, cv::Mat(), cv::Point(-1, -1), 1);
	cv::imwrite("../../Output/labeling/app_2_1_2.jpg", dst3);

	//白黒反転
	cv::bitwise_not(dst3, img_inv);
	cv::imwrite("../../Output/labeling/inv.jpg", img_inv);

	//ラべリング処理
	cv::Mat LabelImg;
	cv::Mat stats;
	cv::Mat centroids;
	int nLab = cv::connectedComponentsWithStats(img_inv, LabelImg, stats, centroids);

	// ラベリング結果の描画色を決定
	std::vector<cv::Vec3b> colors(nLab);
	colors[0] = cv::Vec3b(0, 0, 0);
	for (int i = 1; i < nLab; ++i) {
		colors[i] = cv::Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
	}

	// ラベリング結果の描画
	cv::Mat Dst(img.size(), CV_8UC3);
	for (int i = 0; i < Dst.rows; ++i) {
		int *lb = LabelImg.ptr<int>(i);
		cv::Vec3b *pix = Dst.ptr<cv::Vec3b>(i);
		for (int j = 0; j < Dst.cols; ++j) {
			pix[j] = colors[lb[j]];
		}
	}

	cv::imwrite("../../Output/labeling/labeling.jpg", Dst);
}
