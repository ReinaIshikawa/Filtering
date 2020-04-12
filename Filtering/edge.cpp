#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string>

//http://opencv.jp/opencv-2.1/cpp/image_filtering.html



//ソーベルフィルタ
void sobel_filter(cv::Mat img) {
	/*
	void Sobel(const Mat& src, Mat& dst, int ddepth, int xorder, int yorder, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
	ddepth – 出力画像のビット深度
	xorder – xに関する微分の次数
	delta – dst に格納する前に，結果に足されるオプション値
	*/
	cv::Mat dstX, dstY, sobel;

	//CV_8U is unsigned 8bit/pixel
	cv::Sobel(img, dstX, CV_8UC1, 1, 0, 3);
	cv::Sobel(img, dstY, CV_8UC1, 0, 1, 3);
	sobel = abs(dstX) + abs(dstY);
	cv::convertScaleAbs(sobel, sobel, 1, 0);
	//output
	cv::imwrite("../../Output/sobel/sobel_x.jpg", dstX);
	cv::imwrite("../../Output/sobel/sobel_y.jpg", dstY);
	cv::imwrite("../../Output/sobel/sobel_x+y.jpg", sobel);
}

//ラプラシアンフィルタ
void laplacian_filter(cv::Mat img) {
	cv::Mat dstL;
	// void Laplacian(const Mat& src, Mat& dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
	int kernel_size = 3;
	int ddepth = CV_16S;//3
	cv::Laplacian(img, dstL, ddepth);
	cv::convertScaleAbs(dstL, dstL, 1, 0);
	cv::imwrite("../../Output/laplacian/laplacian.jpg", dstL);
}

//ケニーのエッジ検出アルゴリズム
void canny_filter(cv::Mat img, int th_low, int th_high) {
	/* void Canny(const Mat& image, Mat& edges, double threshold1, double threshold2, int apertureSize=3, bool L2gradient=false)
	image – 8ビット，シングルチャンネルの入力画像
	edges – 出力されるエッジのマップ． image と同じサイズ，同じ型
	threshold1 – ヒステリシスが存在する処理の，1番目の閾値
	threshold2 – ヒステリシスが存在する処理の，2番目の閾値
	apertureSize – Sobel() オペレータのアパーチャサイズ
	L2gradient – 画像勾配の強度を求めるために，より精度の高い L_2 ノルム =\sqrt{(dI/dx)^2 + (dI/dy)^2} を利用するか，
				L_1 ノルム =|dI/dx|+|dI/dy| で十分（ L2gradient=false ）かを指定します
	 */
	cv::Mat dstC;
	cv::Canny(img, dstC, th_low, th_high);
	cv::imwrite("../../Output/canny/canny_" + std::to_string(th_low) + "_" + std::to_string(th_high) + ".jpg", dstC);
}

int main() {
	cv::Mat img;
	cv::imread("../../Input/building.jpg", cv::IMREAD_GRAYSCALE).copyTo(img);
	if (img.empty())
		throw std::runtime_error("Failed to open image");
	sobel_filter(img);
	laplacian_filter(img);
	canny_filter(img, 100, 200);
	canny_filter(img, 50, 100);

	return 0;
}
