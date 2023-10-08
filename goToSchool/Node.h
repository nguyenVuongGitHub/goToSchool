#pragma once
#include <iostream>
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