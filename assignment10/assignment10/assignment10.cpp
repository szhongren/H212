// Zhongren Shao, Assignment 10

#include "std_lib_facilities.h"

//pool class for managing the memory allocations, contains pointers to the first and last unsigned chars of the pool
class Pool
{
public:
	// default constructor, takes a parameter specifying the size of pool
	Pool (int size)
	{
		// loop to ensure that the initial size of pool is sufficient
		while (size <= 16)
		{
			cout << "The size you specified is too small for a memory pool. Please enter a size larger than or equal to 20." << endl;
			cin >> size;
		}
		// sets start and end of the pool
		pool = new unsigned char[size];
		end = pool + size;
		// data is arranged like this: [size][ptr_to_prev][ptr_to_next], in int, long, long respectively
		int* nodeSize = (int*) pool;
		*nodeSize = size;
		long* prev = (long*) (nodeSize + 1);
		*prev = NULL;
		long* next = prev + 1;
		*next = NULL;
		cout << "Memory pool of " << size << " bytes created!" << endl;
	}

	//class function for allocating the specified number of bytes 
	void* allocate (unsigned int bytes)
	{
		// finds the first empty space
		unsigned char* pos = (unsigned char*) findFirst();
		// if first points to null -> there is no empty space
		if (!pos)
		{
			cout << "There is no memory left in the pool." << endl;
			return NULL;
		}
		unsigned char* last = (unsigned char*) findLast(pos);
		long* prev, * next;
		int* chunkSize;
		do
		{
			chunkSize = (int*) pos;
			prev = getPrev(pos);
			next = getNext(pos);
			if (*chunkSize > bytes + 2 * sizeof(int) + 2 * sizeof(long))
			{
				int* newNode = (int*) (pos + bytes + sizeof(int));
				*newNode = *chunkSize - sizeof(int) - bytes;
				*chunkSize = bytes;
				long* nprev = getPrev((unsigned char*) newNode);
				*nprev = *prev;
				*prev = 1;
				long* nnext = getNext((unsigned char*) newNode);
				*nnext = *next;
				updateList((unsigned char*) newNode);
				cout << bytes << " bytes of memory allocated successfully. You have a maximum of " << freeMem() << " bytes of memory left for use." << endl;
				return pos + sizeof(int);
			}
			else if (*chunkSize == bytes + sizeof(int))
			{
				*chunkSize = bytes;
				remNode(pos);
				*prev = 1;
				cout << bytes << " bytes of memory allocated successfully. You have a maximum of " << freeMem() << " bytes of memory left for use." << endl;
				return pos + sizeof(int);
			}
			else if (pos != last)
				pos = (unsigned char*) *next;
		} while (pos != last);
		cout << "Allocation of " << bytes << " bytes unsuccessful. Please create a bigger pool, or try allocating a smaller block of memory." << endl;
		return NULL;
	};

