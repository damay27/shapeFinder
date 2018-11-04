#include "helperFunctions.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;

params parseArgs(int argc, char** argv)
{

    int index = 1;
    
    params p;
    p.red = 0; 
    p.green = 255;
    p.blue = 0;
    p.outFile = "outImg.png";
    p.inFile = "";
    p.points = 4;
    
    
    
    //This loop goes through the arguments and splits them into commands and data
    while(index<argc)
    {
        string currentArg(argv[index]);
        
        //Commands always start with '-'
        if(currentArg.at(0) == '-')
        {
            
            if(currentArg.at(1) == '-')
            {
                currentArg.erase(1,1);
            }
            
            //Identify the argument type
            if(currentArg.at(1) == 's' || currentArg.substr(1, 5) == "shape")
            {
                
                //revome the argument command so only the data is left
                if(currentArg.substr(1, 5) == "shape")
                {
                    currentArg.erase(0, 6);
                }
                else
                {
                    currentArg.erase(0,2);
                }
                
                //If ther is a space in between commands then get the data
                //from the next index
                if(currentArg.size()<=0)
                {
                    index++;//Index is intentionally moved twice
                    currentArg = string(argv[index]);
                }
                
                
                //Set the number of points based on the parameter
                if(currentArg == "triangle" || currentArg == "Triangle")
                {
                    p.points = 3;
                }
                else if(currentArg == "rectangle" || currentArg == "Rectangle")
                {
                    p.points = 4;
                }
                else if(currentArg == "pentagon" || currentArg == "Pentagon")
                {
                    p.points = 5;
                }
               else if(currentArg == "hexagon" || currentArg == "Hexagon")
                {
                    p.points = 6;
                }
                
                cout<<"Finding a shape with "<<p.points<<" points."<<endl;
                
                
            }
            else if(currentArg.at(1) == 'c' || currentArg.substr(1, 5) == "color")
            {
                
                //revome the argument command so only the data is left
                if(currentArg.substr(1, 5) == "color")
                {
                    currentArg.erase(0, 6);
                }
                else
                {
                    currentArg.erase(0,2);
                }
                
                //If ther is a space in between commands then get the data
                //from the next index
                if(currentArg.size()<=0)
                {
                    index++;//Index is intentionally moved twice
                    currentArg = string(argv[index]);

                }
                

                //Set the number of points based on the parameter
                if(currentArg == "red" || currentArg == "Red")
                {
                    p.red = 255;
                    p.blue = 0;
                    p.green = 0;
                }
                else if(currentArg == "blue" || currentArg == "Blue")
                {
                    p.red = 0;
                    p.blue = 255;
                    p.green = 0;
                }
                else if(currentArg == "green" || currentArg == "Green")
                {
                    p.red = 0;
                    p.blue = 0;
                    p.green = 255;
                }
                else if(currentArg == "white" || currentArg == "White")
                {
                    p.red = 255;
                    p.blue = 255;
                    p.green = 255;
                }
                else if(currentArg == "black" || currentArg == "Black")
                {
                    p.red = 0;
                    p.blue = 0;
                    p.green = 0;
                }
                else if(currentArg == "grey" || currentArg == "Grey")
                {
                    p.red = 128;
                    p.blue = 128;
                    p.green = 128;
                }
                else if(currentArg.at(0) == 'x')
                {
                    if(currentArg.size() == 7)
                    {
                        p.red = stoi(currentArg.substr(1,2), 0, 16);
                        p.green = stoi(currentArg.substr(3,2), 0, 16);
                        p.blue =  stoi(currentArg.substr(5,2), 0, 16);
                    }
                    else
                    {
                        cout<<"Invalid color argument. Using default color."<<endl;
                    }
                }
                
                cout<<"Color is (" << int(p.red) << ", " << int(p.blue) << ", "<< int(p.green) << ")." <<endl;
            }
            else if(currentArg.at(1) == 'o')
            {
                currentArg.erase(0,2); 
                
                //If ther is a space in between commands then get the data
                //from the next index
                if(currentArg.size()<=0)
                {
                    index++;//Index is intentionally moved twice
                    currentArg = string(argv[index]);

                }
                
                p.outFile = currentArg;
                cout<<"Saving image to "<<p.outFile<<endl;
            }
            
        }
        //If the argument does not have a '-' in fron then it is the input
        //file name
        else
        {
            p.inFile = currentArg;
            cout<<"Opening file "<<p.inFile<<endl;
        }
        
        index++;
        
    }
    
    return p;
    
}



//Check that p0 is on a horizontal line with only one of the other points and
//that p0 is on a vertical line with only one of the other points
bool rectCheck(Point p0, Point p1, Point p2, Point p3)
{
    //Calculate the slopes between p0 and the three other points
    double slope1 = abs(double(p0.y - p1.y))/abs(double(p0.x - p1.x));
    double slope2 = abs(double(p0.y - p2.y))/abs(double(p0.x - p2.x));
    double slope3 = abs(double(p0.y - p3.y))/abs(double(p0.x - p3.x));
    
    //check to make sure that ONLY one of the points is on a horizontal line
    //with p0
    bool horizontal = (slope1<.2) ^ (slope2<.2) ^ (slope3<.2);
    //check to make sure that ONLY one of the points is on a vertical line
    //with p0
    bool vertical = (slope1>.8) ^ (slope2>.8) ^ (slope3>.8);
    

    return (horizontal && vertical);

    
    
    
}