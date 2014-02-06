//Program finds the convex hull of a given set of points using the 
//QuickHull "Divide and Conquer" method.  
//The points are determined from an input file in5.dat.  
//The convex hull is printed out as pairs of points that determine each line segment.

//@pre program must be run in the command line
//@pre in5.dat must be filled with points separated by commas and 
//@    each new point separated by newline characters.  Furthermore, the points must
//@    be sorted in increasing order on the x-coordinate and then by increasing order
//@    on the y-coordinate.  Also MAKE SURE THE LAST ENTRY DOESN'T HAVE A NEWLINE AFTER IT!
//@post prints out the pair of points to connect in a well-designed format
//@file prog5.cpp
//@author Nathaniel Wendt (nwendt)
//@date 3/26/2013

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

struct point{
   int x;
   int y; 
};

//Prints a given number of new line characters
//@param numLines - number of lines to be printed
//@usage printLines(5);
void PrintLines(int numLines);

//Opens the file on the ifstream buffer
//@post the buffer is opened to in4.dat or error messages are displayed
//@param infile - ifstream buffer to open file in4.dat
//@usage OpenFile(infile);
void OpenFile(ifstream& infile);

//From a given file input stream buffer, the function fills an array with points
//The array size will be 2 * the number of points since they are (x,y) coordinate pairs
//@pre infile buffer must be opened
//@param points[] - array to be populated with values
//@param infile - buffer pointing to the beginning of the file
//@usage FillPoints(points, infile);
int FillPoints(point points[], ifstream& infile);

//Prints the extreme points based on the given i and j index
//@param points[] - array containing points
//@param i - index value of point 1 to print
//@param j - index value of point 2 to print
//@usage PrintExtremePoints(points, i , j);
void PrintExtremePoints(point points[], int count);

//Prints the program heading
//usage PrintHeading();
void PrintHeading();

//Finds the convex hull by using the quickhull method
//@param points[] - array containing the points to form the hull with
//@param size - size of array
//@usage GetQuickHull(points,size);
void GetQuickHull(point points[],int size);

//Finds the intial sets S1 and S2 from a given set of points
//S1 will be points to the left of the line formed from the first and last points of the points array
//S2 will be points to the right of the line formed from the first and last points of the points array
//@param points[] - array of points to separate
//@param S1[] - array to populate with set S1
//@param S1count - count to be updated with the number of elements in S1
//@param S2[] - array to populate with set S2
//@param S2count - count to be updated with the number of elements in S2
//@param size - size of the points array
//@post the S1count and S2count will be updated and S1[] and S2[] will be populated
//@usage FindS1andS2(points,s1,s1count,s2,s2count,size);
void FindS1andS2(point points[], point S1[], int &S1count, point S2[], int &S2count, int size);

//Finds the maximum distance from a line given a subset of points
//@pre The first and last elements of Sx will contain the points on the line
//@param Sx[] - array of points
//@param Scount - count of points in array
//@returns the point that is farthest away from the line
//@usage Pmax = FindPmax(points,10);
point FindPmax(point Sx[], int Scount);

//Finds the distance squared from the line between P1 and P2 and the point P3
//This algorithm returns the distance squared to save computing resources
//@param P1 - first point on line
//@param P2 - second point on line
//@param P3 - third point to check distance from line
//@return the distance squared
//@usage distance = FindDistance(P1,P2,Px);
int FindDistance(point P1, point P2, point P3);

//Finds the two subsets from a given pmax point
//@param points[] - array of points to be sent to subsets
//@param size - size of the points array
//@param pmax - point containing the pmax value
//@param sub1[] - subset 1 array to be populated
//@param sub1Count - subset 1 count
//@param sub2[] - subset 2 array to be populated
//@param sub2Count - subset 2 count
//@param testLeft - determines if the algorithm should test on left side or right of line
//@post sub1[] and sub2[] will be populated and sub1Count and sub2Count will be updated
//@usage FindSubsets(points,size,pmax,sub1,sub1Count,sub2,sub2Count,true);
void FindSubsets(point points[], int size, point pmax, point sub1[], int& sub1Count, 
                 point sub2[], int& sub2Count, bool testLeft);
                
//Tests the direction that the point Px is with respect to he line between P1 and P2
//@param P1 - first point on the line to test
//@param P2 - second point on the line to test
//@param Px - point to test as left or right of the line
//@param testLeft - whether to test on left side or right side
//@returns if the point Px is on the given direction with respect to the line
//@usage TestDirection(p1,p2,px,true);  
bool TestDirection(point P1, point P2, point Px, bool testLeft);

