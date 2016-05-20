#pragma once
#ifndef __SIMPLE_QUEUE_H__
#define __SIMPLE_QUEUE_H__
struct node;

class Queue
{
public:
	Queue();
	~Queue();
public:
	bool push(int);
	bool pop();
	int top();
	bool empty() const;
private:
	node* head_;
	node* tail_;
	size_t size_;
};

#include "Queue.h"

#include <iostream>
#include <new>
#include <exception>

struct node {
	int data;
	node* pNext;
};


Queue::Queue()
{
	head_ = nullptr;
	tail_ = nullptr;
	size_ = 0;
}

bool Queue::push(int _data) 
{
	node* new_elem = new node{ _data, nullptr };

	if (head_ == nullptr)
	{
		head_ = new_elem;
		tail_ = new_elem;
	}
	else
	{
		tail_->pNext = new_elem;
		tail_ = new_elem;
	}
	size_++;
	return true;
}

bool Queue::pop()
{
	if (head_ == nullptr)
		return false;

	node* curr = head_;
	head_ = head_->pNext;
	delete curr;

	size_--;
	return true;
}

int Queue::top()
{
	return head_->data;
}

bool Queue::empty() const
{
	return (head_ == nullptr);
}

Queue::~Queue()
{
	if (!empty()) {
		node* curr = head_;
		while (curr->pNext)
		{
			curr = curr->pNext;
			delete head_;
			head_ = curr;
		}
	}
}

#endif //! __SIMPLE_QUEUE_H__