	//class function for deallocating the memory chunk at the location specified by the pointer
	void deallocate (void* ptr)
	{
		if (!ptr)
		{
			cout << "Pointer is null. No deallocation performed." << endl;
			return;
		}
		int* size = (((int*) ptr) - 1);
		long* next = getNext((unsigned char*) size);
		long* prev = getPrev((unsigned char*) size);
		unsigned char* first = (unsigned char*) findFirst();
		unsigned char* last = (unsigned char*) findLast(first);
		*size += sizeof(int);
		if (!first)
		{
			*next = NULL;
			*prev = NULL;
		}
		else if (ptr < first)
		{
			*prev = NULL;
			*next = (long) first;
			long* fprev = getPrev(first);
			*fprev = (long) size;
		}
		else if (ptr > last)
		{
			*next = NULL;
			*prev = (long) last;
			long* lnext = getNext(last);
			*lnext = (long) size;
		}
		else
		{
			unsigned char* pos = first;
			unsigned char* pos2 = (unsigned char*) *getNext(first);
			while (pos2 < ptr)
			{
				pos = pos2;
				pos2 = (unsigned char*) getNext(pos2);
			}
			long* temp = getNext(pos);
			*temp = (long) ((unsigned char*) ptr - 4);
			temp = getPrev(pos2);
			*temp = (long) ((unsigned char*) ptr - 4);
			*next = (long) pos2;
			*prev = (long) pos;
		}
		cout << "Deallocation of " << *size - sizeof(int) << " bytes successful. There are " << freeMem() << " bytes now available for use." << endl;
		mergeFree((unsigned char*) ptr - 4);
	};
private:
	//helper function for finding the beginning of the linked list in the pool
	void* findFirst()
	{
		unsigned char* pos = pool;
		long* prev;
		while (pos < end)
		{
			int* chunkSize = (int*) pos;
			prev = (long*) (chunkSize + 1);
			if (*prev == NULL)
				return pos;
			else
				pos += sizeof(int) + *chunkSize;
		} 
		return NULL;
	}
	//helper function for finding the end of the linked list in the pool
	void* findLast(unsigned char* pos)
	{
		if (!pos)
			return NULL;
		long* next;
		do
		{
			next = getNext(pos);
			if (*next != NULL)
				pos = (unsigned char*) *next;
		} while (*next != NULL);
		return pos;
	}
	//helper function, returns a pointer to the address in memory holding the address of the next link in the list
	long* getPrev(unsigned char* node)
	{
		return (long*) (node + sizeof(int));
	}
	//helper function, returns a pointer to the address in memory holding the address of the previous link in the list
	long* getNext(unsigned char* node)
	{
		return (long*) (node + sizeof(int) + sizeof(long));
	}
	//updates other links in the linked list given a pointer to the modified link in the list
	void updateList(unsigned char* newNode)
	{
		long* prev = getPrev(newNode); 
		long* next = getNext(newNode);
		if (*prev)
		{
			long* pnext = getNext((unsigned char*) *prev);
			*pnext = (long) newNode;
		}
		if (*next)
		{
			long* nprev = getPrev((unsigned char*) *next);
			*nprev = (long) newNode;
		}
	}
	//removes a node from the list
	void remNode(unsigned char* node)
	{
		long* prev = getPrev(node); 
		long* next = getNext(node);
		if (*prev != NULL)
		{
			long* pnext = getNext((unsigned char*) *prev);
			*pnext = *next;
		}
		if (*next != NULL)
		{
			long* nprev = getPrev((unsigned char*) *next);
			*nprev = *prev;
		}
	}
	//diagnostic function, calculates the available space remaining in bytes
	int freeMem()
	{
		int* pos = (int*) findFirst();
		if (!pos)
			return 0;
		int mem = *pos;
		int* last = (int*) findLast((unsigned char*) pos);
		while (pos != last)
		{
			pos = (int*) *getNext((unsigned char*) pos);
			mem += *pos;
		}
		return mem;
	}
	//helper function, merges adjacent free spaces together given the address of a deallocated chunk of memory
	void mergeFree(unsigned char* ptr)
	{
		long* prev = getPrev(ptr);
		long* next = getNext(ptr);
		int* size = (int*) ptr;
		if (*next)
		{
			unsigned char* cnext = (unsigned char*) (ptr + *size);
			if ((unsigned char*) *next == cnext)
			{
				*size += *((int*) *next);
				*next = *getNext(cnext);
			}
			updateList(ptr);
		}
		if (*prev)
		{
			long* pcnext = (long*) (*prev + *((int*) *prev));
			if (ptr == (unsigned char*) pcnext)
			{
				*((int*) *prev) += *size;
				long* plnext = getNext((unsigned char*) *prev);
				*plnext = *getNext(ptr);
			}
			updateList((unsigned char*) *prev);
		}
	}
	unsigned char* pool;
	unsigned char* end;
};

//entry point, modify the allocation function calls here to test
int main ()
{	
	int size;
	cout << "Please input the amount of memory in bytes that you would like to reserve for use." << endl;
	cin >> size;
	Pool pool(size);
	int *x = (int *)pool.allocate(32);
	double *y = (double *)pool.allocate(16);
	pool.deallocate(x);
	pool.deallocate(y);
}