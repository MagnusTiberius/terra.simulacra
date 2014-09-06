#pragma once
#include <stdlib.h> 

namespace bbg {

typedef struct { int value; } ElemType;

template <class T>
class CircularBuffer
{
public:
	CircularBuffer(void);
	~CircularBuffer(void);
	void Init(int size);
	void Free();
	int IsFull();
	int IsEmpty();
	void Write(T *elem);
	void Read(T *elem);
protected:
	int size;
	//int start;
	//int end; 
	T* elems;
	int writeCtr;
	int readCtr;
	int tail;
	int head;
};

template <class T>
CircularBuffer<T>::CircularBuffer(void)
{
}

template <class T>
CircularBuffer<T>::~CircularBuffer(void)
{
	free(elems);
}

template <class T>
void CircularBuffer<T>::Init(int n)
{
	size = n + 1;
	//start = 0;
	//end = 0;
	free(elems);
	elems = (T*)calloc(size, sizeof(T));
	writeCtr = 0;
	readCtr = 0;
	tail = 0;
	head = 0;
}

template <class T>
void CircularBuffer<T>::Free()
{
	free(elems);
}

template <class T>
int CircularBuffer<T>::IsFull() 
{
    if(head==(tail+1)%size){
        return true;
    }else{
        return false;
    }

}

template <class T>
int CircularBuffer<T>::IsEmpty() 
{
    if(abs(head == tail)){
        return true;
    }else{
        return false;
    }
}

template <class T>
void CircularBuffer<T>::Write(T *elem) 
{
    elems[tail] = *elem;
    tail = (tail+1)%size;
}

template <class T>
void CircularBuffer<T>::Read(T *elem) 
{
	*elem = elems[head];
	head = (head+1)%size;
}

}