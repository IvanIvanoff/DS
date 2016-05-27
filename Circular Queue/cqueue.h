#pragma once
#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include <exception>
#include <new>
#include <algorithm>
const int INIT_CAPACITY = 4;

template<class T>
class CQueue
{
public:
	CQueue();
	CQueue(const CQueue&);
	CQueue& operator=(const CQueue&);
	~CQueue();
public:
	void enqueue(const T&);
	void dequeue();
	T front() const;
	T& front();
	bool empty() const;
	size_t capacity() const;
	size_t size() const;
	void release();
private:
	void free();
	void copy(const T*, size_t, size_t, size_t, unsigned int);
	void resize(size_t);
	void init();
	void set_sizes(size_t, size_t, size_t,size_t, unsigned int);
private:
	T* data;
	size_t qsize, qcapacity;
	size_t head, tail;
	unsigned int mask;
};

static bool power_of_two(int x)
{
	return (!x || !(x & (x - 1)));
}

template<class T>
void CQueue<T>::release(){
	free();
	init();
}

template<class T>
void CQueue<T>::set_sizes(size_t s, size_t c, size_t h,size_t t, unsigned int m)
{
	qsize = s;
	qcapacity = c;
	head = h;
	tail = t;
	mask = m;
}

template<class T>
void CQueue<T>::free()
{
	delete[] data;
	data = nullptr;
	set_sizes(0,0,0,0,1);
}

template<class T>
void CQueue<T>::init()
{
	set_sizes(0, INIT_CAPACITY, 0,0, (unsigned int)(INIT_CAPACITY - 1));
	data = new T[qcapacity];
}

template<class T>
CQueue<T>::CQueue() : data(nullptr)
{
	if (!power_of_two(INIT_CAPACITY))
		throw std::invalid_argument("The initial capacity must be a power of 2!");

	this->init();
}

template<class T>
CQueue<T>::CQueue(const CQueue& rhs) : data(nullptr)
{
	if (!power_of_two(INIT_CAPACITY))
		throw std::invalid_argument("The initial capacity must be a power of 2!");

	copy(rhs.data, rhs.qsize, rhs.qcapacity, rhs.head, rhs.mask);
}

template<class T>
void CQueue<T>::copy(const T* source, size_t s, size_t c, size_t h, unsigned int m)
{
	T* new_data = new T[c];

	for (int i = 0; i < s; i++)
		new_data[i] = source[(i + h) & m];

	this->free();
	set_sizes(
		s, // qsize is the qsize of the source
		c, // qcapacity is the qcapacity of the source
		0, // head is set to 0 (could be anywhere)
		s, // tail is set to qsize ( it is (head + qsize) & mask which equals qsize when head is 0 )
		(unsigned int)(c-1) // mask is one less than qcapacity. qcapacity MUST ALWAYS be a power of 2
	);
	data = new_data;
}

template<class T>
CQueue<T>& CQueue<T>::operator=(const CQueue& rhs)
{
	if (this != &rhs){
		copy(rhs.data, rhs.qsize, rhs.qcapacity, rhs.head, rhs.mask);
	}
	return *this;
}

template<class T>
CQueue<T>::~CQueue()
{
	this->free();
}

template<class T>
bool CQueue<T>::empty() const
{
	return (0 == qsize);
}

template<class T>
size_t CQueue<T>::size() const
{
	return qsize;
}

template<class T>
T CQueue<T>::front() const
{
	if(qsize > 0)
		return data[head];
	else
		throw std::out_of_range();
}

template<class T>
T& CQueue<T>::front()
{
	if (qsize > 0)
		return data[head];
	else
		throw std::out_of_range("Cannot use front() on empty queue");
}

template<class T>
void CQueue<T>::enqueue(const T& elem)
{
	if (qsize == qcapacity)
		this->resize(qcapacity * 2);

	tail &= mask;
	data[tail] = elem;
	tail++;
	qsize++;
}

template<class T>
void CQueue<T>::dequeue()
{
	//doesn't matter where head and tail are pointing to
	if (1 == qsize){
		head = 0;
		tail = 0;
	} else {
		head++;
		head = head & mask;
	}
	qsize--;
}

template<class T>
void CQueue<T>::resize(size_t new_qcapacity)
{
	//check again
	size_t size = std::min(qsize, new_qcapacity);
	copy(data, size, new_qcapacity, head, mask);
}

template<typename T>
size_t CQueue<T>::capacity() const
{
	return qcapacity;
}

#endif //! __CIRCULAR_QUEUE_H__
