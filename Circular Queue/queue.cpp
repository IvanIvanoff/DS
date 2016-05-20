#pragma once
#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include <exception>

const int INIT_CAPACITY = 4;

template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue&);
	Queue(Queue&&);
	Queue& operator=(const Queue&);
	~Queue();
public:
	void enqueue(const T&);
	void dequeue();
	const T& front() const;
	T& front();
	bool empty();
	size_t capacity();
	size_t size();
	void release();
private:
	void free();
	void resize(size_t);
	void init();
private:
	T* data;
	size_t qsize, qcapacity;
	size_t head, tail;
	unsigned int mask;
};

template<class T>
void Queue<T>::free()
{
	if (data)
		delete[] data;
	data = nullptr;
}

template<class T>
void Queue<T>::init()
{
	if (data) this->free();
	qcapacity = INIT_CAPACITY;
	qsize = 0;
	head = 0;
	tail = 0;
	data = new T[qcapacity];
	if (!data)
	{
		throw std::bad_alloc();
	}
	mask = qcapacity - 1;
}

template<class T>
Queue<T>::Queue()
{
	data = nullptr;
	this->init();
}

template<class T>
Queue<T>::Queue(const Queue& rhs)
{
	data = nullptr;
	this->operator=(rhs);
}

template<class T>
Queue<T>::Queue(Queue&& rhs)
{
	this->data = rhs.data;
	this->qcapacity = rhs.qcapacity;
	this->qsize = rhs.qsize;
	this->mask = rhs.mask;


	//TODO (Ivan) : Check if anything else needs change
	rhs.data = nullptr;

}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	if (this != &rhs)
	{
		T* new_data = new T[rhs.qcapacity];
		if (!new_data)
		{
			throw std::bad_alloc();
		}

		this->init();
		data = new_data;
		new_data = nullptr;

		this->head = rhs.head;
		this->tail = rhs.tail;
		this->qcapacity = rhs.qcapacity;
		this->qsize = rhs.qsize;
		this->mask = (unsigned int)(qcapacity - 1);

		for (size_t i = 0; i < qsize; i++)
			data[i] = rhs.data[i];
	}
	return *this;
}

template<class T>
Queue<T>::~Queue()
{
	this->free();
}

template<class T>
bool Queue<T>::empty()
{
	return (0 == qsize);
}

template<class T>
size_t Queue<T>::size()
{
	return qsize;
}

template<class T>
const T& Queue<T>::front() const
{
	if(qsize > 0)
		return data[head];
	else
	{
		throw std::out_of_range();
	}
}

template<class T>
T& Queue<T>::front()
{
	if (qsize > 0)
		return data[head];
	else
	{
		throw std::out_of_range();
	}
}

template<class T>
void Queue<T>::enqueue(const T& elem)
{
	if (qsize == qcapacity)
	{
		this->resize((qcapacity << 1));
	}

	tail = tail & mask;
	data[tail] = elem;
	tail++;
	qsize++;
}

template<class T>
void Queue<T>::dequeue()
{
	if (1 == qsize)
	{
		head = 0;
		tail = 0;
	}
	else
	{
		head++;
		head = head & mask;
	}
	qsize--;
}

template<class T>
void Queue<T>::resize(size_t new_qcapacity)
{
	//TODO (Ivan) : Make it possible to shrink

	T* new_data = new T[new_qcapacity];
	if (!new_qcapacity)
	{
		throw std::bad_alloc();
	}
	this->qcapacity = new_qcapacity;

	for (size_t i = 0; i < qsize; i++)
	{
		new_data[i] = data[(i + head) & mask];
	}
	this->head = 0;
	this->tail = this->qsize;
	this->mask = (unsigned int)(qcapacity - 1);
	this->free();
	data = new_data;
	new_data = nullptr;
}

template<typename T>
void Queue<T>::release()
{
	this->init();
}

template<typename T>
size_t Queue<T>::capacity()
{
	return qcapacity;
}

#endif //! __CIRCULAR_QUEUE_H__