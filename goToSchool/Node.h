//#pragma once
#include <iostream>

#ifndef NODE_H
#define NODE_H

template <class T>
class Node
{
public:
	T data;
	Node* next;
	Node(T data){
		this->data = data;
		next = NULL;
	};
	Node() {
		data = 0;
		next = NULL;
	}
	~Node() {
		delete next;
	}
};


#endif // !NODE_H
