#include "std_lib_facilities.h"
#include <stdlib.h>

//generic template class for a node in a linked list
template <class T>
class Node {
public:
	//constructors
	Node()
		:prev(0), next(0) {}
	Node(T dat)
		:data(dat), prev(0), next(0) {}
	//getters
	Node* getNext() { return next;}
	Node* getPrev() { return prev;}
	T* getData() { return &data;}
	//setters
	void setNext(Node* ptr) { next = ptr;}
	void setPrev(Node* ptr) { prev = ptr;}
	void setData(T dat) { data = dat;}
private:
	T data;
	Node* next;
	Node* prev;
};

//generic template class for a linked list of nodes
template <class T>
class LinkedList {
public:
	//constructor
	LinkedList()
		: first(0), last(0), size(0) {}
	//getters
	Node<T>* getFirst() { return first;}
	Node<T>* getLast() { return last;}
	//setters
	void setFirst(Node<T>* nf) { first = nf;}
	void setLast(Node<T>* nl) { last = nl;}
	//mutators
	//inserts the node whose pointer is given at the front of the linked list
	void insertBeginning(Node<T>* n)
	{
		if(insChk(n))
		{
			first->setPrev(n);
			n->setNext(first);
			first = n;
			size++;
		}
	}
	//inserts the node whose pointer is given at the end of the linked list
	void insertEnd(Node<T>* n)
	{
		if(insChk(n))
		{
			last->setNext(n);
			n->setPrev(last);
			last = n;
			size++;
		}
	}
	//inserts the node whose pointer is given after the specified node in the list
	void insertAfter(Node<T>* n, Node<T>* aft)
	{
		if (last != aft)
		{
			n->setNext(aft->getNext());
			aft->getNext()->setPrev(n);
		}
		else
			last = n;
		aft->setNext(n);
		n->setPrev(aft);
		size++;
	}
	//inserts the node whose pointer is given before the specified node in the list
	void insertBefore(Node<T>* n, Node<T>* bef)
	{
		if (first != bef)
		{
			n->setPrev(bef->getPrev());
			bef->getPrev()->setNext(n);
		}
		else
			first = n;
		bef->setPrev(n);
		n->setNext(bef);
		size++;
	}
	//removes the last item in the list and returns a pointer to it
	Node<T>* pop_back()
	{
		Node<T>* curr = last;
		if (size > 1)
		{
			last = last->getPrev();
			curr->setPrev(nullptr);
			last->setNext(nullptr);
			size--;
		}
		else if (size == 1)
		{
			first = nullptr;
			last = nullptr;
			size--;
		}
		else
			curr = nullptr;
		return curr;
	}
	//removes the first item in the list and returns a pointer to it
	Node<T>* pop_front()
	{
		Node<T>* curr = first;
		if (size > 1)
		{
			first = first->getNext();
			curr->setNext(nullptr);
			first->setPrev(nullptr);
			size--;
		}
		else if (size == 1)
		{
			first = nullptr;
			last = nullptr;
			size--;
		}
		else
			curr = nullptr;
		return curr;
	}
	//returns the pointer of a random node in the list
	Node<T>* randPick()
	{
		int seed = rand();
		seed = seed % size;
		Node<T>* curr = first;
		for (seed; seed > 0; seed--)
			curr = curr->getNext();
		return curr;
	}
	//removes from the list the node whose pointer is given and returns the pointer
	Node<T>* extract(Node<T>* n)
	{
		if (first == 0 && last == 0)
			return nullptr;
		else if (first == last)
		{
			first =0;
			last =0;
			size--;
			return n;
		}
		if (first == n)
		{
			first = n->getNext();
			n->setNext(nullptr);
			first->setPrev(nullptr);
		}
		else if (last == n)
		{
			last = n->getPrev();
			n->setPrev(nullptr);
			last->setNext(nullptr);
		}
		else
		{
			n->getPrev()->setNext(n->getNext());
			n->getNext()->setPrev(n->getPrev());
			n->setNext(nullptr);
			n->setPrev(nullptr);
		}
		size--;
		return n;
	}
	//returns the size of the linked list
	int getSize() { return size;}
	//specifically for linked lists of sets, outputs the unique ID of each shirt-pants pair in the current list
	void out()
	{
		Node<set>* curr = first;
		for (int i = size; i > 0; --i)
		{
			cout << curr->getData()->getID() << endl;
			curr = curr->getNext();
		}
	}
private:
	//checks if the given node is being inserted into an empty linked list
	bool insChk(Node<T>* n)
	{
		if(!first || !last)
		{
			first = n;
			last = n;
			n->setPrev(nullptr);
			n->setNext(nullptr);
			size++;
			return false;
		}
		else
			return true;
	}
	int size;
	Node<T>* first;
	Node<T>* last;
};