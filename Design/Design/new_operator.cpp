//The below code is to demonstrate how to handle memory allocation failures.
//Key concepts:
//1. Using the set_new_handler function
//2. Global handlers vs class specific hanlders to handle memory allocation failures.


// The set_new_handler methods is used to set/change the custom handler function when there are memory allocation failures. 

//Syntax:
// new_handler set_new_handler(new_handler p) throw();

//Parameter:
// A funtion poiner that receives and returns nothing.

//Return value:
//The value of the current new - handler function if this has already been set by this function previously, or a null
//- pointer if this is the first call to set_new_handler(or if it was reset by a previous call).

//Note:
//new_handler is a typedef for a function pointer that receives and returns nothing.


#include <iostream>
using namespace std;


void nomemory()
{
    cerr << "No memory available" << endl;
    throw bad_alloc();
}

void ctest_nomemory()
{
    cerr << "No memory available for allocating the class object" << endl;
    throw bad_alloc();
}


/*
The below test class overloads the new operator.
The currentHandler method points to the function that needs to be invoked when the allocation fails.
*/
class CTest
{
public:
    static new_handler set_new_handler(new_handler p);
    static void* operator new(size_t s);

private:
    static new_handler currHandler;
    double x[100000000];
    double x1[100000000];
    double x2[100000000];
    double x3[100000000];
    double x4[100000000];
};

new_handler CTest::set_new_handler(new_handler p)
{
    new_handler old_handler = currHandler;
    currHandler = p;
    return old_handler;
}


/*
The below function overloads the new operator.
The std::set_new_handler function sets the global handler. 
The function later sets the old handler back before the function exits.
*/
void* CTest::operator new(size_t s)
{
    new_handler global_handler = std::set_new_handler(currHandler);

    void* memory;
    try
    {
        memory = ::operator new(s);
    }
    catch (std::bad_alloc&)
    {
        std::set_new_handler(global_handler);
        throw;
    }
    std::set_new_handler(global_handler);

    return memory;
}

//Initialize the static object 
new_handler CTest::currHandler;

int invoker()
{
    //Sets the global new handler.
    set_new_handler(nomemory);

    try
    {
        for (; ; )
            double* d = new double[100000000];
    }
    catch (bad_alloc)
    {
        cout << "allocation failed" << endl;
    }

    //Sets the class CTest new handler.
    CTest::set_new_handler(ctest_nomemory);
    try {
        CTest* testObj = new CTest;
    }
    catch (std::bad_alloc&)
    {
        cout << "allocation failed" << endl;
    }

    return 1;
}
