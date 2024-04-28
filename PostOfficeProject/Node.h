// Node.h
#pragma once

class Node
{
public:
    Customer data; 
    Node* next; 
    Node* prev;

    Node(Customer data)
    {
        this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
    }
};