//Recursive function for finding the extreme points and appending them to the extremePoints[] array
//@param points[] - array containing the points
//@param count - size of points array
//@param extremePoints[] - array containing the extreme points
//@param extremeCount - count of extreme points array
//@param checkLeft - whether the function should test on left side of line or right side
//@post testLeft is updated with the correct count
//@usage GetExtremePoints(points,count,extremePoints,extremeCount,testLeft);
void GetExtremePoints(point points[], int count, point extremePoints[], 
                      int &extremeCount, bool checkLeft);

int main()
{
   point points[20];
   ifstream infile;
   int size;
   
   OpenFile(infile);
   size = FillPoints(points,infile);

   PrintLines(2);
   PrintHeading();
   PrintLines(2);
   
   GetQuickHull(points,size);
}

//Finds the distance squared from the line between P1 and P2 and the point P3
//This algorithm returns the distance squared to save computing resources
//@param P1 - first point on line
//@param P2 - second point on line
//@param P3 - third point to check distance from line
//@return the distance squared
//@usage distance = FindDistance(P1,P2,Px);
int FindDistance(point P1, point P2, point P3)
{
   int D;
   D = P1.x * (P2.y - P3.y) - P1.y * (P2.x - P3.x) + (P2.x * P3.y - P3.x * P2.y);
   return D * D;  
}

//Finds the maximum distance from a line given a subset of points
//@pre The first and last elements of Sx will contain the points on the line
//@param Sx[] - array of points
//@param Scount - count of points in array
//@returns the point that is farthest away from the line
//@usage Pmax = FindPmax(points,10);
point FindPmax(point sx[], int sCount)
{
   int distance;
   int maxSoFar = 0;
   point max;
   for(int i = 1; i < sCount - 1; i++){
      distance = FindDistance(sx[0], sx[sCount - 1], sx[i]);
      if(distance > maxSoFar){
         maxSoFar = distance;
         max = sx[i];
      }
   }
   if(maxSoFar == 0){ //corrects if FindDistance returns 0
      return sx[1];
   } else
      return max;
}

//Finds the intial sets S1 and S2 from a given set of points
//S1 will be points to the left of the line formed from the first and last points of the points array
//S2 will be points to the right of the line formed from the first and last points of the points array
//@param points[] - array of points to separate
//@param S1[] - array to populate with set S1
//@param S1count - count to be updated with the number of elements in S1
//@param S2[] - array to populate with set S2
//@param S2count - count to be updated with the number of elements in S2
//@param size - size of the points array
//@post the S1count and S2count will be updated and S1[] and S2[] will be populated
//@usage FindS1andS2(points,s1,s1count,s2,s2count,size);
void FindS1andS2(point points[], point S1[], int &S1count, point S2[], int &S2count, int size)
{
   point P1 = points[0];
   point P2 = points[size - 1];
   
   S1count = 0;
   S2[0] = P1; S2count = 1;
   int loopCount;
   for(int i = 0; i < size; i++){
      if(TestDirection(P1, P2, points[i],true)){
         S1[S1count] = points[i];
         S1count++;
      } else {
         S2[S2count] = points[i];
         S2count++;
      }
      loopCount = i;
   } 
   S2[S2count++] = points[loopCount];
}

//Finds the two subsets from a given pmax point
//@param points[] - array of points to be sent to subsets
//@param size - size of the points array
//@param pmax - point containing the pmax value
//@param sub1[] - subset 1 array to be populated
//@param sub1Count - subset 1 count
//@param sub2[] - subset 2 array to be populated
//@param sub2Count - subset 2 count
//@param testLeft - determines if the algorithm should test on left side or right of line
//@post sub1[] and sub2[] will be populated and sub1Count and sub2Count will be updated
//@usage FindSubsets(points,size,pmax,sub1,sub1Count,sub2,sub2Count,true);
void FindSubsets(point points[], int size, point pmax, point sub1[], int& sub1Count, 
                 point sub2[], int& sub2Count, bool testLeft)
{
   point P1 = points[0];
   point P2 = pmax;
   point P3 = points[size - 1];    
   sub1[0] = P1;
   sub1Count = 1; sub2Count = 0;
   
   for(int i = 1; i < size - 1; i++){
      if(TestDirection(P1, P2, points[i],testLeft)){
         sub1[sub1Count] = points[i];
         sub1Count++;  
      }
      if(TestDirection(P2, P3, points[i],testLeft)){
         sub2[sub2Count] = points[i];
         sub2Count++;
      }
   }
   sub2[sub2Count] = P3;
   sub2Count++;
}

