#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "result.png";

int main()
{
	int argc = 5;
	char* argv[5];
	argv[1] = "1.png";
	argv[2] = "2.png";
	argv[3] = "3.png";
	argv[4] = "4.png";
	argv[5] = "5.png";

	for (int i = 1; i < argc; ++i)
    {
        Mat img = imread(argv[i]);
        if (img.empty())
        {
            cout << "Can't read image '" << argv[i] << "'\n";
            return -1;
        }
        imgs.push_back(img);
    }

    Mat pano;
    Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
    Stitcher::Status status = stitcher.stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << int(status) << endl;
        return -1;
    }

    imwrite(result_name, pano);
	imshow("result", pano);
	waitKey();
    return 0;
}
