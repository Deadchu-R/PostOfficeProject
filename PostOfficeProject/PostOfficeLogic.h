#pragma once
#include "Customer.cpp"
#include <list>
class PostOfficeLogic
{
public:
	void runPostOffice();
private:
	void setOfficeSettings();
	int countDigits(int number);
	Customer findCustomer(int ID);
	int officerCount;
	void SetCustomersList();
    std::list<Customer> customersList;

};