//Recursive function for finding the extreme points and appending them to the extremePoints[] array
//@param points[] - array containing the points
//@param count - size of points array
//@param extremePoints[] - array containing the extreme points
//@param extremeCount - count of extreme points array
//@param checkLeft - whether the function should test on left side of line or right side
//@post testLeft is updated with the correct count
//@usage GetExtremePoints(points,count,extremePoints,extremeCount,testLeft);
void GetExtremePoints(point points[], int count, point extremePoints[], int &extremeCount, bool testLeft)
{
   if(count > 2){
      int sub1Count, sub2Count;
      point sub1[count];
      point sub2[count];
      point pmax = FindPmax(points,count);
      FindSubsets(points, count, pmax, sub1, sub1Count, sub2, sub2Count, testLeft);
      
      if(testLeft){
         GetExtremePoints(sub1,sub1Count,extremePoints,extremeCount,testLeft);
         extremePoints[extremeCount++] = pmax;
         GetExtremePoints(sub2,sub2Count,extremePoints,extremeCount,testLeft);
      } else {
         GetExtremePoints(sub2,sub2Count,extremePoints,extremeCount,testLeft);
         extremePoints[extremeCount++] = pmax;
         GetExtremePoints(sub1,sub1Count,extremePoints,extremeCount,testLeft);
      }
   }
}

//Finds the convex hull by using the quickhull method
//@param points[] - array containing the points to form the hull with
//@param size - size of array
//@usage GetQuickHull(points,size);
void GetQuickHull(point points[], int size)
{
   int S1count;
   int S2count;
   point S1[size];
   point S2[size];
   point extremePoints[size];
   int extremeCount = 0;
   
   FindS1andS2(points,S1,S1count,S2,S2count,size);
   
   extremePoints[extremeCount++] = points[0];
   GetExtremePoints(S1,S1count,extremePoints,extremeCount,true);
   extremePoints[extremeCount++] = points[size - 1];
   GetExtremePoints(S2,S2count,extremePoints,extremeCount,false); 

   PrintExtremePoints(extremePoints,extremeCount);
   PrintLines(2);
}

//Prints the program heading
//usage PrintHeading();
void PrintHeading()
{
   cout << "The Convex Hull is defined by the following points " << endl;
   cout << "      and is found using the QuickHull method      " << endl;
   cout << "---------------------------------------------------" << endl;
}

//Prints the extreme points as pairs of points that form edges of the hull
//@param points[] - array containing points
//@param count - size of array to print
//@usage PrintExtremePoints(points, size);
void PrintExtremePoints(point points[], int count)
{
   for(int i = 0; i < count; i++){
      cout << points[i].x << "," << points[i].y;
      cout << " -- ";
      cout << points[(i + 1) % count].x << ",";
      cout << points[(i + 1) % count].y << endl;
   }
}

//Opens the file on the ifstream buffer
//@post the buffer is opened to in5.dat or error messages are displayed
//@param infile - ifstream buffer to open file in5.dat
//@usage OpenFile(infile);
void OpenFile(ifstream& infile)
{
    infile.open("in5.dat");
    if (infile.fail())
    {
        cout << "There was an error opening the data file " << endl;
        exit(1);
    }
}

//From a given file input stream buffer, the function fills an array with points
//@pre infile buffer must be opened
//@param points[] - array to be populated with values
//@param infile - buffer pointing to the beginning of the file
//@returns the number of points retrieved
//@usage size = FillPoints(points, infile);
int FillPoints(point points[], ifstream& infile)
{
   int i = 0;
   string temp;
   
   while(!infile.eof())
   {
      getline(infile,temp,',');
      points[i].x = atoi(temp.c_str());
      getline(infile,temp,'\n');
      points[i].y = atoi(temp.c_str());

      i++;
   }
   return i;
}

//Prints a given number of new line characters
//@pre numLines must be non-negative to print lines
//@param numLines - number of lines to be printed
//@usage printLines(5);
void PrintLines(int numLines)
{
   for(int i = 0; i < numLines; i++)
      cout << "\n";
}

//Tests the direction that the point Px is with respect to he line between P1 and P2
//@param P1 - first point on the line to test
//@param P2 - second point on the line to test
//@param Px - point to test as left or right of the line
//@param testLeft - whether to test on left side or right side
//@returns if the point Px is on the given direction with respect to the line
//@usage TestDirection(p1,p2,px,true);
bool TestDirection(point P1, point P2, point Px, bool testLeft)
{
   if(testLeft)  
      return ((P2.x - P1.x) * (Px.y - P1.y) - (P2.y - P1.y) * (Px.x - P1.x)) >= 0;
   else
      return ((P2.x - P1.x) * (Px.y - P1.y) - (P2.y - P1.y) * (Px.x - P1.x)) <= 0;
}
