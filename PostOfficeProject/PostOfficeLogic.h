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
	void setCustomersList(int ID);
    std::list<Customer> customersList;
	std::string findDataBySymbol(string line, string symbol);
	bool tryFindCustomer(int ID, Customer customer);

};

