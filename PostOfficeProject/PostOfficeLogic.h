#pragma once
#include "Customer.cpp"
#include <list>
class PostOfficeLogic
{
public:
	void runPostOffice();
	bool running = true;
	string exitText;
private:
	string IDSymbol = "~";
	string nameSymbol = "$";
	string yearSymbol = "%";
	void createNewCustomer(int ID);
	void setOfficeSettings();
	int countDigits(int number);
	Customer findCustomer(int ID);
	Customer setCustomerValues(string line);
	int officerCount;
	void searchInCustomersList(int ID);
    std::list<Customer> customersList;
	std::string findDataBySymbol(string line, string symbol);
	bool tryFindCustomer(int ID, Customer customer);
	int queuePlace(Customer customer);

};

