#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

struct params
{
  unsigned int points;
  unsigned char red, blue, green;
  string outFile, inFile;
};

params parseArgs(int argc, char** argv);

bool rectCheck(Point p0, Point p1, Point p2, Point p3);

#endif