#pragma once
#ifndef __SIMPLE_STACK_H__
#define __SIMPLE_STACK_H__

struct node;
class Stack
{
public:
	Stack();
	~Stack();
public:
	bool push(int);
	bool pop();
	int top() const;
	bool empty() const;
private:
	node* head_;
};

#include "Stack.h"
#include <new>

struct node {
	int data;
	node* pNext;
};


Stack::Stack()
{
	head_ = nullptr;
}

bool Stack::push(int _data)
{
	node* new_elem = new (std::nothrow) node{ _data, nullptr };
	if (!new_elem)
	{
		return false;
	}

	if (empty())
	{
		head_ = new_elem;
	}
	else
	{
		new_elem->pNext = head_;
		head_ = new_elem;
	}
}

bool Stack::pop()
{
	if (empty())
	{
		return false;
	}
	else
	{
		node* curr = head_;
		head_ = head_->pNext;
		delete curr;
	}
}

int Stack::top() const
{
	return head_->data;
}

bool Stack::empty() const
{
	return (head_ == nullptr);
}

Stack::~Stack()
{
	if (!empty())
	{
		node* curr = head_;
		while (head_->pNext)
		{
			curr = head_->pNext;
			delete head_;
			head_ = curr;
		}
	}
}

#endif //! __SIMPLE_STACK_H__