#include <iostream>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2\imgproc\imgproc.hpp>

int value = 20;

cv::Mat src;
cv::Mat output;

void PowerLaw(float r)
{
	int h = output.rows, w = output.cols;

	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			//rgb
			output.at<cv::Vec3b>(row, col)[0] = std::pow(src.at<cv::Vec3b>(row, col)[0], r);
			output.at<cv::Vec3b>(row, col)[1] = std::pow(src.at<cv::Vec3b>(row, col)[1], r);
			if (src.channels() == 3)
				output.at<cv::Vec3b>(row, col)[2] = std::pow(src.at<cv::Vec3b>(row, col)[2], r);

			//make sure
			if (output.at<cv::Vec3b>(row, col)[0] > 255)
				output.at<cv::Vec3b>(row, col)[0] = 255;

			if (output.at<cv::Vec3b>(row, col)[1] > 255)
				output.at<cv::Vec3b>(row, col)[1] = 255;

			if (output.at<cv::Vec3b>(row, col)[2] > 255)
				output.at<cv::Vec3b>(row, col)[2] = 255;

		}
	}

	cv::imshow("output", output);
}

void Onbar(int, void*)
{
	float current = (float)value / 20.0;
	PowerLaw(current);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "please input file";
		exit(EXIT_FAILURE);
	}

	src = cv::imread(argv[1]);
	output = cv::Mat(src.rows, src.cols, src.type());

	cv::namedWindow("output");
	cv::createTrackbar("bar", "output", &value, 100, Onbar);
	Onbar(value, 0);
	cv::waitKey(0);

	return 0;
}