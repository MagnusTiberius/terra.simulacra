#pragma once

#include <vector>
#include <ostream>
#include "stdlib.h"
#include <string>
#include <queue>

namespace bbg {

template<class T>
class CircularQueue
{
public:
	CircularQueue(void);
	~CircularQueue(void);
	T* Read(void);
	void Write(T* item);
	bool IsEmpty(void);
private:
	std::queue<T*> m_List;
};

template<class T>
CircularQueue<T>::CircularQueue(void)
{
}

template<class T>
CircularQueue<T>::~CircularQueue(void)
{
}

template<class T>
T* CircularQueue<T>::Read(void)
{
	T* item;
	if (m_List.size() > 0)
	{
		item = m_List.front();
		m_List.pop();
		return item;
	}
	return NULL;
}

template<class T>
void CircularQueue<T>::Write(T* item)
{
	m_List.push(item);
}

template<class T>
bool CircularQueue<T>::IsEmpty(void)
{
	return ( m_List.size()==0 );
}

}