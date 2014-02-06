//Program inputs 2 matrices (representing adjacency matrices) from an input file, in6.dat. 
//Then it runs Warshall's and Depth First Search on each matrix while showing the user
//how the algorithm works.  The result of the two matrices will be the transitive closure
//of the original adjacency matrices

//@pre program must be run in the command line
//@pre in6.dat must be filled with matrice values separated by spaces 
//@    each new row separated by newline characters.  Furthermore, the first line of the
//@    matrix MUST BE THE INTEGER VALUE OF THE SIZE OF ONE DIMENSION OF THE MATRIX.
//@    for example:
//@    3
//@    0 1 1
//@    1 0 0
//@    0 0 0
//@post prints out the guided two algorithms and their respective transitive closures
//@file prog6.cpp
//@author Nathaniel Wendt (nwendt)
//@date 4/15/2013

#include <iostream>
#include "matrix.h"
using namespace std;

typedef enum {standard,red,green,yellow,blue} color;

//@allows user to control the scroll of the screen
//@post accepts an enter key from the user
//@usage ToContinue();
void ToContinue();

//@prints a number of newlines
//@pre num is nonnegative
//@post num newlines are output
//@usage PrintLines(3);
void PrintLines (int num);

//Opens the file on the ifstream buffer
//@post the buffer is opened to in4.dat or error messages are displayed
//@param infile - ifstream buffer to open file in4.dat
//@usage OpenFile(infile);
void OpenFile(ifstream& infile);

//Changes the systems print color to aid in visual aid
//@param color - enumerated value for the color to change
//@usage MakePrintColor(red);
void MakePrintColor(color mycolor);

//Runs the DFS algorithm on an inputted matrix and prints visualization details
//@param matrix - matrix to be depth first searched
//@usage RunDFS(matrix);
void RunDFS(Matrix& matrix);

//Runs the Warshalls algorithm on an inputted matrix and prints visualization details
//@param matrix - matrix to be computed through Warshalls algorithm
//@usage RunWarshalls(matrix);
void RunWarshalls(Matrix& matrix);

int main()
{
   Matrix matrix,matrix2;
   ifstream infile;
   OpenFile(infile);
   infile >> matrix;
   infile >> matrix2;
   system("clear");
   RunDFS(matrix);
   ToContinue();
   RunWarshalls(matrix2);
}

//Runs the DFS algorithm on an inputted matrix and prints visualization details
//@param matrix - matrix to be depth first searched
//@usage RunDFS(matrix);
void RunDFS(Matrix& matrix)
{
   cout << "Original Adjacency Matrix" << endl;
   cout << matrix;
   MakePrintColor(red);
   cout << "***** Algorithm: Depth First Search  *****" << endl << endl;
   MakePrintColor(standard);
  
   matrix.DFS(matrix);
   
   ToContinue();
   cout << "Transitive Closure" << endl;
   cout << matrix; 
}

//Runs the Warshalls algorithm on an inputted matrix and prints visualization details
//@param matrix - matrix to be computed through Warshalls algorithm
//@usage RunWarshalls(matrix);
void RunWarshalls(Matrix& matrix)
{
   cout << "Original Adjacency Matrix" << endl;
   cout << matrix;
   MakePrintColor(red);
   cout << "***** Algorithm: Warshall's  *****" << endl << endl;
   MakePrintColor(standard);
   ToContinue();
   
   int size = matrix.GetMatrixSize();
   matrix.WarshallStep(0);
   for(int i = 1; i <= size; i++){
      cout << matrix;
      cout << "For each 1 in the highlighted row and each 1 in the highlighted column," << endl;
      cout << "find the pairs of points that need to be made ones.  The points are: " << endl;
      matrix.WarshallStep(i);
      ToContinue();
   }
   
   cout << "Transitive Closure" << endl;
   cout << matrix; 
}

//Changes the systems print color to aid in visual aid
//@param color - enumerated value for the color to change
//@usage MakePrintColor(red);
void MakePrintColor(color mycolor)
{
   if(mycolor == standard)
      cout << "\033[0m";
   if(mycolor == red)
      cout << "\033[1;31m";
   else if(mycolor == green)
      cout << "\033[1;32m";
   else if(mycolor == yellow)
      cout << "\033[1;33m";
   else if(mycolor == blue)
      cout << "\033[1;34m";
}

//Opens the file on the ifstream buffer
//@post the buffer is opened to in6.dat or error messages are displayed
//@param infile - ifstream buffer to open file in4.dat
//@usage OpenFile(infile);
void OpenFile(ifstream& infile)
{
    infile.open("in6.dat");
    if (infile.fail())
    {
        cout << "There was an error opening the data file " << endl;
        exit(1);
    }
}

//@allows user to control the scroll of the screen
//@post accepts an enter key from the user
//@usage ToContinue();
void ToContinue()
{
   char ch;
   PrintLines(2);
   cout << "                           Hit <Enter> to continue -> ";
   cin.get(ch);
   system("clear");
}

//@prints a number of newlines
//@pre num is nonnegative
//@post num newlines are output
//@usage PrintLines(3);
void PrintLines (int num)
{
   for (int k = 0; k < num; k++)
      cout << endl;
}

