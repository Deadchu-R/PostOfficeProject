#pragma once
#include "Customer.cpp"
using namespace std;
class PostOfficeLogic
{
public:
	void runPostOffice();
	bool running = true;
private:
	string nameSymbol = "$";
	string IDSymbol = "~";
	string yearSymbol = "%";
	int currentYear;
	int officerCount;
	int maxAge = 150;
	void setOfficeSettings();
	void searchInCustomersList(int ID);
	void customerActions();
	void customerActions(int ID);
	void waitForInput();
	bool isNumber(std::string s);
	void officerActions();
	int countDigits(int number);
	Customer queuePlace(Customer customer);
	Customer createNewCustomer(int ID);
	Customer findCustomer(int ID);
	Customer setCustomerValues(string line);
	string findDataBySymbol(string line, string symbol);
	


};

