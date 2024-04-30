#pragma once
#include "Customer.h"
#include "CustomerList.h"
#include "MyTime.h"
#include "Officer.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class PostOfficeLogic
{
public:
	//singleton
	static PostOfficeLogic& getInstance()
	{
		static PostOfficeLogic instance;
		return instance;
	}
	PostOfficeLogic(const PostOfficeLogic&) = delete;
	void operator=(const PostOfficeLogic&) = delete;

	void runPostOffice();
	bool running = true;
	void setOfficeSettings();
private:
	MyTime time;
	customerList listOfCustomers;
    vector<Officer> officers;
	string nameSymbol = "$";
	string IDSymbol = "~";
	string yearSymbol = "%";
	int currentOfficer = 0;
	int officerCount;
	int currentYear = time.getCurrentYear(); 
	int maxAge = 150;
	int seniorAge = 68;
	int customersInQueue = 0;
	void searchInCustomersQueue(int ID);
	void addToQueue(int ID);
	void customerActions();
	void officerActions();
	void customerActions(int ID);
	void waitForInput();
	bool isNumber(std::string s);
	int countDigits(int number);
	Customer customerChooseAction(Customer customer);
	Customer createNewCustomer(int ID);
	Customer findCustomer(int ID);
	Customer setCustomerValues(string line);
	string findDataBySymbol(string line, string symbol);
public:
	PostOfficeLogic();
	~PostOfficeLogic();
	int getSeniorAge();

};

