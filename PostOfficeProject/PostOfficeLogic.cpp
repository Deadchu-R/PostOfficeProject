#include "PostOfficeLogic.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void PostOfficeLogic::chooseAction()
{
	setOfficeSettings();
	std::string exitText = "Exit";
	bool running = true;
	while (running)
	{
		int ID;
		std::cout << "Welcome to the Post Office! please enter your ID " << std::endl;
		std::cout << "or enter 1 digit then press Enter to " << exitText << std::endl;
		std::cin >> ID;
		int numOfDigits = countDigits(ID);
		switch (numOfDigits)
		{
		case 1:
			std::cout << "GoodBye" << std::endl;
			std::cout << "exiting...";
			running = false;
			break;
           case 9: 
			   std::cout << "choose an action: " << std::endl;
			   break;
			   default:
				   std::cout << "Invalid ID" << std::endl;
				   std:: cout << "ID must be a 9 digit number" << std::endl;
				   break;
		}
	}
}
int PostOfficeLogic::countDigits(int number)
{
	int count = 0;
	while (number != 0)
	{
		number = number / 10;
		++count;
	}
	return count;
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
void SetCustomersList()
{
	 
	// will read from a file and set the list of customers
	// will be used to find a customer
}
Customer PostOfficeLogic::findCustomer(int ID)
{
	Customer customer;
	// will search for customer in an outside list of customers
	// if customer exists , return customer
	// if customer does not exist, prompt user to enter their information
	customer.ID = ID;
	return customer;
}





