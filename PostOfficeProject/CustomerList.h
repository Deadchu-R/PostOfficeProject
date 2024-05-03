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
   void sortCustomers();
   void sortByAge(Node* current);
   Node* insertSorted(Node* head, Node* newNode);
   void printList();
	void push(Customer customerData);
	void deleteNode(Node* del);
	Customer findCustomerByActionType(int actionType, bool elderly);
	Node* findNode(int ID);
	Node* findNodeByActionType(int actionType, Node* fromHere );

private:
	Node* head = nullptr;
	Node* seniorHead = nullptr;
	Node* youngerHead = nullptr;
	int y;
	int maxActions = 4;
};

