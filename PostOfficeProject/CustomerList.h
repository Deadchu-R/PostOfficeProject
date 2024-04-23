#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Customer.h"
#include "Node.h"

class customerList
{

   public:
   void addToQueue(Customer customer);
   void printList();
	void push(Node** head, Customer customerData);
	void insertAfter(Node* prev_node, Customer customerData);
	void append(Node** head, Customer customerData);
	void deleteNode(Node** head, Node* del);

private:
	Node* head;
	
};

