#pragma once
#include "Node.h"

#ifndef QUEUE_H
#define QUEUE_H




const short MAX_SIZE = 100;

template <class T>
class Queue
{
private:
	Node<T>* head;
	Node<T>* tail;
	short size;
public:
	Queue()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	~Queue()
	{
		while (!isEmpty())
			pop();

	}

	// check queue is empty
	bool isEmpty()
	{
		return head == NULL;
	}
	
	// check queue is full
	bool isFull()
	{
		return size == MAX_SIZE;
	}

	// add new element to queue
	void push(T data)
	{
		Node<T>* newNode = new Node<T>(data);

		if (isEmpty())
		{
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}

	// delete element on top and return it
	T pop()
	{
		if (!isEmpty())
		{
			T front = head->data;

			Node<T>* temp = head->next;
			head = NULL;
			head = temp;
			return front;
		}
		else {
			throw std::runtime_error("queue rong");
		}

	}
	
	short getSize()
	{
		return size;
	}
};

#endif // !QUEUE_H