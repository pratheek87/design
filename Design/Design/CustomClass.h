#pragma once
#include <string>
#include "memory_mangement.h"

class MyCustomClass
{

	string mptrData;
	double d;

public:

	static memallocator allocator;


	MyCustomClass(const char* data, int s, double val) : d(val) {
		mptrData = data;
	}

	static void* operator new(size_t s)
	{
		return allocator.allocate(s);
	}

	static void operator delete(void* ptr, size_t s)
	{
		allocator.deallocate(ptr, s);
	}

	string sendData()
	{
		return mptrData + " " + to_string(d);
	}
};
