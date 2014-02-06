//Program calculates the Fibonacci sequence to a given index inputted by the user.
//If the user inputs an index that pushes the Fibonacci sequence beyond the range
//of unsigned int, the program will notice and stop the sequence at that threshold
//The program will then calculate the Fibonacci sequence using the esimation method
//and the matrix method

//@pre program must be run in the command line
//@file prog2.cpp
//@author Nathaniel Wendt (nwendt)
//@date 2/15/2013

#include <iostream>
#include <math.h> //solely for the purpose of the sqrt function
using namespace std;

//Prints the title of the method indicated by the index value
//@param index - index value for title to print, 1 = estimation, 0 = matrix
//@usage PrintMethodTitle(1);
void PrintMethodTitle(int index);

//Prints a given number of new line characters
//@pre numLines must be non-negative to print lines
//@param numLines - number of lines to be printed
//@usage printLines(5);
void PrintLines(int numLines);

//Gets the input integer from the user
//@return the integer value of the user input
//@usage input = getInput();
int GetInput();

//Prints the welcome message for the program
//@usage PrintWelcomeMessage();
void PrintWelcomeMessage();

//Controls the computation and printing of the Fibonacci Array Method
//@pre n must be a natural number
//@param n - index to compute Fibonacci to
//@return the index value of n that has been checked to fit the output within bounds
//@usage answer = FindFibArray(10);
int FindFibArray(int n);

//Computes the fibonacci sequence with the linear array method
//@pre n must be a natural number
//@pre Fib[] must have memory allocated to fit Fib[n] locations
//@post n is updated if it as an index was larger than a Fibonacci number can fit in an unsigned int
//@post Fib[] is populated with the Fibonacci sequence
//@param n - index to calculate Fibonacci to
//@param Fib[] - array to be populated with Fibonacci numbers.
//@returns a pointer to the array populated with the Fibonacci sequence.
//@usage unsigned int *filledFib = ComputeFib(10,Fib);
unsigned int* ComputeFib(int &n, unsigned int Fib[]);

//Prints the Fibonacci sequence calculated with the array method
//@pre n must be a natural number
//@pre Fib[] must have memory allocated to fit Fib[n] locations
//@param n - index to print the Fibonacci sequence to
//@param Fib[] - populated Fibonacci sequence as an array
//@usage PrintFib(10,Fib);
void PrintFib(int n, unsigned int Fib[]);

//Determines the spacing value to print before a given value of the Fibonacci sequence - aligns the output
//@param testVal - value to check how many leading spaces should be printed
//@returns the string spacing according to the testVal
//@usage cout << DetermineSpacing(610);
string DetermineSpacing(unsigned int testVal);

//Prints the Fibonacci Heading for a given calculation
//@param index - index of sequence to print
//@param value - value of sequence to print
//@usage PrintFibonacciHeading(10,55);
void PrintFibonacciHeading(int index, unsigned int value);

//Controls the calculation and printing of the Fibonacci sequence for the estimation method
//@pre index must be a natural number
//@param index - index to calculate the Fibonacci sequence to
//@usage FindFibround(20);
void FindFibRound(int index);

//Breaks down a given exponential into squared versions of itself to compute in logarithmic time
//@pre phi must be positive
//@pre power must be > 0
//@param phi - base number to be raised to a given power
//@param power - exponent to raise the base of phi to
//@returns a double that contains the exponent calculation
//@usage QuickExponent(phi,8);
double QuickExponent(double phi, int power);

//Rounds a given double number to its nearest integer
//@pre unroundedNum > 0
//@param unroundedNum - number to be rounded
//@returns the rounded number
//@usage RoundNumber(30.556);
unsigned int RoundNumber(double numberD);

//Controls the computation and printing of the matrix method
//@pre index must be a natural number
//@param index - index to calculate Fibonacci sequence to
//@usage FindFibMatrix(23);
void FindFibMatrix(int index);

//Breaks down the exponent on a given base array through recursion
//@pre base must be populated with 0,1,1,1
//@pre temp must have memory allocated for 4 array spaces
//@pre power must be a natural number
//@post temp is populated with the array values representing the exponent calculation
//@param base - base array of [0,1,1,1]
//@param temp - temporary array holding current state of calculation
//@param power - power to compute the base matrix to
//@usage QuickMatrix(base,result,index);
void QuickMatrix(unsigned int* base, unsigned int* temp, int power);

//Multiplys two given matrixes into a result matrix
//@pre arr1 must be populated with non garbage values
//@pre arr2 must be populated with non garbage values
//@post result is populated with the matrix multiplication of arr1 and arr2
//@param result - matrix holding result of multiplying arr1 and arr2
//@param arr1 - first array to multiply
//@param arr2 - second array to multiply
//@usage MultiplyMatrix(temp,temp,base);
void MultiplyMatrix(unsigned int* result, unsigned int* arr1, unsigned int* arr2);

