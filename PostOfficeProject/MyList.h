#pragma once
#include <list>
#include <iostream>
#include "Customer.h"
using namespace std;
class MyList : public list<Customer>
{
	public:
	MyList();
	~MyList();
	void setQueueOrder(Customer customer);
	Customer findCustomerByActionType(int actionType, bool elderly);
	void eraseCustomer(Customer customer);
};
