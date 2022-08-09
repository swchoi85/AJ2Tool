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
    bool loop = false;
    if  ( argc > 1 ) loop = true;
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
//	printf("Pupil Center %d,%d\n",P.x,P.y);
//	printf("Rad %d,%d\n",Rad.x,Rad.y);

        imshow("InitImage", image);

	if ( !norImage.empty() && Rad.x && Rad.y ) {
            cvtColor(image,image,cv::COLOR_GRAY2RGB);
            cv::circle(image,P,Rad.x,CV_RGB(200,0,0),2,8,0);
            cv::circle(image,P,Rad.y,CV_RGB(200,200,0),2,8,0);
        j2c.makeFile(p,"Check","iris",image);

            imshow("NormalizedImg", norImage);
	    j2c.makeFile(p,"Conv","normal",norImage);
        }
        else {
            Mat dummy = Mat(Size(600,300),CV_8UC1,10);
            j2c.makeFile(p,"Error","iris",image);
            imshow("NormalizedImg", dummy);
        }

        imshow("Pupil", image);

        char key;
        if ( loop == false ) {
            key = waitKey(0);
            if ( key == 'q' || key ==27 ) break;
            if ( key == 'c' ) loop = true;
        }
	else { 
            key = waitKey(1);
            if ( key == 's' ) loop = false;
        }

    }
    waitKey(1000);
    destroyAllWindows();
    return 0;
}
