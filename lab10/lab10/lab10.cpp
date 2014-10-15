#include "../../std_lib_facilities.h"

// Our generic template class for a LinkedList
template <class T>
class Node {
public:
	Node(T dat)
		:data(dat), prev(0), next(0) {}
	Node* getNext() { return next;}
	Node* getPrev() { return prev;}
	T getData() { return data;}
	void setNext(Node* ptr) { next = ptr;}
	void setPrev(Node* ptr) { prev = ptr;}
	void setData(T dat) { data = dat;}
private:
	T data;
	Node* next;
	Node* prev;
};

template <class T>
class LinkedList {
public:
	LinkedList()
		: first(0), last(0) {}
	Node<T>* getFirst() { return first;}
	Node<T>* getLast() { return last;}
	void setFirst(Node<T>* nf) { first = nf;}
	void setLast(Node<T>* nl) { last = nl;}
	void insertBeginning(Node<T>* n)
	{
		if(insChk(n))
		{
			first->setPrev(n);
			n->setNext(first);
			first = n;
		}
	}
	void insertEnd(Node<T>* n)
	{
		if(insChk(n))
		{
			last->setNext(n);
			n->setPrev(last);
			last = n;
		}
	}
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
	}
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
	}
	void remove(Node<T>* n)
	{
		if (first == 0 && last == 0)
			return;
		else if (first == last)
		{
			first =0;
			last =0;
		}
		if (first != n)
			n->getPrev()->setNext(n->getNext());
		if (last != n)
			n->getNext()->setPrev(n->getPrev());
		delete n;
	}
private:
	bool insChk(Node<T>* n)
	{
		if(!first || !last)
		{
			first = n;
			last = n;
			return false;
		}
		else
			return true;
	}
	Node<T>* first;
	Node<T>* last;
};

template <class T>
void iter(LinkedList<T> *x)
{
  Node<T> *n = x->getFirst();
  while (n != x->getLast())
    {
      cout << n->getData() << " ";
      n = n->getNext();
    }
  cout << n->getData() << endl;
}

template <class T>
void reverseIter(LinkedList<T> *x)
{
  // simple to implement...just change First to Last and Next to Previous.
}

int main() {
  LinkedList<int> *l = new LinkedList<int>();
  Node<int> *n1 = new Node<int>(10);
  Node<int> *n2 = new Node<int>(20);
  Node<int> *n3 = new Node<int>(30);
  Node<int> *n4 = new Node<int>(25);
  Node<int> *n5 = new Node<int>(100);
  cout << n1->getData() << endl;
  l->insertBeginning(n1);
   //functions are: (newNode, oldNode)
  l->insertAfter(n2, n1);
  l->insertAfter(n3, n2);
  l->insertBefore(n4, n3);
  l->insertEnd(n5);
  cout << "Should be: 10, 20, 25, 30, 100 " << endl;
  iter(l);

  cout << endl << "Should now be: 10, 20, 25, 100" << endl;
  l->remove(n3);
  iter(l);

  cout << endl << "Should now be: 17, 10, 20, 25, 100" << endl;
  Node<int> *n6 = new Node<int>(17);
  l->insertBefore(n6, n1);
  iter(l);

  cout << endl << "Should now be: 17, 10, 20, 25, 42, 100" << endl;
  Node<int> *n7 = new Node<int>(42);
  l->insertAfter(n7, n4);
  iter(l);
}