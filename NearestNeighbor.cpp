#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat Comprime(Mat src)
{
	int width = src.rows;
	int height = src.cols;

	Mat dst(width / 2, height / 2, CV_8UC3);
	{
	for (int r = 0, v = 0; v < width; r++, v = v + 2)
		for (int c = 0, d = 0; d< height; c++, d = d + 2)
		{
			Vec3b pixel = src.at<Vec3b>(v, d);
			dst.at<Vec3b>(r, c) = pixel;
		}
	}

	return dst;
}


Mat Expande(Mat src)
{
	int width = src.rows;
	int height = src.cols;

	Mat dst(width*2, height*2, CV_8UC3);

	for (int r = 0, v = 0; r < width; r++, v = v + 2)
	{
		for (int c = 0, d = 0; c < height; c++, d = d + 2)
		{
			Vec3b pixel = src.at<Vec3b>(r, c);
			dst.at<Vec3b>(v, d) = pixel;
			dst.at<Vec3b>(v + 1, d) = pixel;
			dst.at<Vec3b>(v, d + 1) = pixel;
			dst.at<Vec3b>(v + 1, d + 1) = pixel;
		}
	}

	return dst;
}


int main(int argc, char** argv)
{
	string imageName("test.png"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}
	Mat src;

	src = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
	if (src.empty())                      // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat expandida = Expande(src);
	Mat comprimida = Comprime(src);


	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", src);                

	namedWindow("comprimida", WINDOW_AUTOSIZE);
	imshow("comprimida", comprimida);          

	namedWindow("expandida", WINDOW_AUTOSIZE); 
	imshow("expandida", expandida);              

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}