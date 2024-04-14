#include "PostOfficeLogic.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void PostOfficeLogic::runPostOffice()
{
	setOfficeSettings();
	string exitText = "Exit";
	bool running = true;
	while (running)
	{
		string IDString;
		int ID{};
		std::cout << "Welcome to the Post Office! please enter your {9 digit} ID" << std::endl;
		std::cout << "or enter 1 digit then press Enter to" << exitText << std::endl;
		std::cin >> IDString;

		switch (IDString.length()) {
		case 1:
			std::cout << "Goodbye" << std::endl;
			std::cout << "Exiting...";
			running = false;
			break;
		case 9:
			ID = stoi(IDString);
			std::cout << "green " << std::endl;
			setCustomersList(ID);
			break;
		default:
			std::cout << "red " << std::endl;
			std::cout << "Invalid ID" << std::endl;
			std::cout << "ID must be a 9 digit number" << std::endl;
			break;
		}

	}
}

void PostOfficeLogic::setOfficeSettings()
{
	// will adjust setting according to config file
	fstream config("OfficeConfig.txt");
	string line;
	if (config.is_open())
	{
		while (getline(config, line))
		{
			if (line.find("officerCount") != string::npos)
			{
				officerCount = stoi(line.substr(line.find("=") + 1)); // stoi is basiclly like .parse in c# (converts string to int)
				cout << "officerCount: " << officerCount << endl;
			}
		}
		config.close();
	}
	else
	{
		cout << "Unable to open file, please check config.txt";
	}

	// add a file and make a format to accept each setting (same will be later for the list of Customers)
}
void PostOfficeLogic::setCustomersList(int ID)
{
	cout << "setCustomersList" << endl;
	Customer customer;
	//Customer customer = tryFindCustomer(ID);
	tryFindCustomer(ID, customer);
	// Clear console
	system("CLS");
	cout << "Customer ID: " << customer.ID << endl
		<< "Customer Name: " << customer.name << endl
		<< "Customer Birth Year: " << customer.birthYear << endl;
	// will read from a file and set the list of customers
	// will be used to find a customer
}
Customer PostOfficeLogic::findCustomer(int ID)
{
	Customer customer;
	fstream customers("Customers.txt");
	string line;
	bool found = false;
	if (customers.is_open())
	{
		
		while (getline(customers, line))
		{
			if (line.find(to_string(ID)) != string::npos) /// find the line of the ID inside the file (ID of the customer)
			{
				// Format Symbols: Format Symbols: ~ID~, $Name$, %Year% 
				customer.ID = stoi(findDataBySymbol(line, "~"));
				customer.name = findDataBySymbol(line, "$");
				customer.birthYear = stoi(findDataBySymbol(line, "%"));
				found = true;
				return customer;
			}

		}
		if (!found)
		{
			cout << "Customer not found" << endl;
			//customer.ID = 0;
		}
		customers.close();
	}
	else
	{
		cout << "Error: Unable to open file, please check Customers.txt";
		
	}
	// will search for customer in an outside list of customers
	// if customer exists , return customer
	// if customer does not exist, prompt user to enter their information
	//customer.ID = ID;
	//return customer;
}

bool PostOfficeLogic::tryFindCustomer(int ID, Customer customer)
{
	// will search for customer in an outside list of customers
	// if customer exists , return true
	// if customer does not exist, return false
    customer =	findCustomer(ID);
	return customer.ID != 0;
}
/// <summary>
/// finding data between symbols at line from a file
/// </summary>
/// <param name="line">it is the line from the file which you read</param>
/// <param name="symbol">it is the symbol of which you search data between</param>
/// <returns></returns>
string PostOfficeLogic::findDataBySymbol(string line, string symbol)
{
	size_t symbolStart = line.find(symbol) + 1;
	size_t symbolEnd = line.find(symbol, symbolStart);
	return line.substr(symbolStart, symbolEnd - symbolStart);
}





