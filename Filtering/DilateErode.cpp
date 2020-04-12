/*
void dilate(const Mat& src, Mat& dst, const Mat& element, Point anchor=Point(-1, -1), int iterations=1, int borderType=BORDER_CONSTANT, const
element – 膨張に用いられる構造要素． element=Mat() の場合， 3\times 3 の矩形構造要素が用いられます．
anchor – 構造要素内のアンカー位置．デフォルト値の (-1, -1) は，アンカーが構造要素の中心にあることを意味します．
iterations – 膨張が行われる回数．
borderType – ピクセル外挿手法． borderInterpolate() を参照してください．
borderValue – 定数境界モードで利用されるピクセル値．デフォルト値は特別な意味を持ちます
ピクセル近傍領域の形状を決定し，そこから最大値を取り出すような指定構造要素を用いて，入力画像の膨張を行う
この関数は，置換モードをサポートします．
膨張は複数（ iterations ）回適用可
マルチチャンネル画像の場合，各チャンネルは個別に処理
*/

/*
void erode(const Mat& src, Mat& dst, const Mat& element, Point anchor=Point(-1, -1), int iterations=1, int borderType=BORDER_CONSTANT, const
ピクセル近傍領域の形状を決定し，そこから最小値を取り出すような指定構造要素を用いて，入力画像の収縮
*/
#include <opencv2/opencv.hpp>
#include <string>


int main() {

	cv::Mat img;
	cv::imread("../../Input/building.jpg", cv::IMREAD_GRAYSCALE).copyTo(img);
	if (img.empty())
	{
		throw std::runtime_error("Failed to open image");
	}

	int DIL_CNT = 2;
	int ERO_CNT = 2;
	cv::Mat dst1, dst2;
	cv::dilate(img, dst1, cv::Mat(), cv::Point(-1, -1), DIL_CNT);
	cv::erode(dst1, dst2, cv::Mat(), cv::Point(-1, -1), ERO_CNT);
	cv::imwrite("../../Output/DilateErode/closing_" + std::to_string(DIL_CNT) + "_" + std::to_string(ERO_CNT) + ".jpg", dst2);
	cv::Mat dst3, dst4;
	cv::erode(img, dst3, cv::Mat(), cv::Point(-1, -1), DIL_CNT);
	cv::dilate(dst3, dst4, cv::Mat(), cv::Point(-1, -1), ERO_CNT);
	cv::imwrite("../../Output/DilateErode/opening_" + std::to_string(DIL_CNT) + "_" + std::to_string(ERO_CNT) + ".jpg", dst4);

	cv::Mat dst5, dst6, dst7;
	cv::erode(img, dst5, cv::Mat(), cv::Point(-1, -1), 1);
	cv::dilate(dst3, dst6, cv::Mat(), cv::Point(-1, -1), ERO_CNT);
	cv::erode(img, dst5, cv::Mat(), cv::Point(-1, -1), 1);
	cv::imwrite("../../Output/DilateErode/app_" + std::to_string(DIL_CNT) + "_" + std::to_string(ERO_CNT) + ".jpg", dst4);
	return 0;
}
