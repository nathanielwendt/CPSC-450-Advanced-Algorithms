//@Implementation for ADT Matrix
//@   data object: a Matrix which is a n by n collection representing a directed graph
//@   data structure: a two dimensional boolean array for Adjacency matrix
//@                   an int for the size,
//@                   an int for the row to highlight when printing
//@                   an array of ints for the stack
//@                   an int for the stackcount
//@   operations/methods: create, destroy, push, pop, printstack, isstackempty, getmatrixsize,
//@                       continue, locationfill, updatevertexvals, dfs, warshallstep, warshall
//@   friend: print as operator<<, input as operator>>

//@author Nathaniel Wendt
//@date April, 2011
//@file matrix.cpp

#include "matrix.h"
#include <string>

//@creates an empty Matrix and initializes size
//@post an empty Matrix
//@usage Matrix matrix;
Matrix::Matrix()
{
   Size = 0;
   HighlightRow = -1;
   StackCount = 0;
}

//@destroys a Matrix
//@pre Matrix object exists
//@post Matrix object does not exist
Matrix::~Matrix()
{}

//@pushes an inputted block onto the stack
//@post the stack is now one element larger
//@param block - the item to be pushed
//@usage Push(10);
void Matrix::Push(int v)
{
   cout << "Stack PUSH: " << v << endl;
   Stack[StackCount++] = v;
}

//@pops a value from the stack
//@post the stack is now one element smaller
//@usage val = Pop();
int Matrix::Pop()
{
   cout << "Stack POP: " << Stack[StackCount - 1] << endl;
   return Stack[--StackCount]; 
}

//@prints the current stack
//@post the stack is printed
//@usage PrintStack();
void Matrix::PrintStack()
{
   for(int i = StackCount - 1; i >= 0; i--){
      cout << Stack[i] << endl;
   }
   if(StackCount == 0)
      cout << "Empty Stack" << endl;
}

//@determines if the stack is empty
//@returns whether stack is empty or not
//@usage if(!IsStackEmpty())
bool Matrix::IsStackEmpty()
{
   return (StackCount == 0);
}

//@finds the size of the data member matrix
//@return the size of the matrix
//@usage size = matrix.GetMatrixSize(); 
int Matrix::GetMatrixSize()
{
   return Size;
}

//@allows user to control the scroll of the screen
//@post accepts an enter key from the user
//@usage ToContinue();
void Continue()
{
   char ch;
   cout << endl;
   cout << "                           Hit <Enter> to continue -> ";
   cin.get(ch);
   system("clear");
}

//@fills a given location in matrix T, if it has not been filled
//@param T - matrix to be populated with new true values
//@param i - row value
//@param j - column value
//@usage LocationFill(T,i,j);
void Matrix::LocationFill(Matrix& T, int i, int j)
{
   if(!T.Adj[i][j]){
      cout << "Filling In Vij where i = " <<i << ", j = " << j << endl;
      T.Adj[i][j] = true;
      cout << T;
      Continue();
   }
}

//@updates the vertex vals in the matrix T, from values j and the current vertex
//@param T - matrix to be populated with new true values
//@param j - column value to inspect
//@param currentV - current vertex to be examined
//@usage UpdateVertexVals(T, j, currentV);
void Matrix::UpdateVertexVals(Matrix& T, int j, int& currentV)
{
   if(Adj[currentV][j] == 1){  
      for(int t = StackCount - 1; t >= 0; t--){
         LocationFill(T, Stack[t], j);                  
         if(Stack[t] == j){ //we have a loop and must update back
            for(int k = t; k < StackCount; k++){
               for(int x = 0; x < Size; x++){
                  if(T.Adj[j][x])
                     LocationFill(T, Stack[k], x); 
               }  
            }
            //catch the last vertice that is not in the stack
            for(int x = 0; x < Size; x++){
                if(T.Adj[j][x])
                     LocationFill(T, currentV, x);  
            }
         }             
      }
   }
}

