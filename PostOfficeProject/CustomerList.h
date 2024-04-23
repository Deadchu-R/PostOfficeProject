#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Customer.h"

class customerList
{
   public:
   Customer data;
   struct Node
   {
	Customer data;
	struct Node* next;
	struct Node* prev;
   };
   void addToQueue(Customer customer);
   void printList(Node* head);
	void push(Node** head, Customer customerData);
	void insertAfter(Node* prev_node, Customer customerData);
	void append(Node** head, Customer customerData);
	void deleteNode(Node** head, Node* del);
};

