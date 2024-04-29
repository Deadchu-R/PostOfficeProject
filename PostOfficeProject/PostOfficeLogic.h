#pragma once
#include "Customer.h"
#include "CustomerList.h"
#include "MyTime.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class PostOfficeLogic
{
public:
	void runPostOffice();
	bool running = true;
private:
	MyTime time;
	customerList listOfCustomers;
	string nameSymbol = "$";
	string IDSymbol = "~";
	string yearSymbol = "%";
	int officerCount;
	int currentYear = time.getCurrentYear(); 
	int maxAge = 150;
	int seniorAge = 68;
	int customersInQueue = 0;
	void setOfficeSettings();
	void searchInCustomersQueue(int ID);
	void addToQueue(int ID);
	void customerActions();
	void customerActions(int ID);
	void waitForInput();
	bool isNumber(std::string s);
	void officerActions();
	int countDigits(int number);
	Customer customerChooseAction(Customer customer);
	Customer createNewCustomer(int ID);
	Customer findCustomer(int ID);
	Customer setCustomerValues(string line);
	string findDataBySymbol(string line, string symbol);
public:
	int getSeniorAge();

};

