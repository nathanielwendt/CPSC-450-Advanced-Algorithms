//@author Nathaniel Wendt
//@date April, 2013
//@file matrix.h

//@Specification for ADT Matrix
//@   data object: a Matrix which is a n by n collection representing a directed graph
//@   operations/methods: create, destroy, push, pop, printstack, isstackempty, getmatrixsize,
//@                       continue, locationfill, updatevertexvals, dfs, warshallstep, warshall
//@   friend: print as operator<<, input as operator>>

#ifndef MATRIX_H
#define MATRIX_H
const int MAX_SIZE = 40;

#include <iostream>
#include <fstream>
using namespace std;

class Matrix
{
   //@outputs an Matrix to a file or the screen
   //@pre A exists. output is open.
   //@post contents of rhsitem have been output
   //@param output - output stream
   //@param A - matrix in which to be outputted
   //@usage cout << matrix << endl;   
   friend ostream& operator<< (ostream& output, const Matrix& A);
   
   //@inputs the values size, and adjacency matrix from a file or cin
   //@pre input stream must be opened
   //@post contents of rhsitem have been inputted
   //@param input - input stream
   //@param A -  matrix to be filled
   //@usage cin >> matrix;
   friend istream& operator>> (istream& input, Matrix& A);
   
public:

   //@creates an empty Matrix and initializes size
   //@post an empty Matrix
   //@usage Matrix matrix;
   Matrix();

   //@destroys a Matrix
   //@pre Matrix object exists
   //@post Matrix object does not exist
   ~Matrix();
   
   //@Runs the DFS algorithm and outputs the transitive closure on the inputted matrix
   //@The matrix object calling this function and the passed in matrix MUST BE IDENTICAL
   //@pre data member matrix is the adjacency matrix and T must be identical
   //@post the inputted matrix is now the transitive closure matrix
   //@param T - matrix to store the resulting transitive closure
   //@usage matrix.DFS(matrix)
   void DFS(Matrix& T);
   
   //@computes one step of the Warshall algorithm denoted by the input k
   //@pre matrix is assumed as R^(k-1)
   //@post the data member is now R^(k)
   //@param k - denotes the step to compute in Warshalls Algorithm
   //@usage matrix.WarshallStep(2);
   void WarshallStep(int k);
   
   //@computes all steps of the Warshall algorithm on a data member adjacency matrix
   //@post the data member is now R^(Size)
   //@usage matrix.Warshall;
   void Warshall();
   
   //@finds the size of the data member matrix
   //@return the size of the matrix
   //@usage size = matrix.GetMatrixSize(); 
   int GetMatrixSize();
   
private:
   //@pushes an inputted block onto the stack
   //@post the stack is now one element larger
   //@param block - the item to be pushed
   //@usage Push(10);
   void Push(int block);
   
   //@pops a value from the stack
   //@post the stack is now one element smaller
   //@usage val = Pop();
   int Pop();
   
   //@determines if the stack is empty
   //@returns whether stack is empty or not
   //@usage if(!IsStackEmpty())
   bool IsStackEmpty();
   
   //@updates the vertex vals in the matrix T, from values j and the current vertex
   //@param T - matrix to be populated with new true values
   //@param j - column value to inspect
   //@param currentV - current vertex to be examined
   //@usage UpdateVertexVals(T, j, currentV);
   void UpdateVertexVals(Matrix& T, int j, int& currentV);
   
   //@fills a given location in matrix T, if it has not been filled
   //@param T - matrix to be populated with new true values
   //@param i - row value
   //@param j - column value
   //@usage LocationFill(T,i,j);
   void LocationFill(Matrix& T, int i, int j);
   
   //@prints the current stack
   //@post the stack is printed
   //@usage PrintStack();
   void PrintStack();
   
   //For Warshall
   bool Adj[MAX_SIZE][MAX_SIZE];
   int Size;
   int HighlightRow;
   
   //For DFS
   int Stack[MAX_SIZE];
   int StackCount;
};
#endif
