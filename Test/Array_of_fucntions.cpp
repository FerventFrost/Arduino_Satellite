#include <iostream>
using namespace std;

//this is the new int datatybe name and this is how to input the parameter to the function
typedef int (*IntFunctionWithOneParameter) (int a);

int function(int a){ return a; }
int functionTimesTwo(int a){ return a*2; }
int functionDivideByTwo(int a){ return a/2; }

int main()
{
    IntFunctionWithOneParameter functions[] = 
    {
        function, 
        functionTimesTwo, 
        functionDivideByTwo
    };

    for(int i = 0; i < 3; ++i)
    {
        cout << functions[i](8) << endl;
    }
    return 0;
}