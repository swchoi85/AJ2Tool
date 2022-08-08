#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "j2cutil.h"
#include <filesystem>
#include <regex>

using namespace cv;
using namespace std;
int main(int argc,char* argv[])
{
    J2CUtil j2c;
    std::string _dir("./Trans/");
    for (auto& p : filesystem::recursive_directory_iterator(_dir)) {
	auto  path = p.path();

        if (!path.has_extension()) 
	    continue;
        std::string name = path.string();
        if (name.find(".png") == std::string::npos)
            continue;
        printf("Image: %s\n",name.c_str());

        Mat image = imread(name, 0);
        if ( image.empty() ) continue;

        Point P;
        Point Rad;

        cv::Mat norImage = j2c.normalize(image,P,Rad);

        imshow("InitImage", image);
        imshow("NormalizedImg", norImage);

        cvtColor(image,image,cv::COLOR_GRAY2RGB);
	if ( Rad.x )
        cv::circle(image,P,Rad.x,CV_RGB(200,0,0),2,8,0);
	if ( Rad.y )
        cv::circle(image,P,Rad.y,CV_RGB(200,200,0),2,8,0);
        imshow("Pupil", image);

        if (! norImage.empty() )  {
	     j2c.makeFile(p,"Check","iris",image);
        }
        if (! norImage.empty() )  {
	     j2c.makeFile(p,"Conv","normal",norImage);
        }
	if ( argc< 2 )
            waitKey(0);
	else waitKey(10);

    }
    if ( argc> 0 )
            waitKey(1000);
    return 0;
}