int main()
{
   int n;
   PrintWelcomeMessage();
   n = GetInput();
   PrintLines(1);

   n = FindFibArray(n);

   PrintLines(1);
   PrintMethodTitle(1);
   FindFibRound(n);
   FindFibRound(n/2);
   
   PrintLines(2);
   PrintMethodTitle(0);
   FindFibMatrix(n);
   FindFibMatrix(n/2);
   PrintLines(2);
}

//Prints the title of the method indicated by the index value
//@param index - index value for title to print, 1 = estimation, 0 = matrix
//@usage PrintMethodTitle(1);
void PrintMethodTitle(int index)
{
   if(index == 1)
      cout << "------ Estimation Method ------  " << endl;
   else
      cout << "------  Matrix Method  --------  " << endl;    
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

//Prints the welcome message for the program
//@usage PrintWelcomeMessage();
void PrintWelcomeMessage()
{
   system("clear");
   cout <<  endl;
   cout <<  "Welcome to the Fibonacci Number Generator" << endl;
   cout <<  "-----------------------------------------" << endl;
   cout << endl; 
}

//Obtains the index value n from the user
//@return the integer value of the user input
//@usage input = getInput();
int GetInput()
{
   int inputNum;
   cout << "Please enter the index you would like to calculate to " << endl;
   cout << "n = ";
   cin >> inputNum;
   return inputNum;
}

//Controls the computation and printing of the Fibonacci Array Method
//@pre n must be a natural number
//@param n - index to compute Fibonacci to
//@return the index value of n that has been checked to fit the output within bounds
//@usage answer = FindFibArray(10);
int FindFibArray(int n)
{
   unsigned int fib[n];
   unsigned int *filledFib = ComputeFib(n, fib);
   PrintFib(n, fib); 
   return n;
}

//Computes the fibonacci sequence with the linear array method
//@pre n must be a natural number
//@pre Fib[] must have memory allocated to fit Fib[n] locations
//@post n is updated if it as an index was larger than a Fibonacci number can fit in an unsigned int
//@post Fib[] is populated with the Fibonacci sequence
//@param n - index to calculate Fibonacci to
//@param Fib[] - array to be populated with Fibonacci numbers.
//@returns a pointer to the array populated with the Fibonacci sequence.
//@usage unsigned int *filledFib = ComputeFib(10,Fib);
unsigned int* ComputeFib(int &n, unsigned int Fib[])
{
   Fib[0] = 0;
   Fib[1] = 1;
   int index = n;
   bool tooLarge = false;
   
   for(int i = 2; i <= n && !tooLarge; i++){
      Fib[i] = Fib[i-1] + Fib[i-2];
      index = i;
      if(Fib[i] < Fib[i-1]){
         tooLarge = true;
         index = i-1;
      }
   }
   n = index;
   return Fib;     
}

//Prints the Fibonacci sequence calculated with the array method
//@pre n must be a natural number
//@pre Fib[] must have memory allocated to fit Fib[n] locations
//@param n - index to print the Fibonacci sequence to
//@param Fib[] - populated Fibonacci sequence as an array
//@usage PrintFib(10,Fib);
void PrintFib(int n, unsigned int Fib[])
{
   int ncount = 0;
   int fncount = 0;
   string spacer = "";
   float groupRowLimit = ceil( float(n+1) / 5);
   
   for(float groupRow = 0; groupRow < groupRowLimit; groupRow++){
      cout << "    n:  ";
      for(int nRow = 0; nRow < 5; nRow++){
         if(ncount <= n){
            spacer = DetermineSpacing(ncount);
            cout << spacer << ncount << "          ";
            ncount++;
         }
      }      
      cout << endl << " F(n):  ";
      for(int fnRow = 0; fnRow < 5; fnRow++){
         if(fncount <= n){
            spacer = DetermineSpacing(Fib[fncount]);
            cout << spacer << Fib[fncount] << "          ";
            fncount++;
         }
      }
      cout << endl << endl;
      
   }
}

//Determines the spacing value to print before a given value of the Fibonacci sequence - aligns the output
//@param testVal - value to check how many leading spaces should be printed
//@returns the string spacing according to the testVal
//@usage cout << DetermineSpacing(610);
string DetermineSpacing(unsigned int testVal)
{
   string spacer = "";
   if(testVal > 999999999)
      spacer = " ";
   else if(testVal > 99999999)
      spacer = "  ";
   else if(testVal > 9999999)
      spacer = "   ";
   else if(testVal > 999999)
      spacer = "    ";
   else if(testVal > 99999)
      spacer = "     ";
   else if(testVal > 9999)
      spacer = "      ";
   else if(testVal > 999)
      spacer = "       ";
   else if(testVal > 99)
      spacer = "        ";
   else if(testVal > 9)
      spacer = "         ";
   else
      spacer = "          ";
   return spacer;
}

//Prints the Fibonacci Heading for a given calculation
//@param index - index of sequence to print
//@param value - value of sequence to print
//@usage PrintFibonacciHeading(10,55);
void PrintFibonacciHeading(int index, unsigned int value)
{
   cout << "Fib(" << index << ") = " << DetermineSpacing(value) << value << endl;
}

//Controls the calculation and printing of the Fibonacci sequence for the estimation method
//@pre index must be a natural number
//@param index - index to calculate the Fibonacci sequence to
//@usage FindFibround(20);
void FindFibRound(int index)
{
   unsigned int fib;
   if(index == 0)
      fib = 0;
   else{
      double phi, estimation;
      phi = (1 + sqrt(5)) / 2;
      estimation = (1 / sqrt(5)) * QuickExponent(phi, index);
      fib = RoundNumber(estimation);
   }
   PrintFibonacciHeading(index,fib);
}

//Breaks down a given exponential into squared versions of itself to compute in logarithmic time
//@pre phi must be positive
//@pre power must be > 0
//@param phi - base number to be raised to a given power
//@param power - exponent to raise the base of phi to
//@returns a double that contains the exponent calculation
//@usage QuickExponent(phi,8);
double QuickExponent(double phi, int power)
{
   if(power == 1)
      return phi;
   else{
      double temp = QuickExponent(phi, power/2);
      if(power % 2 == 0)
         return temp * temp;
      else
         return temp * temp * phi;
   }
}

//Rounds a given double number to its nearest integer
//@pre unroundedNum > 0
//@param unroundedNum - number to be rounded
//@returns the rounded number
//@usage RoundNumber(30.556);
unsigned int RoundNumber(double unroundedNum)
{
   unsigned int floorNum = (unsigned int)unroundedNum;
   double decimalComponent =  (double)floorNum;
   if(( unroundedNum - decimalComponent) >= .5)
      return (unsigned int)((unroundedNum) + 1);
   else
      return (unsigned int)unroundedNum;
}

//Controls the computation and printing of the matrix method
//@pre index must be a natural number
//@param index - index to calculate Fibonacci sequence to
//@usage FindFibMatrix(23);
void FindFibMatrix(int index)
{
   unsigned int fib;
   unsigned int base[4] = {0,1,1,1};
   unsigned int result[4] = {0,1,1,1};
   QuickMatrix(base,result,index);
   if(index > 0)
      fib = result[2];
   else
      fib = result[0];
   PrintFibonacciHeading(index,fib);
}

//Breaks down the exponent on a given base array through recursion
//@pre base must be populated with 0,1,1,1
//@pre temp must have memory allocated for 4 array spaces
//@pre power must be a natural number
//@post temp is populated with the array values representing the exponent calculation
//@param base - base array of [0,1,1,1]
//@param temp - temporary array holding current state of calculation
//@param power - power to compute the base matrix to
//@usage QuickMatrix(base,result,index);
void QuickMatrix(unsigned int* base, unsigned int* temp, int power)
{
   if(power > 1){
      QuickMatrix(base,temp,power/2);
      if(power % 2 == 0)
         MultiplyMatrix(temp,temp,temp);
      else{
         MultiplyMatrix(temp,temp,temp);
         MultiplyMatrix(temp,temp,base);
      }
   }
}

//Multiplys two given matrixes into a result matrix
//@pre arr1 must be populated with non garbage values
//@pre arr2 must be populated with non garbage values
//@post result is populated with the matrix multiplication of arr1 and arr2
//@param result - matrix holding result of multiplying arr1 and arr2
//@param arr1 - first array to multiply
//@param arr2 - second array to multiply
//@usage MultiplyMatrix(temp,temp,base);
void MultiplyMatrix(unsigned int* result, unsigned int* arr1, unsigned int* arr2)
{
   unsigned int temp1[4];
   unsigned int temp2[4];
   for(int i = 0; i < 4; i++)
      temp1[i] = arr1[i];
   for(int i = 0; i < 4; i++)
      temp2[i] = arr2[i];
      
   result[0] = temp1[0] * temp2[0] + temp1[1] * temp2[2];
   result[1] = temp1[0] * temp2[1] + temp1[1] * temp2[3];
   result[2] = temp1[2] * temp2[0] + temp1[3] * temp2[2];
   result[3] = temp1[2] * temp2[1] + temp1[3] * temp2[3];   
}
