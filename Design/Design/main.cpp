#include <windows.h>
#include <iostream>
#include "CustomClass.h"
#include <vector>
#include "custom_string.h"

using namespace std;

void test_memory_time()
{
    const char* data = "This is object : ";
    vector<MyCustomClass*> objects;

    long long int begin = GetTickCount64();

    for (auto i = 0; i < 240000; ++i)
    {
        auto* mc = new MyCustomClass(data, strlen(data), i);
        //objects.push_back(mc);
    }

    long long int end = GetTickCount64();
    double elapsed = (end - begin);

    cout << "Time measured: %.9f miliseconds.\n" << elapsed << endl;
}

int main()
{
    const char* str = "hello world. ";
    const char* str1 = "My World is Disha Patani";
    CMyString* s = new CMyString(str, strlen(str));
    CMyString* s1 = new CMyString(str1, strlen(str1));
    CMyString* temp = *s + *s1;

    CMyString x("someString", 10);

    //cout << (*s + *s1)->getbuffer() << endl;

    if ((*s + *s1) = x)
    {
        cout << "strings are same" << endl;
    }


    cout << s->getbuffer() << endl;
    int x1;
    cin >> x1;

    return 1;
}
