#include <iostream>
#include <stack>
using namespace std;


struct FreeList
{
	FreeList* next;
};


class memallocator
{
public:

	memallocator(size_t reserve) : mReserve(reserve) {}
	~memallocator()
	{
		//free(mBegin);
	}

private:
	size_t mReserve;
	FreeList* mBegin = nullptr;
	stack<FreeList*> freeptrs;

public:

	void* allocate(size_t s)
	{
		if (mBegin == nullptr)
		{
			if (!freeptrs.empty())
			{
				void* ptr = freeptrs.top();
				freeptrs.pop();
				return ptr;
			}
			else
				createPool(s);
		}

		FreeList* pFreeList = mBegin;
		mBegin = mBegin->next;

		return pFreeList;
	}

	void deallocate(void* ptr, size_t s)
	{
		freeptrs.push(reinterpret_cast<FreeList*>(ptr));
	}


	void createPool(size_t s)
	{
		int total_size = s * mReserve;


		FreeList* pMem = reinterpret_cast<FreeList*>(malloc(total_size));

		FreeList* temp = pMem;

		//Create the list of pointers.
		for (auto i = 0; i < mReserve-1; ++i)
		{
			temp->next = reinterpret_cast<FreeList*>(reinterpret_cast<char*>(temp) + s);
			temp = temp->next;
		}

		temp->next = nullptr;
		mBegin = pMem;
	}
};