#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "helperFunctions.hpp"
using namespace std;
using namespace cv;



int main(int argc, char** argv )
{
    
    //Get parameters and convert image to greyscale
    params p = parseArgs(argc, argv);
    
    if(p.inFile == "")
    {
        cout<<"No input file given"<<endl;
        return 0;
    }
    
    Mat image = imread(p.inFile, CV_LOAD_IMAGE_COLOR);
    Mat greyImage, cannyImage, outImage;
    GaussianBlur(greyImage, greyImage, Size(5,5), 0, 0);
    outImage = image;
    Scalar color(p.blue, p.green, p.red);
    cvtColor(image, greyImage, CV_RGB2GRAY);
    
    //Apply Canny edge detection and find contours
    Canny(greyImage, cannyImage, 128, 255, 5);
    vector<vector<Point>> contours;
    findContours(cannyImage, contours, RETR_LIST , CV_CHAIN_APPROX_SIMPLE);
    
    //Loop through the contours
    for(unsigned int index = 0; index <contours.size(); index++)
    {
        vector<Point> contour = contours.at(index);
        
        vector<Point> poly;

        //Approximate a polygon for the contour
        approxPolyDP(contour, poly, 5, true);
        

        //If the number of points in the polygon matches the number of points 
        //we are looking for then draw the polygon
        if(poly.size() == p.points)
        {
            
            //Do this if you are trying to find rectangles since the points need to
            //form parallel lines
            if(p.points == 4)
            {
                //Extract the indevidual points
                Point p0, p1, p2, p3;
                p0 = poly.at(0);
                p1 = poly.at(1);
                p2 = poly.at(2);
                p3 = poly.at(3);
                
                
                //Check that each point is on a horizontal line with only one of the other points and
                //that p0 is on a vertical line with only one of the other points
                bool isRect = rectCheck(p0, p1, p2, p3);
                isRect &= rectCheck(p1, p0, p2, p3);
                isRect &= rectCheck(p2, p0, p1, p3);
                isRect &= rectCheck(p3, p0, p1, p2);
                
                
                //If it can be proven that the four points do actually form a
                //rectangle then draw the bounding box
                if(isRect)
                {
                    //Find and draw the bounding box 
                    Rect r = boundingRect(poly);
                    rectangle(outImage, r, color, 2);
                }
                
            }
            else//For all other shapes except rectangles
            {
                //Find and draw the bounding box   
                Rect r = boundingRect(poly);
                rectangle(outImage, r, color, 2);
            }
        }
        
    }
    
    


    imwrite(p.outFile, outImage);
    
    cout<<"Done"<<endl;

    return 0;
}



