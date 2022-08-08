#include "opencv2/opencv.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "j2cutil.h"
#include <filesystem>
#include <regex>

using namespace cv;
using namespace std;

// normalize use 
//
// int flags = INTER_LINEAR + WARP_FILL_OUTLIERS;
// warpPolar(Mat soruce, Mat dst, Size(w,h),Point2f(x,y), radius, flags);

cv::Mat ImageRotateInner(const cv::Mat src, double degree
	, cv::Point2f base=cv::Point2f(std::numeric_limits<float>::infinity())) {
	if (base.x == std::numeric_limits<float>::infinity()) {
		base.x = src.cols / 2;
		base.y = src.rows / 2;
	}
	cv::Mat dst = src.clone();
	cv::Mat rot = cv::getRotationMatrix2D(base, degree, 1.0);
	cv::warpAffine(src, dst, rot, src.size());
	return std::move(dst);
}

cv::Mat Rotate3D(const cv::Mat src, cv::Point p,int opt)
{
    Mat dst;
    int w,h;
    w = src.cols;
    h = src.rows;
//    printf("w,h %dx%d\n",w,h);
//    printf("x,y %dx%d\n",p.x,p.y);
    cv::Point2f src_p[4],dst_p[4];

    src_p[0] = Point2f(w-1,h-1);
    src_p[1] = Point2f(w-1,0);
    src_p[2] = Point2f(0,h-1);
    src_p[3] = Point2f(0,0);

    if ( opt ==1  ) {
        dst_p[0] = Point2f(w-p.x,h-p.y);
        dst_p[1] = Point2f(w-1,0);
        dst_p[2] = Point2f(0,h-1);
        dst_p[3] = Point2f(0,0);
    }
    else if ( opt ==2  ) {
        dst_p[0] = Point2f(w-1,h-1);
        dst_p[1] = Point2f(w-p.x,p.y);
        dst_p[2] = Point2f(0,h-1);
        dst_p[3] = Point2f(0,0);
    }
    else if ( opt ==3  ) {
        dst_p[0] = Point2f(w-1,h-1);
        dst_p[1] = Point2f(w-1.,0);
        dst_p[2] = Point2f(p.x,h-p.y);
        dst_p[3] = Point2f(0,0);
    }
    else  {
        dst_p[0] = Point2f(w-1,h-1);
        dst_p[1] = Point2f(w-1,0);
        dst_p[2] = Point2f(0,h-1);
        dst_p[3] = Point2f(p.x,p.y);
    }

    Mat perspectiveMap = getPerspectiveTransform(src_p,dst_p);
    warpPerspective(src,dst,perspectiveMap,Size(w,h), INTER_LINEAR, BORDER_CONSTANT);
    
    return dst;
}

int main(int argc,char *argv[])
{
    J2CUtil j2c;
    std::string _dir("./Iris/");
    for (auto& p : filesystem::recursive_directory_iterator(_dir)) {
	auto  path = p.path();

        if (!path.has_extension()) 
	    continue;
        std::string name = path.string();
        if (name.find(".png") == std::string::npos)
            continue;
        printf("Name: %s\n",name.c_str());

        Mat image = imread(name, 0);
        if ( image.empty() ) continue;
        imshow("OrgImage", image);
        j2c.makeFile(p,"Trans","org",image);

	// Rotate Image
	cv::Point2f li;
	li.x =image.rows/2;
	li.y =image.cols/2;
	cv::Mat mod;

        mod = ImageRotateInner(image,(double)10.,li);
        if (! mod.empty() )  {
            imshow("Rotation+10", mod);
            j2c.makeFile(p,"Trans","rot1",mod);
        }

        mod = ImageRotateInner(image,(double)-10.,li);
        if (! mod.empty() )  {
            imshow("Rotation-10", mod);
            j2c.makeFile(p,"Trans","rot2",mod);
        }

	// contrast & brightness
	float alpha =1.3;
	float beta = 10;

//	image.convertTo(mod, -1, alpha, beta);
	image.convertTo(mod, -1, 1.4, 10);
        if (! mod.empty() )  {
            imshow("contrast_1.4", mod);
            j2c.makeFile(p,"Trans","cont_1.4",mod);
        }
	image.convertTo(mod, -1, 1.2, 10);
        if (! mod.empty() )  {
            imshow("contrast_1.3", mod);
            j2c.makeFile(p,"Trans","cont_1.2",mod);
        }

	image.convertTo(mod, -1, 0.8, -10);
        if (! mod.empty() )  {
            imshow("contrast_0.8", mod);
            j2c.makeFile(p,"Trans","cont_0.8",mod);
        }
	image.convertTo(mod, -1, 0.6, -10);
        if (! mod.empty() )  {
            imshow("contrast_0.6", mod);
            j2c.makeFile(p,"Trans","cont_0.6",mod);
        }

	// 3d rotate
	cv::Point diff;
	diff.x = 30;
	diff.y = 30;

        mod = Rotate3D(image,  diff,1);
        if (! mod.empty() )  {
            imshow("3d_1", mod);
            j2c.makeFile(p,"Trans","3d_1",mod);
        }
        mod = Rotate3D(image,  diff,2);
        if (! mod.empty() )  {
            imshow("3d_2", mod);
            j2c.makeFile(p,"Trans","3d_2",mod);
        }
        mod = Rotate3D(image,  diff,3);
        if (! mod.empty() )  {
            imshow("3d_3", mod);
            j2c.makeFile(p,"Trans","3d_3",mod);
        }
        mod = Rotate3D(image,  diff,0);
        if (! mod.empty() )  {
            imshow("3d_0", mod);
            j2c.makeFile(p,"Trans","3d_0",mod);
        }

	if ( argc< 2) 
            waitKey(0);
	else waitKey(10);

    }
    if ( argc> 1) 
	    waitKey(1000);
    return 0;
}
