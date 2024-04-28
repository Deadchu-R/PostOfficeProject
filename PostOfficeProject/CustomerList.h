#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Customer.h"
#include "Node.h"

class customerList
{

   public:
	   customerList()
	   {
		   head = NULL;
	   }
   void setQueueOrder(Customer customer);
   void ageSort(Customer customer);
   void sortByActionType(Node* current,Customer customer);
   void printList();
	void push(Customer customerData);
	void insertAfter(Node* prev_node, Customer customerData);
	void append(Node** head, Customer customerData);
	void deleteNode(Node* del);
	Node* findNode(int ID);

private:
	Node* head;

	
};

