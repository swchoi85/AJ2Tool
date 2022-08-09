#ifndef J2CUTIL_H
#define J2CUTIL_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/videoio/legacy/constants_c.h>

#include <filesystem>
#include <regex>

using namespace cv;
using namespace std;

class J2CUtil 
{
public:
    J2CUtil();
    ~J2CUtil();

    Mat normalize(Mat img,Point& innerP,Point& rad);
    void makeFile(filesystem::path path,string dir,string name,Mat img);

private:
};

#endif // J2CUTIL_H
