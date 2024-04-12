#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Customer.h"
class node
{
   public:
   Customer data;
	node* next;
	node* prev;
	node(Customer data);
	~node();
};