//@Runs the DFS algorithm and outputs the transitive closure on the inputted matrix
//@The matrix object calling this function and the passed in matrix MUST BE IDENTICAL
//@pre data member matrix is the adjacency matrix and T must be identical
//@post the inputted matrix is now the transitive closure matrix
//@param T - matrix to store the resulting transitive closure
//@usage matrix.DFS(matrix)
void Matrix::DFS(Matrix& T)
{
   int currentV;
   bool foundNext;
   bool visited[MAX_SIZE];
   for(int k = 0; k < Size; k++){
      visited[k] = false;  
   }

   for(int i = 0; i < Size; i++){
      Continue();
      cout << "Now Checking Vertex: " << i << endl << endl;
      if(!visited[i]){        
         //iterative dfs
         currentV = i;
         do {
            PrintStack();
            foundNext = false;
            visited[currentV] = true;
            cout << "Current vertex is now = " << currentV << endl;
            
            //for each vertex in Adj matrix
            int j = 0;
            while(!foundNext && j < Size){
               UpdateVertexVals(T,j,currentV);
               if(Adj[currentV][j] == 1 && !visited[j]){
                     Push(currentV);
                     currentV = j;
                     foundNext = true;
               }
               j++;
            }           
            if(!foundNext && !IsStackEmpty())
               currentV = Pop();   
      
         } while (!IsStackEmpty());
         //end iterative dfs
      }
      PrintStack();
   }
}

//@computes one step of the Warshall algorithm denoted by the input k
//@pre matrix is assumed as R^(k-1)
//@post the data member is now R^(k)
//@param k - denotes the step to compute in Warshalls Algorithm
//@usage matrix.WarshallStep(2);
void Matrix::WarshallStep(int k)
{
   k = k - 1; //indexing happens starting at index 0
   HighlightRow = k+1;
   for(int i = 0; i < Size; i++){
      for(int j = 0; j < Size; j++){
         if((Adj[i][k] and Adj[k][j]) and !Adj[i][j])
            cout << "i = " << i << ", j = " << j << endl;  
         Adj[i][j] = Adj[i][j] or (Adj[i][k] and Adj[k][j]);  
      }  
   } 
}

//@computes all steps of the Warshall algorithm on a data member adjacency matrix
//@post the data member is now R^(Size)
//@usage matrix.Warshall;
void Matrix::Warshall()
{
   for(int k = 1; k <= Size; k++){
      WarshallStep(k);  
   }
   HighlightRow = -1;
}

//@outputs an Matrix to a file or the screen
//@pre A exists. output is open.
//@post contents of rhsitem have been output
//@param output - output stream
//@param A - matrix in which to be outputted
//@usage cout << matrix << endl;   
ostream& operator<< (ostream& output, const Matrix& A)
{
   int row = 0;
   int col = 0;
   
   output << "------------ " << A.Size << " X " << A.Size;
   output << " ------------" << endl;
   while (row < A.Size){
      if(row == A.HighlightRow || col == A.HighlightRow)
         output << "\033[1;34m";
      else
         output << "\033[0m";
      output << A.Adj[row][col] << " ";
      col++;
      if(col == A.Size){
         col = 0;
         row++;
         output << endl;
      }
   }
   output << "\033[0m";
   output << endl;
}

//@inputs the values size, and adjacency matrix from a file or cin
//@pre input stream must be opened
//@post contents of rhsitem have been inputted
//@param input - input stream
//@param A -  matrix to be filled
//@usage cin >> matrix;
istream& operator>> (istream& input, Matrix& A)
{
   int row = 0;
   int col = 0;
   int temp;
   
   if(&input == &cin)
   {
      cout << "---------------- Matrix Enter --------------" << endl;
      cout << "First enter the size of one dimension of the desired matrix: " << endl;
      input >> A.Size;
      cout << "Next enter each value (0/1). Assume that a new row is started when" << endl;
      cout << "Size is reached for the current row" << endl << endl;
      while(row < A.Size){
         input >> temp;
         A.Adj[row][col] = (temp != 0);
         col++;
         if(col == A.Size){
            col = 0;
            row++;
            cout << endl << "Row #" << row + 1 << endl;
         }
      }
      
   } else {
      input >> A.Size;
      while(row < A.Size){
         input >> temp;
         A.Adj[row][col] = (temp != 0);
         col++;
         if(col == A.Size){
            col = 0;
            row++;
         }
      }
   }
}


